#ifndef EVENT_H
#define EVENT_H

#include "CalendarItem.h"

class Event : public CalendarItem {
public:
    Event(const Time TIME);
};

#endif
