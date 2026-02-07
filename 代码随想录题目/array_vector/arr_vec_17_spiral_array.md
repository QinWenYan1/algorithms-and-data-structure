# 螺旋遍历二维数组 — spiral array

- **题目（LeetCode 146）**： [🔗 题目](https://leetcode.cn/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠  螺旋遍历二维数组（模拟，清晰图解）](https://leetcode.cn/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/solutions/129360/mian-shi-ti-29-shun-shi-zhen-da-yin-ju-zhen-she-di) 


---

## 关键点（精简）

* 用**四指针法**模拟顺时针螺旋，每次走完一条边就收缩边界，直到边界重叠。

* **三要素**：
  1. **四个边界指针**：left, right, top, bottom
  2. **四个方向循环**：右→下→左→上
  3. **即时边界收缩**：每走完一条边，立即收缩对应边界并检查

**关键操作**
```
1. 右走：top行 left→right，然后top++
2. 下走：right列 top→bottom，然后right--
3. 左走：bottom行 right→left，然后bottom--
4. 上走：left列 bottom→top，然后left++
```

**结束条件**：任一方向边界重叠（如left≥right或top≥bottom）



---
## 代码实现

```cpp
class Solution {
public:
    vector<int> spiralArray(vector<vector<int>>& array)
    {   
        //处理特殊情况， 为空的情况
        if (array.empty()) return {}; 

        //接下来， 我们记录开始时的边界，left, right, top, buttom
        //使用左闭右开的写法
        unsigned left = 0, top = 0, right = array[0].size(), buttom = array.size(); 

        vector<int> outcome; 

        while (true){

            //从左到右
            for (unsigned i = left; i != right; ++i) outcome.push_back(array[top][i]); 
            if (++top >= buttom ) break; 

            //从上到下
            for (unsigned i = top; i != buttom; ++i) outcome.push_back(array[i][right-1]); 
            if (--right <= left ) break; 
            
            //从右到左
            for (unsigned i = right; left < i; --i) outcome.push_back(array[buttom-1][i-1]); 
            if (--buttom <= top ) break; 
            
            //从下到上
            for (unsigned i = buttom; top < i; --i) outcome.push_back(array[i-1][left]); 
            if (++left >= right) break; 

        }

        return outcome; 

    }
};
```