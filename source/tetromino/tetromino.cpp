#include "tetromino/tetromino.hpp"

using namespace std;

Tetromino::Tetromino() : mino_type(0), rotation(0), pos(make_pair(0, 0)) {}

void Tetromino::set_mino(int type)
{
    mino_type = type;
}

void Tetromino::rotate(int rot) 
{
    rotation = rot;
}

void Tetromino::move(int dir) 
{
    
}

pair<int, int> Tetromino::get_pos()
{
    return pos;
}