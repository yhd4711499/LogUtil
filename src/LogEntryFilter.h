//
// Created by 袁浩东 on 16/6/11.
//

#ifndef WNSLOGHELPER_BLOCKER_H
#define WNSLOGHELPER_BLOCKER_H

#include <vector>
#include <functional>
#include "json.hpp"
#include "LogEntry.h"
#include "ptr.h"

using json = nlohmann::json;
using namespace std;

enum ConditionOperator {
    nullOperator = 0,
    andOperator = 1,
    orOperator = 2
};

class LogEntryFilter {
public:
    bool isEnabled() { return enabled; }
    
    virtual bool apply(const LogEntry &item) const;

    void addChildren(const LogEntryFilter &);

//    LogEntryFilter(const ConditionOperator conditionOperator) : conditionOperator(conditionOperator) { }

    virtual void init(const json &j);

    virtual ~LogEntryFilter() {
        delete_v(children);
    }
protected:

    virtual bool doApply(const LogEntry &item) const = 0;


    virtual void parseJson(const json &j) = 0;


    /**
     * 是否取反
     * 默认: false
     */
    bool reverse = false;
private:

    vector<const LogEntryFilter *> children;
    /**
     * 组合逻辑
     * 默认: nullOperator
     */
    ConditionOperator conditionOperator = nullOperator;
    /**
     * 是否开启
     * 默认: true
     */
    bool enabled = true;

};

#endif //WNSLOGHELPER_BLOCKER_H
