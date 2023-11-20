#ifndef YEAR_H
#define YEAR_H

class Year {
public:
    Year(const unsigned int YEAR);

    int getDayCount() const;
    bool isLeapYear() const;
    int getYear() const;
protected:
    unsigned int _year;
};

#endif
