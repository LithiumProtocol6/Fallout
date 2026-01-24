#include <iostream>
#include "Game.h"


int main()
{
    Game fallout(1600,1200,"Fallout");
    std::string maps[2] = { "maps/testMap.tmx","maps/map1.tmx"};
    fallout.setMaps(maps,2);
    fallout.run();
}