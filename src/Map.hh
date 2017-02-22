#ifndef __MAP_HH__
#define __MAP_HH__

#include <iostream>
#include <vector>
#include <string>

#include "../lib/jsoncpp/json/json.h"

class Map
{
public:
    std::string     name;
    unsigned int    sizeX;
    unsigned int    sizeY;

    Map(){};
    Map(std::string, Json::Value);
};

#endif
