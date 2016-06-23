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
    LogTime(std::string d, std::string t):date(d),time(t) {}

    bool operator<( const LogTime& val ) const {
		int i = date.compare(val.date);
		if (i < 0) {
			return true;
		} else if (i == 0 && time.compare(val.time) < 0){
			return true;
		}
		return false;
    }
};


#endif //WNSLOGHELPER_LOGTIME_H
