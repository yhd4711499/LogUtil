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
            if (!child->apply(item)) {
                result = false;
                goto exit;
            }
        }
        result = true;
    } else if (conditionOperator == orOperator) {
        for (auto child : children) {
            if (child->apply(item)) {
                result = true;
                goto exit;
            }
        }
        result = false;
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
            children.push_back(BlockerFactory::create(child));
        }
    } else {
        parseJson(j);
    }

    find = j.find("reverse");
    if (find != j.end()) {
        reverse = find.value();
    }

    find = j.find("enabled");
    if (find != j.end()) {
        enabled = find.value();
    }
}










