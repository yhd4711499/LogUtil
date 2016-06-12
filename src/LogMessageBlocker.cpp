//
// Created by 袁浩东 on 16/6/11.
//

#include "LogMessageBlocker.h"

bool LogMessageBlocker::doApply(const LogEntry &item) const {
    if (scope == wholeLogLine) {
        for (auto &word : words) {
            if (item.line.lines[0].find(word) != string::npos) {
                return true;
            }
        }
    }
    return false;
}

void LogMessageBlocker::parseJson(const json &j) {
    scope = (Scope) j["scope"].get<int>();
    json words_json = j["words"];
    if (words_json.is_array()) {
        for (json &word : words_json) {
            words.push_back(word);
        }
    } else {
        words.push_back(words_json);
    }
}

