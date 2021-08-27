#ifndef GAMEDRIVER_H
#define GAMEDRIVER_H

#include <cstddef>
#include <QWidget>
#include "window.h"
#include "startwindow.h"

class GameDriver : public QWidget
{
    Q_OBJECT
public:
    explicit GameDriver(QWidget *parent = nullptr);

signals:

private slots:
    void slotStartNewGame(const std::size_t width);
    void slotRestart();
private:
    Window* mainWindow;
    StartWindow* startWindow;
};

#endif // GAMEDRIVER_H
