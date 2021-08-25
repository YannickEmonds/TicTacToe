#ifndef BOARD_H
#define BOARD_H
#include <cstddef>
#include <vector>

#include <QFrame>
#include <QVector>
#include <QPushButton>


class Board : public QFrame
{
    Q_OBJECT

private:
    bool isFinished {false};
    const std::size_t width;
    std::vector<int> boardValues;
    QVector<QPushButton*> buttons;
    unsigned currentPlayerId {0};
private slots:
    void slotButtonClicked();
signals:
    void gameFinished(unsigned playerId);
public:
    Board(const std::size_t w = 3) : width(w), boardValues(w*w, 0) {}

    bool stillPlaying() const;
    void displayBoard() const;
    void setSquare(const std::size_t pos, const unsigned playerId);
    void checkForWin();
    bool winningRow() const;
    bool winningColumn() const;
    bool winningDiagonal() const;
};


#endif // BOARD_H
