#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include <string>

class Square
{
private:

public:
    Square(sf::Font* ifont,int x,int y);
    Square();
    void setvalue(uint64_t ival);
    sf::Text num;
    std::string txt;
    sf::RectangleShape field;
};

class Game
{
private:
    sf::RenderWindow Gamewindow;
    sf::Font font;
    Board gameboard;
    Square squares[SIDE][SIDE];

public:
    Game();
    void render();
    void start();
    void drawgamestate();
    void checkkeys();
};

#endif