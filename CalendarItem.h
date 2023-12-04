#ifndef CALENDAR_ITEM_H
#define CALENDAR_ITEM_H

#include "Date.h"

#include <string>

class CalendarItem {
public:
    CalendarItem(const Date TIME);

    Date getDate() const;

    virtual std::string getDisplayName() const = 0;
private:
    Date _date;
};

#endif
