#include "route.h"


int Route::getTotalTime() const
{
    return totalTime;
}

void Route::addFrontJourney(JourneyInfo *journeyInfo)
{
    journeys.push_front(journeyInfo);
}

void Route::addBackJourney(JourneyInfo *journeyInfo)
{
    journeys.push_back(journeyInfo);
}

Route::Route()
{
}


