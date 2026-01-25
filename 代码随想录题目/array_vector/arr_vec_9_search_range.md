# 在排序数组中查找元素的第一个和最后一个位置 — search range

- **题目（LeetCode 34）**： [🔗 题目](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/)  
- **难度**：中等
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录/Carl）](https://programmercarl.com/0034.%E5%9C%A8%E6%8E%92%E5%BA%8F%E6%95%B0%E7%BB%84%E4%B8%AD%E6%9F%A5%E6%89%BE%E5%85%83%E7%B4%A0%E7%9A%84%E7%AC%AC%E4%B8%80%E4%B8%AA%E5%92%8C%E6%9C%80%E5%90%8E%E4%B8%80%E4%B8%AA%E4%BD%8D%E7%BD%AE.html#%E6%80%9D%E8%B7%AF) 
  -  [🧠 视频解析（灵茶山艾府）， 推荐观看](https://www.bilibili.com/video/BV1AP41137w7/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)
 

---
## 代码实现

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        
        if (nums.size() == 0) return {-1, -1}; 
        int low = lowerbound(nums, target); 
        
        if ( low == nums.size() || nums[low] != target ) return {-1, -1}; 
        //如果能通过那么一定存在low, high
        int high = lowerbound(nums, target+1) -1; 

        return {low, high};

    }

private:

    int lowerbound(vector<int> &nums, int target){

        int low = 0, high = nums.size(); 

        while (low < high){

            int mid = (high - low)/2 + low; 
            if (target > nums[mid]) low = mid + 1; //去[low, mid] 继续搜索
            else high = mid; //nums[mid] < target, 那么左边无意义, 去[mid+1, high]

        }

        return low;  

    }

};
```
