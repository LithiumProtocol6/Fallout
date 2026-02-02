#include <iostream>
#include "Game.h"


int main()
{
    Game fallout(1600,1200,"Fallout");
    std::vector<std::string> maps = { "maps/testMap.tmx","maps/map1.tmx"};
    fallout.setMaps(maps,2);
    std::vector<std::vector<Entity>> ent;
    ent.resize(2);
    ent[0].resize(1);
    ent[1].resize(2);
    ent[0]={ Entity(12, 12, 100, 100, 10, 10, 50, false) };
    ent[1]={ Entity(15, 15, 100, 100, 10, 10, 50, false),Entity(13, 13, 100, 100, 10, 10, 50, false) };
    std::vector<int> a = { 1,2 };
    fallout.setEntities(ent,a,2,1);
    Entity player(1,1,100,100,10,10,50,false);
    std::string path = "Textures/Knight/Idle.png";
    player.initAnimation(path,1,4,4,20,1);
    path = "Textures/Knight/Walk.png";
    player.initAnimation(path, 1, 8, 8, 20, 2);
    fallout.setPlayer(player);
    fallout.run();
}