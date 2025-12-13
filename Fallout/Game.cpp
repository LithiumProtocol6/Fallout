#include "Game.h"
void Game:: parseCSV(const char* text, int* dest, int maxCount)
{
    const char* p = text;
    int n = 0;
    char num[16];
    int ni = 0;

    while (*p && n < maxCount) {
        if (*p == ',' || *p == '\n' || *p == '\r') {
            if (ni > 0) {
                num[ni] = '\0';
                dest[n++] = atoi(num);
                ni = 0;
            }
        }
        else if ((*p >= '0' && *p <= '9')) {
            if (ni < 15) num[ni++] = *p;
        }
        ++p;
    }
    if (ni > 0 && n < maxCount) {
        num[ni] = '\0';
        dest[n++] = atoi(num);
    }
}
bool Game:: loadTMX(const char* file, char* tilesetPath, int pathSize)
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(file) != tinyxml2::XML_SUCCESS) {
        std::cout << "TMX load error: " << file << std::endl;
        return false;
    }

    tinyxml2::XMLElement* map = doc.FirstChildElement("map");
    if (!map) { std::cout << "No <map> element" << std::endl; return false; }

    mapWidth = map->IntAttribute("width");
    mapHeight = map->IntAttribute("height");
    tileW = map->IntAttribute("tilewidth");
    tileH = map->IntAttribute("tileheight");

    tinyxml2::XMLElement* tilesetEl = map->FirstChildElement("tileset");
    if (!tilesetEl) { std::cout << "No <tileset> element" << std::endl; return false; }

    const char* source = tilesetEl->Attribute("source");

    tinyxml2::XMLDocument tsxDoc;
    if (tsxDoc.LoadFile(source) != tinyxml2::XML_SUCCESS) {
        std::cout << "Failed to load TSX: " << source << std::endl;
        return false;
    }

    tinyxml2::XMLElement* tsxTileset = tsxDoc.FirstChildElement("tileset");
    if (!tsxTileset) { std::cout << "No <tileset> in TSX" << std::endl; return false; }

    tinyxml2::XMLElement* imgEl = tsxTileset->FirstChildElement("image");
    if (!imgEl) { std::cout << "No <image> in TSX" << std::endl; return false; }

    const char* imgSrc = imgEl->Attribute("source");
    if (!imgSrc) { std::cout << "TSX image has no source" << std::endl; return false; }

    size_t len = strlen(imgSrc);
    if (len >= pathSize) {
        std::cout << "tilesetPath buffer too small! Needed: "<< len + 1<< std::endl;
        return false;
    }
    strcpy_s(tilesetPath, pathSize, imgSrc);

    int li = 0;
    for (tinyxml2::XMLElement* lay = map->FirstChildElement("layer");
        lay && li < 2;
        lay = lay->NextSiblingElement("layer"), ++li)
    {
        tinyxml2::XMLElement* data = lay->FirstChildElement("data");
        if (!data) { std::cout << "Layer %d has no <data>" << li << std::endl; return false; }
        parseCSV(data->GetText(), layerData[li], MAP_W * MAP_H);
    }
    return true;
}
void Game:: initWindow(int w, int h, const char* name) {
    videoMode.size.x = w;
    videoMode.size.y = h;
    window = new sf::RenderWindow(videoMode,name);
}
void Game::initVar() {
    window = nullptr;
}
Game::Game() {
    initVar();
    initWindow(800,800,"Game");
}
Game::Game(int w, int h, const char* name) {
    initVar();
    initWindow(w, h, name);
}
Game:: ~Game() {
    delete window;
}