#pragma once
#include <list>
#include "journeyinfo.h"

class Route
{
private:
    int totalTime;
    std::list<JourneyInfo*> journeys;
public:
    Route();
    int getTotalTime() const;
    void addFrontJourney(JourneyInfo* journeyInfo);
    void addBackJourney(JourneyInfo *journeyInfo);
};

