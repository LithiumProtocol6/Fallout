#pragma once
#include <iostream>
#include "MapLoad.h"
#include "Entity.h"
class Game {
private:

	//Вся база по окну
    sf::RenderWindow* window;// само окно
    sf:: VideoMode videoMode;//настройки разрешения окна итд
	void initWindow(int h, int w, const char* name);//инициализация окна
	void initVar();//Все параметры в 0
	//Карта
	mapData map;// инфа по всем тайлам
	bool initMap(const std::string& filename);//инициализация карты
	void renderMap();//рендер карты
	bool isAtMap=false;//отрисовывать ли карту
	bool newMap=true;
	std::vector<std::string> maps;
	int currentMap;
	int mapSize;
	//Камера
	float cameraScale = 1.0;//приближение/отдаление камеры
	sf::View camera;//камера
	void zoom(float delta);//зумить камеру
	//Игрок
	Entity player = Entity(20, 20, 100, 100, 10, 10, 50, false);
	//Все сущности
	std::vector<std::vector<Entity>> entities;
	int entitySize=0;
	std::vector<int> entitiesSize;
	void initEntities(std::vector<Entity> _entities,int _entitySize,int i);
	void initAllEntities(int _entitySize);
public:
	//Конструкторы/деструкторы
	Game();
	Game(int w,int h,const char* name);
	~Game();
	//Геттеры
	sf::RenderWindow& getWindow();
	const bool isOpen();
	
	mapData& getMap();

	//Функции
	void setMaps(std::vector<std::string> _maps, int _size);
	void setEntities(std::vector<std::vector<Entity>> _entities, std::vector<int> _entitiesSize, int _entitySize);
	void update();
	void render();
	void run();

};