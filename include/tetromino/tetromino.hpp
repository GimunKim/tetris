#ifndef __TETROMINO_HPP__
#define __TETROMINO_HPP__

#include <cstdint>
#include <cstddef>
#include <utility>

typedef std::uint16_t mino;

extern mino *TETROMINO[7];

class Tetromino
{
    private:
    int mino_type;
    int rotation;
    std::pair<int, int> pos;

    public:
    Tetromino();
    void set_mino(int type);
    void rotate(int rot);
    void move(int dir);
    std::pair<int, int> get_pos();
};

#endif