//
// Created by Jaime Rivera on 27/02/2023.
//

#ifndef PROYECTO_MAZE_RANDOM_H
#define PROYECTO_MAZE_RANDOM_H

#include <iostream>
#include <vector>
#include "../Maze/Maze_Base.h"
using namespace std;
using type_celda = int;
enum id_celda { VACIO = 0, PARED = 1, PREMIO = 2, A = 3, B = 4, ESTELA1 = -1, ESTELA2 = -2, ALREDEDOR = -3};

class Maze_Random : public Maze_Base {
    friend class Menu;

private:
    int col{};
    int row{};
public:

    void recuadro_matriz() const {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (i == 0 || j == 0 || i == row - 1 || j == col - 1)
                    maze[i][j] = 1;
                else
                    maze[i][j] = 0;
            }
        }
    }

    Maze_Random(int row_, int col_) : row(row_), col(col_) {
        for(int i=0; i<row; i++)
            maze.emplace_back(col,PARED);
        recuadro_matriz();
        matriz_laberinto();
    }

    void matriz_laberinto() const {
        srand(time(NULL));
        for (int i = 0; i < (int) row * col / 4; i++) {
            int x = rand() % (col - 4) + 2;
            x = (x / 2) * 2;
            int y = rand() % (row - 4) + 2;
            y = (y / 2) * 2;
            maze[y][x] = 1;
            for (int j = 0; j < 8; j++) {
                int mx[4] = {x, x, x + 2, x - 2};
                int my[4] = {y + 2, y - 2, y, y};
                int r = rand() % 4;
                if (maze[my[r]][mx[r]] == 0) {
                    maze[my[r]][mx[r]] = 1;
                    maze[my[r] + (y - my[r]) / 2][mx[r] + (x - mx[r]) / 2] = 1;
                }
            }
        }
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++) {
                if (i == row - 2)
                    if (j != 0 && j != col - 1)
                        maze[i][j] = 0;
                if (j == col - 2)
                    if (i != 0 && i != row - 1)
                        maze[i][j] = 0;
            }
        for (int i = (row / 2) - 1; i < (row / 2) + 2; i++) {
            for (int j = (col / 2) - 1; j < (col / 2) + 2; j++) {
                maze[i][j] = 0;
            }
        }
        maze[row / 2][col / 2] = 2;
        maze[1][1] = 3;
        maze[row - 2][col - 2] = 4;
    }

    friend ostream& operator<<(ostream& os, const Maze_Random& maze){
        for(int i=0; i < maze.row; i++) {
            for (int j = 0; j < maze.col; j++){
                if (maze.maze[i][j] == VACIO) os << "  ";
                else if(maze.maze[i][j] == -3) os<<"  ";
                else if (maze.maze[i][j] == PARED) os << (char)219 << (char)219;
                else if (maze.maze[i][j] == PREMIO) os << "XX";
                else if (maze.maze[i][j] == A) os << "A ";
                else if (maze.maze[i][j] == B) os << " B";
                else if (maze.maze[i][j] == -1) os << "..";
                else if(maze.maze[i][j] == -2) os <<"~~";
            }
            os<<endl;
        }
        os<<endl;
        return os;
    }

    void print_maze() override{
        cout<<*this<<endl;
    }

    ~Maze_Random() override = default;
};

#endif //PROYECTO_MAZE_RANDOM_H
