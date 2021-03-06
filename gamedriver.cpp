#include "gamedriver.h"
#include <iostream>

GameDriver::GameDriver(QWidget *parent) : QWidget(parent)
{
    startWindow = new StartWindow(this);
    mainWindow = new Window(3, this);

    connect(startWindow, SIGNAL (signalStart(const std::size_t)),
            this, SLOT (slotStartNewGame(const std::size_t)));
    connect(mainWindow, SIGNAL (signalRestartGame()), this, SLOT (slotRestart()));

    startWindow->show();
    mainWindow->hide();
}

void GameDriver::slotStartNewGame(const std::size_t width)
{
    mainWindow->resizeBoard(width);
    resize(mainWindow->size());
    updateGeometry();
    startWindow->hide();
    mainWindow->show();
}

void GameDriver::slotRestart()
{
    std::cerr << "restart signal received\n";
    resize(startWindow->size());
    updateGeometry();
    mainWindow->hide();
    startWindow->show();
}
