//
// Created by logan on 2020/8/12.
//
// 1091. Shortest Path in Binary Matrix(Medium)
// 279. Perfect Squares (Medium)
// 127. Word Ladder (Medium)
// 695. Max Area of Island (Medium)
// 200. Number of Islands (Medium)
// 547. Friend Circles (Medium)
// 130. Surrounded Regions (Medium)
// 417. Pacific Atlantic Water Flow (Medium)
// 17. Letter Combinations of a Phone Number (Medium)
// 93. Restore IP Addresses(Medium)
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
// 1091. Shortest Path in Binary Matrix(Medium)
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

// 279. Perfect Squares (Medium)
//动态规划
    int numSquares_dp(int n) {
        vector<int> result(n + 1, 0x7FFFFFFF); // 每个数的最优解都存在result数组里
        result[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; i - j * j >= 0; j++) {  // 观察比N小的数，且符合N = IxI + N'的数值
                result[i] = min(result[i], result[i - j * j] + 1); // 把最优解（最小值）+ 1 写入result
            }
        }
        return result[n];
    }
//将此题目抽象为，要从n走到0，每次跨越的距离只能为平方数，求最少的跨越次数。很自然用标准的BFS去解决
    /*返回小于n的平方序列: 1, 4, 9...*/
    vector<int> getSquares(int n) {
        vector<int> res;
        for (int i = 1; i * i <= n; ++i) {
            res.emplace_back(i * i);
        }
        return res;
    }

    int numSquares(int n) {
        vector<int> squares = getSquares(n);
        vector<bool> visited(n + 1);    //记录已访问过的节点
        queue<int> q;

        q.push(n);
        int res = 0;
        visited[n] = true;
        while (!q.empty()) {
            int size = q.size();
            res++;
            while (size--) {
                int curr = q.front();
                q.pop();
                /*每次跨越的间隔为平方数*/
                for (int num: squares) {
                    int next = curr - num;
                    if (next < 0) {
                        break;
                    }
                    if (next == 0) {
                        return res;
                    }
                    if (visited[next]) {
                        continue;
                    }
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        return n;
    }

// 127. Word Ladder (Medium)
    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
        unordered_set<string> wordset{wordList.begin(), wordList.end()}; //处理endWord不在wordList中的特殊情况
        if (wordset.find(endWord) == wordset.end()) return 0;
        unordered_set<string> begintoend{beginWord}; //用来存放从起点开始，匹配到的单词
        unordered_set<string> endtobegin{endWord};//用来存放从终点开始，匹配到的单词

        queue<string> beginQ; //从起点开始，可能的单词入队
        queue<string> endQ; //从终点开始，可能的单词入队
        beginQ.push(beginWord);
        endQ.push(endWord);

        int depth = biDirectionBfs( wordset, beginQ, endQ, begintoend, endtobegin);

        return depth;
    }

    int biDirectionBfs(unordered_set<string> &wordset,
                       queue<string> &beginQ, queue<string> &endQ,
                       unordered_set<string> &begintoend,
                       unordered_set<string> &endtobegin) {
        int depth = 0;
        while (!beginQ.empty() && !endQ.empty()) {  //任何一个队列为空，都是线索断了的意思，所以要用&&
            int flag_begintoend = 1;
            if (beginQ.size() > endQ.size()) { //这里选择一个较短的队列进行搜索
                swap(beginQ, endQ); //交换的意义在于，后面代码我们只准备用一个队列变量来进行搜索，所以要把较短的队列统一到beginQ上，便于后面做搜索，当然也可以重新写个bfs函数，就不需要交换了。
                flag_begintoend = 0; //flag用于判断下方代码while使用的BeginQ是真的BeginQ，还是假的BeginQ
            } else {
                flag_begintoend = 1;
            }

            int size = beginQ.size(); //当前较短队列中存放的元素个数
            depth++;
            while (size--) {
                string hop = beginQ.front();
                beginQ.pop();

                for (int i = 0; i < hop.size(); i++) {
                    string w_change = hop;
                    for (char j = 'a'; j <= 'z'; j++) {
                        w_change[i] = j;
                        if (wordset.find(w_change) == wordset.end()) {
                            continue;
                        }
                        //排除重复遍历单词
                        //当前beginQ是begintoend的路径上的元素
                        if (flag_begintoend && begintoend.find(w_change) != begintoend.end())
                            continue;
                        //当前beginQ是endtobegin的路径上的元素
                        if (!flag_begintoend && endtobegin.find(w_change) != endtobegin.end())
                            continue;

                        if (flag_begintoend) {
                            begintoend.insert(w_change);
                            if (endtobegin.find(w_change) != endtobegin.end()) return depth + 1;
                        } else {
                            endtobegin.insert(w_change);
                            if (begintoend.find(w_change) != begintoend.end()) return depth + 1;
                        }
                        beginQ.push(w_change);
                    }
                }
            }
            //最后还是需要还原队列对应关系
            if (!flag_begintoend) {
                swap(beginQ, endQ);
            }
        }
        return 0;
    }

// 695. Max Area of Island (Medium)
    int area(vector<vector<int>>& grid, int r, int c) {
        if (!(0 <= r && r < grid.size()
              && 0 <= c && c < grid[0].size())) {
            return 0;
        }
        if (grid[r][c] != 1) {
            return 0;
        }
        grid[r][c] = 2;
        return 1
               + area(grid, r - 1, c)
               + area(grid, r + 1, c)
               + area(grid, r, c - 1)
               + area(grid, r, c + 1);
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int res = 0;
        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[0].size(); c++) {
                if (grid[r][c] == 1) {
                    int a = area(grid, r, c);
                    res = max(res, a);
                }
            }
        }
        return res;
    }

// 200. Number of Islands (Medium)
    void area(vector<vector<char>> &grid, int r, int c) {
        if (0 > r || r >= grid.size() || 0 > c || c >= grid[0].size() || grid[r][c] != '1') return;

        grid[r][c] = '2';
        area(grid, r - 1, c);
        area(grid, r + 1, c);
        area(grid, r, c - 1);
        area(grid, r, c + 1);
    }

    int numIslands(vector<vector<char>> &grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int res = 0;
        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[0].size(); c++) {
                if (grid[r][c] == '1') {
                    area(grid, r, c);
                    res++;
                }
            }
        }
        return res;
    }


// 547. Friend Circles (Medium)
    void dfs(vector<vector<int>> &M, vector<int> &visited, int i){
        for (int j = 0; j < M.size(); j++) {
            if (M[i][j] == 1 && visited[j] == 0) {
                visited[j] = 1;
                dfs(M, visited, j);
            }
        }
    }
    int findCircleNum(vector<vector<int>>& M) {
        vector<int> visited(M.size(), 0);
        int count = 0;
        for (int i = 0; i < M.size(); i++) {
            if (visited[i] == 0) {
                dfs(M, visited, i);
                count++;
            }
        }
        return count;
    }

// 130. Surrounded Regions (Medium)
    int n, m;

    void dfs(vector<vector<char>>& board, int x, int y) {
        if (x < 0 || x >= n || y < 0 || y >= m || board[x][y] != 'O') {
            return;
        }
        board[x][y] = 'A';
        dfs(board, x + 1, y);
        dfs(board, x - 1, y);
        dfs(board, x, y + 1);
        dfs(board, x, y - 1);
    }

    void solve(vector<vector<char>>& board) {
        n = board.size();
        if (n == 0) {
            return;
        }
        m = board[0].size();
        for (int i = 0; i < n; i++) {
            dfs(board, i, 0);
            dfs(board, i, m - 1);
        }
        for (int i = 1; i < m - 1; i++) {
            dfs(board, 0, i);
            dfs(board, n - 1, i);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'A') {
                    board[i][j] = 'O';
                } else if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }

// 417. Pacific Atlantic Water Flow (Medium)
    int dirs[4][2] = {{-1, 0},
                      {1,  0},
                      {0,  -1},
                      {0,  1}};

    bool valid(int r, int c, int R, int C) {
        return r >= 0 && r < R && c >= 0 && c < C;
    }//判断节点是否有效
//题目意思是每个点都是泉水的出发点
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &matrix) {
        vector<vector<int> > res;
        if (matrix.empty()) return res;
        int R = matrix.size();//行数
        int C = matrix[0].size();//列数
        vector<vector<int> > status(R, vector<int>(C, 0));
        //R * C的全0矩阵
        //第一位存储太平洋能否到达，第二位存储大西洋能否到达，3（11）表示均能到达
        queue<pair<int, int> > q;//队列中为可流通的节点
        //边界节点入队，太平洋和大西洋标志位置1
        for (int i = 0; i < R; ++i) {
            q.push({i, 0});
            status[i][0] |= 1;
            q.push({i, C - 1});
            status[i][C - 1] |= 2;
        }
        for (int i = 0; i < C; ++i) {
            q.push({0, i});
            status[0][i] |= 1;
            q.push({R - 1, i});
            status[R - 1][i] |= 2;
        }
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i) {
                //计算四个方向的坐标
                int r = p.first + dirs[i][0];
                int c = p.second + dirs[i][1];
                //坐标有效且能流通（逆向流通）
                if (valid(r, c, R, C) && matrix[r][c] >= matrix[p.first][p.second]) {
                    if (status[r][c] != status[p.first][p.second]) {
                        status[r][c] |= status[p.first][p.second];
                        q.push({r, c});
                    }
                }
            }
        }
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (status[i][j] == 3) {
                    res.push_back({i, j});
                }
            }
        }
        return res;
    }

// 17. Letter Combinations of a Phone Number (Medium)
    //1. 用map记录每个数字按键对应的所有字母
    unordered_map<char, string> M = {
            {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"},
            {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
    };
    //2. 存储最终结果和临时结果的变量
    vector<string> ans;
    string current;

    //3. DFS函数，index是生成临时结果字串的下标，
    //每一个digits[index]数字对应临时结果current[index]的一位字母
    void DFS(int index, string digits) {
        //出口
        if(index == digits.size()) {
            ans.push_back(current);
            return;
        }
        //递归调用
        //对于当前输入的第index号数字(digits[index])，
        //枚举其对应的所有字母(M[digits[index]][i])
        string letters = M[digits[index]];
        for(int i = 0; i < letters.size(); i++) {
            current.push_back(letters[i]);     //临时结果压入一个字母
            DFS(index + 1, digits);         //以在当前位置压入该字母这一“情况”为前提，构造此“分支”的后续结果
            current.pop_back();             //状态还原，例如临时结果从 "ab" -> "a"，下一次循环尝试"ac"
        }
    }

    vector<string> letterCombinations(string digits) {
        if(digits.size() == 0)  return ans;

        DFS(0, digits);
        return ans;
    }

// 93. Restore IP Addresses(Medium)
};

int main() {
    Solution s;

    vector<string> ans = {"hot", "dot", "dog", "lot", "log", "cog"};
    cout << s.ladderLength("hit", "cog", ans);
}
