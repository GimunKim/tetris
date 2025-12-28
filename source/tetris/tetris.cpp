#include "board/board.hpp"
#include "input/action.hpp"
#include "input/console_input.hpp"
#include "game_rule/game_rule.hpp"

#include <thread>
#include <chrono>

using namespace std;

int main(void) {
    Board board;
    Input input;
    RuleEngine rule;

    int mino_queue[] = {0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6};
    int curr_mino = 0;
    int action;
    int score = 0, new_score;

    board.render();
    cout << "SCORE: " << score << "\r";

    while (1)
    {
        if(!board.has_active_mino()) 
        {
            if (curr_mino >= 14) break;
            if (!board.spawn_mino(mino_queue[curr_mino++])) break;
        }
        
        action = input.console_input();

        if (action != -1) 
        {
            board.move_mino(action);
            board.render();
        }
        
        new_score = rule.update_score(board);
        if (new_score) 
        {
            score += new_score;
            board.render();
            cout << "SCORE: " << score << "\r";
        }
    }

    return 0;
}