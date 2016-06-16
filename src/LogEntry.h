//
// Created by 袁浩东 on 16/6/9.
//

#ifndef WNSLOGHELPER_LOGENTRY_H
#define WNSLOGHELPER_LOGENTRY_H

#include <string>
#include <iostream>
#include "LogTime.h"
#include "LogLine.h"

enum LogLevel {
    verbose = 'V',
    debug = 'D',
    info = 'I',
    warning = 'W',
    error = 'E',
    wtf = 'F'
};

/**
 * an entry of log messages
 */
struct LogEntry {
    LogTime logTime;
//    int tid;
    std::string threadName;
//    std::string processName;
    LogLine line;
    LogLevel level;
public:
    LogEntry(
            LogTime time,
            LogLine logLine,
            LogLevel level,
            std::string threadName) : logTime(time),
                                      threadName(threadName),
                                      line(logLine),
                                      level(level) { }
};


std::ostream &operator<<(std::ostream &os, const LogEntry entry);

#endif //WNSLOGHELPER_LOGENTRY_H
