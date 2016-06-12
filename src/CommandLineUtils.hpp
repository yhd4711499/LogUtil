//
// Created by 袁浩东 on 16/6/10.
//

#ifndef WNSLOGHELPER_COMMANDLINEUTILS_HPP
#define WNSLOGHELPER_COMMANDLINEUTILS_HPP

#include <string>

char *getCmdOption(char **begin, char **end, const std::string &option) {
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char **begin, char **end, const std::string &option) {
    return std::find(begin, end, option) != end;
}

#endif //WNSLOGHELPER_COMMANDLINEUTILS_HPP
