//
// Created by logan on 2020/8/12.
//
// 1091. Shortest Path in Binary Matrix(Medium)
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>> &grid) {
        // corner case
        const int N = grid.size();
        if (grid[0][0] || grid[N - 1][N - 1]) return -1;

        const vector<vector<int>> DIRS{{-1, 0},
                                       {-1, 1},
                                       {0,  1},
                                       {1,  1},
                                       {1,  0},
                                       {1,  -1},
                                       {0,  -1},
                                       {-1, -1}};

        using P = pair<int, int>;
        queue<P> q;
        q.emplace(0, 0);
        grid[0][0] = 2; // visited;

        int distance = 1;
        while (not q.empty()) {
            int size = q.size();
            while (size--) {
                auto[x, y] = q.front();
                q.pop();
                if (x == N - 1 && y == N - 1)
                    return distance;

                for (const auto &d : DIRS) {
                    int dx = x + d[0], dy = y + d[1];
                    if (dx < 0 || dy < 0 || dx >= N || dy >= N || grid[dy][dx] != 0)
                        continue;
                    grid[dy][dx] = 2;
                    q.emplace(dx, dy);
                }
            }
            ++distance;
        }
        return -1;
    }
};

