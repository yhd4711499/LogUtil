//
// Created by 袁浩东 on 16/6/9.
//

#include "LogEntryParser.h"

#include <fstream>

void LogEntryParser::parseFile(string &file, vector<LogEntry *> &out) {
    ifstream is;

    is.open(file, ios::binary);

    if (!is) {
        cerr << "Failed to open file : " << file << endl;
        throw exception();
    }

    parseFile(is, out);

    is.close();
    is.clear();
}

void LogEntryParser::parseFile(istream &stream, vector<LogEntry *> &out) {
    string line;
    LogLine logLine;
    int totalLines = 0;

    while (getline(stream, line)) {
        totalLines++;

        if (!isLineValid(line)) {
            continue;
        }

        bool isMainLine = LogLine::isMainLine(line);

        if (isMainLine) {
            readLogLine(logLine, totalLines, out);
            logLine.lines.clear();
        }
        logLine.lines.push_back(line);
    }

    readLogLine(logLine, totalLines, out);
    logLine.lines.clear();

    auto end = std::remove_if(out.begin(), out.end(), [this](const LogEntry *entry) {
        for (auto &blocker : blockers) {
            if (blocker->isEnabled() && blocker->apply(*entry)) {
                return true;
            }
        }
        return false;
    });
    out.erase(end, out.end());
}

void LogEntryParser::readLogLine(LogLine &logLine, int &lineIndex, vector<LogEntry *> &out) {
    LogLevel logLevel;
    if (logLine.lines.size() == 0) {
        return;
    }
    string firstLine = logLine.lines[0];
    switch (firstLine[0]) {
        case 'V':
            logLevel = verbose;
            break;
        case 'D':
            logLevel = debug;
            break;
        case 'I':
            logLevel = info;
            break;
        case 'E':
            logLevel = error;
            break;
        case 'W':
            logLevel = warning;
            break;
        default:
            logLevel = wtf;
            break;

    }

    logLine.originalIndex = lineIndex;

    if (logLevel == wtf) {
        out.push_back(new LogEntry(LogTime("", ""), logLine, logLevel, ""));
    } else {
        LogTime logTime(firstLine.substr(2, 10), firstLine.substr(13, 12));
        out.push_back(new LogEntry(
                logTime,
                logLine,
                logLevel,
                firstLine.substr(26, 6)
        ));
    }
}

bool LogEntryParser::isLineValid(string &line) {
    return line.size() != 0;
}

void LogEntryParser::addBlocker(Blocker *blocker) {
    blockers.push_back(blocker);
}














