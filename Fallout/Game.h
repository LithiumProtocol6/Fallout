#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "MapLoad.h"

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

};