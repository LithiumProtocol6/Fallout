#include "Game.h"
//только сейчас заметил, что компилятор переносит в .cpp с другим стилем {} чем у меня, так что сделал все как у него
void Game:: initWindow(int w, int h, const char* name)
{
    videoMode.size.x = w;
    videoMode.size.y = h;
    window = new sf::RenderWindow(videoMode,name);
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(false);
    camera.setSize(window->getDefaultView().getSize() * cameraScale);
}
void Game::initVar()
{
    window = nullptr;
}

bool Game::initMap(const std::string& filename)
{
    if (!map.loadTMX(filename.c_str())) {
        std::cerr << "Ошибка загрузки карты: " << filename << std::endl;
        return false;
    }
    else {
        std::cout << "Карта успешно загружена!" << std::endl;
        return true;
    }
}

void Game::renderMap() {
    sf::Sprite tile(map.getTileset());
    for (int li = 0; li < map.getLayersCount(); ++li) {//отображение карты
        for (int y = 0; y < map.getLayersHeight()[li]; ++y) {
            for (int x = 0; x < map.getLayersWidth()[li]; ++x) {
                int gid = map.getTilesData()[li][y * map.getLayersWidth()[li] + x];
                if (gid == 0) continue;
                gid -= 1;
                int srcX = (gid % map.getTilesPerRow()) * map.getTileWidth();
                int srcY = (gid / map.getTilesPerRow()) * map.getTileHeight();
                float screenX = ((x - y) * (map.getTileWidth())) + map.getOffsetsX()[li]*3.5;
                float screenY = ((x + y) * (map.getTileHeight())) / 2.0f + map.getOffsetsY()[li]*1.75f;
                sf::IntRect src({ srcX,srcY }, { map.getTileWidth(), map.getTileHeight() });
                tile.setTextureRect(src);
                tile.setScale({ (float)map.getTileWidth()/15.0f, (float)map.getTileHeight()/15.0f });
                tile.setPosition({ screenX, screenY});
                window->draw(tile);
                /*
                for (int i = 0; i < pathSize; i++) {//остатки старого кода, скоро переделаю
                    if (x == path[0][i] && y == path[1][i]) {
                        SDL_Texture* pointed = IMG_LoadTexture(renderer, "map/Pointed.png");
                        SDL_RenderTexture(renderer, pointed, NULL, &dst);
                        SDL_DestroyTexture(pointed);
                    }
                }
                */
            }
        }
    }
}
void Game:: zoom(float delta)
{
    cameraScale += delta;

    if (cameraScale < 0.3f) cameraScale = 0.3f;
    if (cameraScale > 3.0f) cameraScale = 3.0f;

    camera.setSize( window->getDefaultView().getSize() * cameraScale);
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
    if (window) { delete window; std::cout << "window deleted\n"; }

}

sf::RenderWindow& Game::getWindow() 
{
    return *window;
}

const bool Game::isOpen()
{
    return window->isOpen();
}

mapData& Game::getMap() //чтобы кучу геттеров не прописывать, для этого изменила имя переменной
{
    return map;
}
void Game::setMaps(std::string* _maps,int _size) {
    mapSize = _size;
    maps = new std::string[mapSize];
    for (int i = 0; i < mapSize; i++) maps = _maps;
}
void Game::update()
{
    if (newMap) {
        initMap(maps[currentMap]);
        isAtMap = true;
        newMap = false;
    }
    while (const std::optional ev = window->pollEvent()) {
        if (ev->is<sf::Event::Closed>()) {window->close();}//закрытие окна если нажат крестик (если не сделать эту функцию то из окна нельзя будет выйти без крестика хех)
        else if (const auto* keyPressed = ev->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scan::Escape) {window->close();}//закрытие окна если нажать Escape
            if (keyPressed->scancode == sf::Keyboard::Scan::W) {camera.move({ 0,-25 });}//передвижение камеры
            if (keyPressed->scancode == sf::Keyboard::Scan::A) {camera.move({ -25,0 });}
            if (keyPressed->scancode == sf::Keyboard::Scan::S) {camera.move({ 0,25 });}
            if (keyPressed->scancode == sf::Keyboard::Scan::D) {camera.move({ 25,0 });}
            if (keyPressed->scancode == sf::Keyboard::Scan::Space) {
                if (currentMap== 0) { currentMap = 1; }
                else currentMap = 0;
                newMap = true;
            }
        }
        if (ev->is<sf::Event::MouseWheelScrolled>()) {
            zoom(-0.5f*ev->getIf<sf::Event::MouseWheelScrolled>()->delta);
            /*
            if (const auto* keyPressed = ev->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scan::LShift) {
                    zoom(-0.5f * ev->getIf<sf::Event::MouseWheelScrolled>()->delta);
                }
            }
            */
        }//зум камеры на колесико мышки
    }
}

void Game::render()
{
    window->clear();
    if (isAtMap) renderMap();
    window->setView(camera);
    window->display();
}

void Game::run()
{
    while (window->isOpen())
    {
        update();
        render();
    }
}

