# 移动零 — move zeroes

- **题目（LeetCode 26）**： [🔗 题目](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析 （灵茶山艾府）](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/solutions/2807162/gen-zhao-wo-guo-yi-bian-shi-li-2ni-jiu-m-rvyk) 


---

## 关键点（精简）

* 依旧双指针思路
* 我们首先要明确两个指针是用来干啥的
* 慢指针用于指向去重数组的最后一个元素， 
    * 这样我们可以用于和快指针比较决定是否需要加入到新元素
* 快指针则是用于一个一个遍历所有元素
* 直到快指针遍历完后，快指针指向了最后原数组的尾后位置
* 这个时候我们需要删除的元素数量就是:
    * 原本数组数量-新数组元素量






---
## 代码实现
```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {

        unsigned slowPtr = 0, quickPtr = 0, count = 0; 


        while( quickPtr != nums.size() ){

            if (nums[slowPtr] != nums[quickPtr]) nums[++slowPtr] = nums[quickPtr];
            ++quickPtr; 

        }

        count = quickPtr - slowPtr;
        for (int i = 1; i < count; ++i) nums.pop_back();    
        return nums.size(); 
        
    }
};
```

