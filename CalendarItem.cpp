#include "CalendarItem.h"

CalendarItem::CalendarItem(const Date DATE) : _date(DATE) {
    
}

Date CalendarItem::getDate() const {
    return _date;
}
