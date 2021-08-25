#include "game.h"

Game::Game(const std::size_t width) : board(width)
{

}

static unsigned Game::getCurrentPlayerId()
{

}

static void Game::checkBoardForWin()
{
    board.checkForWin();
}
