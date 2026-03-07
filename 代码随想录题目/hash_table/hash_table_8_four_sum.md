# 四数之和 — four sum 

- **题目（LeetCode 18）**： [🔗 题目](https://leetcode.cn/problems/4sum/description/)  
- **难度**：中等
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0018.%E5%9B%9B%E6%95%B0%E4%B9%8B%E5%92%8C.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)  
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1DS4y147US/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)  


---
## 关键点（精简） 

**依旧使用双指针降维**: 
  * 与[三数之和](./hash_table_7_three_sum.md)思路完全一样
  * 四数之和就是在三数之和外面再嵌套一层循环固定第二个数，把问题变成"**固定前两数后求两数之和**"，核心的降维思路、双指针移动逻辑和去重策略（跳过前驱重复值）完全一致。



**不同点（集中在剪枝操作）：**

*   **三数之和（target=0）的剪枝**：利用"正数不可能凑出0"的特性。当 `nums[i] > 0` 时直接 `break`，因为数组已排序，后面都是正数，三数之和必大于0。这是基于**符号特性**的剪枝。

*   **四数之和（target为任意值）的剪枝**：由于 target 可能为负数或正数，且负负得正、正负相加等情况复杂，不能简单判断 `nums[i] > target`。必须使用**极值比较**：
    *   **最小和剪枝**：若 `nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target`，说明当前及后续最小的四个数之和都太大，直接 `break`。
    *   **最大和剪枝**：若 `nums[i] + nums[n-3] + nums[n-2] + nums[n-1] < target`，说明当前固定值即使配上最大的三个数都不够，应 `continue` 尝试下一个 `i`。
    * 内层循环同理，只是固定了第二个然后来比较

**关键差异总结**：三数之和剪枝看**符号**（是否>0），四数之和剪枝看**范围**（当前固定值与剩余数组极值的关系）。



---
## 代码实现

```cpp
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

        //使用双指针思路
        vector<vector<int>> results; 
        if (nums.size() < 4) return results; 

        //仍然先排序
        sort(nums.begin(), nums.end()); 
        int tail = nums.size(); 
        for (int a = 0; a < tail-3; ++a){
            if (target < static_cast<long>(nums[a])+nums[a+1]+nums[a+2]+nums[a+3]) break; //剪枝
            if (static_cast<long>(nums[a])+nums[tail-3]+nums[tail-2]+nums[tail-1] < target) continue;//枝剪
            if ( 0 < a && nums[a-1] == nums[a]) continue;//去重
            for (int b = a+1; b < tail-2; ++b){
                if (target < static_cast<long>(nums[a])+nums[b]+nums[b+1]+nums[b+2]) break; //剪枝
                if (static_cast<long>(nums[a])+nums[b]+nums[tail-2]+nums[tail-1] < target) continue;//枝剪
                if ( a+1 < b && nums[b-1] == nums[b]) continue; //去重
                int c = b+1, d = tail-1; 

                while( c < d ){
                    long sum = static_cast<long>(nums[a]) + nums[b] + nums[c] + nums[d];
                    if (sum > target) --d; 
                    else if(target > sum) ++c; 
                    else{ //找到了需要的值
                        results.push_back({nums[a],nums[b],nums[c],nums[d]}); 

                        while(c < d && nums[c] == nums[c+1]) ++c; 
                        while(c < d && nums[d-1] == nums[d]) --d; 
                        ++c; 
                        --d; 

                    }
                }
            }
        }
        return results; 
    }
};
```
