#ifndef PROYECTO_MAZE_H
#define PROYECTO_MAZE_H

#include "../Maze_Generator_DFS/Maze_Generator.h"
#include "../Menu/Jugador.h"
using namespace std;

class Maze {
    friend class Menu;
private:
    Grafo<pair<int,int>>* DFS = nullptr;
    int col{}, row{};
    vector<Jugador> jugador;
    vector<char> valores = {'A','B'};
    pair<int, int> centro;
    pair<int, int> actual;
    int y_{},x_{};
public:

    //void print_mapa(){ DFS->print_mapa(); }

    Maze(int r, int c) : row(r), col(c){
        DFS  = new Grafo<pair<int,int>>(row,col);
        DFS->generar_grafo();
        DFS->randomDFS(pair(1,1));
        DFS->generar_conexiones();
        DFS->celdas[1][1] = 'A';
        DFS->celdas[DFS->_celdas_size_row-2][DFS->_celdas_size_col-2] = 'B';
        DFS->celdas[DFS->_celdas_size_row/2][DFS->_celdas_size_col/2] = 'X';
        cout<<*this<<endl;
        centro.first = DFS->_celdas_size_row/2;
        centro.second = DFS->_celdas_size_col/2;
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

    /*
    int contar_ceros(int x, int y){
        int ct = 0;
        if(DFS->celdas[x-1][y] == ' ') ct++;
        if(DFS->celdas[x+1][y] == ' ') ct++;
        if(DFS->celdas[x][y-1] == ' ') ct++;
        if(DFS->celdas[x][y+1] == ' ') ct++;
        return ct;
    }
    */


    inline bool ganador() const {
        int x = actual.second, y = actual.second, i_ = centro.first, j_ = centro.second;
        return ((x == i_-1 and y == j_) or (x == i_-1 and y == j_) or (x = i_-1 and y == j_+1) or (x == i_ and y == j_-1)
                or (x == i_ and y == j_+1) or (x == i_+1 and y == j_-1) or (x == i_+1 and y == j_) or (x == i_+1 and y == j_+1));
    }

    bool can_move(char direccion, char turno){
        int x,y;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if(DFS->celdas[i][j]==turno){x = i;y=j;}
            }
        }
        if (direccion == 'w' || direccion == 'W') {
            if(DFS->celdas[x-1][y]==' '){return true;}
        }
        if (direccion == 's' || direccion == 'S') {
            if(DFS->celdas[x+1][y]==' '){return true;}
        }
        if (direccion == 'a' || direccion == 'A') {
            if(DFS->celdas[x][y-1]==' '){return true;}
        }
        if (direccion == 'd' || direccion == 'D') {
            if (DFS->celdas[x][y + 1] == ' ') { return true; }
        }
        return false;
    }


    void movimiento(char direccion, int turno_){
        char turno = turno_ == 3 ? 'A' : 'B';
        int x,y,ct=0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if(DFS->celdas[i][j]=='A'){
                    x = i;y=j;
                    actual = {i,j};
                }
            }
        }

        auto contar_ceros = [&](int x, int y){
            int ct0 = 0;
            if(DFS->celdas[x-1][y] == ' ') ct0++;
            if(DFS->celdas[x+1][y] == ' ') ct0++;
            if(DFS->celdas[x][y-1] == ' ') ct0++;
            if(DFS->celdas[x][y+1] == ' ') ct0++;
            return ct0;
        };


        switch (direccion){
            case 'W':case 'w':
                if(DFS->celdas[x-1][y]==' '){
                    //ct = contar_ceros(matriz,x,y);
                    vector<char>dir{'d','a'};
                    while (ct<3){
                        DFS->celdas[x][y]=' ';
                        x--;
                        DFS->celdas[x][y] = turno;
                        ct = contar_ceros(x,y);
                        if(DFS->celdas[x-1][y]==PARED){
                            int s = 0;
                            for(auto item:dir){
                                if(can_move(item,turno)){
                                    s++;
                                }
                            }
                            if(s==2){break;}
                            else{
                                if(can_move('d',turno)){
                                    movimiento('d',turno);
                                }
                                else{
                                    movimiento('a',turno);
                                }
                            }
                            break;
                        }
                    }
                }break;
            case 'S':case 's':
                if(DFS->celdas[x+1][y]==' '){
                    vector<char>dir{'d','a'};
                    //ct = contar_ceros(matriz,x,y);
                    while (ct<3){
                        DFS->celdas[x][y]=' ';
                        x++;
                        DFS->celdas[x][y] = turno;
                        ct = contar_ceros(x,y);
                        if(ct==3)break;
                        if(DFS->celdas[x+1][y] == PARED){
                            int s = 0;
                            for(auto item:dir){
                                if(can_move(item,turno)){
                                    s++;
                                }
                            }
                            if(s==2){break;}
                            else{
                                if(can_move('d',turno)){
                                    movimiento('d',turno);
                                }
                                else{
                                    movimiento('a',turno);
                                }
                            }
                            break;
                        }
                    }
                }break;
            case 'A':case 'a':
                if(DFS->celdas[x][y-1]==' '){
                    vector<char>dir{'w','s'};
                    //ct = contar_ceros(matriz,x,y);
                    while (ct<3){
                        DFS->celdas[x][y]=' ';
                        y--;
                        DFS->celdas[x][y] = turno;
                        ct = contar_ceros(x,y);
                        if(DFS->celdas[x][y-1] == PARED){
                            /*if(can_move(matriz,filas,columnas,'w')){
                                movimiento(matriz,filas,columnas,'w');
                            }
                            else{
                                movimiento(matriz,filas,columnas,'s');
                            }*/
                            int s = 0;
                            for(auto item:dir){
                                if(can_move(item, turno)){
                                    s++;
                                }
                            }
                            if(s==2){break;}
                            else{
                                if(can_move('w', turno)){
                                    movimiento('w', turno);
                                }
                                else{
                                    movimiento('s', turno);
                                }
                            }
                            break;
                        }
                    }
                }break;
            case 'D':case 'd':
                if(DFS->celdas[x][y+1]==' '){
                    vector<char>dir {'w','s'};
                    //ct = contar_ceros(matriz,x,y);
                    while (ct<3){
                        DFS->celdas[x][y] = ' ';
                        y++;
                        DFS->celdas[x][y] = turno;
                        ct = contar_ceros(x,y);
                        if(DFS->celdas[x][y+1] == PARED){
                            int s = 0;
                            for(auto item:dir){
                                if(can_move(item, turno)){
                                    s++;
                                }
                            }
                            if(s==2){break;}
                            else{
                                if(can_move('w', turno)){
                                    movimiento('w', turno);
                                }
                                else{
                                    movimiento('s', turno);
                                }
                            }
                            break;
                        }
                    }
                }break;
            default:
                cout << "WARNING!!!!"<<endl;
                cout << "Digite 'W' 'A' 'S' D'"<<endl;break;
        }
    }

};

#endif

