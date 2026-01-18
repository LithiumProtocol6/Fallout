#include "MapLoad.h"
mapData::mapData()
{
    tiles = nullptr;
    tileW = 0;
    tileH = 0;
    offsetX = nullptr;
    offsetY = nullptr;
    layerW = nullptr;
    layerH = nullptr;
    layersCount = 0;
    tilesPerRow = 0;
}
mapData::~mapData()
{
    for (int i = 0; i < layersCount; i++) { if (tiles[i])delete[] tiles[i]; std::cout << "tiles " << i << " deleted\n"; }
    if (tiles) delete[] tiles;
    std::cout << "tiles deleted\n";
    if (offsetX) delete[] offsetX;
    std::cout << "offsetX deleted\n";
    if (offsetY) delete[] offsetY;
    std::cout << "offsetY deleted\n";
    if (layerH) delete[] layerH;
    std::cout << "layerH deleted\n";
    if (layerW) delete[] layerW;
    std::cout << "layerW deleted\n";
}
void mapData::parseCSV(const char* text, int* dest, int maxCount)
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
bool mapData::loadTMX(const char* file)
{
    for (int i = 0; i < layersCount; i++) { if (tiles[i])delete[] tiles[i]; std::cout << "tiles " << i << " deleted\n"; }
    if (tiles) delete[] tiles;
    std::cout << "tiles deleted\n";
    if (offsetX) delete[] offsetX;
    std::cout << "offsetX deleted\n";
    if (offsetY) delete[] offsetY;
    std::cout << "offsetY deleted\n";
    if (layerH) delete[] layerH;
    std::cout << "layerH deleted\n";
    if (layerW) delete[] layerW;
    std::cout << "layerW deleted\n";

    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(file) != tinyxml2::XML_SUCCESS) {
        std::cout << "TMX load error: " << file << std::endl;
        return false;
    }

    tinyxml2::XMLElement* map = doc.FirstChildElement("map");
    if (!map) { std::cout << "No <map> element" << std::endl; return false; }

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

    if (!tileset.loadFromFile(imgSrc)) { std::cout << "TSX image has no source" << std::endl; return false; }
    tilesPerRow = tileset.getSize().x / tileW;
    size_t len = strlen(imgSrc);

    int li = 0;
    layersCount = 0;
    for (tinyxml2::XMLElement* lay = map->FirstChildElement("layer"); lay != nullptr; lay = lay->NextSiblingElement("layer")) {
        layersCount++;
    }
    tiles = new int* [layersCount];
    layerW = new int[layersCount];
    layerH = new int[layersCount];
    offsetX = new int[layersCount];
    offsetY = new int[layersCount];
    for (tinyxml2::XMLElement* lay = map->FirstChildElement("layer"); lay != nullptr; lay = lay->NextSiblingElement("layer"), li++)
    {
        layerW[li] = lay->IntAttribute("width");
        layerH[li] = lay->IntAttribute("height");
        offsetX[li] = lay->IntAttribute("offsetx");
        offsetY[li] = lay->IntAttribute("offsety");
        tiles[li] = new int[layerW[li] * layerH[li]];
        tinyxml2::XMLElement* data = lay->FirstChildElement("data");
        if (!data) { std::cout << "Layer %d has no <data>" << li << std::endl; return false; }
        parseCSV(data->GetText(), tiles[li], layerW[li] * layerH[li]);
    }
    return true;
}
int** mapData::getTilesData()
{
    return tiles;
}
int mapData::getTileWidth()
{
    return tileW;
}
int mapData::getTileHeight()
{
    return tileH;
}
const int* mapData::getOffsetsX()
{
    return offsetX;
}
const int* mapData::getOffsetsY()
{
    return offsetY;
}
const int* mapData::getLayersWidth()
{
    return layerW;
}
const int* mapData::getLayersHeight()
{
    return layerH;
}
int mapData::getLayersCount()
{
    return layersCount;
}
int mapData::getTilesPerRow()
{
    return tilesPerRow;
}

sf::Texture& mapData::getTileset()
{
    return tileset;
}
