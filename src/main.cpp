#include <fstream>
#include <vector>
#include "LogEntryFilter.h"
#include "LogEntryRootFilter.h"
#include "LogEntryMessageFilter.h"
#include "LogEntryTimeFilter.h"
#include "FileUtils.hpp"
#include "CommandLineUtils.hpp"
#include "LogEntryParser.h"
#include "Rearranger.h"
#include "LogEntryFilterFactory.h"

using namespace std;

int main(int argc, char *argv[]) {
    int ret = 0;
    if (argc == 1 || cmdOptionExists(argv, argv + argc, "--help")) {
        cout << "LogUtil: An handy tool to merge/filter log files.\n";
        cout << "usage :\tlogutil";
        cout << "\t[-d] [-f] [-o] [-r] [-start] [-end]\n";
        cout << "\n";
        cout << "\t-d merge all files under the directory.\n";
        cout << "\t-f sort the log file.\n";
        cout << "\t-o output file. [<file_or_dirname>_ALL.log] will be used if not set.\n";
        cout << "\t-r filter rules.\n";
        cout << "\t-start/end show logs between [start , end), \"YYYY-mm-dd hh:MM:SS.SSS\" .\n\n";
        cout << "examples :\n";
        cout << "\tlogutil -d ~/LogDir\n";
        cout << "\tlogutil -d ~/LogDir -start 2016-06-18\n";
        cout << "\tlogutil -d ~/LogDir -start 2016-06-18 -end 2016-06-19\n";
        cout << "\tlogutil -d ~/LogDir -f ~/block_rules.json\n";
        cout << "\tlogutil -d ~/LogDir -o ~/Log_ALL.log\n";
        cout << "\tlogutil -f ~/LogDir/log.log -o ~/Log_ALL.log\n";
        return 0;
    }
    vector<string> files;
    char *dirname = nullptr, *filename = nullptr, *outputFilename = nullptr;

    if (argc == 2) {
        if (isFile(argv[1])) {
            filename = argv[1];
        } else {
            dirname = argv[1];
        }
    } else {
        dirname = getCmdOption(argv, argv + argc, "-d");
        filename = getCmdOption(argv, argv + argc, "-f");
    }

    if (filename) {
        files.push_back(filename);
    }

    if (dirname) {
        ret = listFiles(dirname, files);
    }

    if (ret != 0) {
        return ret;
    }

    char *blockFile = getCmdOption(argv, argv + argc, "-b");
    char *startTime = getCmdOption(argv, argv + argc, "-start");
    char *endTime = getCmdOption(argv, argv + argc, "-end");

    outputFilename = getCmdOption(argv, argv + argc, "-o");
    if (!outputFilename) {
        if (filename) {
            string folderName, filenameWoDir;
            splitFilename(string(filename), folderName, filenameWoDir);

            string newFilename(folderName + "/All_" + filenameWoDir);
            outputFilename = new char[newFilename.length() + 1];
            strcpy(outputFilename, newFilename.c_str());
        } else if (dirname) {
            string newFilename(string(dirname) + "/" + "All.log");
            outputFilename = new char[newFilename.length() + 1];
            strcpy(outputFilename, newFilename.c_str());
        }
    }

    LogEntryFilterFactory::registerCreator("root", LogEntryRootFilter::creator);
    LogEntryFilterFactory::registerCreator("log", LogEntryMessageFilter::creator);
    LogEntryFilterFactory::registerCreator("time", LogEntryTimeFilter::creator);

    LogEntryParser parser;

    if (blockFile) {
        auto blockFs = fstream(blockFile);
        json blockJson;
        blockFs >> blockJson;
        parser.addBlocker(LogEntryFilterFactory::create(blockJson));
    }

    if (startTime || endTime) {
        string start = startTime ? (string) startTime : "";
        string end = endTime ? (string) endTime : "";
        LogEntryTimeFilter *blocker = new LogEntryTimeFilter(start, end, true);
        parser.addBlocker(blocker);
    }

    vector<LogEntry *> entries;

    for (string file : files) {
        try {
            parser.parseFile(file, entries);
        } catch (runtime_error &error) {
            cerr << "Failed to parse file : " << file << ". error: " << error.what() << endl;
        } catch (...) {
            cerr << "Failed to parse file : " << file << endl;
        }
    }

    Rearranger rearranger;
    rearranger.sort(entries);

    int index = 1;
    for (LogEntry *entry : entries) {
        entry->line.orderedIndex = index;
        index += entry->line.lines.size();
    }

    if (outputFilename) {
        ofstream os(outputFilename);
        for (LogEntry *entry : entries) {
            os << *entry;
        }
    } else {
        for (LogEntry *entry : entries) {
            cout << *entry;
        }
    }

    return 0;
}