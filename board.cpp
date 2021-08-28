#include "board.h"
#include <stdexcept>
#include <numeric>
#include <iostream>
#include <QString>


void initializeButtons(Board* board, const int buttonSize = 30)
{
    const std::size_t width = board->getWidth();
    for (std::size_t i=0; i<width; ++i)
    {
        std::size_t x {i*buttonSize};
        for (std::size_t j=0; j<width; ++j)
        {
            std::size_t y {j*buttonSize};
            QPushButton* newButton = new QPushButton("", board);
            newButton->setGeometry(x, y, buttonSize, buttonSize);
            Board::connect(newButton, SIGNAL (clicked()), board, SLOT (slotButtonClicked()));
            board->addButton(newButton);
        }
    }
}


Board::Board(const std::size_t w, QWidget *parent)
    : QFrame(parent),
      width(w),
      boardValues(w*w, 0)
{
    std::cerr << "Constructing Board.\n";
    initializeButtons(this, 30);
}

void Board::addButton(QPushButton *newButton)
{
    buttons.append(newButton);
}

QSize Board::sizeHint() const
{
    return QSize(width*50, width*50);
}

QSize Board::minimumSizeHint() const
{
    return QSize(width*30, width*30);
}

void Board::slotButtonClicked()
{
        QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
        QString playerMark = currentPlayerId == 0 ? "x" : "o";
        clickedButton->setText(playerMark);
        clickedButton->setEnabled(false);

        const int pos = buttons.indexOf(clickedButton);
        const int valueToSet = currentPlayerId == 0 ? -1 : 1;
        boardValues[pos] = valueToSet;

        checkForWin();
        currentPlayerId = (currentPlayerId + 1) % 2;
}

void Board::slotRestartGame()
{
    for (std::size_t i=0; i<width*width; ++i)
    {
        boardValues[i] = 0;
        buttons[i]->setText("");
        buttons[i]->setEnabled(true);
        currentPlayerId = 0;
    }
}

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
    if (isFinished)
    {
        emit gameFinished(currentPlayerId);
        for (auto button : buttons)
        {
            button->setEnabled(false);
        }
    }
    else
    {
        emit nextTurn(currentPlayerId);
    }
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

std::size_t Board::getWidth() const
{
    return width;
}

void Board::resize(const std::size_t newWidth)
{
    for (auto button : buttons)
    {
        delete button;
    }
    buttons.resize(0);
    width = newWidth;
    boardValues.resize(width*width, 0);
    for (int &val : boardValues)
    {
        val = 0;
    }
    initializeButtons(this);
    std::cerr << buttons.size() << ' ' << boardValues.size() << '\n';
    currentPlayerId = 0;
    isFinished = false;
}
