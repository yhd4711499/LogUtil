//
// Created by 袁浩东 on 16/6/9.
//

#include "LogEntry.h"

std::ostream &operator<<(std::ostream &os, const LogEntry entry) {
    os << entry.line;
//    if (entry.level == wtf) {
//    } else {
//        os << (char) entry.level << '/' << entry.logTime.date << " " << entry.logTime.time << " " << entry.line;
//    }
    return os;
}