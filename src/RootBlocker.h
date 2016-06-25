//
// Created by 袁浩东 on 16/6/11.
//

#ifndef WNSLOGHELPER_ROOTBLOCKER_H
#define WNSLOGHELPER_ROOTBLOCKER_H

#include "LogEntry.h"
#include "Blocker.h"

using namespace std;
using json = nlohmann::json;

enum FilterType {
    filterOut = 1,
    filterIn = 2
};

class RootBlocker : Blocker {

public:
    static Blocker *creator(const json &j) {
        RootBlocker *blocker = new RootBlocker();
        blocker->init(j);
        return blocker;
    };
    virtual bool apply(const LogEntry &item) const override;

private:
    RootBlocker() {};

    FilterType filterType;
protected:
    virtual bool doApply(const LogEntry &item) const override { throw exception(); };

    virtual void parseJson(const json &j) override ;

};

#endif //WNSLOGHELPER_ROOTBLOCKER_H
