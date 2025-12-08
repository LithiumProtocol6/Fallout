#include <SFML/Graphics.hpp>
#include <iostream>
#include "tinyxml2.h"

//Переменные и функции карты
#define MAP_W 64      // максимальная ширина карты в тайлах
#define MAP_H 64      // максимальная высота
#define LAYERS 2      // кол-во слоев !!! ИЗМЕНИТЬ ЕСЛИ БУДЕТ ИЗМЕНЕНО КОЛ-ВО СЛОЕВ !!!
int mapWidth=0,mapHeight=0,tileW=0,tileH=0;
int layerData[LAYERS][MAP_W * MAP_H]; // это инфа по всем тайлам

void parseCSV(const char* text, int* dest, int maxCount)
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

bool loadTMX(const char* file, char* tilesetPath, int pathSize)
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(file) != tinyxml2::XML_SUCCESS) {
        printf("TMX load error: %s", file);
        return false;
    }

    tinyxml2::XMLElement* map = doc.FirstChildElement("map");
    if (!map) { printf("No <map> element\n"); return false; }

    mapWidth = map->IntAttribute("width");
    mapHeight = map->IntAttribute("height");
    tileW = map->IntAttribute("tilewidth");
    tileH = map->IntAttribute("tileheight");

    tinyxml2::XMLElement* tilesetEl = map->FirstChildElement("tileset");
    if (!tilesetEl) { printf("No <tileset> element\n"); return false; }

    const char* source = tilesetEl->Attribute("source");

    tinyxml2::XMLDocument tsxDoc;
    if (tsxDoc.LoadFile(source) != tinyxml2::XML_SUCCESS) {
        printf("Failed to load TSX: %s", source);
        return false;
    }

    tinyxml2::XMLElement* tsxTileset = tsxDoc.FirstChildElement("tileset");
    if (!tsxTileset) { printf("No <tileset> in TSX\n"); return false; }

    tinyxml2::XMLElement* imgEl = tsxTileset->FirstChildElement("image");
    if (!imgEl) { printf("No <image> in TSX\n"); return false; }

    const char* imgSrc = imgEl->Attribute("source");
    if (!imgSrc) { printf("TSX image has no source\n"); return false; }

    size_t len = strlen(imgSrc);
    if (len >= pathSize) {
        printf("tilesetPath buffer too small! Needed: %zu", len + 1);
        return false;
    }
    strcpy_s(tilesetPath, pathSize, imgSrc);

    int li = 0;
    for (tinyxml2::XMLElement* lay = map->FirstChildElement("layer");
        lay && li < 2;
        lay = lay->NextSiblingElement("layer"), ++li)
    {
        tinyxml2::XMLElement* data = lay->FirstChildElement("data");
        if (!data) { printf("Layer %d has no <data>", li); return false; }
        parseCSV(data->GetText(), layerData[li], MAP_W*MAP_H);
    }
    return true;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    char* tsPath = new char[256];
    if (!loadTMX("maps/testMap.tmx", tsPath, 256)) {
        printf("LoadTMX failure");
        window.close();
    }
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    delete[] tsPath;
}