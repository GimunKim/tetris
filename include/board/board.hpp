#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <chrono>
#include <iostream>
#include "tetromino/tetromino.hpp"

class Board
{
    private:
    Tetromino* active_mino;
    mino game_board[22];

    public:
    Board();
    bool can_move();
    void move(int cmd);
    bool has_active_mino();
    void spawn_mino(int type);
    void update_board();
    void draw_board();
};

#endif