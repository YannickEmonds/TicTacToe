#ifndef GAMEDRIVER_H
#define GAMEDRIVER_H

#include <QWidget>
#include "window.h"
#include "startwindow.h"

class GameDriver : public QWidget
{
    Q_OBJECT
public:
    explicit GameDriver(QWidget *parent = nullptr);

signals:

public slots:

private:
    Window* mainWindow;
    StartWindow* startWindow;
};

#endif // GAMEDRIVER_H
