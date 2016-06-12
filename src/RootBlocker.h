//
// Created by 袁浩东 on 16/6/11.
//

#ifndef WNSLOGHELPER_ROOTBLOCKER_H
#define WNSLOGHELPER_ROOTBLOCKER_H

#include "LogEntry.h"
#include "Blocker.h"

using namespace std;
using json = nlohmann::json;

class RootBlocker : Blocker {

public:
    static Blocker *creator(const json &j) {
        RootBlocker *blocker = new RootBlocker();
        blocker->init(j);
        return blocker;
//        return nullptr;
    };
private:
    RootBlocker() {};

protected:
    virtual bool doApply(const LogEntry &item) const { throw exception(); };

    virtual void parseJson(const json &j) { };

};

#endif //WNSLOGHELPER_ROOTBLOCKER_H
