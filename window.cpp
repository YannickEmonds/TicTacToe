#include "window.h"
#include "game.h"
#include <QApplication>

Window::Window(const std::size_t width, QWidget *parent)
    : boardWidth(width),
      QWidget(parent)
{
    // 30 per button + 10 per margin at each side
    const std::size_t windowSize {30*boardWidth + 20};
    setFixedSize(windowSize, windowSize);

    for (std::size_t i=0; i<boardWidth; ++i)
    {
        std::size_t x {10 + i*30};
        for (std::size_t j=0; j<boardWidth; ++j)
        {
            std::size_t y {10 + j*30};
            QPushButton* newButton = new QPushButton("", this);
            newButton->setGeometry(x, y, 30, 30);
            connect(newButton, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked(bool)));
            buttons.push_back(newButton);
        }
    }

//    m_button = new QPushButton("Hello World", this);
//    m_button->setGeometry(10, 10, 80, 30);
//    m_button->setCheckable(true);

//    m_counter = 0;

//    connect(m_button, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked(bool)));
//    connect(this, SIGNAL (counterReached()), QApplication::instance(), SLOT (quit()));

//    connect(m_button, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));
}

void Window::slotButtonClicked()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    // check syntax
    const unsigned playerId {Game::getCurrentPlayerId()};
    char playerMark = playerId == 0 ? 'x' : 'o';
    clickedButton->setText(playerMark);
    clickedButton->setEnabled(false);
    Game::checkBoardForWin();
}
