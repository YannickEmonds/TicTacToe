#include "window.h"
#include "game.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <string>
#include <iostream>
#include <algorithm>

Window::Window(const std::size_t width, QWidget *parent)
    : QWidget(parent),
      boardWidth(width),
      board(new Board(width, this))
{
    std::cerr << "Constructing Window.\n";
    // 30 per button + 10 per margin at each side
    QFont font("times", 24);
    QFontMetrics fm(font);
    const QSize textSize = fm.size(Qt::TextSingleLine, "Player 1, it's your turn.");
    restartGameButton = new QPushButton("Restart game", this);
    const std::size_t windowSizeX = std::max(30*boardWidth + 50, static_cast<std::size_t>(textSize.width()));
    const std::size_t windowSizeY {30*boardWidth + 20 + textSize.height() + restartGameButton->height()};
    setFixedSize(windowSizeX, windowSizeY);

    playerPrompt = createLabel(tr("Player 1, it's your turn."));
    QVBoxLayout* layout = new QVBoxLayout();
//    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(playerPrompt);
    layout->addWidget(board, 10); //, Qt::AlignHCenter);
//    layout->setAlignment(board, Qt::AlignHCenter);
//    layout->addSpacing(20);
    layout->addWidget(restartGameButton);
//    layout->setStretch(1, 100);
    setLayout(layout);

    connect(board, SIGNAL (nextTurn(unsigned)), this, SLOT (slotNextTurn(unsigned)));
    connect(board, SIGNAL (gameFinished(unsigned)), this, SLOT (gameWon(unsigned)));
//    connect(restartGameButton, SIGNAL (clicked()), board, SLOT (slotRestartGame()));
    connect(restartGameButton, SIGNAL (clicked()), this, SLOT (slotRestartGame()));
}

QLabel *Window::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}

void Window::resizeBoard(const std::size_t newWidth)
{
    board->resize(newWidth);
}

void Window::slotNextTurn(unsigned playerId)
{
    playerId = (playerId + 1) % 2 + 1;
    const std::string message {"Player " + std::to_string(playerId) + ", it's your turn."};
    playerPrompt->setText(QString::fromStdString(message));
}

void Window::slotRestartGame()
{
    std::cerr << "restart game\n";
    emit signalRestartGame();
//    playerPrompt->setText("Player 1, it's your turn.");
}

void Window::gameWon(const unsigned playerId)
{
    const std::string message {"Player " + std::to_string(playerId+1) + " won. Congratulations!"};
    playerPrompt->setText(QString::fromStdString(message));
}
