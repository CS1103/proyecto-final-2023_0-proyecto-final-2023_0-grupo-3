#ifndef PROYECTO_DFS_H
#define PROYECTO_DFS_H

#include <iostream>
//#include "../src1/Maze.h"
#include <map>
#include <set>

using namespace std;


class Maze;

template<typename T>
class Grafo{
    friend class Maze;
    friend ostream& operator<<(ostream& os, const Maze& maze);
private:
    map<T,set<T>> g_mapa;
    set<T> visitados;
    map<T,set<T>> conexiones;

    int row{}, col{};
    int _celdas_size_row{};
    int _celdas_size_col{};
    char** celdas{};

public:
    explicit Grafo(int r, int c):  row(r), col(c) {};
    ~Grafo();

    void generar_grafo();
    void nueva_arista(T v1, T v2);
    void randomDFS(T u);

    set<T> no_visitados(T u);
    T random_vecino_no_visitado(T u);

    // Generacion del laberinto
    void generar_conexiones();
    void dibujar_celdas();
};

template<typename T>
void Grafo<T>::generar_grafo(){
    _celdas_size_row = row%2 != 0 ? row : row+1;
    _celdas_size_col = col%2 != 0 ? col : col+1;
    celdas = new char*[_celdas_size_row];

    // Generar la matriz de celdas, inicialmente
    // todas cerradas
    for(int i=0; i < _celdas_size_row; i++){
        celdas[i] = new char[_celdas_size_col];
        for(int j=0; j < _celdas_size_col; j++){
            celdas[i][j] = (char)219;
        }
    }


    // Generandos los nodos
    for(int i=1; i < _celdas_size_row; i+=2){
        for(int j=1; j < _celdas_size_col; j+=2){
            pair<int,int> p0(i,j);

            // Abriendo las celda en p0
            celdas[i][j] = ' ';

            // Generando los aristas con los nodos vecino a p0
            nueva_arista(p0,make_pair(min(i+2,_celdas_size_row-1),j));
            nueva_arista(p0,make_pair(i,min(j+2,_celdas_size_col-1)));
            nueva_arista(p0,make_pair(max(i-2,1),j));
            nueva_arista(p0,make_pair(i,max(j-2,1)));
        }
    }
}

template<typename T>
Grafo<T>::~Grafo(){
    for(int i=0; i<_celdas_size_row; i++)
        delete[] celdas[i];
    delete[] celdas;
}

template<typename T>
void Grafo<T>::nueva_arista(T v1, T v2){
    // Creando la arista v1--v2
    g_mapa[v1].insert(v2);
    g_mapa[v2].insert(v1);
}

template<typename T>
set<T> Grafo<T>::no_visitados(T u){
    set<T> out;
    for(const T& item: g_mapa[u]){
        if(visitados.find(item)==visitados.end()){
            out.insert(item);
        }
    }
    return out;
}
template<typename T>
T Grafo<T>::random_vecino_no_visitado(T u){
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
void Grafo<T>::randomDFS(T u){
    visitados.insert(u);
    T next = random_vecino_no_visitado(u);

    while (next.first != -1){
        conexiones[u].insert(next);
        randomDFS(next);
        next = random_vecino_no_visitado(u);
    }
}

template<typename T>
void Grafo<T>::generar_conexiones(){
    for(int i=1; i < _celdas_size_row; i+=2){
        for(int j=1; j < _celdas_size_col; j+=2){
            pair<int,int> p0(i,j);
            for(const T& p: conexiones[p0]){
                int union_x = (i + p.first) / 2;
                int union_y = (j + p.second)/ 2;
                celdas[union_x][union_y] = ' ';
            }
        }
    }
}

template<typename T>
void Grafo<T>::dibujar_celdas(){
    for(int i=0; i < _celdas_size_row; i++){
        for(int j=0; j < _celdas_size_col; j++)
            cout << celdas[i][j];
        cout << endl;
    }
    cout<<endl;
}


#endif
