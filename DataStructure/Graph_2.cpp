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
    bool canFinish_bfs(int numCourses, vector<vector<int>> &prerequisites) {
//有向图是否存在环
        vector<int> indegree(numCourses, 0);//每个节点(每门课)的入度值
        vector<vector<int>> graph(numCourses);//入度表
//记录每个节点的入度值以及每个节点的入度表
        for (auto it:prerequisites) {
            indegree[it[0]]++;
            graph[it[1]].push_back(it[0]);
        }
//将入度为0的顶点入队
        queue<int> indegree_queue;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                indegree_queue.push(i);
            }
        }
        int cnt = 0;
        while (!indegree_queue.empty()) {
            int temp = indegree_queue.front();
            indegree_queue.pop();
            cnt++;//满足条件课程数
            for (int i = 0; i < graph[temp].size(); ++i) {
//遍历出队节点的入度表，每个值的入度数减一，若为0，加入队列
                indegree[graph[temp][i]]--;
                if (indegree[graph[temp][i]] == 0) {
                    indegree_queue.push(graph[temp][i]);
                }
            }
        }
        return cnt == numCourses;
    }

private:
    vector<vector<int>> edges;//出度表
    vector<int> visited;//每个节点的出度数
    bool valid = true;

public:
    void dfs(int u) {
        visited[u] = 1;
        for (int v: edges[u]) {
            if (visited[v] == 0) {
                dfs(v);
                if (!valid) {
                    return;
                }
            }
            else if (visited[v] == 1) {
                valid = false;
                return;
            }
        }
        visited[u] = 2;
    }

    bool canFinish_dfs(int numCourses, vector<vector<int>> &prerequisites) {
/*        1. 首先构造出度表
        2. 用数组记录每个节点（每门课）的入度值以及每个节点（每门课）的出度表
        3. 遍历入度值数组，将入度为0的节点入队
        4. 若队列不为空，出队，设置变量记录出队数（符合条件的课程数）并加一
        5. 遍历出队节点的入度表，每个值的入度数减一，若减完后为0，加入队列
        6. 比较出队数和课程数是否相同       */
        edges.resize(numCourses);
        visited.resize(numCourses);
//构造出度表
        for (const auto& info: prerequisites) {
            edges[info[1]].push_back(info[0]);
        }
        for (int i = 0; i < numCourses && valid; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        return valid;

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