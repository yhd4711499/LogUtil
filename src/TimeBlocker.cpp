//
// Created by 袁浩东 on 16/6/11.
//

#include "TimeBlocker.h"

void TimeBlocker::parseJson(const json &j) {
    startTime = j["start"];
    endTime = j["end"];
}

bool TimeBlocker::doApply(const LogEntry &item) const {
    string dateTime = item.logTime.date + " " + item.logTime.time;
    return (dateTime >= startTime && dateTime <= endTime);
}



