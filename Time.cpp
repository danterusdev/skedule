#include "Time.h"

Time::Time(const unsigned int YEAR, const unsigned short int MONTH, const unsigned short int DAY, const unsigned short int HOUR, const unsigned short int MINUTE) : Date(YEAR, MONTH, DAY) {
    _hour = HOUR;
    _minute = MINUTE;
}
