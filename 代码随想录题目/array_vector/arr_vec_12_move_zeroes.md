# 移动零 — move zeroes

- **题目（LeetCode 283）**： [🔗 题目](https://leetcode.cn/problems/move-zeroes/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析 （灵茶山艾府）](https://leetcode.cn/problems/move-zeroes/solutions/2969353/kuai-man-zhi-zhen-wei-shi-yao-ke-yi-ba-s-1h8x) 


---

## 关键点（精简）
* 依旧使用**双指针**即可解决问题
* 可以将0元素视为空位子，慢指针指向第一个空位
* 通过将右边的非0元素移动到左边的空位上后，才可以保证元素顺序
* 同时快指针向右寻找非0元素，保证慢指针和快指针之间，也就是:
    * `[slowPtr, quickPtr)`之间都是空位
    * 一旦`nums[quickPtr]`为非0元素
    * 随即将`nums[slowPtr]`和`nums[quickPtr]`互换位置
    * 保证`[slowPtr+1, quickPtr)`依然都为空位，保持成立
    * 当`quickPtr`到达`n`时候，就能保证最尾巴的位置都是空位置
    * 遍历此时也结束




---
## 代码实现

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {

        unsigned slowPtr = 0, quickPtr = 0; 

        while( quickPtr != nums.size() ){
            
            auto temp = nums[quickPtr];
            nums[quickPtr] = nums[slowPtr];
            nums[slowPtr] = temp; 
            
            if (nums[slowPtr] != 0) ++slowPtr;
        
            ++ quickPtr;

        }
        
    }
};
```
