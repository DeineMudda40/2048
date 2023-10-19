#include "../include/Board.hpp"

Board::Board() : generator(rd())
{
    for (int x = 0; x < SIDE; x++)
    {
        for (int y = 0; y < SIDE; y++)
        {
            this->mybrett.field[x][y] = 0;
            this->freefields.push_back(x * SIDE + y);
        }
    }
}

void Board::printboard()
{
    for (int y = 0; y < SIDE; y++)
    {
        for (int x = 0; x < SIDE; x++)
        {
            std::cout << this->mybrett.field[x][y] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------------------------------" << std::endl;
}

void Board::addrandom()
{
    std::shuffle(freefields.begin(), freefields.end(), generator);
    for (int i = 0; i < freefields.size(); i++)
    {
        std::cout << freefields[i] << " ";
    }
    std::cout << std::endl;
    uint32_t val = freefields.back();
    freefields.pop_back();
    int x = val / SIDE;
    int y = val % SIDE;
    mybrett.field[x][y] = 2;
}

void Board::shift(uint64_t ifield[SIDE][SIDE], Directions input)
{
    int nothing = 0;
    switch (input)
    {
    case UP:
        for (int x = 0; x < SIDE; x++)
        {
            shiftrowup(ifield[x]);
            mergerowup(ifield[x]);
            nothing += shiftrowup(ifield[x]);
        }
        break;
    case DOWN:
        for (int x = 0; x < SIDE; x++)
        {
            shiftrowdown(ifield[x]);
            mergerowdown(ifield[x]);
            nothing += shiftrowdown(ifield[x]);
        }
        break;
    case LEFT:
        for (int y = 0; y < SIDE; y++)
        {
            uint64_t vecrow[SIDE];
            for (int x = 0; x < SIDE; x++)
            {
                vecrow[x] = mybrett.field[x][y];
            }
            shiftrowup(vecrow);
            mergerowup(vecrow);
            nothing += shiftrowup(vecrow);
            for (int x = 0; x < SIDE; x++)
            {
                mybrett.field[x][y] = vecrow[x];
            }
        }
        break;
    case RIGHT:
        for (int y = 0; y < SIDE; y++)
        {
            uint64_t vecrow[SIDE];
            for (int x = 0; x < SIDE; x++)
            {
                vecrow[x] = mybrett.field[x][y];
            }
            shiftrowdown(vecrow);
            mergerowdown(vecrow);
            nothing += shiftrowdown(vecrow);
            for (int x = 0; x < SIDE; x++)
            {
                mybrett.field[x][y] = vecrow[x];
            }
        }
        break;
    default:
        break;
    }
    if (nothing != 0)
    {
        std::cout << "Nichts!" << std::endl;
    }
    else
    {
        calcfreespace();
        addrandom();
    }
}

int Board::shiftrowup(uint64_t *row)
{
    int index = 0;
    for (int i = 0; i < SIDE; ++i)
    {
        if (row[i] != 0)
        {
            row[index++] = row[i];
        }
    }

    for (int i = index; i < SIDE; ++i)
    {
        row[i] = 0;
    }
    if (index == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Board::mergerowup(uint64_t *row)
{

    for (int i = 0; i < SIDE - 1; ++i)
    {
        if (row[i] == row[i + 1])
        {
            // Merge adjacent equal elements
            row[i] *= 2;
            row[i + 1] = 0;
            // Optionally, you can update the score here
        }
    }
}

int Board::shiftrowdown(uint64_t *row)
{
    int index = SIDE - 1;
    for (int i = SIDE - 1; i >= 0; --i)
    {
        if (row[i] != 0)
        {
            row[index--] = row[i];
        }
    }

    for (int i = index; i >= 0; --i)
    {
        row[i] = 0;
    }

    if (index == (SIDE - 1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Board::mergerowdown(uint64_t *row)
{

    for (int i = SIDE - 1; i > 0; --i)
    {
        if (row[i] == row[i - 1])
        {
            // Merge adjacent equal elements
            row[i] *= 2;
            row[i - 1] = 0;
            // Optionally, you can update the score here
        }
    }
}

void Board::calcfreespace()
{
    this->freefields.clear();
    for (int x = 0; x < SIDE; x++)
    {
        for (int y = 0; y < SIDE; y++)
        {
            if (mybrett.field[x][y] == 0)
            {
                this->freefields.push_back(x * SIDE + y);
            }
        }
    }
}

brett *Board::getfield()
{
    return &mybrett;
}

void Board::shiftup()
{
    this->shift(mybrett.field, RIGHT);
}