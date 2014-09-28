#ifndef JOURNEYINFO_H
#define JOURNEYINFO_H

#include "cityinfo.h"

class JourneyInfo
{
private:
    CityInfo* from;
    CityInfo* to;
    int time;

public:
    JourneyInfo(CityInfo* from, CityInfo *to, int time);

    CityInfo *getTo() const;
    CityInfo *getFrom() const;
    int getTime() const;
    void setTime(int value);
};

#endif // JOURNEYINFO_H
