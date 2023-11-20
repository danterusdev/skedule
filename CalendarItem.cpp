#include "CalendarItem.h"

CalendarItem::CalendarItem(const Time TIME) : _time(TIME) {
    
}

Time CalendarItem::getTime() const {
    return _time;
}
