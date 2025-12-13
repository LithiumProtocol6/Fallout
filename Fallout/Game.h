#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "tinyxml2.h"
#include <SFML/Network.hpp>
#include <iostream>
class Game {
private:

	//Вся база по окну
    sf::RenderWindow* window;// само окно
    sf:: VideoMode videoMode;//настройки разрешения окна итд
	//Карта
	//тут использовал дефайны просто по приколу, не хочу добавлять кучу переменных
	#define MAP_W 64      // максимальная ширина карты в тайлах
	#define MAP_H 64      // максимальная высота
	#define LAYERS 2      // кол-во слоев !!! ИЗМЕНИТЬ ЕСЛИ БУДЕТ ИЗМЕНЕНО КОЛ-ВО СЛОЕВ !!!
	int mapWidth = 0, mapHeight = 0, tileW = 0, tileH = 0;//Размеры карты в тайлах и для тайлов
	int layerData[LAYERS][MAP_W * MAP_H]; // это инфа по всем тайлам
    void parseCSV(const char* text, int* dest, int maxCount);//парсинг CSV
	bool loadTMX(const char* file, char* tilesetPath, int pathSize);//загрузка данных по карте их TMX файла
	
	void initWindow(int h, int w, const char* name);//инициализация окна
	void initVar();//Все парамтеры в 0
public:
	//Конструкторы/деструкторы
	Game();
	Game(int w,int h,const char* name);
	~Game();
	//Геттеры
	sf::RenderWindow& getWindow() {
		return *window;
	}
	const bool isOpen() {
		return window->isOpen();
	}
	//Функции
	void update();
	void render();

};