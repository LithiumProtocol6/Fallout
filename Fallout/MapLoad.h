#pragma once
#include "tinyxml2.h"
#include <iostream>
class mapData {
	int** tiles;//инфа по расположению тайлов
	int tileW;//ширина тайла
	int tileH;//высота тайла
	int* offsetX;//сдвиг слоев по X коорд
	int* offsetY;//сдвиг слоев по Y коорд
	int* layerW;//ширина слоев в тайлах
	int* layerH;//высота слоев в тайлах
	int layersCount;//кол-во слоев
public:
	mapData();
	~mapData();
	void parseCSV(const char* text, int* dest, int maxCount);//парсинг CSV
	bool loadTMX(const char* file, char* tilesetPath, int pathSize);//загрузка данных по карте их TMX файла
	int** getTilesData();
	int getTileWidth();
	int getTileHeight(); 
	int* getOffsetsX();
	int* getOffsetsY();
	int* getLayersWidth();
	int* getLayersHeight();
	int getLayersCount();
};