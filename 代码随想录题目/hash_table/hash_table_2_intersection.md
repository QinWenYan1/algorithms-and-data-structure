# 两个数组的交集 — Intersection

- **题目（LeetCode 349）**： [🔗 题目](https://leetcode.cn/problems/intersection-of-two-arrays/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0349.%E4%B8%A4%E4%B8%AA%E6%95%B0%E7%BB%84%E7%9A%84%E4%BA%A4%E9%9B%86.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)  
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1ba411S7wu/)

---
## 关键点（精简）

**核心思路：**

* 利用题目数据范围（0-1000）使用固定大小的 `array<bool, 1001>` 作为哈希表
* 先将 `nums1` 的元素标记为存在，再遍历 `nums2` 时若发现已标记则加入结果并去重，可以将映射的空间复杂度优化至 O(1)。
* 当数据范围有限时，优先使用数组替代 `set` 作为哈希表——数组通过直接索引实现 O(1) 访问，无需哈希计算，空间更省且速度更快，数据量越大优势越明显。


---
## 代码实现


```cpp
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        // 用数组模拟哈希集合：索引代表数值，值代表是否出现过
        // 题目数据范围 0-1000，所以开 1001 大小，空间复杂度 O(1)
        array<bool, 1001> lookupTable{};
        vector<int> outcome;  // 存储交集结果

        // 第一步：将 nums1 中出现的数字在 lookupTable 中标记为 true
        for (const auto e : nums1) {
            lookupTable[e] = true;
        }

        // 第二步：遍历 nums2，若数字已被标记，说明是交集元素
        // 加入结果后立即取消标记（置 false），避免重复加入
        for (const auto e : nums2) {
            if (lookupTable[e]) { 
                outcome.push_back(e);
                lookupTable[e] = false;  // 去重：确保每个交集数字只出现一次
            }
        }

        return outcome;
    }
};
```