//
// Created by 袁浩东 on 16/6/11.
//

#include "LogEntryFilter.h"
#include "LogEntryFilterFactory.h"

bool LogEntryFilter::apply(const LogEntry &item) const {
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

void LogEntryFilter::addChildren(const LogEntryFilter &child) {
    children.push_back(&child);
}

void LogEntryFilter::init(const json &j) {
    auto find = j.find("operator");
    if (find != j.end()) {
        conditionOperator = (ConditionOperator) find.value().get<int>();
    }
    find = j.find("children");
    if (find != j.end() && find.value().is_array()) {
        for (const json &child : find.value()) {
            LogEntryFilter *blocker = LogEntryFilterFactory::create(child);
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










