//
// Created by logan on 2020/7/30.
//
// 785. Is Graph Bipartite? (Medium)
// 207. Course Schedule (Medium)
#include <stack>
#include <deque>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
// 785. Is Graph Bipartite? (Medium)
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> color(graph.size(), -1);
        stack<int> color_stack;
        for (int i = 0; i < graph.size(); ++i) {
            if (color[i] == -1) {
                color_stack.push(i);
                color[i] = 0;

                while (!color_stack.empty()) {
                    int index = color_stack.top();
                    color_stack.pop();
                    int j;
                    for (j = 0; j < graph[index].size(); j++) {
                        if (color[graph[index][j]] == -1) {
                            color[graph[index][j]] = color[index] ^ 1;
                            color_stack.push(graph[index][j]);
                        } else {
                            if (color[graph[index][j]] != color[index] ^ 1) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }
// 207. Course Schedule (Medium)
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
//拓扑排序
        vector<int> indegree(numCourses,0);//每个点的入度值
        vector<vector<int>> graph(numCourses);//入度表
//构造入度表
        for (int i = 0; i < prerequisites.size(); i++)
        {
            indegree[prerequisites[i][0]]++;
            graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }
//将入度为0的顶点入队
        queue<int> myqueue;
        for (int i = 0; i < numCourses; i++)
        {
            if (indegree[i] == 0)
                myqueue.push(i);
        }
        int cnt = 0;
        while (!myqueue.empty())
        {
            int temp = myqueue.front();
            myqueue.pop();
            cnt++;
            //更新：
            for (int i = 0; i < graph[temp].size(); i++)
            {
                indegree[graph[temp][i]]--;
                if (indegree[graph[temp][i]] == 0)
                    myqueue.push(graph[temp][i]);
            }
        }
        return cnt == numCourses;
    }
};