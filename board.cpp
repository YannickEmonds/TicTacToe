#include "board.h"
#include <stdexcept>
#include <numeric>
#include <iostream>


bool Board::stillPlaying() const
{
    return !isFinished;
}

void Board::displayBoard() const
{
    const std::string rowline(4*width -1, '-');
    for (std::size_t row=0; row<width; ++row)
    {
        for (std::size_t col=0; col<width; ++col)
        {
            std::string fieldValue {' '};
            if (boardValues[row*width + col] == -1)
                fieldValue = 'x';
            else if (boardValues[row*width + col] == 1)
                fieldValue = 'o';
            std::cout << ' ' << fieldValue << ' ';
            if (col < width-1)
                std::cout << '|';
            else
                std::cout << '\n';
        }

        if (row < width-1)
            std::cout << rowline << '\n';
    }
}

void Board::setSquare(const std::size_t pos, const unsigned playerId)
{
    if (pos < 0 || pos >= boardValues.size())
    {
        throw std::out_of_range("Invalid position. Try again.\n");
    }

    if (playerId != 0 && playerId != 1)
    {
        std::cerr << "Invalid player ID. There must be something wrong.\n";
        return;
    }

    if (boardValues[pos] != 0)
    {
        throw std::logic_error("Position is already taken. Try again.\n");
    }

    int valueToSet = playerId == 0 ? -1 : 1;
    boardValues[pos] = valueToSet;
}

void Board::checkForWin()
{
    isFinished = winningRow() || winningColumn() || winningDiagonal();
}

bool Board::winningRow() const
{
    for (std::size_t i=0; i<width; ++i)
    {
        int rowValue = std::accumulate(boardValues.begin() + i*width,
                                       boardValues.begin() + (i+1)*width,
                                       0);
        if (rowValue == width)
        {
            std::cout << "Player 2 wins! Congratulation!\n";
            return true;
        }
        else if (rowValue == -width)
        {
            std::cout << "Player 1 wins! Congratulation!\n";
            return true;
        }
    }

    return false;
}

bool Board::winningColumn() const
{
    for (std::size_t i=0; i<width; ++i)
    {
        int colValue {0};
        // TODO: optimize!
        for (std::size_t j=0; j<width; ++j)
        {
            colValue += boardValues[j*width + i];
        }

        if (colValue == width)
        {
            std::cout << "Player 2 wins! Congratulation!\n";
            return true;
        }
        else if (colValue == -width)
        {
            std::cout << "Player 1 wins! Congratulation!\n";
            return true;
        }
    }

    return false;
}

bool Board::winningDiagonal() const
{
    int diagSum1 {0};
    int diagSum2 {0};
    for (std::size_t i=0; i<width; ++i)
    {
        diagSum1 += boardValues[i*width + i];
        diagSum2 += boardValues[(width-1-i)*width + i];
    }

    if (diagSum1 == width || diagSum2 == width)
    {
        std::cout << "Player 2 wins! Congratulation!\n";
        return true;
    }
    else if (diagSum1 == -width || diagSum2 == -width)
    {
        std::cout << "Player 1 wins! Congratulation!\n";
        return true;
    }

    return false;
}
