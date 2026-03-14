# 反转字符串 — Reverse string 

- **题目（LeetCode 344）**： [🔗 题目](https://leetcode.cn/problems/reverse-string/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0344.%E5%8F%8D%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1fV4y17748/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）

* **双指针**：这道题就是一个简单的双指针思路，不多讲
* ⚠️ **注意事项**：
    1. **边界检查**：
        * 循环条件应该是左指针 `<` 右指针， 而不是 `<=`
        * 否则，如果是偶数个字符的时候会出现最中间的一对字符串交换两次的情况
    2. **什么时候使用库函数?**：
        * 如果题目关键的部分**直接用库函数就可以解决**，建议不要使用库函数。
        * 如果库函数仅仅是**解题过程中的一小部分**，并且你已经很清楚这个库函数的内部实现原理的话，可以考虑使用库函数。


    




---

## 代码实现
```cpp
class Solution {
public:
    void reverseString(vector<char>& s) {

        //双指针思维
        size_t head = 0, tail = s.size() - 1; 
        while ( head < tail ){
            swap(s[head++], s[tail--]); 
        }
        
    }
};
```