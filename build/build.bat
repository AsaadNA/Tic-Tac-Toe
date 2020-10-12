@echo off
cls
g++ ../src/tictactoe.cpp ../src/menu.cpp ../src/board.cpp ../src/placeholder.cpp -o TicTacToe -std=c++11 -lmingw32 -lsdl2main -lsdl2_image -lsdl2 -lsdl2_ttf -lsdl2_mixer
