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
> **先让模式串自己跟自己比算出失配回退表（next），匹配主串时一旦失配直接查表跳到下一个可能位置，保证主串指针永不回溯。**

1. **next数组定义**：
`next[i]` = `pattern[0..i]` 的最长相等**前缀后缀**长度（含i）

```
pattern: a b a b a c a
next:    0 0 1 2 3 0 1
```

2. **构建next（自己匹配自己）**：

    * **模式串内部匹配**：只拿模式串自己跟自己比，找每个前缀的最长相等前后缀，不涉文本串。

    * **`suffix` 遍历后缀尾**：
        * `suffix` 从 1 往后扫，始终指向当前子串的最后一个字符（即后缀的尾巴）。 
        * 这是为了计算`suffix`位置的公共子串长度
    * **`prefix` 维护当前长度**：
        * `prefix` 存当前已匹配的最长长度（也是下一个该比的前缀位置）。
        * 于`suffix`比较：
            **case 1**: `p[suffix]==p[prefix]` 则 `prefix++` 延长
            **case 2**: 不等则 `prefix` 回跳到 `next[prefix-1]` 试更短的。
```
prefix ← 0                 // 当前已匹配的最长长度（即下一个该比的前缀位置）
next[0] ← 0
for suffix 从 1 到 n-1:     // suffix 始终指向后缀尾
    while prefix > 0 且 pattern[prefix] ≠ pattern[suffix]:
        prefix ← next[prefix-1]    // 失配：跳回次长前缀继续试
    
    if pattern[prefix] = pattern[suffix]:
        prefix ← prefix + 1        // 匹配：延长当前长度
    
    next[suffix] ← prefix          // 记录：前 suffix+1 个字符的最长前后缀长
```

3. **匹配主串（查表回退）**：

    * **主串单向不回溯**：`txtI` 从头到尾只进不退，永不回头。

    * **`patI` 失配跳 next**：对不上时 `patI` 回跳到 `next[patI-1]`，省去中间无效比对。

    * **匹配并进至贯穿**：相等则双指针同步前进，`patI` 走完模式串即命中。

```
patI ← 0                          // 已匹配长度（也是模式串当前比对位置）

for txtI 从 0 到 text.length-1:   // 主串指针单向扫描，永不回退
    while patI > 0 且 text[txtI] ≠ pattern[patI]:
        patI ← next[patI - 1]    // ⚠️ 关键：失配时回退到次长前缀（注意是 patI-1！）
    
    if text[txtI] = pattern[patI]:
        patI ← patI + 1          // 匹配成功：双指针并进
    
    if patI = pattern.length:
        return txtI - patI + 1     // 贯穿：找到匹配起始位置
```

4. **易错点（死记）**：
`prefix`和`patI`都是**已匹配长度**，查表永远用 **`next[?-1]`**（除了等于0）。

| 场景 | 用哪个下标 | 为什么 |
|:---:|:---:|:---|
| **构建时回退** | `next[prefix-1]` | `prefix`是当前长度，前`prefix`个字符信息在`prefix-1` |
| **匹配时回退** | `next[patI-1]` | 已匹配`patI`个（`0~patI-1`），信息在`patI-1` |
| **next含义** | 前`i+1`个字符 | `next[i]`含`i`这个位置 |

5. **时间复杂度**：
    * 将从暴力解法的O(m*n)降到O(m+n)


---
## 代码实现
```cpp
class Solution {
public:
    // 生成next表：pattern自己匹配自己，记录每个位置的最长相等前后缀长度
    vector<int> &genNext(vector<int> &next, const string &pattern){
        int prefix = 0;  // 当前最长前后缀长度（也是下一个要比的前缀位置）
        next[0] = 0;     // 单个字符无前后缀
        // suffix遍历后缀末尾（从1开始），prefix维护前缀长度
        for (int suffix = 1; suffix < next.size(); ++suffix){
            // 失配：回退到前一个位置的最长前缀处继续尝试
            while (prefix > 0 && pattern[prefix] != pattern[suffix]){
                prefix = next[prefix - 1]; 
            }
            // 匹配：当前最长前后缀长度+1
            if(pattern[prefix] == pattern[suffix]){
                ++prefix;
            }
            next[suffix] = prefix;  // 记录前suffix+1个字符的最长前后缀长
        }
        return next;
    }

    int strStr(string haystack, string needle) {
        if (haystack.size() < needle.size()) return -1;
        if (needle.empty()) return 0;  // 空模式串特判
        
        vector<int> nextTable(needle.size()); 
        genNext(nextTable, needle);

        int patI = 0;  // 模式串指针（已匹配的字符数，也是当前要比的位置）
        // txtI遍历主串，patI跟随匹配，失配时patI按next表回退
        for (int txtI = 0; txtI < haystack.size(); ++txtI){
            // 失配：回退到最长公共前缀的下一个位置（已匹配patI个，查表用patI-1）
            while(patI > 0 && haystack[txtI] != needle[patI]){ 
                patI = nextTable[patI - 1]; 
            }
            // 匹配：模式串指针前进
            if (haystack[txtI] == needle[patI]){
                ++patI;  
            }
            // patI贯穿模式串，匹配成功，返回起始位置
            if (patI == needle.size()){
                return txtI - patI + 1; 
            }
        }
        return -1; 
    }
};
```
