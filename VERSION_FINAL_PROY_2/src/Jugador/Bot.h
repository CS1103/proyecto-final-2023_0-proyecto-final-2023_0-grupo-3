#ifndef PROYECTO_BOT_H
#define PROYECTO_BOT_H

#include <utility>
#include <future>
#include <thread>
#include "../Jugador/Jugador_Base.h"
#include "../Grafos/BFS.h"

class Bot : public Jugador_Base {
    friend class Menu;
private:
    string type = "BOT";
    pair<int,int> inicio;
public:
    explicit Bot(Maze_DFS* maze, string n_, int valor_jugador) : Jugador_Base(maze, std::move(n_), valor_jugador){
        valor_jugador == 3 ? maze->maze[1][1] = A : maze->maze[row-2][col-2] = B;
        valor_jugador == 3 ? valor_jugador = 3 : valor_jugador = 4;

        pair<int, int> partida;
        if(valor_jugador == 3)
            partida = {1, 1};
        else
            partida = {row - 2, col - 2};
        pair<int,int> destino = {maze->row/2,maze->col/2};
        BFS* bfs = new BFS(maze->maze);
        caminos = bfs->bfs(partida,destino);
        delete bfs;
        formar_string();
    }

    bool borrado(char, int) override { return true; }

     bool set_to_queue(pair<int,int> pos1, pair<int,int> pos2){
        if(pos1.first == pos2.first-1 and pos1.second == pos2.second){
            cola.push('S');
            return true;
        }
        else if(pos1.first == pos2.first+1 and pos1.second == pos2.second){
            cola.push('W');
            return true;
        }
        else if(pos1.first == pos2.first and pos1.second == pos2.second-1){
            cola.push('D');
            return true;
        }
        else if(pos1.first == pos2.first and pos1.second == pos2.second+1){
            cola.push('A');
            return true;
        }
        return false;
    }

    void formar_string(){
        if(valor_jugador == 3)
            inicio = {1,1};
        else
            inicio = {row-2, col-2};
        while(caminos.size() != 1) {
            for (auto item: caminos) {
                if(set_to_queue(inicio, item)){
                    caminos.erase(caminos.find(inicio));
                    inicio = item;
                    continue;
                }
            }
        }
    }

    string get_Type() override { return type; }

    /*
    void get_pos(int &x,int &y){
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++) {
                if(maze->maze[i][j] == valor_jugador){
                    x = i;y=j;
                }
            }
    }
     */

    bool verificar(int x, int y, char z){
        switch (z) {
        case 'w' : case 'W':
            if(maze->maze[x-1][y] <= VACIO) return true; break;
        case 's': case 'S':
            if(maze->maze[x+1][y] <= VACIO) return true; break;
        case 'A': case 'a':
            if(maze->maze[x][y-1] <= VACIO) return true; break;
        case 'D': case 'd':
            if(maze->maze[x][y+1] <= VACIO) return true; break;
        }
        return false;
     }

    void movimiento(char, int , int) {
        int ct = 0,x,y;
        while (ct<3){
            thread hilo1([&](){                 // Hilo 1: Se usa para reducir la complejidad planteada inicialmente: O(n^3)
            for (int i = 0; i < row; i++)
                for (int j = 0; j < col; j++) {
                    if(maze->maze[i][j] == valor_jugador){
                        x = i;
                        y=j;
                    }
                }});
            hilo1.join();
            //get_pos(x,y);
            if(!verificar(x,y, cola.front())) break;
            thread hilo2([&](){             // Hilo 2: Se usa para reducir la complejidad planteada inicialmente: O(n^3)
                for (int i = 0; i < row; i++)
                    for (int j = 0; j < col; j++) {
                        if(maze->maze[i][j] == valor_jugador){
                            x = i;
                            y=j;
                        }
                    }});
            movimiento_simple(cola.front());
            //get_pos(x,y);
            hilo2.join();
            ct=contar_ceros(x,y);
            cola.pop();
            if(cola.empty()) { break;}
        }
    }

    void movimiento_simple(char movimiento){
        int x,y,ct;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if(maze->maze[i][j]==valor_jugador){
                    x = i;y=j;
                }
            }
        }
        int help = valor_jugador == 3 ? 4 : 3;
        switch (movimiento){
            case 'W':case 'w':
                if(maze->maze[x-1][y] == help){
                    cout<<"Jugador "<<(help==valor_jugador?'A':'B')<<" no le permite pasar..."<<endl;
                    return;
                }
                else if(maze->maze[x-1][y] <= VACIO){
                    maze->maze[x][y] = valor_jugador == 3 ? ESTELA1 : ESTELA2;
                    maze->maze[x-1][y] = valor_jugador;
                }
                break;
            case 'S':case 's':
                if(maze->maze[x+1][y] == help){
                    cout<<"Jugador "<<(help==valor_jugador?'A':'B')<<" no le permite pasar..."<<endl;
                    return;
                }
                else if(maze->maze[x+1][y] <= VACIO){
                    maze->maze[x][y] = valor_jugador == 3 ? ESTELA1 : ESTELA2;
                    maze->maze[x+1][y] = valor_jugador;
                }
                break;
            case 'A':case 'a':
                if(maze->maze[x][y-1] == help){
                    cout<<"Jugador "<<(help==valor_jugador?'A':'B')<<" no le permite pasar..."<<endl;
                    return;
                }
                else if(maze->maze[x][y-1] <= VACIO){
                    maze->maze[x][y] = valor_jugador == 3 ? ESTELA1 : ESTELA2;
                    maze->maze[x][y-1] = valor_jugador;
                }
                break;
            case 'D':case 'd':
                if(maze->maze[x][y+1] == help){
                    cout<<"Jugador "<<(help==valor_jugador?'A':'B')<<" no le permite pasar..."<<endl;
                    return;
                }
                else if(maze->maze[x][y+1] <= VACIO){
                    maze->maze[x][y] = valor_jugador == 3 ? ESTELA1 : ESTELA2;
                    maze->maze[x][y+1] = valor_jugador;
                }
                break;
            default:cout << "WARNING!!!!"<<endl;cout << "Digite 'W' 'A' 'S' D'"<<endl;break;
        }
    }

    ~Bot() = default;
};

#endif
