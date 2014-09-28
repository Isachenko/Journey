#include "route.h"


int Route::getTotalTime() const
{
    return totalTime;
}

void Route::addFrontJourney(JourneyInfo *journeyInfo)
{
    journeys.push_front(journeyInfo);
    totalTime += journeyInfo->getTime();
}

void Route::addBackJourney(JourneyInfo *journeyInfo)
{
    journeys.push_back(journeyInfo);
    totalTime += journeyInfo->getTime();
}

Route::Route() :
    totalTime(0),
    journeys()
{
}


