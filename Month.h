#ifndef MONTH_H
#define MONTH_H

#include "Year.h"

#include <string>

class Month : public Year {
public:
    Month(const int YEAR, const unsigned short int MONTH);

    int getDayOfWeek() const;
    unsigned int getDayCount() const;
    std::string toString() const;
    short unsigned int getMonth() const;
protected:
    short unsigned int _month;
};

#endif
