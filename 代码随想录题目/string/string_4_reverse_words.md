# 翻转字符串里的单词 — reverse words 

- **题目（卡码网 151）**： [🔗 题目](https://leetcode.cn/problems/reverse-words-in-a-string/description/)  
- **难度**：中等

- **解析 / 学习链接**：
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0151.%E7%BF%BB%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2%E9%87%8C%E7%9A%84%E5%8D%95%E8%AF%8D.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1uT41177fX/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)
  
---
## 关键点（精简）

* **挑战一下**：你的答案需要时间O(n), 空间为O(1)的话如何做？

* **总体思路**：
  * **先双指针去多余空格 + 全串反转 + 最后逐个单词反转。**

* **关键步骤**：

  1. **双指针原地压缩**：
    - `readPtr` 遍历，`writePtr` 只在写入非空格时移动
    - 非开头位置先写空格再写单词，自动保证单词间单空格
    - 最后 `resize(write)` 截断尾部

  2. **反转字符串使用左闭右开区间 `[begin, end)`**：
    - `j` 从 `end-1` ，`i`从`begin`开始，`i < j` 时交换
    - 方便直接用 `s.size()` 或空格索引作为 `end`

  3. **单词遍历并反转**:
    - `j` 走到空格或 `s.size()` 时，`[i, j)` 即为一个单词
    - 循环条件 `j <= s.size()` 必须取等，确保最后一个单词被处理

* **易错点**:
  - 忘记使用`resize` 截断
  - 整个字符串遍历时的停止条件
  - 前导空格判断用 `writePtr!=0`跳过不必要空格




---
## 代码实现

```cpp
class Solution {
public:
    // 双指针原地去除多余空格（前导/后缀/连续空格）
    // 处理后格式：单词之间只保留一个空格，无前后空格
    string &remExtraSpace(string &s) {
        int writePtr = 0, readPtr = 0, bound = s.size();
        
        while (readPtr != bound) {
            if (s[readPtr] != ' ') {  // 找到单词起始位置
                // 非首个单词前加空格，保证单词间只有一个空格
                if (writePtr != 0) s[writePtr++] = ' ';
                
                // 写入整个单词，直到遇到空格或结尾
                while (readPtr != bound && s[readPtr] != ' ') {
                    s[writePtr++] = s[readPtr++];
                }
            } else {
                ++readPtr;  // 跳过当前空格（包括前导空格和多余空格）
            }
        }
        
        s.resize(writePtr);  // 截断尾部多余空间
        return s;
    }

    // 反转区间 [begin, end)，左闭右开
    void reverse(string &s, int begin, int end) {
        for (int i = begin, j = end - 1; i < j; ++i, --j) {
            swap(s[i], s[j]);
        }
    }

    string reverseWords(string s) {
        // 三步法：去空格 -> 整体反转 -> 单词内反转
        // 时间O(n)，空间O(1)
        
        remExtraSpace(s);                    // 1. 去除多余空格
        reverse(s, 0, s.size());   // 2. 整体反转
        
        // 3. 逐个反转单词，恢复单词内部顺序
        for (int i = 0, j = 0; j <= s.size(); ++j) {
            // j找到空格或结尾，确定单词区间[i, j)
            if (s[j] == ' ' || j == s.size()) {
                reverses, i, j);
                i = j + 1;  // 指向下一个单词起始
            }
        }
        
        return s;
    }
};
```


