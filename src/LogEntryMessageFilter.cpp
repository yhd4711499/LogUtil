//
// Created by 袁浩东 on 16/6/11.
//

#include "LogEntryMessageFilter.h"

bool LogEntryMessageFilter::doApply(const LogEntry &item) const {
    bool result = false;
    string line = item.line.lines[0];
    switch (wordsConditionOperator) {
        case andOperator:
            for (auto &word : words) {
                if (!(result = (line.find(word) != string::npos))) {
                    break;
                }
            }
            break;
        case orOperator:
            for (auto &word : words) {
                if ((result = (line.find(word) != string::npos))) {
                    break;
                }
            }
            break;
        default:
            throw runtime_error("unknown wordsConditionOperator");
    }

    return result;
}

void LogEntryMessageFilter::parseJson(const json &j) {
    json words_json = j["words"];
    if (words_json.is_array()) {
        for (json &word : words_json) {
            words.push_back(word);
        }
    } else {
        words.push_back(words_json);
    }

    auto wordsConditionOperator_json = j.find("wordsOperator");
    if (wordsConditionOperator_json != j.end()) {
        wordsConditionOperator = (ConditionOperator) wordsConditionOperator_json->get<int>();
    } else {
        wordsConditionOperator = andOperator;
    }
}

