//
// Created by logan on 2020/7/30.
//
// 785. Is Graph Bipartite? (Medium)
// 207. Course Schedule (Medium)
// 210. Course Schedule II (Medium)
// 684. Redundant Connection (Medium)
#include <stack>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
// 785. Is Graph Bipartite? (Medium)
    bool isBipartite(vector<vector<int>> &graph) {
        vector<int> vec(graph.size(), -1);
        stack<int> s;
        for (int i = 0; i < graph.size(); ++i) {
            if (vec[i] == -1) {
//该点未着色，当前节点入栈
                vec[i] = 0;
                s.push(i);
                while (!s.empty()) {
                    int cur_node = s.top();
                    s.pop();
//相邻节点着色
                    for (int j = 0; j < graph[cur_node].size(); ++j) {
                        if (vec[graph[cur_node][j]] == -1) {
//当前相邻节点未被着色
                            vec[graph[cur_node][j]] = vec[cur_node] ^ 1;
                            s.push(graph[cur_node][j]);
                        } else {
//已着色，判断是否符合要求
                            if (vec[graph[cur_node][j]] != (vec[cur_node] ^ 1)) return false;
                        }
                    }
                }
            }
        }
        return true;
    }

// 207. Course Schedule (Medium)
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {

    }

// 210. Course Schedule II (Medium)
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {

    }
// 684. Redundant Connection (Medium)

    vector<int> findRedundantConnection(vector<vector<int>> &edges) {

    }


};

int main() {
    Solution s;
    vector<vector<int>> test;
    vector<int> a;
    vector<int> b;
    a.push_back(0);
    a.push_back(1);
    test.push_back(a);
    s.findOrder(2, test);
}