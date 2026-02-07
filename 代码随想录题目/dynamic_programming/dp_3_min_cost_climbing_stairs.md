# 使用最小花费爬楼梯 — Min Cost Climbing Stairs

- **题目（LeetCode 746）**： [🔗 题目](https://leetcode.cn/problems/min-cost-climbing-stairs/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0746.%E4%BD%BF%E7%94%A8%E6%9C%80%E5%B0%8F%E8%8A%B1%E8%B4%B9%E7%88%AC%E6%A5%BC%E6%A2%AF.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)  
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV16G411c7yZ/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）

  * 问题分析:
    * **`dp`数组含义**：
        - 先要理解`dp`数组代表什么，本题我们要求的是到达楼顶的最小花费。
          * 那么用什么表示到达楼顶呢？- 下标志
          * 什么表示最小花费呢？- 也就是`dp[i]`的值
    * **递推公式**: 既然求的是`dp[i]`， 如何求得？根据题意 `dp[i]`可以是`dp[i-1]+cost[i-1]`或者`dp[i-2]+cost[i-2]`
      * 也就是`dp[i] = min(dp[i-1]+cost[i-1], dp[i-2]+cost[i-2])`
    * **初始化**: 有递推公式可知道, `dp[i]`都是由前两个阶段求得的， 而器递推础其实是`dp[0]`, `dp[1]`
      * 那么我们其实就可以初始化`dp[0]`, `dp[1]`作为开始, 故`dp[0] = dp[1] = 0`
    * **遍历顺序**：
      * 因为我们侍从`dp[0]`, `dp[1]`开始的, 那么就是从签到后即可

---
## 代码实现

```cpp
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {

        //初始化我们的dp数组
        int size = cost.size()+1; 
        vector<int> dp(size); 

        dp[0] = 0;
        dp[1] = 0;

        //递推公式: dp[i] = dp[i-1] + cost[i-1] or dp[i] = dp[i-2] + cost[i-2]
        //由于我们知道第一阶和第二阶的初始值， 我们可以从左向右遍历
        for(int i = 2; i < dp.size(); ++i){
            dp[i] = min(dp[i-1] + cost[i-1], dp[i-2]+cost[i-2]);
        }

        return dp[size-1]; 
        
    }
};
```
