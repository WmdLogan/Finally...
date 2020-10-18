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
#include <algorithm>

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
//当前相邻节点未被着色，着色并入栈
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
    vector<vector<int>> out_degree;//出度表
    vector<int> visited;//课程标记数组
    bool valid = true;

public:
    void dfs(int u) {
        visited[u] = 1;//标记该节点状态为搜索中
//遍历该课程的出度表，即该课程之前的课程
        for (int &v: out_degree[u]) {
            if (visited[v] == 0) {
                dfs(v);
                if (!valid) {
                    return;
                }
            } else if (visited[v] == 1) {
                valid = false;
                return;
            }
        }
        visited[u] = 2;//标记该节点状态为已完成
    }

    bool canFinish_dfs(int numCourses, vector<vector<int>> &prerequisites) {
        out_degree.resize(numCourses);
        visited.resize(numCourses);
//构造出度表，出度表中每个节点有三种状态：未访问、已搜索、搜索中
        for (const auto &info: prerequisites) {
            out_degree[info[1]].push_back(info[0]);
        }
        for (int i = 0; i < numCourses && valid; ++i) {
            if (!visited[i]) {//该节点未访问，深搜
                dfs(i);
            }
        }
        return valid;

    }

// 210. Course Schedule II (Medium)
    vector<int> ans;
    bool find_valid = true;

    void dfs_findOrder(int course) {
        visited[course] = 1;
        for (auto &last_course:out_degree[course]) {
            if (visited[last_course] == 0) {
                dfs_findOrder(last_course);
            } else if (visited[last_course] == 1) {
                find_valid = false;
                return;
            }
        }
        visited[course] = 2;
        ans.emplace_back(course);
    }

    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
        visited.resize(numCourses);
        out_degree.resize(numCourses);
        for (auto prerequisite : prerequisites) {
            out_degree[prerequisite[1]].emplace_back(prerequisite[0]);
        }
        for (int i = 0; i < numCourses && find_valid; ++i) {
            if (visited[i] == 0) {
                dfs_findOrder(i);
            }
        }
        if (ans.size() != numCourses) return {};
        reverse(ans.begin(), ans.end());
        return ans;
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