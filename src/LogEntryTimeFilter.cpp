//
// Created by 袁浩东 on 16/6/11.
//

#include "LogEntryTimeFilter.h"

void LogEntryTimeFilter::parseJson(const json &j) {
    startTime = j["start"];
    endTime = j["end"];
}

bool LogEntryTimeFilter::doApply(const LogEntry &item) const {
    string dateTime = item.logTime.date + " " + item.logTime.time;
    bool ret = false;
    if (!startTime.empty()) {
        ret = dateTime >= startTime;
    }
    if (ret && !endTime.empty()) {
        ret &= dateTime <= endTime;
    }
    return ret;
}


