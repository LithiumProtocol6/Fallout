#include <iostream>
#include "Game.h"


int main()
{
    //пока класс делается тут будет временно пусто :(
    Game fallout(600,800,"Fallout");
    fallout.run();
    sf::Texture texture;
    /*
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    */
}