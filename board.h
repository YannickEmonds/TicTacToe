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
    std::size_t width;
    std::vector<int> boardValues;
    QVector<QPushButton*> buttons;
    unsigned currentPlayerId {0};
private slots:
    void slotButtonClicked();
public slots:
    void slotRestartGame();
signals:
    void gameFinished(unsigned playerId);
    void nextTurn(unsigned playerId);
public:
//    Board(const std::size_t w = 3) : width(w), boardValues(w*w, 0) {}
    Board(const std::size_t w = 3, QWidget *parent = nullptr);
    void addButton(QPushButton* newButton);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    bool stillPlaying() const;
    void displayBoard() const;
    void setSquare(const std::size_t pos, const unsigned playerId);
    void checkForWin();
    bool winningRow() const;
    bool winningColumn() const;
    bool winningDiagonal() const;
    std::size_t getWidth() const;
    void resize(const std::size_t newWidth);
};


#endif // BOARD_H
