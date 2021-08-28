#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <cstddef>
#include <vector>
#include <memory>
#include "board.h"

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(const std::size_t width, QWidget *parent = nullptr);
    void resizeBoard(const std::size_t newWidth);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
private slots:
    void slotNextTurn(unsigned playerId);
    void slotRestartGame();
public slots:
    void gameWon(const unsigned playerId);
signals:
    void signalRestartGame();
private:
    QLabel* createLabel(const QString &text);

    const std::size_t maximumPromptWidth;
    std::size_t boardWidth;
    Board *board;
    QLabel *playerPrompt;
    QPushButton *restartGameButton;
};

#endif // WINDOW_H
