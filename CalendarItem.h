#ifndef CALENDAR_ITEM_H
#define CALENDAR_ITEM_H

#include "Time.h"

#include <string>

class CalendarItem {
public:
    CalendarItem(const Time TIME);

    Time getTime() const;

    virtual std::string getDisplayName() const = 0;
private:
    Time _time;
};

#endif
