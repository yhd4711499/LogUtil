//
// Created by 袁浩东 on 16/6/11.
//

#ifndef WNSLOGHELPER_TIMEBLOCKER_H
#define WNSLOGHELPER_TIMEBLOCKER_H

#include "LogEntry.h"
#include "LogEntryFilter.h"

using namespace std;
using json = nlohmann::json;


class LogEntryTimeFilter : public LogEntryFilter {
public:
    LogEntryTimeFilter(const json &j) { init(j); };

    LogEntryTimeFilter(string &start, string &end, bool r) : startTime(start), endTime(end) {
        reverse = r;
    }

    static LogEntryFilter *creator(const json &j) {
        return new LogEntryTimeFilter(j);
    };

protected:
    virtual bool doApply(const LogEntry &item) const;

    virtual void parseJson(const json &j);

private:
    string startTime;
    string endTime;
};


#endif //WNSLOGHELPER_TIMEBLOCKER_H
