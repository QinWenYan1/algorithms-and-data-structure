# 斐波那契数 — Fibonacci Number

- **题目（LeetCode）**： [🔗 题目](https://leetcode.cn/problems/fibonacci-number/description/)  
- **难度**：简单
- **代码**：[`code/fibonacci.cpp`](./code/fibonacci.cpp)（或内嵌代码块）
- **解析 / 学习链接**： [🧠 解析（代码随想录/Carl）](https://www.google.com/search?q=https://programmercarl.com/0509.%25E6%2596%2590%25E6%25B3%25A2%25E9%2582%25A3%25E5%25A5%2587%25E6%2595%25B0.html%23%25E7%25AE%2597%25E6%25B3%2595%25E5%2585%25AC%25E5%25BC%2580%25E8%25AF%25BE)

---
```cpp
class Solution {
public:
    int fib(int n) {

        //我们通过爬阶梯的方式来计算
        int i = 0, j = 1; 

        //如果n是0的话需要返回0 
        if( !n ){ return i; }

        for(int iter = 1; iter < n; ++ iter){

            int old_i = i; 
            int new_i = j; 
            j = j+old_i; 
            i = new_i; 

        }

        return j;  
        
    }
}; 
```
