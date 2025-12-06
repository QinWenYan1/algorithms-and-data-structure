# 不同路径 2 — Unique Paths 2

- **题目（LeetCode 62）**： [🔗 题目](https://leetcode.cn/problems/unique-paths/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录/Carl）](https://programmercarl.com/0062.%E4%B8%8D%E5%90%8C%E8%B7%AF%E5%BE%84.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)  
  - [🎥 视频讲解（Bilibili）](https://www.bilibili.com/video/BV1ve4y1x7Eu?vd_source=7923b10dbf11c28879c337d8e0bfa8de&spm_id_from=333.788.videopod.sections)

---
## 关键点（精简）

  * 问题分析:
    * **`dp`数组定义**：
      * 由于是一个而为地图，故我们使用二维数组`dp[][]`来表示， 其值`dp[i][j]`表示的就是在i,j这个位置有多少种走法
    * **递推公式**:
      * 如果我们要到`dp[i][j]`这个位置的话，我们要么从`dp[i-1][j]`或者dp`[i][j-1]`到达
      * 所以我们能得到公式`dp[i][j] = dp[i-1][j]+dp[i][j-1]` 
      * 而不是`dp[i][j] = dp[i-1][j]+1`，因为我们这里的`dp`表示的是多少种不同路径
    * **初始化**: 
      * 因为`dp[i][j]`其实是由上面和左边初始化来的，那么不难想，最上边一排和最左列都需要初始化
      * 初始化值为1
    * **遍历顺序**:
      * 由于我们都知道`dp[i][j]`都是由上面和左面推导出来的, 遍历顺序就应该**从上到下从左到右**遍历

---
## 代码实现

```cpp

class Solution {
public:
    int uniquePaths(int m, int n) {

        //定义dp, dp[i][j]表示到达ixj这个格子的方式共有多少种
        vector<vector<int>> dp(m, vector<int>(n, 1)); 

        //初始化dp, 我们知道只有两种移动方式，说一第一列和第一排都可以初始化为1, 我们直接在dp创建那里初始化

        //递推公式， 我们可以找到规律：dp[i][j] = dp[i][j-1] + dp[i-1][j]，递推方向就是从左上到右下

        for(int i = 1; i < m; ++i){

            for (int j = 1; j < n; ++j){

                dp[i][j] = dp[i-1][j] + dp[i][j-1]; //递推公式

            }
        }

        return dp[m-1][n-1];
        
    }
};
```
时间复杂度: O(mn)
空间复杂度: O(mn)

---

## 滚动数组优化

* 滚动数组是一种动态规划的空间优化技巧：
  * 当某个 DP 状态只依赖“上一行”和“当前行左侧”时，我们不需要完整的二维表，只需用一行数组不断覆盖更新即可，从而将空间从 O(mn) 降到 O(n)。

* 在本题中，`dp[i][j] = dp[i-1][j] + dp[i][j-1]`。可以看到：

  * `dp[i][j]` 只依赖上一行的同一列，以及当前行的前一列；
  * 这意味着除了上一行以外，其余行都不会再次被使用。

  因此，保存全部 m × n 的网格其实是浪费的。


* 我们只保留一行 `dp[j]`：

  * `dp[j]`（更新前）代表上一行的值；
  * `dp[j - 1]` 是当前行左侧已更新好的值；
  * 这样就能正确计算出新的 `dp[j]`，并覆盖旧值。

* **所以我们只需保留一行，从上到下、从左到右滚动更新；这一行最右侧的值就是最终答案。**（O(n) 空间）

* **为了节省空间，我们其实不需要保存整个二维数组，只需保留一行，从上到下、从左到右滚动更新；这一行最右侧的值就是最终答案。**

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[j] = dp[j] + dp[j - 1];
            }
        }
        return dp[n - 1];
    }
};
```

**时间复杂度**：O(mn)
**空间复杂度**：O(n)
