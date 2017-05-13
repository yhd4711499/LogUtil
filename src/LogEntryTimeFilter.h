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
    LogEntryTimeFilter(const string &startDate, const string &startTime, const string &endDate, const string &endTime, bool r)
            : startTime(LogTime::from(startDate, startTime)), endTime(LogTime::from(endDate, endTime)) {
        reverse = r;
    }

    LogEntryTimeFilter(const json &j, const string &startDate, const string &startTime, const string &endDate, const string &endTime)
            : startTime(LogTime::from(startDate, startTime)), endTime(LogTime::from(endDate, endTime)) {
        init(j);
    }

    static inline string getDate(string &dateTime) {
        if (dateTime.length() >= 10) {
            return dateTime.substr(0, 10);
        }
        else {
            return dateTime.substr(0);
        }
    }

    static inline string getTime(string &dateTime) {
        if (dateTime.length() >= 23) {
            return dateTime.substr(11, 12);
        }
        else if (dateTime.length() > 11) {
            return dateTime.substr(11);
        }
        else {
            return "";
        }
    }

    static LogEntryFilter *creator(const json &j) {
        string start = j["start"];
        string end = j["end"];

        return new LogEntryTimeFilter(j, getDate(start), getTime(start), getDate(end), getTime(end));
    };

protected:
    virtual bool doApply(const LogEntry &item) const;

    virtual void parseJson(const json &j);

private:
    LogTime startTime;
    LogTime endTime;
};

#endif //WNSLOGHELPER_TIMEBLOCKER_H