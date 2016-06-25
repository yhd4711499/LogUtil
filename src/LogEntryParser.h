//
// Created by 袁浩东 on 16/6/9.
//

#ifndef WNSLOGHELPER_LOGENTRYPARSER_H
#define WNSLOGHELPER_LOGENTRYPARSER_H

#include <vector>
#include <istream>
#include "LogEntry.h"
#include "LogEntryFilter.h"
#include "ptr.h"

using namespace std;

//enum LineFilterAction {
//    none,
//    hideOnlyThisLine,
//    hideWholeLogLine
//};

//typedef std::function <bool (const string & )> LineBlocker;
//typedef std::function <bool (const LogEntry & )> LogEntryBlocker;

class LogEntryParser {
public:
    void parseFile(string &, vector<LogEntry *> &);

    void parseFile(istream &, vector<LogEntry *> &);

    void addBlocker(LogEntryFilter *);

    ~LogEntryParser() {
        delete_v(blockers);
    }

private:
    void readLogLine(LogLine &, int &, vector<LogEntry *> &);

    inline bool isLineValid(string &);

    vector<LogEntryFilter *> blockers;
};


#endif //WNSLOGHELPER_LOGENTRYPARSER_H
