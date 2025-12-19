#include "Game.h"
#include "MapLoad.h"

//только сейчас заметил, что компилятор переносит в .cpp с другим стилем {} чем у меня, так что сделал все как у него
void Game:: initWindow(int w, int h, const char* name)
{
    videoMode.size.x = w;
    videoMode.size.y = h;
    window = new sf::RenderWindow(videoMode,name);
}
void Game::initVar()
{
    window = nullptr;
}

void Game::initMap(const std::string& filename) {
    char tilesetPath[256]; // буфер для пути к тайлсету, если нужен
    if (!map.loadTMX(filename.c_str(), tilesetPath, sizeof(tilesetPath))) {
        std::cerr << "Ошибка загрузки карты: " << filename << std::endl;
    }
    else {
        std::cout << "Карта успешно загружена!" << std::endl;
    }
}
Game::Game()
{
    initVar();
    initWindow(800,800,"Game");
}
Game::Game(int w, int h, const char* name) 
{
    initVar();
    initWindow(w, h, name);
    initMap();
}
Game:: ~Game()
{
    delete window;
}

