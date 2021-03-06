//
// Created by 袁浩东 on 16/6/9.
//

#ifndef WNSLOGHELPER_LOGTIME_H
#define WNSLOGHELPER_LOGTIME_H

#include <string>

using namespace std;

struct LogTime {
    string date;
    string time;
public:
    LogTime(const std::string &d, const std::string &t) : date(d), time(t) { }

    bool empty() const {
        return this->date.empty() && this->time.empty();
    }

    bool operator==(const LogTime &val) const {
        if (date.compare(val.date)) {
            return false;
        }
        if (time.compare(val.time)) {
            return false;
        }
        return true;
    }

    bool operator<(const LogTime &val) const {
        int i = date.compare(val.date);
        if (i < 0) {
            return true;
        } else if (i == 0 && time.compare(val.time) < 0) {
            return true;
        }
        return false;
    }

    bool operator>=(const LogTime &val) const {
        return !(*this < val);
    }

    bool operator<=(const LogTime &val) const {
        return *this < val || *this == val;
    }

    static LogTime from(const string &date, const string &time);
};


#endif //WNSLOGHELPER_LOGTIME_H
