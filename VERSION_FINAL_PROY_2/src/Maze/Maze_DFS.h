#ifndef PROYECTO_MAZE_DFS_H
#define PROYECTO_MAZE_DFS_H

#include "../Grafos/DFS.h"
#include "../Maze/Maze_Base.h"
using namespace std;

class Maze_DFS : public Maze_Base {
    friend class Menu;
    friend class Jugador_Base;
    friend class Jugador;
    friend class Bot;
    friend class AsciiMazeRenderer;
private:
    static Maze_DFS* inst;
    Maze_DFS(int r, int c) : Maze_Base() {
        row = r%2 == 0 ? ++r : r;
        col = c%2 == 0 ? ++c : c;
        auto* maze_generator  = new DFS<pair<int,int>>(row,col);
        maze = maze_generator->dfs();
        delete maze_generator;
        maze[1][1] = A;
        maze[row-2][col-2] = B;

        maze[row/2][col/2] = PREMIO;
        cout<<endl;
        if(row == 31) for(int i=0; i<5; i++) cout<<'\t';
        else for(int i=0; i<2; i++) cout<<'\t';
        cout<<".:Maze:."<<endl;
        cout<<*this<<endl;
        centro.first = row/2;
        centro.second = col/2;
    }

public:
    ~Maze_DFS() override { delete inst;}
    Maze_DFS(const Maze_DFS&) = delete;
    Maze_DFS& operator=(const Maze_DFS& ) = delete;

    static Maze_DFS* getInstancia(int r, int c);
    void print_maze() override { // Adapter
        cout<<*this<<endl;
    }
    friend ostream& operator<<(ostream& os, const Maze_DFS& maze){
        for(int i=0; i < maze.row; i++) {
            for (int j = 0; j < maze.col; j++){
                if (maze.maze[i][j] == VACIO) os << "  ";
                else if(maze.maze[i][j] == ALREDEDOR) os<<"  ";
                else if (maze.maze[i][j] == PARED) os << (char)219 << (char)219;
                else if (maze.maze[i][j] == PREMIO) os << "XX";
                else if (maze.maze[i][j] == A) os << "A ";
                else if (maze.maze[i][j] == B) os << " B";
                else if (maze.maze[i][j] == ESTELA1) os << "..";
                else if(maze.maze[i][j] == ESTELA2) os <<"~~";
            }
            os<<endl;
        }
        os<<endl;
        return os;
    }
};

Maze_DFS* Maze_DFS::inst = nullptr;
Maze_DFS* Maze_DFS::getInstancia(int row, int col) {
    if(inst == nullptr)
        inst = new Maze_DFS(row, col);
    return inst;
}

class MazeRenderer { // Patron de diseño: Bridge
protected:
    Maze_DFS* maze;
public:
    explicit MazeRenderer(Maze_DFS* maze) : maze(maze){}
    virtual void render() = 0;
    virtual ~MazeRenderer() = default;
};

class GraphicsMazeRenderer : public MazeRenderer {
public:
    void render() override {
        // Código para renderizar el laberinto con gráficos en 2D o 3D
    }
    ~GraphicsMazeRenderer() override = default;
};

class AsciiMazeRenderer : public MazeRenderer {
public:
    explicit AsciiMazeRenderer(Maze_DFS* maze) : MazeRenderer(maze) {}

    void render() override {
        maze->print_maze();
    }
    ~AsciiMazeRenderer() override = default;
};

#endif

