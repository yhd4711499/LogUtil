//
// Created by 袁浩东 on 16/6/11.
//

#ifndef WNSLOGHELPER_TIMEBLOCKER_H
#define WNSLOGHELPER_TIMEBLOCKER_H

#include "LogEntry.h"
#include "Blocker.h"

using namespace std;
using json = nlohmann::json;


class TimeBlocker : Blocker {
public:
    TimeBlocker(const json &j) { init(j); };

    static Blocker* creator(const json & j) {
        return new TimeBlocker(j);
    };

protected:
    virtual bool doApply(const LogEntry &item) const;

    virtual void parseJson(const json &j);

private:
    string startTime;
    string endTime;
};


#endif //WNSLOGHELPER_TIMEBLOCKER_H
