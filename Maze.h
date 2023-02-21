#ifndef PROYECTO_MAZE_H
#define PROYECTO_MAZE_H

#include "../DFS/DFS.h"
#include "../src/Jugador.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Maze {
    friend class Menu;
private:
    Grafo<pair<int,int>>* DFS = nullptr;
    int col{}, row{};
    vector<Jugador> jugador;
    vector<char> valores = {'A','B'};
    int i_{}, j_{};
    int y_{},x_{};
public:

    char** getLaberinto() { return DFS->celdas; }
    //void print_mapa(){ DFS->print_mapa(); }

    Maze(int r, int c) : row(r), col(c){
        DFS  = new Grafo<pair<int,int>>(row,col);
        DFS->generar_grafo();
        DFS->randomDFS(make_pair(1,1));
        DFS->generar_conexiones();
        DFS->celdas[1][1] = 'A';
        DFS->celdas[DFS->_celdas_size_row-2][DFS->_celdas_size_col-2] = 'B';
        DFS->celdas[DFS->_celdas_size_row/2][DFS->_celdas_size_col/2] = 'X';
        cout<<*this<<endl;
        i_ = DFS->_celdas_size_row/2;
        j_ = DFS->_celdas_size_col/2;
    }

    friend ostream& operator<<(ostream& os, const Maze& maze){
        for(int i=0; i < maze.DFS->_celdas_size_row; i++){
            for(int j=0; j < maze.DFS->_celdas_size_col; j++)
                os << maze.DFS->celdas[i][j];
            os << endl;
        }
        os<<endl;
        return os;
    }

    int contar_ceros(int x, int y){
        int ct = 0;
        if(DFS->celdas[x-1][y] == ' ') ct++;
        if(DFS->celdas[x+1][y] == ' ') ct++;
        if(DFS->celdas[x][y-1] == ' ') ct++;
        if(DFS->celdas[x][y+1] == ' ') ct++;
        return ct;
    }


    inline bool ganador() const {
        int x = x_;
        int y = y_;
        return ((x == i_-1 and y == j_) or (x == i_-1 and y == j_) or (x = i_-1 and y == j_+1) or (x == i_ and y == j_-1)
                or (x == i_ and y == j_+1) or (x == i_+1 and y == j_-1) or (x == i_+1 and y == j_) or (x == i_+1 and y == j_+1));
    }


    void movimiento(char mov, int turno_){
        char turno = turno_ == 3 ? 'A' : 'B';
        //cout<<"Turno: "<<turno<<endl;
        int x{}, y{}, ct{};
        for(int i=0; i<DFS->_celdas_size_row; i++) {
            for (int j = 0; j < DFS->_celdas_size_col; j++) {
                if (DFS->celdas[i][j] == turno) {
                    x = i;
                    y = j;
                }
            }
        }
        x_ = x;
        y_ = y;

        if(ganador()) {
            cout<<"BREAK!!!"<<endl;
            return;
        }

        switch(mov) {
            case 'W':
            case 'w':
                if (DFS->celdas[x - 1][y] == ' ') {
                    //ct = contar_ceros(matriz,x,y);
                    while (ct < 3) {
                        //cout<<"WWW"<<endl;
                        DFS->celdas[x][y] = ' ';
                        x--;
                        DFS->celdas[x][y] = turno;
                        ct = contar_ceros(x, y);
                        if (DFS->celdas[x - 1][y] == (char)219)
                            break;
                    }
                }
                break;
            case 'S':
            case 's':
                if (DFS->celdas[x + 1][y] == ' ') {
                    //ct = contar_ceros(matriz,x,y);
                    while (ct < 3) {
                        //cout<<"SSS"<<endl;
                        DFS->celdas[x][y] = ' ';
                        x++;
                        DFS->celdas[x][y] = turno;
                        ct = contar_ceros(x, y);
                        if (DFS->celdas[x + 1][y] == (char)219)
                            break;
                    }
                }
                break;
            case 'A':
            case 'a':
                if (DFS->celdas[x][y - 1] == ' ') {
                    //ct = contar_ceros(matriz,x,y);
                    while (ct < 3) {
                        //cout<<"AAA"<<endl;
                        DFS->celdas[x][y] = ' ';
                        y--;
                        DFS->celdas[x][y] = turno;
                        ct = contar_ceros(x, y);
                        if (DFS->celdas[x][y - 1] == (char)219)
                            break;
                    }
                }
                break;
            case 'D':
            case 'd':
                if (DFS->celdas[x][y + 1] == ' ') {
                    //ct = contar_ceros(matriz,x,y);
                    while (ct < 3) {
                        //cout<<"DDD"<<endl;
                        DFS->celdas[x][y] = ' ';
                        y++;
                        DFS->celdas[x][y] = turno;
                        ct = contar_ceros(x, y);
                        if (DFS->celdas[x][y + 1] == (char)219)
                            break;
                    }
                }
                break;
            default:
                cout << "WARNING!!!!" << endl;
                cout << "Digite 'W' 'A' 'S' 'D'" << endl;
                break;
        }
    }
};

#endif

