# 反转字符串 2 — Reverse string 2

- **题目（LeetCode 541）**： [🔗 题目](https://leetcode.cn/problems/reverse-string-ii/description/)  
- **难度**：简单

- **解析 / 学习链接**：
    - [🧠 文字解析（灵茶山艾府） - 推荐阅读](https://leetcode.cn/problems/reverse-string-ii/solutions/3056217/jian-dan-ti-jian-dan-zuo-pythonjavaccgoj-ig15)
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0541.%E5%8F%8D%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2II.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1dT411j7NN/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）

* **模拟迭代步长为`2k`**: 
    * 一些同学通过逻辑：每隔2k个字符的反转前k的字符， 搞计数器
    * 但是这道题其实只需要将**步长定为`2k`即可**，将字符串切割为:
    `[0, 2k), [2k, 4k) ...`
    * 对于每一段来说， 反转前k个字符，反转区间为:
    `[0,k), [2k,3k) ...`
    * 注意，最后一个区间的右开端点要和字符串的最后一个元素索引取最小值，防止下标越界。

---
## 代码实现

```cpp
class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.size();
        for (int i = 0; i < n; i += k * 2) {
            reverse(s.begin() + i, s.begin() + min(i + k, n));
        }
        return s;
    }
};
```
