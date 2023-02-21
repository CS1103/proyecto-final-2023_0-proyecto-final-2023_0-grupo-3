#include <iostream>
#include <conio.h>
#include "Maze.h"
using namespace std;

int main(){
    srand(time(nullptr));
    int row{}, col{};
    cout<<"Row: ";cin>>row;
    cout<<"Col: "; cin>>col;
    Maze maze(row,col);
    //cout<<maze<<endl;

    maze.print_mapa();

    return 0;
}