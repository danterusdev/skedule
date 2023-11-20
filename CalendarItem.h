#ifndef CALENDAR_ITEM_H
#define CALENDAR_ITEM_H

#include "Time.h"

class CalendarItem {
public:
    CalendarItem(const Time TIME);

    Time getTime() const;
private:
    Time _time;
};

#endif
