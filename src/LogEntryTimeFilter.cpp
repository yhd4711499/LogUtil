//
// Created by 袁浩东 on 16/6/11.
//

#include "LogEntryTimeFilter.h"

void LogEntryTimeFilter::parseJson(const json &j) {
}

bool LogEntryTimeFilter::doApply(const LogEntry &item) const {
    bool ret = false;
    if (!startTime.empty()) {
        ret = item.logTime >= startTime;
    }
    if (ret && !endTime.empty()) {
        ret &= item.logTime <= endTime;
    }
    return ret;
}



