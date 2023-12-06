#include "Month.h"

#include <stdexcept>

Month::Month(const int YEAR, const unsigned short int MONTH)
    : Year(YEAR) {
    _month = MONTH;

    if (_month > 11) {
        throw new std::out_of_range("Month not in range [0-12)");
    }
}

int Month::getDayOfWeek() const {
    int result = 0;
    // Uses the year 1600 as a fixed point because it unlikely anyone wants to go back before then
    for (unsigned int i = 1600; i < _year; i++) {
        result += Year(i).getDayCount();
    }

    for (short int i = 0; i < _month; i++) {
        result += Month(_year, i).getDayCount();
    }

    // the + 6 is accounting for the fact that January 1st 1600 was a Saturday
    return (result + 6) % 7;
}
unsigned int Month::getDayCount() const {
    switch (_month) {
        case 0:
            return 31;
        case 1:
            if (isLeapYear()) {
                return 29;
            } else {
                return 28;
            }
        case 2:
            return 31;
        case 3:
            return 30;
        case 4:
            return 31;
        case 5:
            return 30;
        case 6:
            return 31;
        case 7:
            return 31;
        case 8:
            return 30;
        case 9:
            return 31;
        case 10:
            return 30;
        case 11:
            return 31;
        default:
            return -1;
    }
}

std::string Month::toString() const {
    switch (_month) {
        case 0:
            return "January";
        case 1:
            return "February";
        case 2:
            return "March";
        case 3:
            return "April";
        case 4:
            return "May";
        case 5:
            return "June";
        case 6:
            return "July";
        case 7:
            return "August";
        case 8:
            return "September";
        case 9:
            return "October";
        case 10:
            return "November";
        case 11:
            return "December";
        default:
            return "";
    }
}

short unsigned int Month::getMonth() const {
    return _month;
}
