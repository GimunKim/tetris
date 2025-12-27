#ifndef __TETROMINO_HPP__
#define __TETROMINO_HPP__

#include <cstdint>



class Tetromino
{
    private:
    int shape[4][4][4];
    int rotation;

    public:
    Tetromino(unsigned int block_type);
    void rotate(int rot);
};

#endif