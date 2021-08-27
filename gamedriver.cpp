#include "gamedriver.h"

GameDriver::GameDriver(QWidget *parent) : QWidget(parent)
{
    mainWindow = new Window(3, this);
    startWindow = new StartWindow(this);

    mainWindow->hide();

}
