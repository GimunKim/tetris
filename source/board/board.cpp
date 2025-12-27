#include "board/board.hpp"

using namespace std;

static uint16_t left_edge = 1u << 9;

Board::Board()
{
    for (size_t i = 0; i < 22; ++i)
    {
        game_board[i] = 0;
    }
}

bool Board::can_move()
{

}

void Board::spawn_mino(int type)
{
    
}

void Board::update_board()
{
    if (active_mino == nullptr) return;

    auto [pos_r, pos_c] = active_mino->get_pos();

    uint16_t mask = 0b1111000000000000;
    for (int i = 0; i < 4; ++i) {

    }
}

/**
 * @brief 테스트용 임시 함수
 */
void Board::draw_board()
{
    static bool called = false;
    if (called) std::cout << "\x1b[22A";
    else called = true;

    cout << "==========" << endl;
    for (int r = 2; r < 22; ++r) 
    {
        for (uint16_t mask = left_edge; mask > 0u; mask >>= 1)
        {
            cout << ((game_board[r] & mask) ? "■" : "□");
        }
        cout << endl;
    }
    cout << "==========" << endl << flush;
}