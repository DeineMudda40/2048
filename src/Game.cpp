#include "../include/Game.hpp"

Game::Game() : Gamewindow{sf::VideoMode(465, 465), "Spiel"}
{
    this->font.loadFromFile("sansation.ttf");

    for (int x = 0; x < SIDE; x++)
    {
        for (int y = 0; y < SIDE; y++)
        {
            squares[x][y] = Square(&this->font, x, y);
        }
    }
}

void Game::start()
{
    this->gameboard.addrandom();
    this->gameboard.addrandom();
    while (Gamewindow.isOpen())
    {
        for (auto event = sf::Event{}; Gamewindow.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                Gamewindow.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                this->checkkeys();
            }
        }

        this->render();
    }
}

void Game::render()
{
    this->Gamewindow.clear(sf::Color(50, 200, 50));
    this->drawgamestate();
    this->Gamewindow.display();
}

void Game::drawgamestate()
{
    brett *tempboard = gameboard.getfield();
    for (int x = 0; x < SIDE; x++)
    {
        for (int y = 0; y < SIDE; y++)
        {
            squares[x][y].setvalue(tempboard->field[x][y]);
            this->Gamewindow.draw(squares[x][y].field);
            this->Gamewindow.draw(squares[x][y].num);
        }
    }
}

void Game::checkkeys()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->gameboard.shift(this->gameboard.getfield()->field, Board::LEFT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->gameboard.shift(this->gameboard.getfield()->field, Board::RIGHT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->gameboard.shift(this->gameboard.getfield()->field, Board::UP);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->gameboard.shift(this->gameboard.getfield()->field, Board::DOWN);
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

Square::Square()
{
}

Square::Square(sf::Font *ifont, int x, int y) : field(sf::Vector2f(100, 100)), num()
{
    num.setFont(*ifont);
    num.setCharacterSize(24);
    num.setFillColor(sf::Color::Black);
    field.setPosition(sf::Vector2f(25 + x * 100 + x * 5, 25 + y * 100 + y * 5));

    sf::FloatRect textBounds = num.getLocalBounds();

    // Calculate the position to center the text inside the rectangle
    float centerX = field.getPosition().x + (field.getSize().x - textBounds.width) / 2;
    float centerY = field.getPosition().y + (field.getSize().y - textBounds.height) / 2;

    num.setPosition(centerX, centerY);

    field.setFillColor(sf::Color::Yellow);
    num.setColor(sf::Color::Black);
}

void Square::setvalue(uint64_t ival)
{
    this->num.setString(std::to_string(ival));
}