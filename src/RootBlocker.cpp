//
// Created by 袁浩东 on 16/6/11.
//

#include "RootBlocker.h"

void RootBlocker::parseJson(const json &j) {
    auto filterType_json = j.find("filterType");
    if (filterType_json != j.end()) {
        filterType = (FilterType)filterType_json->get<int>();
    } else {
        filterType = filterIn;
    }
}

bool RootBlocker::apply(const LogEntry &item) const {
    bool result = Blocker::apply(item);
    switch (filterType) {
        case filterIn:
            return !result;
        case filterOut:
            return result;
        default:
            throw runtime_error("unknown filterType");
    }
}



