# 找出字符串第一个匹配项的下标 — KMP algorithm

- **题目（力扣 28）**： [🔗 题目](https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/description/)  
- **难度**：简单

- **解析 / 学习链接**：
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0028.%E5%AE%9E%E7%8E%B0strStr.html#%E6%80%9D%E8%B7%AF)

  
---
## 关键点（精简）

* 本题是**KMP**经典题目，这里我并不讲解KMP的概念，需要回顾的看这：
  1. [KMP理论剖析 - 文字](https://programmercarl.com/0028.%E5%AE%9E%E7%8E%B0strStr.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  2. [KMP理论剖析 - 视频](https://www.bilibili.com/video/BV1PD4y1o7nd/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)
  3. KMP代码实现理解（难点）:
      * [next数组的搭建 - 视频](https://www.bilibili.com/video/BV1M5411j7Xx/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)
      * [最浅显易懂的KMP算法：next数组回退原理 - 视频](https://www.bilibili.com/video/BV1AY4y157yL?spm_id_from=333.788.recommend_more_video.0&trackid=web_related_0.router-related-2479604-tn27s.1773986439828.383&vd_source=7923b10dbf11c28879c337d8e0bfa8de)
      * [next数组建立 - 文字](https://www.geeksforgeeks.org/dsa/kmp-algorithm-for-pattern-searching/#naive-approach-and-how-kmp-overcomes-it)




---
## 代码实现
