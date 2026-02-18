# 两数之和 — Two Sum 

- **题目（LeetCode 1）**： [🔗 题目](https://leetcode.cn/problems/two-sum/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0454.%E5%9B%9B%E6%95%B0%E7%9B%B8%E5%8A%A0II.html)  
  - [🎥 视频讲解（代码随想录）](bilibili.com/video/BV1Md4y1Q7Yh/)  


---
## 关键点（精简）

**哈希表思路：**
* **暴力算法** O(N²) 的瓶颈：每次寻找 `target - x` 都需要线性扫描数组。
* **哈希表优化**：将查找 `target - x` 的时间从 O(N) 降到 O(1)。
* **遍历策略**：对于每个元素 `x`，**先查询**哈希表中是否存在 `target - x`。
* **若存在**：立即返回当前下标与哈希表中存储的下标，即为答案。
* **若不存在**：将 `x` 及其下标插入表中，继续遍历。
* **避免重复使用**：哈希表中只保存**之前遍历过的元素**，当前 `x` 只能与前面的元素配对，不会和自己匹配。

**复杂度**：总时间 O(N)，空间 O(N)。

---
## 代码实现
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 哈希表存储 <数值, 下标>，用于快速查找 target - x
        unordered_map<int, int> lookupTable; 
        
        for (int i = 0; i != nums.size(); ++i) {
            // 先查询：哈希表中是否存在 target - nums[i]
            auto iter = lookupTable.find(target - nums[i]);
            
            // 若存在，返回配对元素的下标（iter->second）和当前下标 i
            if (iter != lookupTable.end()) return {iter->second, i};
            
            // 后插入：将当前元素及其下标存入哈希表，供后续元素查询
            // 保证不会用同一个元素匹配自己
            lookupTable[nums[i]] = i;  
        }

        return {-1, -1};  // 未找到（题目保证有解，此行不会执行）
    }
};
```

