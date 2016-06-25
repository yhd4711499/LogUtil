//
// Created by 袁浩东 on 16/6/11.
//

#ifndef WNSLOGHELPER_ROOTBLOCKER_H
#define WNSLOGHELPER_ROOTBLOCKER_H

#include "LogEntry.h"
#include "LogEntryFilter.h"

using namespace std;
using json = nlohmann::json;

enum FilterType {
    filterOut = 1,
    filterIn = 2
};

class LogEntryRootFilter : LogEntryFilter {

public:
    static LogEntryFilter *creator(const json &j) {
        LogEntryRootFilter *blocker = new LogEntryRootFilter();
        blocker->init(j);
        return blocker;
    };
    virtual bool apply(const LogEntry &item) const override;

private:
    LogEntryRootFilter() {};

    FilterType filterType;
protected:
    virtual bool doApply(const LogEntry &item) const override { throw exception(); };

    virtual void parseJson(const json &j) override ;

};

#endif //WNSLOGHELPER_ROOTBLOCKER_H
