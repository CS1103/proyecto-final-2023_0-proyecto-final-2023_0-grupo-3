#ifndef PROYECTO_MENU_H
#define PROYECTO_MENU_H

#include "../Maze/Maze_DFS.h"
#include "../Maze/Maze_Base.h"
#include "../Jugador/Jugador.h"
#include "../Jugador/Bot.h"
#include "../Jugador/Jugador_Base.h"
#include <unistd.h>

class Menu : public Maze_Base {
private:
    Maze_DFS* maze = nullptr;
    MazeRenderer* renderer = nullptr;
    vector<Jugador_Base*> Jugadores;
    int opcion_modo{};

public:
    Menu(){
        int opc1;
        cout<<"\tBIENVENIDO"<<endl;

        cout<<endl<<"TAMANIO MAZE:"<<endl;
        cout<<"1. 15 x 21"<<endl;
        cout<<"2. 30 x 42"<<endl;
        cout<<"OPTION: "; cin>>opc1;

        switch (opc1) {
            case 1: maze = Maze_DFS::getInstancia(15, 21); break;
            case 2: maze = Maze_DFS::getInstancia(30, 42); break;
            default: cout<<"INCORRECTO!. Vuelve a digitar"<<endl;
        }

        renderer = new AsciiMazeRenderer(maze);

        cout<<"Opciones:"<<endl;
        cout<<"1. Jugador vs Jugador"<<endl;
        cout<<"2. Jugador vs BOT"<<endl;
        cout<<"3. BOT VS BOT"<<endl;
        cout<<"OPTION: "; cin>>opcion_modo;
        string nombre {};
        cout<<endl;

        switch (opcion_modo) {
            case 1:
                cout<<"\t.:Digiten sus nombres:."<<endl;
                cout<<"Nombre 1: "; cin>>nombre;
                Jugadores.push_back(new Jugador(maze, nombre,3));
                cout<<"Nombre 2: "; cin>>nombre;
                Jugadores.push_back(new Jugador(maze, nombre,4));
                break;

            case 2:
                cout<<"\t.:Digite su nombre:."<<endl;
                cout<<"Nombre: "; cin>>nombre;
                Jugadores.push_back(new Jugador(maze, nombre,3));
                Jugadores.push_back(new Bot(maze, "BOT",4));
                break;
            case 3:
                Jugadores.push_back(new Bot(maze, "BOT 1",3));
                Jugadores.push_back(new Bot(maze, "BOT 2",4));
                break;
            default:
                cout<<"INCORRECTO!. Vuelve a digitar"<<endl;
                break;
        }
        cout<<endl;
    }

    void jugar(){
        int cont_1{};
        char mv_1{};
        int turno_1 = 3;
        cout<<"\t.:Inicio del Juego:."<<endl<<endl;
        switch(opcion_modo){
            case 1:
                while(true){
                    if(turno_1 == 3) {
                        cout << "Turno: " << Jugadores[0]->nombre << endl;
                        cout<<"Movimiento: ";cin>>mv_1;
                        if(cont_1==0)
                            Jugadores[0]->movimiento(mv_1,turno_1,ESTELA1);
                        else {
                            if (Jugadores[0]->borrado(mv_1, turno_1))
                                Jugadores[0]->movimiento(mv_1, turno_1, VACIO);
                            else
                                Jugadores[0]->movimiento(mv_1,turno_1,ESTELA1);
                        }

                    }
                    else {
                        cout << "Turno: " << Jugadores[1]->nombre << endl;
                        cout<<"Movimiento: ";cin>>mv_1;
                        if(cont_1==0)
                            Jugadores[1]->movimiento(mv_1,turno_1,ESTELA2);
                        else {
                            if (Jugadores[1]->borrado(mv_1, turno_1))
                                Jugadores[1]->movimiento(mv_1, turno_1, VACIO);
                            else
                                Jugadores[1]->movimiento(mv_1,turno_1,ESTELA2);
                        }
                    }

                    print_maze(); // Adapter

                    if(Jugadores[0]->ganador_2()){
                        cout<<string(30,'-')<<endl;
                        cout<<"\t.:Fin del juego:."<<endl;
                        cout<<"Ganador Jugador 1"<<endl;
                        cout<<string(30,'-')<<endl<<endl;
                        break;
                    }

                    if(Jugadores[1]->ganador_2()) {
                        cout<<string(30,'-')<<endl;
                        cout<<"\t.:Fin del juego:."<<endl;
                        cout << "Ganador Jugador 2" << endl;
                        cout<<string(30,'-')<<endl<<endl;
                        break;
                    }

                    if(turno_1 == 3)
                        turno_1 = 4;
                    else
                        turno_1 = 3;
                    cont_1++;
                };

                break;

            case 2:
                while(true){
                    if(turno_1 == 3) {
                        cout << "Turno: " << Jugadores[0]->nombre << endl;
                        cout<<"Movimiento: ";cin>>mv_1;
                        if(cont_1==0)
                            Jugadores[0]->movimiento(mv_1,turno_1,ESTELA1);
                        else {
                            if (Jugadores[0]->borrado(mv_1, turno_1))
                                Jugadores[0]->movimiento(mv_1, turno_1, VACIO);
                            else
                                Jugadores[0]->movimiento(mv_1,turno_1,ESTELA1);
                        }
                        print_maze(); // Adapter
                    }
                    else {
                        cout << "Turno: " << Jugadores[1]->nombre << endl;
                        Jugadores[1]->movimiento();
                        print_maze(); // Adapter
                        sleep(3);
                    }

                    if(Jugadores[0]->ganador_2()){
                        cout<<string(30,'-')<<endl;
                        cout<<"\t.:Fin del juego:."<<endl;
                        cout<<"Ganador Jugador 1"<<endl;
                        cout<<string(30,'-')<<endl<<endl;
                        break;
                    }

                    if(Jugadores[1]->ganador_2()){
                        cout<<string(30,'-')<<endl;
                        cout<<"\t.:Fin del juego:."<<endl;
                        cout<<"Ganador BOT"<<endl;
                        cout<<string(30,'-')<<endl<<endl;
                        break;
                    }

                    if(turno_1 == 3)
                        turno_1 = 4;
                    else
                        turno_1 = 3;
                    cont_1++;
                };
                break;

            case 3:
                while (true) {
                    if (turno_1 == 3) {
                        cout << "Turno: " << Jugadores[0]->nombre << endl;
                        Jugadores[0]->movimiento();
                    }
                    else {
                        cout << "Turno: " << Jugadores[1]->nombre << endl;
                        Jugadores[1]->movimiento();
                    }

                    renderer->render(); // Patron Bridge
                    sleep(2);

                    if (Jugadores[0]->ganador_2()) {
                        cout<<string(30,'-')<<endl;
                        cout<<"\t.:Fin del juego:."<<endl;
                        cout << "Ganador: BOT 1" << endl;
                        cout<<string(30,'-')<<endl<<endl;
                        break;
                    }

                    if (Jugadores[1]->ganador_2()) {
                        cout<<string(30,'-')<<endl;
                        cout<<"\t.:Fin del juego:."<<endl;
                        cout << "Ganador: BOT 2" << endl;
                        cout<<string(30,'-')<<endl<<endl;
                        break;
                    }

                    if(turno_1 == 3)
                        turno_1 = 4;
                    else
                        turno_1 = 3;
                }
        }
    }

    void print_maze() override { // Patron De Diseño: Adapter
        maze->print_maze();
    }

    ~Menu() override = default;
};

#endif
