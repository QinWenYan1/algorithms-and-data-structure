# 有效的完全平方数 — perfect square 

- **题目（LeetCode 367）**： [🔗 题目](https://leetcode.cn/problems/valid-perfect-square/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析 （力扣官方题解）](https://leetcode.cn/problems/valid-perfect-square/solutions/1081379/you-xiao-de-wan-quan-ping-fang-shu-by-le-wkee) 

 

---

## 关键点（精简）

* 思路和力扣[69题](./arr_vec_10_mySqrt.md)一样
* 同样还是要注意值对的溢出，比如:
    * `if (mid * mid <= num)`
    * 这里如果你的`mid`申明为`int`在计算的时候就会有问题
    * 因为`mid*mid`的时候`int`就容易导致值的溢出
    * 所以要注意

---
## 代码实现

```cpp
class Solution {
public:
    bool isPerfectSquare(int num) {

        //这道题题意是叫我们先找到第一个平方大于num的元素的前面一个
        //也就是找右边界
        unsigned long low = 0, high = (unsigned long)num+1; 

        while ( low < high ){
            //左闭右开
            unsigned long mid = (high - low)/2 + low; 
            if (mid*mid <= num ) low = mid + 1; 
            else high = mid; 

        }
        //low = high, 指向第一个大于num的元素

        unsigned long outcome = low-1; 
        return (outcome*outcome == num); 
        
    }
};
```
