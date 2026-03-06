# 赎金信 — ransom note 

- **题目（LeetCode 383）**： [🔗 题目](https://leetcode.cn/problems/ransom-note/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0015.%E4%B8%89%E6%95%B0%E4%B9%8B%E5%92%8C.html)  
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1GW4y127qo/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)  


---
## 关键点（精简）

**核心思想**：
* 将 `magazine` 视为**字母库存**，`ransomNote` 视为**需求清单**，判断库存是否能满足需求。
* **实现方式**：
  * 和[有效的字母异位词](./hash_table_1_is_anagram.md)思路一样，利用26位定长数组充当哈希表，偏移量作为 index
  * 分别统计需求与供给的字母频次，若遍历后所有字母的净需求均不大于0（即库存有盈余或刚好满足），则返回 true。

1. **统计需求**：遍历 `ransomNote`，记录每种字母的需求量（++）
2. **消耗库存**：遍历 `magazine`，消耗对应字母的库存（--）
3. **检查余量**：若所有字母需求都 ≤ 0（即库存足够），返回 true；若存在 > 0，说明该字母短缺，返回 false

**复杂度**：时间 $O(m+n)$，空间 $O(1)$（固定26个字母）


---
## 代码实现

```cpp
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        // 固定大小的数组作为哈希表（比unordered_map更快）
        // 索引0-25对应字母'a'-'z'，值表示该字母的"剩余需求"
        array<int, 26> lookup{};
        // ^ 注意：必须初始化，否则值为未定义
        
        // 第一步：统计ransomNote中各字母的需求次数
        for (char c : ransomNote) {
            ++lookup[c - 'a'];  // 需求增加
        }
        
        // 第二步：用magazine的字母来满足需求
        for (char c : magazine) {
            --lookup[c - 'a'];  // 库存消耗，需求减少
        }
        
        // 第三步：检查是否所有需求都被满足
        // 若存在正值，说明该字母magazine提供的不够
        for (int remain : lookup) {
            if (remain > 0) return false;
        }
        
        return true;
    }
};
```

