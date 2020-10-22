//
// Created by logan on 2020/8/21.
//
// 70. Climbing Stairs (Easy)
// 198. House Robber (Easy)
// 213. House Robber II (Medium)
// 337. House Robber III (Medium)
// 64. Minimum Path Sum (Medium)
// 62. Unique Paths (Medium)
// 413. Arithmetic Slices (Medium)
// 343. Integer Break (Medim)
// 279. Perfect Squares (Medium)
// 91. Decode Ways (Medium)
// 300. Longest Increasing Subsequence (Medium)
// 646. Maximum Length of Pair Chain (Medium)
// 376. Wiggle Subsequence (Medium)
// 1143. Longest Common Subsequence
// 416. Partition Equal Subset Sum (Medium)
// 494. Target Sum (Medium)
// 474. Ones and Zeroes (Medium)
// 322. Coin Change (Medium)
// 139. Word Break (Medium)
// 377. Combination Sum IV (Medium)
// 309. Best Time to Buy and Sell Stock with Cooldown(Medium)
// 714. Best Time to Buy and Sell Stock with Transaction Fee (Medium)
// 123. Best Time to Buy and Sell Stock III (Hard)
// 188. Best Time to Buy and Sell Stock IV (Hard)
// 583. Delete Operation for Two Strings (Medium)
// 72. Edit Distance (Hard)
// 650. 2 Keys Keyboard (Medium)


#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>

using namespace std;

class Solution {
// 70. Climbing Stairs (Easy)
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        int pre2 = 1, pre1 = 2;
        for (int i = 2; i < n; i++) {
            int cur = pre1 + pre2;
            pre2 = pre1;
            pre1 = cur;
        }
        return pre1;
    }

// 198. House Robber (Easy)
    int rob(vector<int> &nums) {
        //pre2 = dp[i-2], pre1 = dp[i-1]
        int pre2 = 0, pre1 = 0;
        for (int i = 0; i < nums.size(); i++) {
            int cur = max(pre2 + nums[i], pre1);//（选当前的不选上一个，不选当前的）
            pre2 = pre1;
            pre1 = cur;
        }
        return pre1;
    }

// 213. House Robber II (Medium)
//分两种情况，偷第一间不偷最后一间、偷最后一间不偷第一间
    int rob_2(vector<int> &nums) {
        int size = nums.size();
        if (size == 1) return nums[0];
        return max(rob_range(nums, 0, size - 2),
                   rob_range(nums, 1, size - 1));
    }

    int rob_range(vector<int> &nums, int start, int end) {
        int dp_i_1 = 0, dp_i_2 = 0;
        int dp_i = 0;
        for (int i = end; i >= start; i--) {
            dp_i = max(dp_i_1, nums[i] + dp_i_2);
            dp_i_2 = dp_i_1;
            dp_i_1 = dp_i;
        }
        return dp_i;
    }

// 337. House Robber III (Medium)
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    struct SubtreeStatus {
        int selected;
        int notSelected;
    };

    SubtreeStatus dfs(TreeNode *o) {
        if (!o) {
            return {0, 0};
        }
        auto l = dfs(o->left);
        auto r = dfs(o->right);
        int selected = o->val + l.notSelected + r.notSelected;
        int notSelected = max(l.selected, l.notSelected) + max(r.selected, r.notSelected);
        return {selected, notSelected};
    }

    int rob(TreeNode *o) {
        auto rootStatus = dfs(o);
        return max(rootStatus.selected, rootStatus.notSelected);
    }


// 64. Minimum Path Sum (Medium)
    int minPathSum(vector<vector<int>> &grid) {
//dp[i][j] = max(dp[i-1][j],dp[i][j-1]
        if (grid.size() == 0 || grid[0].size() == 0) {
            return 0;
        }
        int rows = grid.size(), columns = grid[0].size();
        auto dp = vector<vector<int> >(rows, vector<int>(columns));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < rows; i++) {//每行第一个元素只能由上方的元素得到
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int j = 1; j < columns; j++) {//每列第一个元素只能由左方的元素得到
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        for (int i = 1; i < rows; i++) {
            for (int j = 1; j < columns; j++) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[rows - 1][columns - 1];
    }

// 62. Unique Paths (Medium)
    int uniquePaths(int m, int n) {
        //dp[i][j] = dp[i-1][j] + dp[i][j-1]
        if (m == 0 || n == 0) {
            return 1;
        }
        auto dp = vector<vector<int> >(m, vector<int>(n, 1));
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }

// 413. Arithmetic Slices (Medium)
    int numberOfArithmeticSlices(vector<int> &A) {
        int dp = 0;
        int sum = 0;
        for (int i = 2; i < A.size(); i++) {
            if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
                dp = 1 + dp;
                sum += dp;
            } else
                dp = 0;
        }
        return sum;

    }

// 343. Integer Break (Medim)
    int integerBreak(int n) {
        vector<int> dp(n + 1);
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i - 1; j++) {
                dp[i] = max(dp[i], max(j * dp[i - j], j * (i - j)));
            }
        }
        return dp[n];
    }

// 279. Perfect Squares (Medium)
    vector<int> getSquares(int n) {
        vector<int> res;
        for (int i = 1; i * i <= n; ++i) {
            res.emplace_back(i * i);
        }
        return res;
    }

    int numSquares(int n) {
        vector<int> squares = getSquares(n);
        vector<bool> zhu(n + 1);    //记录已访问过的节点
        queue<int> q;

        q.push(n);
        int res = 0;//层数
        zhu[n] = true;
        while (!q.empty()) {
            int size = q.size();
            res++;//层数
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
                    if (zhu[next]) {
                        continue;
                    }
                    zhu[next] = true;
                    q.push(next);
                }
            }
        }
        return n;
    }

// 91. Decode Ways (Medium)
    int numDecodings(string s) {
        if (s[0] == '0') return 0;
        int pre = 1, curr = 1;//dp[-1] = dp[0] = 1 ,pre=dp[i-2],curr=de[i-1]
        for (int i = 1; i < s.size(); i++) {
            int tmp = curr;//tmp = dp[i-1] , pre = dp[i-2]
            if (s[i] == '0')
                if (s[i - 1] == '1' || s[i - 1] == '2') curr = pre;
                else return 0;
            else if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] >= '1' && s[i] <= '6'))
                curr = curr + pre;
//            else curr = curr
            pre = tmp;//dp[i-2] = dp[i-1]
        }
        return curr;
    }

// 300. Longest Increasing Subsequence (Medium)
    int lengthOfLIS(vector<int> &nums) {
        vector<int> tails(nums.size());//tails[k]代表长度为k+1的子序列尾部元素的值
        int res = 0;
        for (int num : nums) {
            int i = 0, j = res;
            while (i < j) {
                int m = (i + j) / 2;
                if (tails[m] < num) i = m + 1;
                else j = m;
            }
            tails[i] = num;
            if (res == j) res++;//长度+1
        }
        return res;
    }

// 646. Maximum Length of Pair Chain (Medium)
    int findLongestChain_1(vector<vector<int>> &pairs) {
        if (pairs.empty())return 0;
        sort(pairs.begin(), pairs.end(), [](const vector<int> &a, const vector<int> &b) {
            return (a[0] == b[0] && a[1] < b[1]) || (a[0] < b[0]);
        });
        int n = pairs.size(), res = 0;
        vector<int> dp(n, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (pairs[j][1] < pairs[i][0]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            res = max(res, dp[i]);
        }
        return res;
    }

    //解法2：动态规划+二分法，时间复杂度O(nlogn)，空间复杂度O(n)
    int findLongestChain_2(vector<vector<int>> &pairs) {
        if (pairs.empty())return 0;
        sort(pairs.begin(), pairs.end(), [](const auto &a, const auto &b) {
            return (a[0] < b[0]) || (a[0] == b[0] && a[1] < b[1]);
        });
        vector<vector<int>> dp;
        for (auto &p:pairs) {
            //二分法寻找大于等于p[0]的最小值dp[i][1]
            int left = 0, right = dp.size();
            while (left < right) {//进入while循环区间内至少有2个元素，退出循环的极值只有0或size
                int mid = left + ((right - left) >> 1);
                if (dp[mid][1] >= p[0]) right = mid;
                else left = mid + 1;
            }
            //dp[size-1][1]<p[0]，则更新最长数对链的长度
            if (left >= dp.size()) dp.emplace_back(p);
                //dp[left][1]大于（等于）p[0]同时也大于p[1]，那么我们更新dp[left]为p，这样可以将left变小，以便形成最长的数对链
            else if (dp[left][1] > p[1]) dp[left] = p;
        }
        return dp.size();
    }

// 376. Wiggle Subsequence (Medium)
    int wiggleMaxLength(vector<int> &nums) {
        int size = nums.size();
        if (size < 2) return size;
        int pre = nums[0], cur;
        int i = 1;
        int length = 1;//序列长度
        for (; i < size; i++) {//确定前两个不相等的数
            if (nums[i] != pre) {
                cur = nums[i];
                i++;
                length++;
                break;
            }
        }
        for (; i < size; i++) {
            if ((pre > cur && nums[i] > cur) || (pre < cur && nums[i] < cur)) {//上一个是升序,当前是降序，符合
                pre = cur;
                length++;
            }
            cur = nums[i];
        }
        return length;
    }

// 1143. Longest Common Subsequence
    int longestCommonSubsequence(string text1, string text2) {
// dp[i][j] 的含义是：对于 s1[1..i] 和 s2[1..j]，它们的 LCS 长度是 dp[i][j]。
        int n1 = text1.length(), n2 = text2.length();
        vector<int> temp(n2 + 1, 0);
        vector<vector<int>> dp(n1 + 1, temp);
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[n1][n2];
    }

// 416. Partition Equal Subset Sum (Medium)
// 输入一个集合，返回是否能够分割成和相等的两个子集
    bool canPartition(vector<int> &nums) {
        int sum = 0, n = nums.size();
        for (int num : nums) sum += num;
        if (sum % 2 != 0) return false;
        sum = sum / 2;
        vector<bool> dp(sum + 1, false);
        // base case
        dp[0] = true;

        for (int i = 0; i < n; i++)
            for (int j = sum; j >= 0; j--)
                if (j - nums[i] >= 0)
                    dp[j] = dp[j] || dp[j - nums[i]];
//dp[j]相当于dp[i-1][j]，状态压缩
        return dp[sum];
    }


//0-1背包
    int knapsack(int W, int N, vector<int> &wt, vector<int> &val) {
        // vector 全填入 0，base case 已初始化
        //dp[N][W]表示前N个物品，当前背包的容量为W，这种情况下可以装的最大价值
        vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));
        for (int i = 1; i <= N; i++) {
            for (int w = 1; w <= W; w++) {
                if (w - wt[i - 1] < 0) {
                    // 当前背包容量装不下，只能选择不装入背包
                    dp[i][w] = dp[i - 1][w];
                } else {
                    // 装入或者不装入背包，择优
                    dp[i][w] = max(dp[i - 1][w - wt[i - 1]] + val[i - 1],
                                   dp[i - 1][w]);
                }
            }
        }
        return dp[N][W];
    }

// 494. Target Sum (Medium)
    int findTargetSumWays(vector<int> nums, int S) {
//   2 * sum(正数) = target + sum(nums)
// 因此只要找到一个子集，令它们都取正号，并且和等于 (target + sum(nums))/2，就证明存在解。
        int sum = 0;
        for (int i:nums) {
            sum += i;
        }
        // sum+S为奇数的话不满足要求
        if ((sum % 2) != (S % 2)) {
            return 0;
        }
        // 目标和不可能大于总和
        if (S > sum) {
            return 0;
        }
        int len = (sum + S) / 2;
        vector<int> dp(len + 1);
        dp[0] = 1;

        for (int num:nums) {
            for (int i = len; i >= num; --i) {
                dp[i] += dp[i - num];
            }
        }

        return dp[len];
    }

// 474. Ones and Zeroes (Medium)
    int findMaxForm(vector<string> &strs, int m, int n) {
        int S = strs.size();
        vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));
        for (int l = 0; l < S; ++l) {
            int zero = 0;
            int one = 0;
            for (int i = 0; i < strs[l].size(); ++i) {//统计字符串中0和1的个数
                if (strs[l][i] == '0') ++zero;
                else ++one;
            }
            for (int i = m; i >= zero; --i) {
                for (int j = n; j >= one; --j) {
                    dp[i][j] = max(dp[i][j], 1 + dp[i - zero][j - one]);
                }
            }
        }
        return dp[m][n];
    }

// 322. Coin Change (Medium)
//dp法
    int coinChange(vector<int> &coins, int amount) {
        // 数组的定义：当目标金额为 i 时，至少需要 dp[i] 枚凑出。
        // 数组大小为 amount + 1，初始值也为 amount + 1
        vector<int> dp(amount + 1, amount + 1);
        // base case
        dp[0] = 0;
        // 外层 for 循环在遍历所有状态的所有取值
        for (int i = 0; i <= amount; i++) {
            // 内层 for 循环在求所有选择的最小值
            for (int coin : coins) {
                // 子问题无解，跳过
                if (i - coin < 0) continue;
                dp[i] = min(dp[i], 1 + dp[i - coin]);
            }
        }
        return (dp[amount] == amount + 1) ? -1 : dp[amount];
    }

//贪心法
    void coinChange(vector<int> &coins, int amount, int c_index, int count, int &ans) {
        if (amount == 0) {
            ans = min(ans, count);
            return;
        }
        if (c_index == coins.size()) return;

        for (int k = amount / coins[c_index]; k >= 0 && k + count < ans; k--) {
            coinChange(coins, amount - k * coins[c_index], c_index + 1, count + k, ans);
        }
    }

    int coinChange_greedy(vector<int> &coins, int amount) {
        if (amount == 0) return 0;
        sort(coins.rbegin(), coins.rend());
        int ans = amount + 1;
        coinChange(coins, amount, 0, 0, ans);
        return ans == amount + 1 ? -1 : ans;
    }

// 518. Coin Change 2 (Medium)
//完全背包问题
    int change(int amount, vector<int> &coins) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int coin : coins) {
            for (int i = 1; i <= amount; i++) {
                // 子问题无解，跳过
                if (i - coin < 0) continue;
                dp[i] += dp[i - coin];
            }
        }
        return dp[amount];
    }

// 139. Word Break (Medium)
    bool wordBreak(string s, vector<string> &wordDict) {
        int validEnd = 0;//记录所有最大的新词开头字母（最大的待匹配位置）
// i - 1 个字符是上一个词（已匹配中）的结尾字母，第 i 个字符是一个新词（待匹配）的开头字母
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;//0为true，代表一个新词的开始
        for (int i = 0; i < s.size(); i++) {
            if (i == validEnd + 1) return false;//如果当前字符已经超过了所有新词开头字母，必然匹配不中
            if (!dp[i]) continue;//false说明字符串当前位置之前未完全匹配中，剪枝
            for (auto &word : wordDict) {//因为单词可重复，所以每次匹配都遍历整个词典
                int newEnd = i + word.size();//已匹配中长度 + 待匹配单词长度
                if (newEnd > s.size()) continue;//长度超过字符串长度，剪枝
                if (memcmp(&s[i], &word[0], word.size()) == 0) {//比较当前单词与字符串当前匹配位置是否相同
                    dp[newEnd] = true;
                    validEnd = max(validEnd, newEnd);//更新最大的新词开头字母
                }
            }
        }
        return dp.back();
    }

// 377. Combination Sum IV (Medium)
// 涉及顺序的完全背包。
    int combinationSum4(vector<int> &nums, int target) {
        int N = nums.size();
        vector<unsigned long long> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; i++) {
            for (int j = 0; j < N; j++) {
                dp[i] += ((i - nums[j] >= 0) ? dp[i - nums[j]]
                                             : 0);//当i==nums[j]时，以nums[j]为结尾的所有排列就一个啊，所以可知直接使dp[0]=1实现这一目的
            }
        }
        return dp[target];

    }

// 309. Best Time to Buy and Sell Stock with Cooldown(Medium)
    int maxProfit(vector<int> &prices) {
//每天结束有三种状态：无股票非冷冻期、有股票、冷冻期
//dp[i][0] 表示第i天结束，处于可以买入的状态的收益的最大值
//dp[i][1] 表示第i天结束，手中有股票的状态的收益的最大值
//dp[i][2] 表示第i天结束，处于冷冻期的收益的最大值
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(3, -2e9));
        dp[0][0] = 0;
        for (int i = 0; i < n; i++) {
            //根据状态0/2。今天休息（状态不变）、卖了股票（转移至状态1）。
            dp[i + 1][0] = max(dp[i][0], dp[i][2]);
            //今天休息（根据状态1）、今天买入（根据状态0）。
            dp[i + 1][1] = max(dp[i][0] - prices[i], dp[i][1]);
            //根据状态1。卖出，无条件转移至状态0
            dp[i + 1][2] = dp[i][1] + prices[i];
        }
        return max(dp[n][0], dp[n][2]);
    }

// 714. Best Time to Buy and Sell Stock with Transaction Fee (Medium)
    int maxProfit(vector<int> &prices, int fee) {
// 状态1：无股票
// 状态2：有股票
        int n = prices.size();
        int dp_0 = 0, dp_1 = -50001;
        for (int i = 0; i < n; i++) {
            dp_0 = max(dp_0, dp_1 + prices[i] - fee);
            dp_1 = max(dp_0 - prices[i], dp_1);
        }
        return dp_0;
    }

// 123. Best Time to Buy and Sell Stock III (Hard)
    int maxProfit_3(vector<int> &prices) {
// 状态0：卖出
// 状态1：买入
        int profitOne0 = 0, profitOne1 = -prices[0], profitTwo0 = 0, profitTwo1 = -prices[0];
        int length = prices.size();
        for (int i = 1; i < length; i++) {
//第一次买入
            profitOne0 = max(profitOne0, profitOne1 + prices[i]);
            profitOne1 = max(profitOne1, -prices[i]);
//第二次买入
            profitTwo0 = max(profitTwo0, profitTwo1 + prices[i]);
            profitTwo1 = max(profitTwo1, profitOne0 - prices[i]);
        }
        return profitTwo0;
    }

// 188. Best Time to Buy and Sell Stock IV (Hard)
    int maxProfit(int k, vector<int> &prices) {
        int len_ = prices.size();
        if (len_ == 0) return 0;
//无限次交易
        if (k > len_ / 2) return maxProfit_inf(prices);
        int dp[k + 1][2];
        dp[0][0] = 0; //0代表卖出状态、1代表买入状态
        for (int i = 0; i < len_; i++) {
            for (int j = k; j > 0; j--) {
                if (i == 0) {
                    dp[j][0] = 0;
                    dp[j][1] = -prices[0];
                    continue;
                }
                dp[j][0] = max(dp[j][0], dp[j][1] + prices[i]);
                dp[j][1] = max(dp[j][1], dp[j - 1][0] - prices[i]);
            }
        }
        return dp[k][0];
    }

    int maxProfit_inf(vector<int> &prices) {
        int len_ = prices.size();
        int dp_i_0 = 0;
        int dp_i_1 = INT_MIN;
        for (int i = 0; i < len_; i++) {
            int tmp = dp_i_0;
            dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
            dp_i_1 = max(dp_i_1, tmp - prices[i]);
        }
        return dp_i_0;
    }//无限次交易

// 583. Delete Operation for Two Strings (Medium)
//1、dp[i][j]表示s1[1...i]和s2[1...j]的最长公共子序列长度
    int minDistance(string word1, string word2) {
        int n1 = word1.length(), n2 = word2.length();
        vector<int> dp(n2 + 1, 0);
        for (int i = 1; i <= n1; i++) {
            vector<int> temp = dp;
            for (int j = 1; j <= n2; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[j] = temp[j - 1] + 1;
                } else {
                    dp[j] = max(dp[j], dp[j - 1]);
                }
            }
        }
        return n1 + n2 - 2 * dp[n2];
    }

//2、dp[i][j]表示s1[1...i]和s2[1...j]的字符串匹配最少删除次数
    int minDistance2(string word1, string word2) {
        int len1 = word1.size();
        int len2 = word2.size();
        int i, j;
        vector<int> temp(len2 + 1, 0);
        vector<vector<int>> dp(len1 + 1, temp);
        for (i = 0; i <= len1; ++i) {
            for (j = 0; j <= len2; ++j) {
                if (i == 0 || j == 0) dp[i][j] = i + j;
                else if (word1[i - 1] == word2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
                else dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
            }
        }
        return dp[len1][len2];
    }

// 72. Edit Distance (Hard)
    int EditDistance(string word1, string word2) {
        int len1 = word1.size(), len2 = word2.size();
        vector<int> temp(len2 + 1, 0);
        vector<vector<int>> dp(len1 + 1, temp);
        for (int i = 0; i <= len1; ++i) {
            for (int j = 0; j <= len2; ++j) {
                if (i == 0 || j == 0) dp[i][j] = i + j;
                else if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1] - 1)) + 1;
                else
                    dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
            }
        }
        return dp[len1][len2];
    }

// 650. 2 Keys Keyboard (Medium)
    int minSteps(int n) {
    //  i 从 2 开始遍历找到 n - 1，判断 i 是不是 n 的因子，
    //  如果 i 是 n 的因子，那么总的需要操作 minSteps(i) + n / i次。
    //  如果从 2 到 n - 1 没有 n 的因子，那么 n 是个素数，必须操作 n 次。
        vector<int> dp(n + 1, 0);
        for (int i = 2; i < n + 1; i++) {
            int minCount = INT_MAX;
            for (int j = 1; j < i; j++) {
                if (i % j == 0) {
                    //min = min(i) + 1 + (j - 1) = min(i) + n/i
                    minCount = min(dp[j] + i / j, minCount);
                }
            }
            dp[i] = minCount;
        }
        return dp[n];
    }
};

int main() {
    vector<int> nums = {3, 33, 333};
    Solution s;
    cout << s.numSquares(12);
}