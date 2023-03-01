
#ifndef PROYECTO_BFS2_H
#define PROYECTO_BFS2_H

#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <set>
#include <queue>
using namespace std;

class BFS {
private:
    vector<vector<int>> maze;
    queue<pair<int, int>> q;
    map<pair<int, int>, pair<int, pair<int, int>>> visited;
    set<pair<int, int>> path;
public:
    explicit BFS(vector<vector<int>> maze_) : maze(std::move(maze_)) {}

    bool isValid(int row, int col) {
        int numRows = maze.size(), numCols = maze[0].size();
        return (row >= 0 && row < numRows && col >= 0 && col < numCols && maze[row][col] != 1);  // -> 1 : PREMIO
    }

    set<pair<int,int>> bfs(pair<int, int> start, pair<int, int> end) {
        q.push(start);
        visited[start] = make_pair(0, make_pair(-1, -1));
        while (!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            int row = curr.first, col = curr.second;
            int dist = visited[curr].first + 1;
            vector<pair<int, int>> neighbors = {{-1, 0},
                                                {0,  -1},
                                                {1,  0},
                                                {0,  1}};
            for (pair<int, int> neighbor: neighbors) {
                int newRow = row + neighbor.first, newCol = col + neighbor.second;
                if (isValid(newRow, newCol) && visited.count(make_pair(newRow, newCol)) == 0) {
                    q.push(make_pair(newRow, newCol));
                    visited[make_pair(newRow, newCol)] = make_pair(dist, curr);
                    if (make_pair(newRow, newCol) == end) {
                        getPath(start, end);
                        return path;
                    }
                }
            }
        }
        cout << "No path found.\n";
        return {};
    }

    void getPath(pair<int, int> start, pair<int, int> end) {
        pair<int, int> curr = end;
        while (curr != start) {
            path.insert(curr);
            curr = visited[curr].second;
        }
        path.insert(start);
    }
};

#endif //PROYECTO_BFS2_H
