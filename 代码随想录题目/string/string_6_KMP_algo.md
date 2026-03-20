# 找出字符串第一个匹配项的下标 — KMP algorithm

- **题目（力扣 28）**： [🔗 题目](https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/description/)  
- **难度**：简单

- **解析 / 学习链接**：
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0028.%E5%AE%9E%E7%8E%B0strStr.html#%E6%80%9D%E8%B7%AF)

  
---
## 关键点（精简）

本题是**KMP**经典题目，这里我并不讲解KMP的概念，需要回顾的看这：
  1. [KMP理论剖析 - 文字](https://programmercarl.com/0028.%E5%AE%9E%E7%8E%B0strStr.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  2. [KMP理论剖析 - 视频](https://www.bilibili.com/video/BV1PD4y1o7nd/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)
  3. KMP代码实现理解（难点）:
      * [next数组的搭建和KMP运行 - 视频](https://www.bilibili.com/video/BV1M5411j7Xx/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)
      * 推荐阅读方便理解：[最浅显易懂的KMP算法：next数组回退原理 - 视频](https://www.bilibili.com/video/BV1AY4y157yL?spm_id_from=333.788.recommend_more_video.0&trackid=web_related_0.router-related-2479604-tn27s.1773986439828.383&vd_source=7923b10dbf11c28879c337d8e0bfa8de)
      * [next数组建立逻辑处理 - 文字](https://www.geeksforgeeks.org/dsa/kmp-algorithm-for-pattern-searching/#naive-approach-and-how-kmp-overcomes-it)
---
**核心思路**：
  * **先让模式串自己跟自己比算出失配回退表（next），匹配主串时一旦失配直接查表跳到下一个可能位置，保证主串指针 i 永不回溯。**



1. **next数组定义**：
`next[i]` = `pattern[0..i]` 的最长相等**前缀后缀**长度（含i）

```
pattern: a b a b a c a
next:    0 0 1 2 3 0 1
```

2. **构建next（自己匹配自己）**：
模式串双指针自匹配：`posfix`遍历后缀尾，`prefix`维护前缀长，相等则`prefix++`，失配则`prefix`回退`next[prefixs-1]`，`next[prefix]`记录`prefix`。

```cpp
prefix = 0; next[0] = prefix;
for(i=1; i<n; i++) {
    while(prefix>0 && p[prefix]!=p[postfix]) prefix = next[prefix-1];  // 回退
    if(p[prefix]==p[postfix]) j++;                      // 匹配+1
    next[postfix] = prefix;                             // 记录长度
}
```

3. **匹配主串（查表回退）**：
主串指针`i`单向遍历绝不回溯，`j`失配时按`next`表跳回最长公共前缀处续比，匹配则并进，直至`j`贯穿模式串即为命中。

```cpp
j = 0;
for(i=0; i<主串长; i++) {
    while(j>0 && 主[i]!=针[j]) j = next[j-1]; // ⚠️ 关键：j-1！
    if(主[i]==针[j]) j++;
    if(j==针长) return i-j+1;
}
```


4. **易错点（死记）**:
`j`是已匹配长度，查表永远用 **`next[j-1]`**（除了`j=0`）。

| 场景 | 用哪个下标 | 为什么 |
|:---:|:---:|:---|
| **构建时回退** | `next[prefix-1]` | `prefix`是当前长度，前`prefix`个字符信息在`prefix-1` |
| **匹配时回退** | `next[j-1]` | 已匹配`j`个（`0~j-1`），信息在`j-1` |
| **next含义** | 前`i+1`个字符 | `next[i]`含`i`这个位置 |




---
## 代码实现
