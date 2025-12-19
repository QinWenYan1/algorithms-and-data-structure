# 搜索插入位置 — search insert  

- **题目（LeetCode 35）**： [🔗 题目](https://leetcode.cn/problems/search-insert-position/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录/Carl）](https://programmercarl.com/0035.%E6%90%9C%E7%B4%A2%E6%8F%92%E5%85%A5%E4%BD%8D%E7%BD%AE.html#%E6%80%9D%E8%B7%AF)  
 

---
## 代码实现

```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {

        int low = 0, high = nums.size(); 

        while(low != high ){

            int mid = (low+high)/2; 

            if (nums[mid] < target)
                low = mid+1; 
            else if(target < nums[mid])
                high = mid; 
            else return mid;  
            
        }

        return low; 

    }
};
```

