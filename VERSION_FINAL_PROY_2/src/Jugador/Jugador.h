#ifndef PROYECTO_JUGADOR_H
#define PROYECTO_JUGADOR_H

#include <utility>
#include "../Jugador/Jugador_Base.h"
#include "../Grafos/DFS.h"

class Jugador : public Jugador_Base {
    friend class Menu;
private:
    string type = "Jugador";
public:
    explicit Jugador(Maze_DFS* maze, string n_, int pos ) : Jugador_Base(maze, std::move(n_), pos){
        valor_jugador = valor_jugador == 3 ? maze->maze[1][1] = A : maze->maze[row-2][col-2] = B;
        int sum{};
        for(int i=(row/2)-1;i<(row/2)+2;i++)
            for(int j=(col/2)-1 ;j<(col/2)+2;j++){
                ++sum;
                if(sum % 2 == 0)
                    if(maze->maze[i][j] == VACIO)
                        maze->maze[i][j] = ALREDEDOR;
            }
    }
    string get_Type() override { return type; }

    bool borrado(char direccion, int turno) override {
        int x = actual.first;
        int y = actual.second;
        if(direccion=='w'){
            if(maze->maze[x-1][y]== (valor_jugador == 3 ? ESTELA1 : ESTELA2))return true;
        }
        else if(direccion=='s'){
            if(maze->maze[x+1][y]==(valor_jugador == 3 ? ESTELA1 : ESTELA2))return true;
        }
        else if(direccion=='d'){
            if(maze->maze[x][y+1]==(valor_jugador == 3 ? ESTELA1 : ESTELA2))return true;
        }
        else if(direccion=='a'){
            if(maze->maze[x][y-1]==(valor_jugador == 3 ? ESTELA1 : ESTELA2))return true;
        }
        return false;
    }

    bool can_move(char direccion, int turno){
        int x = actual.first;
        int y = actual.second;
        if (direccion == 'w' || direccion == 'W') {
            if(maze->maze[x-1][y] <= VACIO){return true;}
        }
        if (direccion == 's' || direccion == 'S') {
            if(maze->maze[x+1][y] <= VACIO){return true;}
        }
        if (direccion == 'a' || direccion == 'A') {
            if(maze->maze[x][y-1] <= VACIO){return true;}
        }
        if (direccion == 'd' || direccion == 'D') {
            if(maze->maze[x][y + 1] <= VACIO) { return true; }
        }
        return false;
    }

    void movimiento(char direccion, int turno , int estela) override {
        int x = actual.first, y = actual.second, ct=0;
        int help = valor_jugador == 3 ? 4 : 3;
        switch (direccion){
            case 'W':case 'w':
                if(maze->maze[x-1][y] <= VACIO){

                    vector<char>dir{'d','a'};
                    while (ct<3){
                        maze->maze[x][y] = estela;
                        x--;
                        maze->maze[x][y] = turno;
                        actual.first = x;
                        actual.second = y;
                        if(maze->maze[x][y] == PREMIO or ganador_2()){
                            break;
                        }
                        ct = contar_ceros(x,y);
                        if(maze->maze[x-1][y] == help){
                            cout<<"Jugador "<<(help==3?'A':'B')<<" no le permite pasar..."<<endl;
                            break;
                        }
                        if(maze->maze[x-1][y] == PARED){
                            int s = 0;
                            for(auto item:dir){
                                if(can_move(item, turno))
                                    s++;
                            }
                            if(s==2){break;}
                            else{
                                if(can_move('d',turno))
                                    movimiento('d',turno, estela);
                                else
                                    movimiento('a',turno, estela);
                            }
                            break;
                        }
                    }
                }break;
            case 'S':case 's':
                if(maze->maze[x+1][y] <= VACIO){
                    vector<char>dir{'d','a'};

                    while (ct<3){
                        maze->maze[x][y] = estela;
                        x++;
                        maze->maze[x][y] = turno;
                        actual.first = x;
                        actual.second = y;
                        if(maze->maze[x][y] == PREMIO or ganador_2()){
                            break;
                        }
                        ct = contar_ceros(x,y);

                        if(maze->maze[x+1][y] == help){
                            cout<<"Jugador "<<(help==3?'A':'B')<<" no le permite pasar..."<<endl;
                            break;
                        }
                        if(maze->maze[x+1][y] == PARED){
                            int s = 0;
                            for(auto item:dir){
                                if(can_move(item,turno)){
                                    s++;
                                }
                            }
                            if(s==2){break;}
                            else{
                                if(can_move('d',turno)){
                                    movimiento('d',turno, estela);
                                }
                                else{
                                    movimiento('a',turno, estela);
                                }
                            }
                            break;
                        }
                    }
                }break;
            case 'A':case 'a':
                if(maze->maze[x][y-1] <= VACIO){
                    vector<char>dir{'w','s'};
                    while (ct<3){
                        maze->maze[x][y] = estela;
                        y--;
                        maze->maze[x][y] = turno;
                        actual.first = x;
                        actual.second = y;
                        if(maze->maze[x][y] == PREMIO or ganador_2()){
                            break;
                        }
                        ct = contar_ceros(x,y);
                        if(maze->maze[x][y-1] == help){
                            cout<<"Jugador "<<(help==3?'A':'B')<<" no le permite pasar..."<<endl;
                            break;
                        }
                        if(maze->maze[x][y-1] == PARED){

                            int s = 0;
                            for(auto item:dir){
                                if(can_move(item, turno)){
                                    s++;
                                }
                            }
                            if(s==2){break;}
                            else{
                                if(can_move('w', turno)){
                                    movimiento('w', turno, estela);
                                }
                                else{
                                    movimiento('s', turno, estela);
                                }
                            }
                            break;
                        }
                    }
                }break;
            case 'D':case 'd':
                if(maze->maze[x][y+1] <= VACIO){
                    vector<char>dir {'w','s'};

                    while (ct<3){
                        maze->maze[x][y] = estela;
                        y++;
                        maze->maze[x][y] = turno;
                        actual.first = x;
                        actual.second = y;
                        if(maze->maze[x][y] == PREMIO or ganador_2()){
                            break;
                            return;
                        }
                        ct = contar_ceros(x,y);
                        if(maze->maze[x][y+1] == help){
                            cout<<"Jugador "<<(help==3?'A':'B')<<" no le permite pasar..."<<endl;
                            break;
                        }
                        if(maze->maze[x][y+1] == PARED){
                            int s = 0;
                            for(auto item:dir){
                                if(can_move(item, turno)){
                                    s++;
                                }
                            }
                            if(s==2){break;}
                            else{
                                if(can_move('w', turno)){
                                    movimiento('w', turno, estela);
                                }
                                else{
                                    movimiento('s',turno, estela);
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

    ~Jugador() = default;
};





#endif
