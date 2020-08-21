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
// 79. Word Search (Medium)
// 257. Binary Tree Paths (Easy)
// 46. Permutations (Medium)
// 47. Permutations II (Medium)
// 77. Combinations (Medium)
// 78. Subsets (Medium)
// 39. Combination Sum (Medium)
// 40. Combination Sum II (Medium)
// 216. Combination Sum III (Medium)
// 90. Subsets II (Medium)
// 131. Palindrome Partitioning (Medium)
// 37. Sudoku Solver (Hard)
// 51. N-Queens (Hard)

#include <vector>
#include <queue>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <stack>

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

        int depth = biDirectionBfs(wordset, beginQ, endQ, begintoend, endtobegin);

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
                std::swap(beginQ,
                          endQ); //交换的意义在于，后面代码我们只准备用一个队列变量来进行搜索，所以要把较短的队列统一到beginQ上，便于后面做搜索，当然也可以重新写个bfs函数，就不需要交换了。
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
                std::swap(beginQ, endQ);
            }
        }
        return 0;
    }

// 695. Max Area of Island (Medium)
    int area(vector<vector<int>> &grid, int r, int c) {
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

    int maxAreaOfIsland(vector<vector<int>> &grid) {
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
    void dfs(vector<vector<int>> &M, vector<int> &visited, int i) {
        for (int j = 0; j < M.size(); j++) {
            if (M[i][j] == 1 && visited[j] == 0) {
                visited[j] = 1;
                dfs(M, visited, j);
            }
        }
    }

    int findCircleNum(vector<vector<int>> &M) {
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

    void dfs(vector<vector<char>> &board, int x, int y) {
        if (x < 0 || x >= n || y < 0 || y >= m || board[x][y] != 'O') {
            return;
        }
        board[x][y] = 'A';
        dfs(board, x + 1, y);
        dfs(board, x - 1, y);
        dfs(board, x, y + 1);
        dfs(board, x, y - 1);
    }

    void solve(vector<vector<char>> &board) {
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
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}
    };
    //2. 存储最终结果和临时结果的变量
    vector<string> ans;
    string current;

    //3. DFS函数，index是生成临时结果字串的下标，
    //每一个digits[index]数字对应临时结果current[index]的一位字母
    void DFS(int index, string digits) {
        //出口
        if (index == digits.size()) {
            ans.push_back(current);
            return;
        }
        //递归调用
        //对于当前输入的第index号数字(digits[index])，
        //枚举其对应的所有字母(M[digits[index]][i])
        string letters = M[digits[index]];
        for (int i = 0; i < letters.size(); i++) {
            current.push_back(letters[i]);     //临时结果压入一个字母
            DFS(index + 1, digits);         //以在当前位置压入该字母这一“情况”为前提，构造此“分支”的后续结果
            current.pop_back();             //状态还原，例如临时结果从 "ab" -> "a"，下一次循环尝试"ac"
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) return ans;

        DFS(0, digits);
        return ans;
    }

// 93. Restore IP Addresses(Medium)
private:
    static constexpr int SEG_COUNT = 4;

private:
    vector<int> segments;//网段

public:
    void dfs(const string &s, int segId, int segStart) {
        // 如果找到了 4 段 IP 地址并且遍历完了字符串，那么就是一种答案
        if (segId == SEG_COUNT) {
            if (segStart == s.size()) {//遍历完字符串了
                string ipAddr;
                for (int i = 0; i < SEG_COUNT; ++i) {
                    ipAddr += to_string(segments[i]);//每段数字的网段转换成字符串
                    if (i != SEG_COUNT - 1) {
                        ipAddr += ".";
                    }
                }
                ans.push_back(move(ipAddr));
            }
            return;
        }

        // 如果还没有找到 4 段 IP 地址就已经遍历完了字符串，那么提前回溯
        if (segStart == s.size()) {
            return;
        }

        // 由于不能有前导零，如果当前数字为 0，那么这一段 IP 地址只能为 0
        if (s[segStart] == '0') {
            segments[segId] = 0;
            dfs(s, segId + 1, segStart + 1);
        }

        // 一般情况，枚举每一种可能性并递归
        int addr = 0;
        for (int segEnd = segStart; segEnd < s.size(); ++segEnd) {
            addr = addr * 10 + (s[segEnd] - '0');//更新网段地址
            if (addr > 0 && addr <= 0xFF) {//小于256且不为零
                segments[segId] = addr;
                dfs(s, segId + 1, segEnd + 1);
            } else {
                break;
            }
        }
    }

    vector<string> restoreIpAddresses(string s) {
        segments.resize(SEG_COUNT);
        dfs(s, 0, 0);
        return ans;
    }

// 79. Word Search (Medium)
    bool exist(vector<vector<char>> &board, string word) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (backtrack(board, word, 0, i, j)) { // 从二维表格的每一个格子出发
                    return true;
                }
            }
        }
        return false;
    }

private:
    bool backtrack(vector<vector<char>> &board, string &word, int wordIndex, int x, int y) {
        if (board[x][y] != word[wordIndex]) { // 当前位的字母不相等，此路不通
            return false;
        }
        if (word.size() - 1 == wordIndex) { // 最后一个字母也相等, 返回成功
            return true;
        }
        char tmp = board[x][y];
        board[x][y] = 0; // 避免该位重复使用
        wordIndex++;
        if ((x > 0 && backtrack(board, word, wordIndex, x - 1, y)) // 往上走
            || (y > 0 && backtrack(board, word, wordIndex, x, y - 1)) // 往左走
            || (x < board.size() - 1 && backtrack(board, word, wordIndex, x + 1, y)) // 往下走
            || (y < board[0].size() - 1 && backtrack(board, word, wordIndex, x, y + 1))) { // 往右走
            return true; // 其中一条能走通，就算成功
        }
        //精髓!!!!!
        board[x][y] = tmp; // 如果都不通，则回溯上一状态
        return false;
    }

// 257. Binary Tree Paths (Easy)
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    vector<string> tree_path;
    string one_path;

    void find_tree_path(TreeNode *root) {
        string temp_path = one_path;
        if (!one_path.empty()) one_path += "->";
        one_path += to_string(root->val);
        //到叶子结点，返回路径，回溯
        if (root->left == nullptr && root->right == nullptr) {
            tree_path.push_back(one_path);
            //弹出当前结点
            one_path = temp_path;
            return;
        }
        if (root->left) find_tree_path(root->left);
        if (root->right) find_tree_path(root->right);
        //弹出当前结点
        one_path = temp_path;
    }

    vector<string> binaryTreePaths(TreeNode *root) {
        if (root == nullptr) return tree_path;
        find_tree_path(root);
        return tree_path;
    }

// 46. Permutations (Medium)
    vector<vector<int>> permute_ans;
    vector<bool> isvisited;

    void swap(vector<int> &nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    void permute_dfs(vector<int> &nums, int change_loc, int size) {
        if (change_loc == nums.size()) {
            permute_ans.push_back(nums);
            return;
        }

        for (int i = change_loc; i < size; i++) {
            if (i != 0 && nums[i] == nums[i - 1] && isvisited[i - 1] == 1) continue;
            isvisited[i] = 1;
            swap(nums, i, change_loc);//交换结点
            permute_dfs(nums, change_loc + 1, size);
            swap(nums, change_loc, i);//交换结点
        }
    }

    vector<vector<int>> permute(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        int size = nums.size();
        isvisited.resize(nums.size(), 0);
        permute_dfs(nums, 0, size);
        return permute_ans;
    }

// 47. Permutations II (Medium)
public:
    vector<vector<int> > result;

    void func(vector<int> &nums, vector<int> &current, vector<int> &freq, int n) {
        //freq：记录排序后每个元素的个数数组
        //nums：去重且排好序的nums
        if (current.size() == n)//完成一次排列
            result.push_back(current);
        else {
            for (int i = 0; i < nums.size(); i++) {
                if (freq[i]) {
                    current.push_back(nums[i]);
                    freq[i]--;
                    func(nums, current, freq, n);
                    freq[i]++;
                    current.pop_back();
                }
            }
        }
    }

    vector<vector<int>> permuteUnique(vector<int> &nums) {
        if (nums.size() == 0)
            return {};
        else if (nums.size() == 1)
            return {{nums[0]}};
        else {
            sort(nums.begin(), nums.end());
            vector<int> freq;//记录排序后每个元素的个数数组
            vector<int> temp;//去重且排好序的nums
            temp.push_back(nums[0]);
            freq.push_back(1);
            for (int i = 1; i < nums.size(); i++) {
                if (nums[i] == temp[temp.size() - 1])//nums[i]比较的是重构数组里面的最后一个元素！
                {
                    freq[freq.size() - 1]++;//freq数组的最后一个元素的次数++
                } else {
                    temp.push_back(nums[i]);
                    freq.push_back(1);
                }
            }
            vector<int> current;
            func(temp, current, freq, nums.size());
            return result;
        }
    }

// 77. Combinations (Medium)
    vector<vector<int>> res;

    vector<vector<int>> combine(int n, int k) {
        if (k <= 0 || n <= 0) return res;
        vector<int> track;
        backtrack(n, k, 1, track);
        return res;
    }

    void backtrack(int n, int k, int start, vector<int> &track) {
        // 到达树的底部
        if (k == track.size()) {
            res.push_back(track);
            return;
        }
        // 注意 i 从 start 开始递增
        for (int i = start; i <= n; i++) {
            // 做选择
            track.push_back(i);
            backtrack(n, k, i + 1, track);
            // 撤销选择
            track.pop_back();
        }
    }


// 78. Subsets (Medium)
    vector<vector<int>> subsets(vector<int> &nums) {
// base case，返回一个空集
        if (nums.empty()) return {{}};
// 把最后一个元素拿出来
        int n = nums.back();
        nums.pop_back();
// 先递归算出前面元素的所有子集
        vector<vector<int>> res = subsets(nums);
//subsets(A[1,...,n,j]) = subsets(A[1,...n]) + subsets(A[1,,,n]).pushback(j)
        int size = res.size();
        for (int i = 0; i < size; i++) {
            // 然后在之前的结果之上追加
            res.push_back(res[i]);
            res.back().push_back(n);
        }
        return res;
    }

// 39. Combination Sum (Medium)
    vector<vector<int>> com_ans;

    void com_dfs(int target, vector<int> &cur, int cur_num, vector<int> &candidates) {
        if (0 == target) {//等于，存入答案
            com_ans.push_back(cur);
            return;
        }
        for (int i = cur_num; i < candidates.size() && target >= candidates[i]; i++) {
            cur.push_back(candidates[i]);
            com_dfs(target - candidates[i], cur, i, candidates);
            cur.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> cur;
        com_dfs(target, cur, 0, candidates);
        return com_ans;
    }

// 40. Combination Sum II (Medium)
    vector<vector<int>> com2_ans;

    void com2_dfs(int target, vector<int> &cur, int cur_num, vector<int> &candidates) {
        if (0 == target) {//等于，存入答案
            com2_ans.push_back(cur);
            return;
        }
        for (int i = cur_num; i < candidates.size() && target >= candidates[i]; ++i) {
            if (i > cur_num && candidates[i] == candidates[i - 1]) continue; //剪枝2
            cur.push_back(candidates[i]);
            com2_dfs(target - candidates[i], cur, i + 1, candidates);
            cur.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> cur;
        com2_dfs(target, cur, 0, candidates);
        return com2_ans;
    }

// 216. Combination Sum III (Medium)
    vector<vector<int>> com3_ans;

    void com3_dfs(int target, vector<int> &cur, int cur_num, int k) {
        if (0 == target && k == 0) {//等于，存入答案
            com3_ans.push_back(cur);
            return;
        }
        for (int i = cur_num; i < 10 && target >= i && k > 0; i++) {
            cur.push_back(i);
            if (target - i < i + 1) {
                com3_dfs(target - i, cur, i + 1, k - 1);
            }
            cur.pop_back();
        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> cur;
        com3_dfs(n, cur, 1, k);
        return com3_ans;
    }

// 90. Subsets II (Medium)
    vector<vector<int>> subset_ans;

    void subset_dfs(vector<int> &nums, vector<int> cur, int cur_num) {
        subset_ans.push_back(cur);
        for (int i = cur_num; i < nums.size(); ++i) {
            if (i > cur_num && nums[i - 1] == nums[i]) continue;
            cur.push_back(nums[i]);
            subset_dfs(nums, cur, i + 1);
            cur.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        vector<int> cur;
        subset_dfs(nums, cur, 0);
        return subset_ans;
    }

// 131. Palindrome Partitioning (Medium)
    vector<vector<string>> p_res;
    int size;

    bool check(const string &s, int i, int j) {//判断s[i...j]是不是回文字符串
        if (j <= i) return true;
        if (s[i++] == s[j--]) return check(s, i, j);
        else return false;
    }

    void backtrack(const string &s, int ps, vector<string> &temp) {
        if (ps >= size) {
            p_res.push_back(temp);
            return;
        }
        for (int i = ps; i < size; ++i) {
            if (check(s, ps, i)) {//是回文字符串
                temp.push_back(s.substr(ps, i - ps + 1));
                backtrack(s, i + 1, temp);
                temp.pop_back();
            }
        }
    }

    vector<vector<string>> partition(const string &s) {
        size = s.size();
        if (size == 0) return p_res;
        vector<string> temp;
        backtrack(s, 0, temp);
        return p_res;
    }

// 37. Sudoku Solver (Hard)
    //行，列，小格内某数字是否已填标记
    bool visitRow[9][9] = {false};
    bool visitCol[9][9] = {false};
    bool visitBox[9][9] = {false};
    int num = 0;

    void solveSudoku(vector<vector<char>> &board) {
        //先记录表格中的初始状态
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {//非空白格
                    visitRow[i][board[i][j] - '1'] = true;
                    visitCol[j][board[i][j] - '1'] = true;
                    visitBox[(i / 3) * 3 + j / 3][board[i][j] - '1'] = true;
                }
            }
        }
        backTrack(board, 0, 0);
    }

    bool backTrack(vector<vector<char>> &board, int row, int col) {
        //找到没填的
        while (board[row][col] != '.') {
            if (++col >= 9) {
                col = 0;
                row++;
            }
            //填满了
            if (row >= 9)
                return true;
        }
        for (int i = 0; i < 9; i++) {
            int boxIndex = (row / 3) * 3 + col / 3;//定位小九宫格
            //已经填了
            if (visitRow[row][i] || visitCol[col][i] || visitBox[boxIndex][i])
                continue;
            board[row][col] = i + '1';//填数
            visitRow[row][i] = true;
            visitCol[col][i] = true;
            visitBox[boxIndex][i] = true;//更新标记
            if (backTrack(board, row, col)) {
                return true;
            } else {
                //最后无法填满,回溯
                board[row][col] = '.';
                visitRow[row][i] = false;
                visitCol[col][i] = false;
                visitBox[boxIndex][i] = false;
            }
        }
        return false;
    }

// 51. N-Queens (Hard)
    vector<vector<string>> queen_res;
    vector<string> board;

/* 输入棋盘边长 n，返回所有合法的放置 */
    vector<vector<string>> solveNQueens(int n) {
        // '.' 表示空，'Q' 表示皇后，初始化空棋盘。
        board.resize(n, string(n, '.'));
        backtrack(0);
        return queen_res;
    }

// 路径：board 中小于 row 的那些行都已经成功放置了皇后
// 选择列表：第 row 行的所有列都是放置皇后的选择
// 结束条件：row 超过 board 的最后一行
    void backtrack(int row) {
        // 触发结束条件
        if (row == board.size()) {
            queen_res.push_back(board);
            return;
        }

        int n = board[row].size();
        for (int col = 0; col < n; col++) {
            // 排除不合法选择
            if (!isValid(row, col))
                continue;
            // 做选择
            board[row][col] = 'Q';
            // 进入下一行决策
            backtrack(row + 1);
            // 撤销选择
            board[row][col] = '.';
        }
    }

/* 是否可以在 board[row][col] 放置皇后？ */
    bool isValid(int row, int col) {
        int n = board.size();
        // 检查列是否有皇后互相冲突
        for (int i = 0; i < n; i++) {
            if (board[i][col] == 'Q')
                return false;
        }
        // 检查右上方是否有皇后互相冲突
        for (int i = row - 1, j = col + 1;
             i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q')
                return false;
        }
        // 检查左上方是否有皇后互相冲突
        for (int i = row - 1, j = col - 1;
             i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q')
                return false;
        }
        return true;
    }


};

int main() {
    Solution s;
    vector<int> test = {1, 2, 2, 5, 2};
    s.partition("aab");
}