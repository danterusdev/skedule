#include "Year.h"

Year::Year(const unsigned int YEAR) {
    _year = YEAR;
    
    if (_year < 1600) {
        _year = 1600;
    }
}

int Year::getDayCount() const {
    if (this->isLeapYear()) {
        return 366;
    } else {
        return 365;
    }
}

bool Year::isLeapYear() const {
    if ((_year % 4 != 0 || _year % 100 == 0) && _year % 400 != 0) {
        return false;
    } else {
        return true;
    }
}

int Year::getYear() const {
    return _year;
}
