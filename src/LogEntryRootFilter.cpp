//
// Created by 袁浩东 on 16/6/11.
//

#include "LogEntryRootFilter.h"

void LogEntryRootFilter::parseJson(const json &j) {
    auto filterType_json = j.find("filterType");
    if (filterType_json != j.end()) {
        filterType = (FilterType)filterType_json->get<int>();
    } else {
        filterType = filterIn;
    }
}

bool LogEntryRootFilter::apply(const LogEntry &item) const {
    bool result = LogEntryFilter::apply(item);
    switch (filterType) {
        case filterIn:
            return !result;
        case filterOut:
            return result;
        default:
            throw runtime_error("unknown filterType");
    }
}



