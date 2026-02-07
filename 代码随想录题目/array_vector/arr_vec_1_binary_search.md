# 二分查找 — binary search 

- **题目（LeetCode 704）**： [🔗 题目](https://leetcode.cn/problems/binary-search/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0704.%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)  
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1fA4y1o715/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）

* 一般我们在区间`[low, high)`左闭右开
* 易错点：
  * 循环里面到底是`low` `<`还是`<=` `high`?
    - 我们考虑边界情况，当`low = high`的时候本身里面已经没有元素也就没有意义
    - 所以不用在继续循环了，所以应该使用`<`
  * 如果`target < nums[mid]`那应该是 `high=mid`还是`high=mid-1`?
    - 因为时左闭右开，`high`范围缩小后，搜索范围里面不包含`mid`
    - 因为我们在上一次迭代里面已经检查过`mid`
    - 所以`high=mid`就可以了
    - 同样道理，如果是`low`范围缩小后，搜索范围里还包含`mid`， 所以`mid = low + 1` 




---
## 代码实现

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {

        int hi = nums.size();
        int lo = 0; 

        while(lo < hi){

            int mid = (lo+hi)/2; 
            if( nums[mid] < target ) lo = mid+1; 
            if( target < nums[mid] ) hi = mid; 
            if ( target == nums[mid] ) return mid; 
            
        }

        return -1; 
        
    }
};
```
时间复杂度: O(nlogn)

