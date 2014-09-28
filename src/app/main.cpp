#include <stdio.h>
#include "../libs/map.h"

int main()
{
    printf("start\n");
    Map map;
    CityInfo* nyCity;
    CityInfo* lvCity;
    CityInfo* cbCity;
    CityInfo* ctCity;
    CityInfo* baCity;
    nyCity = new CityInfo("New York");
    lvCity = new CityInfo("Liverpool");
    cbCity = new CityInfo("Casablanca");
    ctCity = new CityInfo("Cape Town");
    baCity = new CityInfo("Buenos Aires");

    map.addCity(nyCity);
    map.addCity(lvCity);
    map.addCity(cbCity);
    map.addCity(ctCity);
    map.addCity(baCity);

    map.addJourney(new JourneyInfo(baCity, nyCity, 6));
    map.addJourney(new JourneyInfo(baCity, cbCity, 5));
    map.addJourney(new JourneyInfo(baCity, ctCity, 4));
    map.addJourney(new JourneyInfo(nyCity, lvCity, 4));
    map.addJourney(new JourneyInfo(lvCity, cbCity, 3));
    map.addJourney(new JourneyInfo(lvCity, ctCity, 6));
    map.addJourney(new JourneyInfo(cbCity, lvCity, 3));
    map.addJourney(new JourneyInfo(cbCity, ctCity, 6));
    map.addJourney(new JourneyInfo(ctCity, nyCity, 8));

    map.getFastestRoute(nyCity, nyCity);
    map.getFastestRoute(baCity, lvCity);
}
