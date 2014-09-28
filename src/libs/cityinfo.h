#pragma once

#include <string>
#include <list>
#include <iostream>

class CityInfo
{
private:
    std::string name;
public:
    CityInfo(std::string name);

    std::string getName() const;
    void setName(const std::string &value);

    bool operator == (const CityInfo& city) const;
    bool operator == (const std::string& cityName) const;
    friend bool operator == (const std::string& cityName, const CityInfo& dt) {
        return dt.getName() == cityName;
    }
    friend std::ostream& operator<<(std::ostream& os, const CityInfo& dt) {
        os << dt.getName();
        return os;
    }
};



