# 三数之和 — three sum 

- **题目（LeetCode 15）**： [🔗 题目](https://leetcode.cn/problems/3sum/)  
- **难度**：中等
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0015.%E4%B8%89%E6%95%B0%E4%B9%8B%E5%92%8C.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)  
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1GW4y127qo/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)  


---
## 关键点（精简）

方法一：**哈希**
* 这道题目如果要使用哈希的话思路和[四数之和](./hash_table_5_four_sum_count.md)是一样的
* 具体实现可以看看代码随想录的文字解说
* 唯一的区别是这道题目需要去重，而且去重逻辑非常复杂，面试中很难直接写出没有bug的代码
* 所以这道题并不推荐使用哈希表

方法二：**双指针** - 推荐！


**排序 + 固定锚点 + 双向双指针**

1. **排序**：先对数组升序排序，这是使用双指针的前提，使得我们可以通过比较和与0的大小来决定指针移动方向。

2. **固定锚点**：外层循环遍历 `i`（从0到n-3），将 `nums[i]` 作为三元组的第一个数。由于数组已排序：
    - 若 `nums[i] == nums[i-1]`则表示已经重复元素在`i`这个锚点位置，直接跳过
    - 若 `nums[i] > 0` 则可直接终止循环（后面都是正数，三数之和不可能为0）。

3. **双指针查找**：初始化 `left = i+1`，`right = n-1`，在 `[i+1, n-1]` 区间内寻找两数，使得三数之和为0：
   - **若 `sum > 0`**：说明 `right` 处的值太大，需将 `right--`（向左移动才能遇到更小的值）
   - **若 `sum < 0`**：说明 `left` 处的值太小，需将 `left++`（向右移动才能遇到更大的值）  
   - **若 `sum == 0`**：找到一组解，记录后需同时 `left++` 且 `right--`（当前两数已用完，必须向中间收缩寻找新组合）

4. **去重**：由于数组有序且存在重复元素，需在两个层面去重：外层跳过重复的 `i`，内层找到解后跳过重复的 `left` 和 `right`。

**复杂度**：时间 $O(N^2)$，空间 $O(1)$。



**注意点**

**1. 为什么判断 `nums[i] == nums[i-1]` 而非 `nums[i+1]`？**  
  * `i-1` 已作为 pivot 处理过，跳过 `i` 可避免生成重复三元组；
  * 若判断 `i+1`，会跳过当前值的首次出现导致漏解（如 `[-1,-1,2]` 会漏掉第一个 `-1`）。

**2. 为什么找到解后要那样去重？**  
  * 当前 `left` 和 `right` 已被使用，若邻居值相同，不跳过会在同一`pivot`下产生重复的三元组。
  * 先 `while` 跳过所有相同邻居，再移动指针寻找全新组合。

**3. 为什么找到答案时双指针要同时收缩？**  
  * 因为当前的两个值已经被"用尽"了，单独移动无法产生新的有效解。
  * **同时收缩**是为了在排除当前已使用的数值对后，立即开始寻找全新的数值组合，避免在"无效区间"内做多余的判断。

---
## 代码实现
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> results;
        if (nums.size() < 3) return results;
        
        sort(nums.begin(), nums.end());  // O(NlogN)
        
        // 固定第一个数，转化为两数之和问题
        for (int i = 0; i < nums.size() - 2; ++i) {
            // 剪枝1：跳过重复的 pivot
            if (i > 0 && nums[i] == nums[i-1]) continue;
            
            // 剪枝2：当前数已大于0，后面不可能有三元组和为0
            if (nums[i] > 0) break;
            
            int left = i + 1, right = nums.size() - 1;
            
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                
                if (sum > 0) {
                    --right;  // 和太大，右指针左移减小数值
                } else if (sum < 0) {
                    ++left;   // 和太小，左指针右移增大数值
                } else {
                    // 找到有效三元组
                    results.push_back({nums[i], nums[left], nums[right]});
                    
                    // 去重：跳过相同的 left 和 right
                    while (left < right && nums[left] == nums[left+1]) ++left;
                    while (left < right && nums[right] == nums[right-1]) --right;
                    
                    // 同时收缩，寻找下一组解
                    ++left;
                    --right;
                }
            }
        }
        return results;
    }
};
```


