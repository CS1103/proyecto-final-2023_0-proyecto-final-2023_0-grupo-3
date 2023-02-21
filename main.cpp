#include "Menu.h"
#include "Maze.h"

// DFS/DFS.h src1/main.cpp src1/Menu.h src1/Maze.h

int main(){
    srand(time(NULL));

    Menu menu;
    menu.jugar();

    /*
    int row = 21;
    int col = 15;
    Maze maze(row/2,col/2);
    char mov{};

    while(true){
        cout<<"Movimiento: "; cin>>mov;
        maze.movimiento(mov,3);
        cout<<maze<<endl;
    }
    */

    return 0;
}

