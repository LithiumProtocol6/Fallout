#pragma once
#include "tinyxml2.h"
#include <iostream>
#include <SFML/Graphics.hpp>
class mapData {
	int** tiles;//инфа по расположению тайлов
	int tileW;//ширина тайла
	int tileH;//высота тайла
	int* offsetX;//сдвиг слоев по X коорд
	int* offsetY;//сдвиг слоев по Y коорд
	int* layerW;//ширина слоев в тайлах
	int* layerH;//высота слоев в тайлах
	int layersCount;//кол-во слоев
	int tilesPerRow;//сколько тайлов в строке тайлсета
	sf::Texture tileset;//текстурка тайлсета
public:
	mapData();
	~mapData();
	void parseCSV(const  char* text, int* dest, int maxCount);//парсинг CSV
	bool loadTMX(const  char* file);//загрузка данных по карте их TMX файла
	int** getTilesData();
	int getTileWidth();
	int getTileHeight(); 
	const int* getOffsetsX();
	const int* getOffsetsY();
	const int* getLayersWidth();
	const int* getLayersHeight();
	int getLayersCount();
	int getTilesPerRow();
	sf::Texture& getTileset();
};