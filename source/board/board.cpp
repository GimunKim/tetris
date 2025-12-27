#include "board/board.hpp"
#include "input/action.hpp"

using namespace std;

static uint16_t left_edge = 1u << 9;

static int dr[6] = {0, 0, 1, 0, 0, 0};
static int dc[6] = {-1, 1, 0, 0, 0, 0};

Board::Board()
{
    is_mino_active = false;

    for (size_t i = 0; i < 22; ++i)
    {
        game_board[i] = 0;
    }
}

void Board::clear_mino_()
{
    auto [pos_r, pos_c] = active_mino.get_pos();
    uint16_t mino_mask = 0b1111000000000000;
    uint16_t mino_shape = active_mino.get_shape();
    uint16_t mino_row;

    for (int i = 3; i >= 0; --i, mino_mask >>= 4, pos_r++)
    {
        mino_row = ~(mino_mask & mino_shape);
        mino_row >>= i * 4;
        mino_row <<= (6 - pos_c);
        game_board[pos_r] &= mino_row;
    }
}

/**
 * @brief board 상의 mino가 active 상태인지 반환
 * @return mino가 active이면 true 반환
 */
bool Board::has_active_mino()
{
    return is_mino_active;
}

/**
 * @brief 테트로미노 충돌 판정
 * @return 충돌 없는 경우 true 반환
 */
void Board::move_mino(int cmd)
{   
    if (!is_mino_active) return;

    bool can_go = true;
    int new_r, new_c;
    auto [curr_r, curr_c] = active_mino.get_pos();
    int curr_rot = active_mino.get_rotation();
    int new_rot;

    uint16_t mino_mask = 0b1111000000000000;
    uint16_t mino_shape;
    uint16_t mino_row;

    new_r = curr_r + dr[cmd], new_c = curr_c + dc[cmd];

    if (cmd == Action::ROTATE_CW) new_rot = curr_rot + 1;
    else if (cmd == Action::ROTATE_CCW) new_rot = curr_rot - 1;
    else new_rot = curr_rot;

    if (new_rot == -1) new_rot = 3;
    new_rot %= 4;

    mino_shape = active_mino.get_shape(new_rot);

    if (new_c < 0 || new_c >= 10) return;

    for (int i = 3, r = new_r; i >= 0; --i, mino_mask >>= 4, r++)
    {
        mino_row = mino_mask & mino_shape;
        mino_row >>= i * 4;
        mino_row <<= (6 - new_c);
        if ((r >= 22 && mino_row) || game_board[r] & mino_row) 
        {
            can_go = false;
            break;
        }
    }

    if (can_go) 
    {
        active_mino.set_pos(new_r, new_c);
        active_mino.set_rotation(new_rot);
    }
    else
    {
        update_board();
        is_mino_active = false;
    }
}

/**
 * @brief 새 테트로미노를 스폰
 * @param type 테트로미노의 타입
 */
void Board::spawn_mino(int type)
{
    active_mino.init_mino(type);
    is_mino_active = true;
}

/**
 * @brief 보드 상태를 업데이트
 */
void Board::update_board()
{
    if (!is_mino_active) return;

    auto [pos_r, pos_c] = active_mino.get_pos();
    uint16_t mino_mask = 0b1111000000000000;
    uint16_t mino_shape = active_mino.get_shape();
    uint16_t mino_row;

    for (int i = 3; i >= 0; --i, mino_mask >>= 4, pos_r++)
    {
        mino_row = mino_mask & mino_shape;
        mino_row >>= i * 4;
        mino_row <<= (6 - pos_c);
        game_board[pos_r] |= mino_row;
    }
}

/**
 * @brief 게임 보드 출력
 */
void Board::draw_board()
{
    static bool called = false;

    if (called) std::cout << "\x1b[20A";
    else called = true;

    for (int r = 2; r < 22; ++r) 
    {
        for (uint16_t mask = left_edge; mask > 0u; mask >>= 1)
        {
            cout << ((game_board[r] & mask) ? "■" : "□");
        }
        cout << endl;
    }
    cout << flush;
}

/**
 * @brief 게임 보드 위에 테트로미노를 출력 
 */
void Board::draw_mino() 
{
    if (is_mino_active)
    {
        std::cout << "\x1b[20A";
        auto [pos_r, pos_c] = active_mino.get_pos();
        uint16_t mino_mask = 0b1111000000000000;
        uint16_t mino_shape = active_mino.get_shape();
        uint16_t mino_row;

        for (int r = 2; r < 22; ++r) 
        {
            if (r >= pos_r && r < pos_r + 4)
            {
                mino_row = (mino_mask >> (r - pos_r) * 4) & mino_shape;
                mino_row >>= (3 - (r - pos_r)) * 4;
                mino_row <<= (6 - pos_c);

                for (uint16_t mask = left_edge; mask > 0u; mask >>= 1)
                {
                    cout << ((mino_row & mask) ? "■" : "\x1b[C");
                }
            }
            cout << endl;
        }
        cout << flush;
    }
}

/**
 * @brief 게임 화면 렌더링
 */
void Board::render()
{
    draw_board();
    draw_mino();
}