# 四数相加 — Four Sum count

- **题目（LeetCode 454）**： [🔗 题目](https://leetcode.cn/problems/4sum-ii/description/)  
- **难度**：中等
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0454.%E5%9B%9B%E6%95%B0%E7%9B%B8%E5%8A%A0II.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)  
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1Md4y1Q7Yh/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)  


---
## 关键点（精简）
方法一:
* 使用暴力搜索办法， 四个数组去排列组合，但是时间复杂读为$O(n^4)$
* 这样的复杂度无法接受

方法二:

* 为了降低复杂度， 我们使用<b>"两两分组 + 哈希表"</b>的分治策略将其转换为**两数之和**的互补问题

1. **分治转化**：将四数之和为0的问题转化为两数之和的互补问题  
   `a + b + c + d = 0` 等价于 `a + b = -(c + d)`

2. **预处理**：用哈希表存储前两个数组（nums1、nums2）所有可能的**两数之和**及其**出现频率**  
   - Key: 两数之和 `a + b`  
   - Value: 该和出现的次数

3. **查询匹配**：遍历后两个数组（nums3、nums4），计算 `target = -(c + d)`  
   - 如果在哈希表中找到该target，说明存在对应的 `(a,b)` 组合能与当前 `(c,d)` 配成四元组  
   - 累计次数 = 哈希表中该target的出现频率（因为每个 `(a,b)` 都是独立的组合）

**复杂度分析**：
- 时间：$O(n^2)$，两重循环预处理 + 两重循环查询
- 空间：$O(n^2)$，哈希表最坏存储 n² 个不同的和

**注意点**
* 为何选择两两分组而非只先预处理一个数组？
  * 因为若查找剩余三个数组的和，需进行三重循环遍历所有三元组组合，时间复杂度将达 $O(n^3)$。
  * 而采用两两分组策略可将问题转化为 Two Sum 模型，仅需 $O(n^2)$ 即可高效解决。

---
## 代码实现

方法二：

```cpp
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        // HashMap: key = a + b 的和, value = 该和出现的次数
        unordered_map<int, int> sumCount;
        
        // 第一阶段：预处理 nums1 和 nums2 的所有两数之和
        // 时间复杂度: O(n^2)
        for (int a : nums1) {
            for (int b : nums2) {
                // operator[] 会自动将不存在的key初始化为0，然后自增
                ++sumCount[a + b];
            }
        }
        
        // 第二阶段：在 nums3 和 nums4 中查找互补组合
        // 若存在 a + b + c + d = 0，则必有 a + b = -(c + d)
        int result = 0;
        for (int c : nums3) {
            for (int d : nums4) {
                int target = -(c + d);
                auto it = sumCount.find(target);
                if (it != sumCount.end()) {
                    // 找到匹配：所有能产生该 target 的 (a,b) 组合 
                    // 都能与当前 (c,d) 构成有效四元组
                    result += it->second;
                }
            }
        }
        
        return result;
    }
};
```