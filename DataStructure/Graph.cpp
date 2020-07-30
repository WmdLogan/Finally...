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
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
//拓扑排序
        vector<int> indegree(numCourses, 0);//每个点的入度值
        vector<vector<int>> graph(numCourses);//入度表
//构造入度表
        for (int i = 0; i < prerequisites.size(); i++) {
            indegree[prerequisites[i][0]]++;
            graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }
//将入度为0的顶点入队
        queue<int> myqueue;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0)
                myqueue.push(i);
        }
        int cnt = 0;
        while (!myqueue.empty()) {
            int temp = myqueue.front();
            myqueue.pop();
            cnt++;
            //更新：
            for (int i = 0; i < graph[temp].size(); i++) {
                indegree[graph[temp][i]]--;
                if (indegree[graph[temp][i]] == 0)
                    myqueue.push(graph[temp][i]);
            }
        }
        return cnt == numCourses;
    }

// 210. Course Schedule II (Medium)
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
        vector<int> indegree(numCourses, 0);//每个点的入度值
        vector<vector<int>> graph(numCourses);//入度表
        vector<int> ans(numCourses);
//构造入度表
        for (int i = 0; i < prerequisites.size(); i++) {
            indegree[prerequisites[i][0]]++;
            graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }
//将入度为0的顶点入队
        queue<int> myqueue;
        int cnt = 0;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                myqueue.push(i);
                ans[cnt] = i;
                cnt++;
            }
        }
        while (!myqueue.empty() && cnt < numCourses) {
            int temp = myqueue.front();
            myqueue.pop();
            for (int i = 0; i < graph[temp].size(); i++) {
                indegree[graph[temp][i]]--;
                if (indegree[graph[temp][i]] == 0) {
                    myqueue.push(graph[temp][i]);
                    ans[cnt] = graph[temp][i];
                    cnt++;
                }
            }
        }
        if (cnt == numCourses) {
            return ans;
        }
        return {};
    }
// 684. Redundant Connection (Medium)
    vector<int> rp;
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int sz = edges.size();
        // 初始化各元素为单独的集合，代表节点就是其本身
        for (int i = 0; i < sz; i++)
            rp.push_back(-1);
        for(int j=0;j<sz;j++){
            // 找到边上两个节点所在集合的代表节点
            int set1 = find(edges[j][0]);
            int set2 = find(edges[j][1]);
            if(set1 == set2)  // 两个集合代表节点相同，说明出现环，返回答案
                return edges[j];
            else    // 两个集合独立，合并集合。将前一个集合代表节点戳到后一个集合代表节点上
                rp[set1] = set2;
        }
        return {0, 0};
    }

    int find(int n){
        if (rp[n] < 0) return n;
        return find(rp[n]);
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