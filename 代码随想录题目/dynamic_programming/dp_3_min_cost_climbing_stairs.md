# 使用最小花费爬楼梯 — Min Cost Climbing Stairs

- **题目（LeetCode 746）**： [🔗 题目](https://leetcode.cn/problems/min-cost-climbing-stairs/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录/Carl）](https://programmercarl.com/0746.%E4%BD%BF%E7%94%A8%E6%9C%80%E5%B0%8F%E8%8A%B1%E8%B4%B9%E7%88%AC%E6%A5%BC%E6%A2%AF.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)  
  - [🎥 视频讲解（Bilibili）](https://www.bilibili.com/video/BV16G411c7yZ/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）

  * 问题分析:
    1. 1阶：1种方法
    2. 2阶：2种方法
    3. 3阶：
      * 如果我们只关心要到第3阶前的上一个状态， 那么要么是从2阶或者1阶上来的
      * 因此到达三阶的方法综合相当于1阶方法和2阶梯方法的总和也就是: 1+2=3
  * **`dp[i]`代表**到达i阶梯有`dp[i]`种方法
  * 所以我们能快速总结出**递推公式**为: `dp[i] = dp[i-1] + dp[1-2]`
  * 对于**初始化**来说，一些认考虑将`dp[0]=1`其实不符逻辑， 不妨直接从`dp[1]=1,dp[2]=2`来考虑
  * **遍历顺序**：不难看出只有得到了`dp[i-1]`和`dp[i-2]`才能求出`dp[i]`，所以应该是顺序

---
## 代码实现
