#ifndef DATE_H
#define DATE_H

#include "Month.h"

class Date : public Month {
public:
    Date(const unsigned int YEAR, const unsigned short int MONTH, const unsigned short int DAY);

    bool dateEquals(const Date& OTHER) const;

    unsigned short int getDay() const;
private:
    unsigned short int _day;
};

#endif
