#include "window.h"
#include "game.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <string>
#include <iostream>
#include <algorithm>

std::size_t initMaximumPromptWidth()
{
    QFont font;
    QFontMetrics fm(font);
    const QSize textSize = fm.size(Qt::TextSingleLine, "Player 1 won. Congratulations!");
    return textSize.width();
}

Window::Window(const std::size_t width, QWidget *parent)
    : QWidget(parent),
      maximumPromptWidth(initMaximumPromptWidth()),
      boardWidth(width),
      board(new Board(width, this))
{
    std::cerr << "Constructing Window.\n";
    restartGameButton = new QPushButton("Restart game", this);
    playerPrompt = createLabel(tr("Player 1, it's your turn."));
    const std::size_t windowSizeX = std::max(30*boardWidth, maximumPromptWidth) + 22;
    const std::size_t windowSizeY {30*boardWidth + 22 + playerPrompt->height() + restartGameButton->height()};
    resize(windowSizeX, windowSizeY);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(10);
    layout->addWidget(playerPrompt);
    layout->addWidget(board, 0, Qt::AlignHCenter);
    layout->addWidget(restartGameButton);
    setLayout(layout);

    connect(board, SIGNAL (nextTurn(unsigned)), this, SLOT (slotNextTurn(unsigned)));
    connect(board, SIGNAL (gameFinished(unsigned)), this, SLOT (gameWon(unsigned)));
    connect(restartGameButton, SIGNAL (clicked()), this, SLOT (slotRestartGame()));
}

QLabel *Window::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    QFont font;
    QFontMetrics fm(font);
    const QSize textSize = fm.size(Qt::TextSingleLine, text);
    label->setFont(font);
    label->resize(textSize);
    return label;
}

void Window::resizeBoard(const std::size_t newWidth)
{
    board->resize(newWidth);
    board->updateGeometry();
    boardWidth = newWidth;
    std::cerr << playerPrompt->width() << ' ' << playerPrompt->height() << ' ' << restartGameButton->height() << '\n';

    const std::size_t windowSizeX = std::max(30*boardWidth, maximumPromptWidth) + 22;
    const std::size_t windowSizeY {30*boardWidth + 22 + playerPrompt->height() + restartGameButton->height() + 20};
    std::cerr << windowSizeX << ' ' << windowSizeY << '\n';
    setFixedSize(windowSizeX, windowSizeY);
    updateGeometry();
}

QSize Window::sizeHint() const
{
    const std::size_t windowSizeX = std::max(30*boardWidth, maximumPromptWidth) + 22;
    const std::size_t windowSizeY {30*boardWidth + 22 + playerPrompt->height() + restartGameButton->height() + 20};
    return QSize(windowSizeX, windowSizeY);
}

QSize Window::minimumSizeHint() const
{
    const std::size_t windowSizeX = std::max(30*boardWidth, maximumPromptWidth) + 22;
    const std::size_t windowSizeY {30*boardWidth + 22 + playerPrompt->height() + restartGameButton->height() + 20};
    return QSize(windowSizeX, windowSizeY);
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
    playerPrompt->setText("Player 1, it's your turn.");
}

void Window::gameWon(const unsigned playerId)
{
    const std::string message {"Player " + std::to_string(playerId+1) + " won. Congratulations!"};
    playerPrompt->setText(QString::fromStdString(message));
}
