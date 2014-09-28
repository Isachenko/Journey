#include "map.h"
#include <queue>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdexcept>

//return -1 if not exist
int Map::getNodeIdByCityInfo(const CityInfo *cityInfo)
{
    for(int i = 0; i < nodes.size(); ++i) {
        if (nodes[i]->cityInfo == cityInfo) {
            return i;
        }
    }
    return -1;
}

int Map::deepSearchEqual(int fromId, int toId, int depth)
{
    if (depth == 0) {
        if (fromId == toId) {
            return 1;
        } else {
            return 0;
        }
    }

    Node* fromNode = nodes.at(fromId);
    int routesCount = 0;
    for(Edge* edge : fromNode->edges) {
        routesCount += deepSearchEqual(edge->toNodeId, toId, depth - 1);
    }
    return routesCount;
}

int Map::deepSearchEqualOrLess(int fromId, int toId, int depth)
{
    int routesCount = 0;
    if (fromId == toId) {
        routesCount += 1;
    }
    if (depth == 0) {
        return routesCount;
    }

    Node* fromNode = nodes.at(fromId);
    for(Edge* edge : fromNode->edges) {
        routesCount += deepSearchEqualOrLess(edge->toNodeId, toId, depth - 1);

    }
    return routesCount;

}

int Map::deepSearchEqualOrLessTime(int fromId, int toId, int time)
{
    int routesCount = 0;
    if (time < 0) {
        return routesCount;
    }
    if (fromId == toId) {
        routesCount = 1;
    }

    Node* fromNode = nodes.at(fromId);
    for(Edge* edge : fromNode->edges) {
        routesCount += deepSearchEqualOrLessTime(edge->toNodeId, toId, time - edge->journeyInfo->getTime());

    }
    return routesCount;
}


Map::Map()
{
}

//return -1 if exist and id if added
int Map::addCity(CityInfo *cityInfo)
{
    if (getNodeIdByCityInfo(cityInfo) != -1) {
        return -1;
    }
    nodes.push_back(new Node(cityInfo));
    return nodes.size() - 1;
}

//throws out_of_range
CityInfo* Map::getCityById(int id)
{
    Node* node = nodes.at(id);

    CityInfo* city = node->cityInfo;
    return city;
}

//return nullptr if not exist
CityInfo* Map::getCityByName(std::string &name)
{
    for(Node* node : nodes) {
        CityInfo* city = node->cityInfo;
        if (city->getName() == name) {
            return city;
        }
    }
    return nullptr;
}

void Map::addJourney(JourneyInfo *journeyInfo)
{
    CityInfo* from = journeyInfo->getFrom();
    CityInfo* to = journeyInfo->getTo();
    //I don't know what bihavior should be here
    if (getJourneyInfo(from, to)) {
        return;
    }
    int fromId = getNodeIdByCityInfo(from);
    int toId = getNodeIdByCityInfo(to);
    if ((fromId == -1) || (toId == -1)) {
        throw std::invalid_argument("City don't exist");
    }
    Node* fromNode = nodes.at(fromId);
    fromNode->edges.push_back(new Edge(toId, journeyInfo));
}

//return nullptr if not exist
JourneyInfo *Map::getJourneyInfo(CityInfo *from, CityInfo *to)
{
    Node* fromNode = nodes.at(getNodeIdByCityInfo(from));
    for(Edge* edge : fromNode->edges) {
        JourneyInfo* journeyInfo = edge->journeyInfo;
        if (journeyInfo->getTo() == to) {
            return journeyInfo;
        }
    }
    return nullptr;
}

Route *Map::CreateRoute(std::list<CityInfo *> cities)
{
    if (cities.size() < 2) {
        throw std::invalid_argument("City Count to litle");
    }
    Route* route = new Route();
    auto it = cities.begin();
    CityInfo* curCity = *it;
    while (true) {
        ++it;
        if(it == cities.end()) {
            break;
        }
        CityInfo* nextCity = *it;
        int curCityId = getNodeIdByCityInfo(curCity);
        if (curCityId == -1) {
            throw std::invalid_argument("City didn't find");
        }
        bool exist = false;
        JourneyInfo* journeyInfo;
        Node* curNode = nodes.at(curCityId);
        for(Edge* edge : curNode->edges) {
            if (*(edge->journeyInfo->getTo()) == *(nextCity)) {
                exist = true;
                journeyInfo = edge->journeyInfo;
                break;
            }
        }
        if (!exist) {
            delete route;
            return nullptr;
        }
        route->addBackJourney(journeyInfo);
        curCity = nextCity;
    }
    return route;
}

Route *Map::getFastestRoute(CityInfo* from, CityInfo* to)
{
    int fromId = getNodeIdByCityInfo(from);
    int toId = getNodeIdByCityInfo(to);

    if (fromId == -1 || toId == -1) {
        throw std::invalid_argument("City didn't find");
    }

    int* range = new int[nodes.size()];
    memset(range, 0, sizeof(int) * nodes.size());
    int* parent = new int[nodes.size()];
    memset(parent, -1, sizeof(int) * nodes.size());
    bool* visited = new bool[nodes.size()];
    memset(visited, false, sizeof(bool) * nodes.size());

    visited[fromId] = true;

    std::queue<int> nodesForVisit;

    nodesForVisit.push(fromId);
    while (!nodesForVisit.empty()) {
        int cutNodeId = nodesForVisit.front();
        Node* curNode = nodes.at(nodesForVisit.front());
        nodesForVisit.pop();
        for(Edge* edge : curNode->edges) {
            int toId = edge->toNodeId;
            if (!visited[toId] || (range[toId] > (range[cutNodeId] + edge->journeyInfo->getTime()) ) ) {
                nodesForVisit.push(toId);
                visited[toId] = true;
                parent[toId] = cutNodeId;
                range[toId] =range[cutNodeId] + edge->journeyInfo->getTime();
            }
        }
    }

    Route *route = new Route;
    if (!visited[toId]) {
        return route;
    }

    int curParentId = parent[toId];
    int curNodeId = toId;
    while(curParentId != -1) {
        Node curNode = *(nodes.at(curNodeId));
        Node curParent = *(nodes.at(curParentId));
        route->addFrontJourney(new JourneyInfo(curParent.cityInfo, curNode.cityInfo, range[curNodeId] - range[curParentId]));
    }

    delete[] range;
    delete[] parent;
    delete[] visited;

    return route;
}

//I know that copy-paste is bad, but i didn't find solution
int Map::getRouteCountByEqualOrLessStopsCount(const CityInfo *from, const CityInfo *to, int stopsCount)
{
    int fromId = getNodeIdByCityInfo(from);
    int toId = getNodeIdByCityInfo(to);
    return deepSearchEqualOrLess(fromId, toId, stopsCount + 1);
}

int Map::getRouteCountByEqualStopsCount(const CityInfo *from, const CityInfo *to, int stopsCount)
{
    int fromId = getNodeIdByCityInfo(from);
    int toId = getNodeIdByCityInfo(to);
    return deepSearchEqual(fromId, toId, stopsCount + 1);
}

int Map::getRouteCountByEqualOrLessTime(const CityInfo *from, const CityInfo *to, int time)
{
    int fromId = getNodeIdByCityInfo(from);
    int toId = getNodeIdByCityInfo(to);
    return deepSearchEqualOrLessTime(fromId, toId, time);
}

