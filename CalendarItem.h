#ifndef CALENDAR_ITEM_H
#define CALENDAR_ITEM_H

#include "Date.h"

#include <string>

class CalendarItem {
public:
    CalendarItem(const Date TIME);

    Date getDate() const;

    virtual std::string getDisplayName() const = 0;

    virtual void saveToFile(std::ofstream& stream) const = 0;
protected:
    Date _date;
};

#endif
