# 重复的子字符串 — repeated substring pattern

- **题目（力扣 459）**： [🔗 题目](https://leetcode.cn/problems/repeated-substring-pattern/)  
- **难度**：简单

- **解析 / 学习链接**：
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0459.%E9%87%8D%E5%A4%8D%E7%9A%84%E5%AD%90%E5%AD%97%E7%AC%A6%E4%B8%B2.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1cg41127fw/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)
  
---
## 关键点（精简）

**方法一：字符串移动匹配** (懂了即可)
核心思路：
> **s+s后掐头去尾，若中间仍能匹配到原串，则该串由重复子串构成。**
  * 详细实现请看[代码随想录文字解析](https://programmercarl.com/0459.%E9%87%8D%E5%A4%8D%E7%9A%84%E5%AD%90%E5%AD%97%E7%AC%A6%E4%B8%B2.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  
**方法二：KMP的最大公共子串差**（重点）
核心思路
> **最小重复单元长 = 总长 - 最长相等前后缀长**  


**原理解释：**
  * `p1`表示字符串的第一个位置，令`p1,p2,p3`后为公共子串中后缀
  * 在公共子串中，前缀中的第1个周期 `p1,p2,p3` 必须等于后缀中对应位置`p4,p5,p6`（同时也是字符串中`p4,p5,p6`位的实际字符。
  * 这样以此类推下去那么这个整个字符串以及后缀也都是由`p1,p2,p3`重复得到的。
  * 因此，**总长减去最长相等前后缀长度（`len - next[len-1]`）就是最小重复单元的长度**。

解法思路：

1. **构建next数组**  
   * 模式串自匹配求最长相等前后缀长度，标准KMP构建流程。
2. **判定周期性**  
    * 取 `next[len-1]` 得最长前后缀长
    * 计算重复单元长度`len - next[len-1]`， 如果为0说明不存在，要小心这种情况
    * 通过判断能不能和`len`整除，来确定是不是又重复单元组成的。



---
## 代码实现
```cpp
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        // KMP解法：利用最长相等前后缀推导最小重复单元
        // 若字符串由重复单元组成，则 next[len-1] 为最长相等前后缀长度
        // 总长减去该长度即为最小重复单元长度，若总长能被其整除则为true
        
        int len = s.size();
        vector<int> next(len);
        
        // 1. 构建next数组：标准KMP自匹配
        // prefix: 当前最长前后缀长度（也是下一个要比较的前缀位置）
        int prefix = 0;
        next[0] = 0;
        for (int suffix = 1; suffix < len; ++suffix) {
            // 失配：回退到前一个位置的最长前缀处继续尝试
            while (prefix > 0 && s[prefix] != s[suffix]) 
                prefix = next[prefix - 1];
            // 匹配：当前最长前后缀长度+1
            if (s[prefix] == s[suffix]) 
                ++prefix;
            next[suffix] = prefix;  // 记录前suffix+1个字符的最长前后缀长
        }
        
        // 2. 判定周期性
        // lcs: 最长相等前后缀长度（即前后重叠部分的长度）
        int lcs = next[len - 1];
        // 最小重复单元长度 = 总长 - 最长相等前后缀长
        // 若lcs>0（存在前后缀）且总长能被单元长度整除，则为重复子串构成
        if (lcs != 0 && len % (len - lcs) == 0) 
            return true;
        return false;
    }
};
```
