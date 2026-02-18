# 快乐数 — Is Happy 

- **题目（LeetCode 202）**： [🔗 题目](https://leetcode.cn/problems/happy-number/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0202.%E5%BF%AB%E4%B9%90%E6%95%B0.html#%E6%80%9D%E8%B7%AF)  
  - [🧠 文字解析（快慢指针方法，推荐阅读）](https://leetcode.cn/problems/happy-number/solutions/21454/shi-yong-kuai-man-zhi-zhen-si-xiang-zhao-chu-xun-h)  


---
## 关键点（精简）

**方法一：**

* 通过 `unordered_set` 记录每次平方和计算的结果来检测循环：若结果为1则返回`true`，若结果重复出现（回到之前的状态）则说明进入无限循环，返回`false`。
* **为什么使用`unorered_list`**: 因为 `unordered_set` 提供平均 O(1) 的查找性能，而 `set` 是 O(log n)，在大数据量下哈希表显著更快。

**方法二**
* 快乐数的计算过程会生成一个**确定性的数字序列**（每个数字唯一决定下一个数字）。
* 这个序列只有两种结局：**到达1**（无环），或**进入循环**（非快乐数）。
* 快慢指针中，快指针走两步、慢指针走一步，**若存在环则必相遇**，无环则快指针先到1。
* 相遇时若值为1则是快乐数，否则说明有环不是快乐数。
* 无需额外空间，用**指针追及替代哈希判重**。
* 可以将空间复杂度优化从O(n)到O(1)


---
## 代码实现
**方法一**
```cpp
class Solution {
public:
    bool isHappy(int n) {
        // 快乐数判定：不断替换 n 为其各位数字平方和
        // - 若最终得到 1，则是快乐数
        // - 若进入循环（重复出现之前的数），则不是快乐数
        
        unordered_set<unsigned> seen;  // 记录已出现的数字，用于检测循环
        
        while (n != 1) {
            // 计算 n 的各位数字平方和
            unsigned sum = 0;
            while (n > 0) {
                int digit = n % 10;      // 取末位数字
                sum += digit * digit;    // 累加平方
                n /= 10;                 // 去掉末位
            }
            n = sum;  // 更新为下一轮要处理的数
            
            // 检测是否进入循环：若该数字已出现过，说明无限循环
            if (seen.count(n)) return false;
            seen.insert(n);
        }
        
        return true;  // n 变为 1，是快乐数
    }
};
```

**方法二**
```cpp
class Solution {
    // 计算各位数字的平方和
    unsigned calSum(unsigned input) {
        unsigned sum = 0;
        while (input > 0) {
            int digit = input % 10;      // 取末位数字
            sum += digit * digit;        // 累加平方
            input /= 10;                 // 去掉末位
        }
        return sum;
    }

public:
    bool isHappy(int n) {
        unsigned slow = n, fast = n;     // 快慢指针从同一起点出发
        
        do {
            slow = calSum(slow);         // 慢指针：走一步（计算一次平方和）
            fast = calSum(fast);         // 快指针：走两步（计算两次平方和）
            fast = calSum(fast);
        } while (fast != slow);          // 相遇时停止，说明有环或都到达1
        
        return fast == 1;                // 相遇点为1则是快乐数，否则不是
    }
};
```

