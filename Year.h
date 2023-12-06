#ifndef YEAR_H
#define YEAR_H

/**
 * Stores a calendar year
 */
class Year {
public:
    /**
     * Constructs a Year with the given year value
     *
     * @param YEAR the given year value
     */
    Year(const unsigned int YEAR);

    /**
     * Returns the number of days in the year
     *
     * @return the number of days
     */
    int getDayCount() const;

    /**
     * @return whether the year is a leap year
     */
    bool isLeapYear() const;

    /**
     * @return the internal year id of the Year
     */
    int getYear() const;
protected:
    unsigned int _year;
};

#endif
