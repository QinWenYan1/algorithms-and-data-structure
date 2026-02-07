# 螺旋矩阵2 — generate matrix

- **题目（LeetCode 59）**： [🔗 题目](https://leetcode.cn/problems/spiral-matrix-ii/)  
- **难度**：中等
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0059.%E8%9E%BA%E6%97%8B%E7%9F%A9%E9%98%B5II.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)  
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1SL4y1N7mV/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）
* 这道题没有算法涉及，但是边界检查尤其繁杂
* 每条边，每个方向边界条件判断都不一样, 很容易写着写着自己就绕进去走不出来了
* 解决这种问题，我们需要去寻找**循环不变量**
  * 而**循环不变量**其实就是一圈一圈循环的时候，每条边的处理规则
  * 在这里我们对每条边的处理都坚持**左闭右开**的原则 
  * 也就是比如上边条处理的时候，我们只考虑左上点而将右上点交给下一个边处理
  * 不难发现，我们在整个过程都是坚持的一个原则-左闭右开，最后一个点交给下一个边处理
  * 这样四条边的处理规则就统一了
* 在条件判断上：
  1. 对于一个n的矩阵，我们不难发现，一共需要n/2次圈才可以解决完问题
      * 因为每次转一圈就会将最上面和最下面的数组给遍历完，也就是每一圈消耗两条数组
  2. 但如果n为奇数的话，我们不难发现，会留下中间位置一格空白
      * 那么此时，我们判断一下是否为奇数，并特殊处理即可
  3. 每一次在迭代中， 循环转圈会慢慢往里面转圈， 为了实现这个操作， 我们需要一个`offset`来在每个`for`迭代里面控制偏移量

---
## 代码实现

```cpp
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {

        int offset = 1; 
        int loop = n/2; 
        vector<vector<int>> matrix(n, vector<int>(n));
        int start_x=0, start_y=0, count=1; 
        int x = 0, y = 0; 

        while(loop--){ 
            
            x = start_x;
            y = start_y;

            for(; x < (n-offset);++x) matrix[y][x] = count++; 
            for(; y < (n-offset);++y) matrix[y][x] = count++; 
            for(; x > (start_x);--x) matrix[y][x] = count++; 
            for(; y > (start_y);--y) matrix[y][x] = count++; 
            ++ offset;  
            ++ start_x; 
            ++ start_y;

        }

        if(n%2 == 1) matrix[n/2][n/2] = count; 

        return matrix; 
    }
};
```
时间复杂度:O(n^2)
**注意**：
* 每次转完一圈的时候更新起始点的时候，不要`x`, `y`单独在`for`循环里面更新
* 要同时一起更新, 否则会污染下一个循环


