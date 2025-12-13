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
	mapData mapData;// инфа по всем тайлам
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