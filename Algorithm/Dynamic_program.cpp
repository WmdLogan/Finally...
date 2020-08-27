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

#include <iostream>
#include <vector>
#include <algorithm>

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

    bool canPartition(vector<int> &nums) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        return sum;
    }
};