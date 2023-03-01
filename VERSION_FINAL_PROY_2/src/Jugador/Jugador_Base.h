#ifndef PROYECTO_JUGADOR_BASE_H
#define PROYECTO_JUGADOR_BASE_H

#include <iostream>
#include <utility>
#include <vector>
#include <queue>
using namespace std;

class Jugador_Base{
    friend class Menu;
protected:
    Maze_DFS* maze;
    string nombre{};
    int row{}, col{};
    int valor_jugador;
    queue<char> cola;
    set<pair<int,int>> caminos;
    pair<int,int> actual;
public:
    Jugador_Base(Maze_DFS* maze, string  n_, int valor_jugador) : valor_jugador(valor_jugador), maze(maze), nombre(std::move(n_)), row(maze->maze.size()), col(maze->maze[0].size()){
        valor_jugador == 3 ? maze->maze[1][1] = A : maze->maze[row-2][col-2] = B;
        if(valor_jugador == 3)
            actual = {1,1};
        else
            actual = {row - 2, col - 2};
    }
    virtual void movimiento(char mov = 'D', int turno = A, int estela = 0) = 0;
    virtual bool borrado(char, int) = 0;
    virtual string get_Type() = 0;

    int contar_ceros(int x, int y){
        int ct = 0;
        if(maze->maze[x-1][y] <= VACIO) ct++;
        if(maze->maze[x+1][y] <= VACIO) ct++;
        if(maze->maze[x][y-1] <= VACIO) ct++;
        if(maze->maze[x][y+1] <= VACIO) ct++;
        return ct;
    }

    bool ganador_2(){
        int x = row/2;
        int y = col/2;
        if(maze->maze[x-1][y] == valor_jugador) return true;
        if(maze->maze[x+1][y] == valor_jugador) return true;
        if(maze->maze[x][y-1] == valor_jugador) return true;
        if(maze->maze[x][y+1] == valor_jugador) return true;
        return false;
    }

    ~Jugador_Base(){ delete maze; };
};

#endif
