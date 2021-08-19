#include <iostream>
#include "board.h"

int main()
{
    Board board;

    int playerId {0};
    int pos {0};
    while (board.stillPlaying())
    {
        std::cout << "Player " << playerId+1 << ", it's your turn.\n";
        std::cin >> pos;
        try
        {
            board.setSquare(pos, playerId);
        }
        catch (std::out_of_range& e)
        {
            e.what();
        }
        catch (std::logic_error& e)
        {
            e.what();
        }

        board.checkForWin();

        board.displayBoard();
        playerId = (playerId+1) % 2;
    }

    return 0;
}
