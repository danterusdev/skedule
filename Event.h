#ifndef EVENT_H
#define EVENT_H

#include "CalendarItem.h"

#include <string>

class Event : public CalendarItem {
public:
    Event(const std::string NAME, const Date TIME);

    std::string getDisplayName() const override;
private:
    std::string _name;
};

#endif
