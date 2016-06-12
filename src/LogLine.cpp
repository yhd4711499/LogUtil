//
// Created by 袁浩东 on 16/6/9.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include "LogLine.h"
#include "LogEntry.h"

using namespace std;

std::ostream &operator<<(std::ostream &os, const LogLine& entry) {
    //int index = entry.orderedIndex;
    for (auto &line : entry.lines) {
        os << line << endl;
    }
    return os;
}

bool LogLine::isMainLine(std::string &line) {
    bool isMain;
    if (line.size() < 13) {
        isMain = false;
    } else {
        isMain = (line[0] == verbose ||
                  line[0] == debug ||
                  line[0] == info ||
                  line[0] == warning ||
                  line[0] == wtf ||
                  line[0] == error) && (line[1] == '/');
    }
    return isMain;
}

