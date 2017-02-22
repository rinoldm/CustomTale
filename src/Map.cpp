#include "Map.hh"

Map::Map(std::string mapName, Json::Value mapData)
{
    this->name = mapName;
    this->sizeX = mapData["width"].asUInt();
    this->sizeY = mapData["height"].asUInt();

    if (mapData["orientation"].asString() != "orthogonal")
    {
        std::cout << "Error: map orientation must be orthogonal" << std::endl;
        exit (-1);
    }

    if (mapData["renderorder"].asString() != "right-down")
    {
        std::cout << "Error: map renderorder must be right-down" << std::endl;
        exit (-1);
    }
}
