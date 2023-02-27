#include "Menu/Menu.h"
#include <conio.h>

// add_executable(PROYECTO src/main.cpp src/Maze_Generator_DFS/Maze_Generator.h src/Maze_Generator_DFS/Maze_Generator_DFS.cpp
//        src/Menu/Jugador.h src/Maze/Maze.h src/Menu/Menu.h)

int main(){
    Menu menu;
    menu.jugar();
    getch();
    return 0;
}