#include "journeyinfo.h"

CityInfo *JourneyInfo::getTo() const
{
    return to;
}

CityInfo *JourneyInfo::getFrom() const
{
    return from;
}


int JourneyInfo::getTime() const
{
    return time;
}

void JourneyInfo::setTime(int value)
{
    time = value;
}
JourneyInfo::JourneyInfo(CityInfo *from, CityInfo* to, int time):
    from(from),
    to(to),
    time(time)
{
}
