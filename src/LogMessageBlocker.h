//
// Created by 袁浩东 on 16/6/11.
//

#ifndef WNSLOGHELPER_LOGMESSAGEBLOCKER_H
#define WNSLOGHELPER_LOGMESSAGEBLOCKER_H

#include "LogEntry.h"
#include "Blocker.h"

using namespace std;
using json = nlohmann::json;

enum Scope {
    thisLine = 0,
    wholeLogLine = 1,
};

class LogMessageBlocker : Blocker {
public:
    LogMessageBlocker(const json &j) { init(j); };
    static Blocker* creator(const json & j) {
        return new LogMessageBlocker(j);
    };
protected:
    virtual bool doApply(const LogEntry &item) const;

    virtual void parseJson(const json &j);

private:
    vector<string> words;
    ConditionOperator wordsConditionOperator;
    
};

#endif //WNSLOGHELPER_LOGMESSAGEBLOCKER_H
