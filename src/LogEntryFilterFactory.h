//
// Created by 袁浩东 on 16/6/11.
//

#ifndef WNSLOGHELPER_BLOCKERFACTORY_H
#define WNSLOGHELPER_BLOCKERFACTORY_H

#include <vector>
#include <functional>
#include "json.hpp"
#include "LogEntryFilter.h"

using json = nlohmann::json;
using namespace std;

typedef LogEntryFilter *(*Creator)(const json &);

class LogEntryFilterFactory {
public:

    static void registerCreator(const string &, Creator);

    static LogEntryFilter *create(const json &);

private:
    static map<string, Creator> factoryMap;
};

#endif //WNSLOGHELPER_BLOCKERFACTORY_H
