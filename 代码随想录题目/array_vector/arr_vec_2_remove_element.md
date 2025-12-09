# 移除元素 — remove element  

- **题目（LeetCode 27）**： [🔗 题目](https://leetcode.cn/problems/remove-element/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录/Carl）](https://programmercarl.com/0027.%E7%A7%BB%E9%99%A4%E5%85%83%E7%B4%A0.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BEhtml#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)  
  - [🎥 视频讲解（Bilibili）](https://www.bilibili.com/video/BV12A4y1Z7LP/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）

* 基本概念：`vector`是通过`array`实现， 当我们删除一个元素后，`size`会减一但并不代表空间并不真正减少了，只是计数器减小而已
    * 当一道题可以调用库函数如`erase()`就直接解决问题的话，那么就不要调用他
    * 如果使用暴力移除-也就是删除一个元素然后将后面所有元素一个一个前移的时间复杂度为O(n^2)
* **双指针思路**: 
    * 我们定义两个指针：**快指针**和**慢指针**
    * **快指针**：指向新数组（删除后）所需要的元素
    * **慢指针**：指向新数组需要更新的元素位置
    * 快指针向慢指针传递需要更新的元素
        * 开始两者指向同一起点
        * 没有遇到目标值就更新和移动
        * 遇到了目标值就不更新，慢指针不动，快指针依然移动
        * 到下一个非目标值再继续更新
    * 最后慢指针就是指向的新数组的尾后
* 这道题就是一个容器函数里面的`erase()`的实现，时间复杂度为`O(n)`





---
## 代码实现

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
 
       int slow = 0; 
       int sent = nums.size(); 

       for(int fast = 0; fast < sent; ++fast){

            if(nums[fast] != val){

                nums[slow] = nums[fast]; 
                ++slow; 

            }

       }

       return slow; 

    }
};
```



