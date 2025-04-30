#pragma once

#include "EventData.hpp"

class Event
{
public:
    Event();
    const EventData& getData() const { return eventData_; }
    
private:
    EventData eventData_;
};