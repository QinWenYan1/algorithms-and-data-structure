# 长度最小的子数组 — min subarray length 

- **题目（LeetCode 209）**： [🔗 题目](https://leetcode.cn/problems/minimum-size-subarray-sum/description/)  
- **难度**：中等
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录/Carl）](https://programmercarl.com/0209.%E9%95%BF%E5%BA%A6%E6%9C%80%E5%B0%8F%E7%9A%84%E5%AD%90%E6%95%B0%E7%BB%84.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)  
  - [🎥 视频讲解（Bilibili）](https://www.bilibili.com/video/BV1tZ4y1q7XE/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）
* 暴力搜索法: 两个`for`循环嵌套即可完成
* **双指针&&滑动窗口方法**: 
  * 我们需要通过一个`for`循环就完成暴力搜索两个`for`循环做的事儿
  * 我们需要两个指针表示起始和终止位置去记录最小长度
  * `for`循环里的`j`是表示起始位置还是终止位置呢？ 
    * 如果`j`表示的是起始位置的话，那么另外一个终止位置指针实际上还是需要去一个一个元素往前遍历去找最小的subarray长度，实际依然是两个for循环嵌套，没有意义
    * 那么`j`一定就是终止位置的指针
  * 当起始位置和终止位置里面元素和>=目标值时，我们就可以暂停移动终止点并移动起始点
  * 缩小集合范围来看下一个子集合是否满足条件，来搜集不同长度里面的和, **并取最小的那一个**
  * 因此在初始化的时候，我们必须将subarray的长度初始化为无限大
  * 就像毛毛虫，一拉一缩往前走
  * 这样可以保证在`j`向前移动时寻找集合时，还在收缩，保证这个集合是满足条件的最小长度



---
## 代码实现

```cpp

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {

        int end = nums.size(); 
        int i = 0; 
        int len = INT32_MAX; //标记为无穷大
        int total_value = 0; 

        for(int j=0; j<end; ++j){

            total_value += nums[j];

            while(total_value >= target){

                int local_len = j-i+1; 
                total_value -= nums[i++]; 
                len = min(local_len, len);

            }

        }
        
        return (len == INT32_MAX)? 0:len;

    }
};
```
时间复杂度:O(n)
空间复杂度:O(1)
