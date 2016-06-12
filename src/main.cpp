#include <fstream>
#include <vector>
#include "Blocker.h"
#include "RootBlocker.h"
#include "LogMessageBlocker.h"
#include "TimeBlocker.h"
#include "FileUtils.hpp"
#include "CommandLineUtils.hpp"
#include "LogEntryParser.h"
#include "Rearranger.h"
#include "BlockerFactory.h"

using namespace std;

int main(int argc, char *argv[]) {
    int ret = 0;
    vector<string> files;

    char *filename = getCmdOption(argv, argv + argc, "-f");
    if (filename) {
        files.push_back(filename);
    }

    char *dirname = getCmdOption(argv, argv + argc, "-d");
    if (dirname) {
        ret = listFiles(dirname, files);
    }

    char *blockFile = getCmdOption(argv, argv + argc, "-b");

    char *outputFilename = getCmdOption(argv, argv + argc, "-o");

    BlockerFactory::registerCreator("root", RootBlocker::creator);
    BlockerFactory::registerCreator("log", LogMessageBlocker::creator);
    BlockerFactory::registerCreator("time", TimeBlocker::creator);

    LogEntryParser parser;

    if (blockFile) {
        auto blockFs = fstream(blockFile);
        json blockJson;
        blockFs >> blockJson;
        parser.addBlocker(BlockerFactory::create(blockJson));
    }

    vector<LogEntry *> entries;

    for (string file : files) {
        try {
            parser.parseFile(file, entries);
        } catch (...) {
            cerr << "Failed to parse file : " << file << endl;
        }
    }

    if (ret != 0) {
        return ret;
    }

    Rearranger rearranger;
    rearranger.sort(entries);

	int index = 1;
	for (LogEntry* entry : entries) {
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