#include "cityinfo.h"

std::string CityInfo::getName() const
{
    return name;
}

void CityInfo::setName(const std::string &value)
{
    name = value;
}

bool CityInfo::operator ==(const CityInfo &city) const
{
    return this->name == city.name;
}


bool CityInfo::operator == (const std::string& cityName) const
{
    return this->name == cityName;
}


CityInfo::CityInfo(std::string name):
    name(name)
{
}

