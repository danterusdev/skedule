#ifndef DATE_H
#define DATE_H

#include "Month.h"

/**
 * Stores a specific date, including day, month, and year
 */
class Date : public Month {
public:
    /**
     * Constructs a Date with a specifi day, month, and year
     */
    Date(const unsigned int YEAR, const unsigned short int MONTH, const unsigned short int DAY);

    /**
     * @return whether the two dates represent the same day
     */
    bool dateEquals(const Date& OTHER) const;

    /**
     * @return the day part of the date
     */
    unsigned short int getDay() const;
private:
    unsigned short int _day;
};

#endif
