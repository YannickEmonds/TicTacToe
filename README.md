# TicTacToe
Simple TicTacToe game for two players written in C++. Qt (version 5.12.8) is used for the GUI. 

## Building
Use `qmake` to generate the Makefile and subsequently `make` to build the application.

## Playing
Simply click on the field you want to set. Already set field cannot be set by the other player, obviously.  
The board size can be chosen when calling the program:
For example, `./TicTacToe 4` starts a game with a 4x4 board.
When the argument is omitted, a standard 3x3 board will be created.
