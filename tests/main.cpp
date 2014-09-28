#include <unittest++/UnitTest++.h>
#include "../src/libs/map.h"

struct ConstructorFixture
{
   ConstructorFixture():
       map()
   {
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
   }

   Map map;
   CityInfo* nyCity;
   CityInfo* lvCity;
   CityInfo* cbCity;
   CityInfo* ctCity;
   CityInfo* baCity;
};

TEST_FIXTURE(ConstructorFixture, CityTest)
{
    CHECK(*(map.getCityById(0)) == std::string("New York"));
    CHECK_EQUAL(std::string("Liverpool"), *(map.getCityById(1)));
    CHECK_EQUAL(std::string("Casablanca"), *(map.getCityById(2)));
    CHECK_EQUAL(std::string("Cape Town"), *(map.getCityById(3)));
    CHECK_EQUAL(std::string("Buenos Aires"), *(map.getCityById(4)));

    std::string nyName("New dorfk");
    CityInfo* nyCity2 = map.getCityByName(nyName);
    CHECK(nullptr == nyCity2);
}

TEST_FIXTURE(ConstructorFixture, JourneyTest)
{
    JourneyInfo* journeyInfo = map.getJourneyInfo(baCity, nyCity);
    CHECK_EQUAL(journeyInfo->getTime(), 6);

    journeyInfo = map.getJourneyInfo(baCity, cbCity);
    CHECK_EQUAL(journeyInfo->getTime(), 5);

    journeyInfo = map.getJourneyInfo(baCity, ctCity);
    CHECK_EQUAL(journeyInfo->getTime(), 4);

    journeyInfo = map.getJourneyInfo(nyCity, lvCity);
    CHECK_EQUAL(journeyInfo->getTime(), 4);

    journeyInfo = map.getJourneyInfo(lvCity, cbCity);
    CHECK_EQUAL(journeyInfo->getTime(), 3);

    journeyInfo = map.getJourneyInfo(lvCity, ctCity);
    CHECK_EQUAL(journeyInfo->getTime(), 6);

    journeyInfo = map.getJourneyInfo(cbCity, lvCity);
    CHECK_EQUAL(journeyInfo->getTime(), 3);

    journeyInfo = map.getJourneyInfo(cbCity, ctCity);
    CHECK_EQUAL(journeyInfo->getTime(), 6);

    journeyInfo = map.getJourneyInfo(ctCity, nyCity);
    CHECK_EQUAL(journeyInfo->getTime(), 8);

    journeyInfo = map.getJourneyInfo(nyCity, ctCity);
    CHECK(journeyInfo == nullptr);
}


TEST_FIXTURE(ConstructorFixture, RouteTest1)
{

}

TEST_FIXTURE(ConstructorFixture, RouteTest2)
{

}

TEST_FIXTURE(ConstructorFixture, RouteTest3)
{
    int routCount = map.getRouteCountByEqualOrLessStopsCount(lvCity, lvCity, 3);
    CHECK_EQUAL(5, routCount);
}

TEST_FIXTURE(ConstructorFixture, RouteTest4)
{
    int routCount = map.getRouteCountByEqualStopsCount(baCity, lvCity, 4);
    CHECK_EQUAL(3, routCount);
}

TEST_FIXTURE(ConstructorFixture, RouteTest5)
{
    int routCount = map.getRouteCountByEqualOrLessTime(lvCity, lvCity, 6);
    CHECK_EQUAL(2, routCount);

    routCount = map.getRouteCountByEqualOrLessTime(lvCity, lvCity, 25);
    CHECK_EQUAL(9, routCount);
}


int main()
{
    return UnitTest::RunAllTests();
}
