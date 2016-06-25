//
// Created by 袁浩东 on 16/6/11.
//

#include "LogEntryFilterFactory.h"

map<string, Creator> LogEntryFilterFactory::factoryMap;

void LogEntryFilterFactory::registerCreator(const string &type, Creator creator) {
    factoryMap.insert(make_pair(type, creator));
}

LogEntryFilter* LogEntryFilterFactory::create(const json &j) {
    string type = j["type"];
    auto creator = LogEntryFilterFactory::factoryMap.find(type);
    if (creator == LogEntryFilterFactory::factoryMap.end()) {
        throw runtime_error("failed to find creator of type : " + type);
    }

    return creator->second(j);
}