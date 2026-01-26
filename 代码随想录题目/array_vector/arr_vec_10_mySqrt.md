# x的平方根 — x square root 

- **题目（LeetCode 69）**： [🔗 题目](https://leetcode.cn/problems/sqrtx/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析 （灵茶山艾府），推荐观看](https://leetcode.cn/problems/sqrtx/solutions/2942682/kai-qu-jian-er-fen-jian-ji-xie-fa-python-v4fb) 

 

---

## 关键点（精简）

* 这道题本意就是输入非负整数`x`，返回最大的非负整数`m`，满足$m^2≤x$。
    * 那么左边界一定就是 0 
    * 右边界可以保证在 `x+1`
    * 满足 $0≤m≤x+1$
* 但是这道题还要注意值溢出的问题, 计算机在处理 `unsigned long high = x + 1;` 这行代码时，是分两步走的：

    * **第一步：计算右侧表达式 (`x + 1`)**
    编译器看到 `x` 是 `int` 类型，`1` 也是 `int` 类型。于是它按照 `int` 的规则进行加法运算。
    如果 `x` 是 `2147483647` (INT_MAX)，加 1 之后在 `int` 范围内就**溢出**了，结果变成了 `-2147483648`。
    * **第二步：赋值给左侧变量 (`high`)**
    计算完成后，编译器才看到要把这个结果存入 `unsigned long long`。但此时结果已经溢出变质了，存进去的是一个错误的数值。
* 因此我们要写成 `unsigned long high = (unsigned long)x+1`
* 在灵茶山艾府的文字解析中，还有另外一种解决办法，推荐阅读

---
## 代码实现

```
class Solution {
public:
    int mySqrt(int x) {

        unsigned long  low = 0, high = (unsigned long)x+1; 

        while (low < high){
            // 左闭右开区间

            unsigned long mid = (high - low)/2 + low; 
            if (mid*mid <= x) low = mid + 1; //向右边寻找
            else high = mid;  // 向左边寻找

        }
        //循环结束是low == high, 此时指向的是第一个大于m的元素，因此返回一定要减一

        return low-1; 
        
    }
};
```