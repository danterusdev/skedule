#ifndef MONTH_H
#define MONTH_H

#include "Year.h"

#include <string>

/**
 * Represents a specific calendar month in a specific year
 */
class Month : public Year {
public:
    /**
     * Constructs a month based on a year and month value
     *
     * @param YEAR the year of the month
     * @param MONTH the month id
     */
    Month(const int YEAR, const unsigned short int MONTH);

    /**
     * Computes the day of the week that the month starts on
     *
     * @return the day of the week
     */
    int getDayOfWeek() const;

    /**
     * Computes the day count in the month, including leap years
     *
     * @return the amount of days in the month
     */
    unsigned int getDayCount() const;

    /**
     * Converts the month to a month name string for display
     *
     * @return the month's name
     */
    std::string toString() const;

    /**
     * @return the month's intern id
     */
    short unsigned int getMonth() const;
protected:
    short unsigned int _month;
};

#endif
