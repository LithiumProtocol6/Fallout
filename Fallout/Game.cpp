#include "Game.h"
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
Game::Game()
{
    initVar();
    initWindow(800,800,"Game");
}
Game::Game(int w, int h, const char* name) 
{
    initVar();
    initWindow(w, h, name);
}
Game:: ~Game()
{
    delete window;
}
