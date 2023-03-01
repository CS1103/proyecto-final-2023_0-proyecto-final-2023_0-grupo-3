#ifndef PROYECTO_DFS_H
#define PROYECTO_DFS_H

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <thread>
using namespace std;

class Maze_DFS;
using type_celda = int;
enum id_celda { VACIO = 0, PARED = 1, PREMIO = 2, A = 3, B = 4, ESTELA1 = -1, ESTELA2 = -2, ALREDEDOR = -3};

template<typename T>
class DFS {
    friend class Maze;
    friend ostream& operator<<(ostream& os, const Maze_DFS& maze);
private:
    map<T,set<T>> g_mapa;
    set<T> visitados;
    map<T,set<T>> conexiones;

    int row{}, col{};
    int _celdas_size_row{};
    int _celdas_size_col{};
    vector<vector<type_celda>> celdas;

public:

    explicit DFS(int r, int c):  row(r), col(c) {};
    ~DFS(){}

    DFS<T>& generar_grafo();
    void nueva_arista(T v1, T v2);
    DFS<T>& randomDFS(T u);

    set<T> no_visitados(T u);
    T random_vecino_no_visitado(T u);

    // Generacion del laberinto
    DFS<T>& generar_conexiones();

    vector<vector<type_celda>> dfs(){

        generar_grafo(). // Patron De Diseño: Builder
        randomDFS(pair(1,1)).
        generar_conexiones();

        return celdas;
    }
};

template<typename T>
DFS<T>& DFS<T>::generar_grafo(){
    _celdas_size_row = row;
    _celdas_size_col = col;

    for(auto i = 0; i< row; i++)
        celdas.emplace_back(col,PARED);

    // Generandos los nodos
    for(int i=1; i < _celdas_size_row; i+=2){
        for(int j=1; j < _celdas_size_col; j+=2){
            pair<int,int> p0(i,j);

            // Abriendo las celda en p0
            celdas[i][j] = VACIO;

            // Generando los aristas con los nodos vecino a p0
            nueva_arista(p0,make_pair(min(i+2,_celdas_size_row-1),j));
            nueva_arista(p0,make_pair(i,min(j+2,_celdas_size_col-1)));
            nueva_arista(p0,make_pair(max(i-2,1),j));
            nueva_arista(p0,make_pair(i,max(j-2,1)));
        }
    }

    return *this;
}


template<typename T>
void DFS<T>::nueva_arista(T v1, T v2){
    // Creando la arista v1--v2
    g_mapa[v1].insert(v2);
    g_mapa[v2].insert(v1);
}

template<typename T>
set<T> DFS<T>::no_visitados(T u){
    set<T> out;
    for(const T& item: g_mapa[u]){
        if(visitados.find(item)==visitados.end()){
            out.insert(item);
        }
    }
    return out;
}

template<typename T>
T DFS<T>::random_vecino_no_visitado(T u){
    set<T> s = no_visitados(u);
    int size = s.size();
    if (size == 0)
        return make_pair(-1,-1);

    int indc = rand() % size;
    auto it  = s.begin();
    advance(it, indc);

    return *it;
}

template<typename T>
DFS<T>& DFS<T>::randomDFS(T u){
    visitados.insert(u);
    T next = random_vecino_no_visitado(u);

    while (next.first != -1){
        conexiones[u].insert(next);
        randomDFS(next);
        next = random_vecino_no_visitado(u);
    }
    return *this;
}

template<typename T>
DFS<T>& DFS<T>::generar_conexiones(){
    for(int i=1; i < _celdas_size_row; i+=2){
        for(int j=1; j < _celdas_size_col; j+=2){
            pair<int,int> p0(i,j);
            for(const T& p: conexiones[p0]){
                int union_x = (i + p.first) / 2;
                int union_y = (j + p.second)/ 2;
                celdas[union_x][union_y] = VACIO;
            }
        }
    }
    return *this;
}

#endif