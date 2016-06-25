//
// Created by 袁浩东 on 16/6/9.
//

#ifndef WNSLOGHELPER_LOGLINE_H
#define WNSLOGHELPER_LOGLINE_H

#include <vector>
#include <string>

class LogLine {
public:
    int orderedIndex;
    int originalIndex;
    std::vector<std::string> lines;

    static bool isMainLine(std::string &line);
};

std::ostream &operator<<(std::ostream &os, const LogLine &entry);

#endif //WNSLOGHELPER_LOGLINE_H
