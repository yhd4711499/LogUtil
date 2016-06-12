//
// Created by 袁浩东 on 16/6/9.
//

#ifndef WNSLOGHELPER_REARRANGER_H
#define WNSLOGHELPER_REARRANGER_H

#include <vector>
#include "LogEntry.h"

using namespace std;

/**
 * 根据时间排序日志
 */
class Rearranger {
public:
    void sort(vector<LogEntry*>&);
};


#endif //WNSLOGHELPER_REARRANGER_H
