#include "board/board.hpp"
#include "input/action.hpp"

#include <thread>
#include <chrono>

using namespace std;

int main(void) {
    Board board;

    int mino_queue[] = {0, 1, 2, 3, 4, 5, 6};
    int curr_mino = 0;
    while (1)
    {
        if(!board.has_active_mino()) 
        {
            if (curr_mino >= 7) break;
            if (!board.spawn_mino(curr_mino++)) break;
        }

        if (curr_mino % 2) board.move_mino(Action::RIGHT);
        else board.move_mino(Action::LEFT);
        board.render();
        this_thread::sleep_for(chrono::milliseconds(500));

        board.move_mino(Action::DROP);
        board.render();
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    return 0;
}