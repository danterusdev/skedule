#ifndef TIME_H
#define TIME_H

#include "Date.h"

class Time : public Date {
public:
    Time(const unsigned int YEAR, const unsigned short int MONTH, const unsigned short int DAY, const unsigned short int HOUR, const unsigned short int MINUTE);
private:
    unsigned short int _hour;
    unsigned short int _minute;
};

#endif
