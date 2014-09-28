#pragma once

#include "cityinfo.h"
#include "journeyinfo.h"
#include <vector>
#include "route.h"
#include <list>

class Map
{
private:
    class Node;
    class Edge;

    class Edge{
    public:
        int toNodeId;
        JourneyInfo* journeyInfo;
        Edge(int toNodeId, JourneyInfo* journeyInfo):
            toNodeId(toNodeId),
            journeyInfo(journeyInfo)
        {
        }
    };

    class Node{
    public:
        CityInfo* cityInfo;
        std::list<Edge*> edges;
        Node(CityInfo* cityInfo):
            cityInfo(cityInfo)
        {
        }
    };

    std::vector<Node*> nodes;

    //return -1 if not exist
    int getNodeIdByCityInfo(const CityInfo *cityInfo);
    //return count of routes;
    int deepSearchEqual(int fromId, int toId, int depth);
    int deepSearchEqualOrLess(int fromId, int toId, int depth);
    int deepSearchEqualOrLessTime(int fromId, int toId, int time);

public:
    Map();
    //City operations

    //return -1 if exist and id if added
    int addCity(CityInfo* cityInfo);
    //throws out_of_range
    CityInfo *getCityById(int id);
    //return nullptr if not exist
    CityInfo *getCityByName(std::string &name);

    //JourneyOperations

    void addJourney(JourneyInfo* journeyInfo);
    //return nullptr if not exist
    JourneyInfo *getJourneyInfo(CityInfo* from, CityInfo* to);

    //1
    Route *createRoute(std::list<CityInfo*> &cities);
    //2
    Route* getFastestRoute(CityInfo *from, CityInfo *to);
    //3
    int getRouteCountByEqualOrLessStopsCount(const CityInfo *from, const CityInfo *to, int stopsCount);
    //4
    int getRouteCountByEqualStopsCount(const CityInfo *from, const CityInfo *to, int stopsCount);
    //5
    int getRouteCountByEqualOrLessTime(const CityInfo *from, const CityInfo *to, int time);

    CityInfo* operator [] (int id);
};

