//
// Created by 袁浩东 on 16/6/9.
//

#include "Rearranger.h"
#include <algorithm>

void Rearranger::sort(vector<LogEntry *> &entries) {
    std::sort(entries.begin(), entries.end(), [](const LogEntry *lhs, const LogEntry *rhs) {
        return lhs->logTime < rhs->logTime;
    });
}

