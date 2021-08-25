#ifndef GAME_H
#define GAME_H

#include "board.h"

// maybe subclass QApplication here
class Game
{
private:
    Board board;
public:
    Game(const std::size_t width);

    static unsigned getCurrentPlayerId();
    static void checkBoardForWin();
};

#endif // GAME_H
