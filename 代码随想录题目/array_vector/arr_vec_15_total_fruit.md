# 水果成篮 — total fruit

- **题目（LeetCode 904）**： [🔗 题目](https://leetcode.cn/problems/fruit-into-baskets/description/)  
- **难度**：中等
- **解析 / 学习链接**：  
  - [🧠 文字解析 灵茶山艾府](https://leetcode.cn/problems/fruit-into-baskets/solutions/3042744/hua-dong-chuang-kou-ha-xi-biao-pythonjav-uzmw/) 


---

## 关键点（精简）

* 子数组越长，包含的元素越多，越可能不满足题目要求；
  * 反之，子数组越短，包含的元素越少，越可能满足题目要求。
* 本题属于**越短越合法**，有这种性质的题目，可以用滑动窗口`left`, `right`解决：
  * 同时用一个**哈希表**`cnt`维护子数组内每个元素的出现次数。
  * 当`fruits[right]`加入哈希表后，发现哈希表大小超过了2：
    * 那么子数组不满足要求
    * **移动子数组的左端点`left`**，把`fruits[left]`的出现次数减一，直到哈希表中的元素种数等于2。

---

## 注意点

  * ⚠️ 为什么使用`unordered_map`而不是`map`?
    * `std::map` 底层是红黑树，查找和插入是 $O(\log n)$。
    * 对于这种频繁查写的滑动窗口题目，使用 `std::unordered_map`（哈希表）可以将平均复杂度降到 $O(1)$，效率更高。
    * 理论上哈希提供更好的平均性能，在大多数情况下。


---
## 代码实现

```cpp
class Solution {
public:
    int totalFruit(vector<int>& fruits) {

        unsigned total = 0, left = 0; 
        unordered_map<int, unsigned> lookup; //使用unordered_map会有更好的性能大多数情况下
        for (unsigned right = 0; right != fruits.size(); ++right){

            ++ lookup[fruits[right]]; //将果子放入篮子中
            while(lookup.size() > 2){ //当种类大于2种后开始收缩
                auto f = lookup.find(fruits[left]); //寻找现在应该去掉的水果
                if((--f->second) == 0 ) lookup.erase(f); //数量为0的水果需要删除
                ++ left; 

            }

            total = max(total, right - left + 1); 
        }

        return total; 
    
    }
};
```

