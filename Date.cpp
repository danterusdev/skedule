#include "Date.h"

Date::Date(const unsigned int YEAR, const unsigned short int MONTH, const unsigned short int DAY)
    : Month(YEAR, MONTH) {
    _day = DAY;
}

bool Date::dateEquals(const Date& OTHER) const {
    return _year == OTHER._year &&
            _month == OTHER._month &&
            _day == OTHER._day;
}
