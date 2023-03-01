
#ifndef PROYECTO_MAZE_BASE_H
#define PROYECTO_MAZE_BASE_H

class Maze_Random;

class Maze_Base { // Patron de Diseño: Factory Construction
    friend class Maze_Random;
    friend class Maze_DFS;
protected:
    vector<vector<type_celda>> maze;
    int col{}, row{};
    pair<int, int> centro;
public:
    Maze_Base()= default;
    virtual void print_maze() = 0;
    virtual ~Maze_Base()= default;
};

#endif
