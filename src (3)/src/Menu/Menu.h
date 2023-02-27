#ifndef PROYECTO_MENU_H
#define PROYECTO_MENU_H

#include "../Maze/Maze.h"

class Menu {
private:
    Maze* maze = nullptr;

public:
    Menu(){
        int opc1;
        cout<<"\tBIENVENIDO"<<endl;

        cout<<endl<<"TAMANIO MAZE:"<<endl;
        cout<<"1. 21 x 15"<<endl;
        cout<<"2. 42 x 30"<<endl;
        cout<<"OPTION: "; cin>>opc1;

        switch (opc1) {
            case 1: maze = new Maze(15,21); break;
            case 2: maze = new Maze(30,42); break;
            default: cout<<"INCORRECTO!. Vuelve a digitar"<<endl;
        }

        cout<<"Opciones:"<<endl;
        cout<<"1. 1 vs 1"<<endl;
        cout<<"2. 1 vs MAQUINA"<<endl;
        cout<<"3. MAQUINA VS MAQUINA"<<endl;
        cout<<"OPTION: "; cin>>opc1;
        string nombre {};

        switch (opc1) {
            case 1:
                cout<<"Nombre 1: "; cin>>nombre;
                maze->jugador.emplace_back(nombre);
                cout<<"Nombre 2: "; cin>>nombre;
                maze->jugador.emplace_back(nombre);
                break;

            case 2:
                cout<<"Nombre: "; cin>>nombre;
                maze->jugador.emplace_back(nombre);
                maze->jugador.emplace_back("MAQUINA");
                break;
            case 3:
                maze->jugador.emplace_back("MAQUINA 1");
                maze->jugador.emplace_back("MAQUINA 2");
                break;
            default:
                cout<<"INCORRECTO!. Vuelve a digitar"<<endl;
                break;
        }
    }

    void jugar(){
        char mv;
        int turno = 3;

        while(true){
            if(turno == 3)
                cout<<"Turno: "<<maze->jugador[0].nombre<<endl;
            else
                cout<<"Turno: "<<maze->jugador[1].nombre<<endl;
            cout<<"Movimiento: ";cin>>mv;
            maze->movimiento(mv,turno);
            cout<<*maze<<endl;

            if(maze->ganador())
                break;
            if(turno == 3)
                turno = 4;
            else
                turno = 3;
        }
    }

};



#endif
