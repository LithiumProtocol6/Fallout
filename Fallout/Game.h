#pragma once
#include <iostream>
#include "MapLoad.h"
#include "Player.h"
class Game {
private:

	//Вся база по окну
    sf::RenderWindow* window;// само окно
    sf:: VideoMode videoMode;//настройки разрешения окна итд
	//Карта
	mapData map;// инфа по всем тайлам
	void initWindow(int h, int w, const char* name);//инициализация окна
	void initVar();//Все параметры в 0
	void initMap(const std::string& filename);//инициализация карты
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
	
	mapData& getMap() //чтобы кучу геттеров не прописывать, для этого изменила имя переменной
	{
		return map; 
	}

	//Функции
	void update();
	void render();
	void run();

};