#ifndef PROYECTO_JUGADOR_H
#define PROYECTO_JUGADOR_H

#include <iostream>
#include <utility>
using namespace std;

class Jugador {
private:
    friend class Menu;
    string nombre{};
public:
    explicit Jugador(string n_) : nombre(std::move(n_)){}
};


#endif
