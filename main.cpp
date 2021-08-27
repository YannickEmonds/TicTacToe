#include <iostream>
#include "board.h"
#include "window.h"
#include "startwindow.h"
#include <QApplication>


int main(int argc, char * argv[])
{
    // TODO: make this nicer
    int width = 3;
    if (argc > 1)
        width = atoi(argv[1]);

    QApplication app(argc, argv);

    StartWindow start;
    start.show();

    Window game(width);
    game.show();

    return app.exec();
}
