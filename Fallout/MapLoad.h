#pragma once
#include "tinyxml2.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
class mapData {
	std::vector <std::vector<int>> tiles;//инфа по расположению тайлов
	int tileW;//ширина тайла
	int tileH;//высота тайла
	std::vector<int> offsetX;//сдвиг слоев по X коорд
	std::vector<int> offsetY;//сдвиг слоев по Y коорд
	std::vector<int> layerW;//ширина слоев в тайлах
	std::vector<int> layerH;//высота слоев в тайлах
	int layersCount;//кол-во слоев
	int tilesPerRow;//сколько тайлов в строке тайлсета
	sf::Texture tileset;//текстурка тайлсета
public:
	mapData();
	~mapData();
	void parseCSV(const char* text, std::vector<int>& dest, int maxCount);//парсинг CSV
	bool loadTMX(std::string file);//загрузка данных по карте их TMX файла
	std::vector<std::vector<int>> getTilesData();
	int getTileWidth();
	int getTileHeight(); 
	const std::vector<int> getOffsetsX();
	const std::vector<int> getOffsetsY();
	const std::vector<int> getLayersWidth();
	const std::vector<int> getLayersHeight();
	int getLayersCount();
	int getTilesPerRow();
	sf::Texture& getTileset();
};