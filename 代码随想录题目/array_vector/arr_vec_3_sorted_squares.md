# 有序数组的平方 — sorted squares

- **题目（LeetCode 977）**： [🔗 题目](https://leetcode.cn/problems/squares-of-a-sorted-array/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0977.%E6%9C%89%E5%BA%8F%E6%95%B0%E7%BB%84%E7%9A%84%E5%B9%B3%E6%96%B9.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)  
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1QB4y1D7ep/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）

* 我可以发现一个本题规律：经过平方之后，其最大的数一定出现在数组两边, 越来越小的元素将向中间合拢
* 那么我们就可以使用**双指针**来从两头一个一个将元素放入直到收拢
* **双指针策略**：
  * 头尾各一个指针，检查其平方之后谁大谁小， 依次放入到新数组
  * 直到合拢即可-也就是前面指针已经越过后面的指针就中止

---
## 代码实现
```cpp
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {

        vector<int> new_nums(nums.size());
        int k = new_nums.size()-1; 

        for (int i = 0, j = nums.size()-1; i <= j; ){

            int num1 = nums[i]*nums[i];
            int num2 = nums[j]*nums[j];

            if (num1 < num2){ new_nums[k--] = num2; --j; }
            else{ new_nums[k--] = num1; ++i; }

        }
 
        return new_nums; 
        
    }
};
```

 



