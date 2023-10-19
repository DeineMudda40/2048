#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#define SIDE 4

class brett
{
public:
    uint64_t field[SIDE][SIDE];
};

class Board
{
private:
    brett mybrett;

public:
    Board();
    std::vector<uint32_t> freefields;
    enum Directions
    {
        UP,
        DOWN,
        RIGHT,
        LEFT
    };
    void printboard();
    void shift(uint64_t ifield[SIDE][SIDE], Directions input);
    void addrandom();
    void shiftup();
    int shiftrowup(uint64_t *row);
    void mergerowup(uint64_t *row);
    int shiftrowdown(uint64_t *row);
    void mergerowdown(uint64_t *row);
    void calcfreespace();
    brett* getfield();

    std::random_device rd;
    std::default_random_engine generator;
};

#endif