#include "board/board.hpp"
#include "input/action.hpp"

#include <thread>
#include <chrono>

using namespace std;

int main(void) {
    Board board;

    int mino_queue[] = {0, 1, 2, 3, 4, 5, 6};
    int curr_mino = 6;
    while (curr_mino < 7)
    {
        if(!board.has_active_mino()) board.spawn_mino(curr_mino++);

        board.move_mino(Action::ROTATE_CW);
        board.render();
        this_thread::sleep_for(chrono::milliseconds(500));

        board.move_mino(Action::DROP);
        board.render();
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    return 0;
}