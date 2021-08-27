#include <iostream>
#include "board.h"
#include "window.h"
#include <QApplication>



int main(int argc, char * argv[])
{
    // TODO: make this nicer
    int width = 3;
    if (argc > 1)
        width = atoi(argv[1]);

    QApplication app(argc, argv);

    Window game(width);
    game.show();

    return app.exec();


//    Board board(width);

//    int playerId {0};
//    int pos {0};
//    while (board.stillPlaying())
//    {
//        std::cout << "Player " << playerId+1 << ", it's your turn.\n";
//        std::cin >> pos;
//        try
//        {
//            board.setSquare(pos, playerId);
//        }
//        catch (std::out_of_range& e)
//        {
//            std::cout << e.what();
//            continue;
//        }
//        catch (std::logic_error& e)
//        {
//            std::cout << e.what();
//            continue;
//        }

//        board.checkForWin();

//        board.displayBoard();
//        playerId = (playerId+1) % 2;
//    }

//    return 0;
}
