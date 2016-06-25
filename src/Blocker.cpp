//
// Created by 袁浩东 on 16/6/11.
//

#include "Blocker.h"
#include "BlockerFactory.h"

bool Blocker::apply(const LogEntry &item) const {
    bool result = false;
    if (conditionOperator == nullOperator) {
        result = doApply(item);
    } else if (conditionOperator == andOperator) {
        for (auto child : children) {
            if (!(result = child->apply(item))) {
                goto exit;
            }
        }
    } else if (conditionOperator == orOperator) {
        for (auto child : children) {
            if ((result = child->apply(item))) {
                goto exit;
            }
        }
    }
    exit:
    return reverse == !result;
}

void Blocker::addChildren(const Blocker &child) {
    children.push_back(&child);
}

void Blocker::init(const json &j) {
    auto find = j.find("operator");
    if (find != j.end()) {
        conditionOperator = (ConditionOperator) find.value().get<int>();
    }
    find = j.find("children");
    if (find != j.end() && find.value().is_array()) {
        for (const json &child : find.value()) {
            Blocker *blocker = BlockerFactory::create(child);
            if (blocker->enabled) {
                children.push_back(blocker);
            }
        }
    }

    find = j.find("reverse");
    if (find != j.end()) {
        reverse = find.value();
    }

    find = j.find("enabled");
    if (find != j.end()) {
        enabled = find.value();
    }
    
    parseJson(j);
}










