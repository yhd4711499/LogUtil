//
// Created by 袁浩东 on 16/6/11.
//

#include "BlockerFactory.h"

map<string, Creator> BlockerFactory::factoryMap;

void BlockerFactory::registerCreator(const string &type, Creator creator) {
    factoryMap.insert(make_pair(type, creator));
}

Blocker* BlockerFactory::create(const json &j) {
    string type = j["type"];
    auto creator = BlockerFactory::factoryMap.find(type);
    if (creator == BlockerFactory::factoryMap.end()) {
        throw exception();
    }

    return creator->second(j);
}