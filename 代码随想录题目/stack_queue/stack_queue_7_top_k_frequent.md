# 前K个高频元素 — top k frequent  

- **题目（LeetCode 347）**： [🔗 题目](https://leetcode.cn/problems/top-k-frequent-elements/description/)  
- **难度**：中等
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0347.%E5%89%8DK%E4%B8%AA%E9%AB%98%E9%A2%91%E5%85%83%E7%B4%A0.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1Xg41167Lz/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)
  - [🧠 文字解析（灵茶山艾府）- 桶排序法`O(n)`, 推荐阅读](https://programmercarl.com/0347.%E5%89%8DK%E4%B8%AA%E9%AB%98%E9%A2%91%E5%85%83%E7%B4%A0.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)

---
## 关键点（精简）

**方法一：桶排序哈希法**
<details close> 
<summary><b>👉 点击展开</b></summary>

先用哈希表统计各元素出现频率，再以频率为索引建立"桶"（索引即频率，桶内装具有该频率的所有元素），最后从高频往低频倒序取满k个。

- **为什么是桶排序？** 频率范围上限为n（数组长度），属于**有限范围整数键**，桶排序可将O(n log n)的排序优化至O(n)
- **倒序收集的必然性**：题目保证答案唯一且必然存在某次`insert`后恰好凑齐k个，从`max_freq`递减遍历确保优先取到高频元素

**关键点**

1. **频率作为数组索引**
   - **机制**：`vector<vector<int>> buckets(max_freq+1)` 用数组索引天然表示频率值
   - **场景**：频率为3的元素放入`buckets[3]`，实现O(1)频率归类
   - **容量设定**：`max_freq+1` 因为频率范围是`[1, max_freq]`，索引0闲置（没有元素出现0次）

2. **倒序收集的终止条件**
   - **逻辑**：`for (int i = max_freq; ret.size() < k; --i)` 从高频往低频扫，直到`ret`凑够k个
   - **题目保证**：答案唯一意味着不会出现"同频率需选择"的情况，且必然存在某次insert后`ret.size()`恰好等于k
   - **代码对应**：`ret.insert(ret.end(), buckets[i].begin(), b.end())` 整桶倒入结果（该桶所有元素同频率，无需内部排序）

3. **`max_freq`的动态追踪**
   - **机制**：第一遍遍历数组时同步更新`max_freq = max(max_freq, lookup[e])`
   - **优势**：第二遍建桶前已知最高频率，避免建立大小为n的冗余桶（节省空间至O(max_freq)）
   - **对比**：若直接开`n+1`大小的桶也可，但浪费`n - max_freq`个空桶空间

4. **哈希表与桶的解耦**
   - **两阶段处理**：先`unordered_map`统计（值→频），再转置为桶（频→值列表）
   - **意图**：桶的索引只能是频率（整数），无法直接用`nums`的值作索引（可能为负或很大），哈希表承担"压缩映射"作用

**易错提醒**

- ⚠️ **桶大小开错**：`buckets(max_freq+1)` 不是`max_freq`，频率恰好等于`max_freq`的元素需要合法索引，漏+1会导致访问越界
- ⚠️ **倒序遍历边界**：必须从`i = max_freq`开始而非`i = buckets.size()-1`，后者可能包含空桶尾部，虽不影响结果但浪费迭代；且终止条件是`ret.size() < k`而非`i >= 0`，题目保证k有效且提前凑齐k个即可停
- ⚠️ **`insert` vs `push_back`混用**：当前使用`ret.insert`整桶插入正确，但需注意若改用`push_back`需遍历buckets[i]；另外题目保证唯一性意味着无需处理同频率内优先级，但通用场景下若需稳定性应考虑该细节

**复杂度分析**
时间复杂度： O(n)
空间复杂度： O(n)
</details>

---

**方法二：小顶堆维护Top K**

<details>
<summary> <b>👉 点击展开 </b></summary>
利用优先队列维护一个大小为k的"精英窗口"，堆顶始终存放当前频率第k大的元素（即门槛），遇到更高频元素就挤掉堆顶。

- **为什么是小顶堆？** 大顶堆弹出的是最大值，无法快速剔除最小值；小顶堆的`top()`是堆中最小的，新元素频率更高时直接`pop()`即可替换，保证堆中始终是最大的k个
- **与桶排序对比**：适用于k远小于n的场景，时间复杂度O(n log k)优于桶排序的O(n)仅当k极小时，但空间仅需O(k)优于桶排序的O(n)

**关键点**

1. **比较器的反向逻辑**
   - **机制**：`lhs.second > rhs.second`表示"左边频率大于右边时，左边优先级更低"
   - **堆性质**：priority_queue默认是大顶堆（堆顶最大），但通过此比较器反转，频率小的反而上浮到堆顶
   - **代码对应**：`decltype(compare)`推导类型，构造函数传入`compare`实例初始化
   - **反例**：若写成`<`则变成大顶堆，最终保留的是频率最低的k个元素而非最高

2. **lambda捕获与mutable**
   - **捕获方式**：`[&lookup]`按引用捕获哈希表，供比较器内部访问（虽然本题比较器只用pair的second，无需访问lookup）
   - **mutable标记**：允许lambda内部修改捕获的变量（本题实际无修改，属冗余但无害）
   - **陷阱**：若捕获方式误写为值捕获`[lookup]`，会触发拷贝且无法反映外部lookup变化（虽本题无后续修改，但属不良实践）

3. **堆大小动态维持**
   - **流程**：先push新元素，再判断`size()>k`，若超界则pop堆顶（最小频率）
   - **边界**：始终保持堆大小≤k，遍历结束后恰好为k个
   - **意图**：确保堆中始终是目前见过的频率最高的k个候选，弱于堆顶的直接淘汰

4. **结果的无序性**
   - **现象**：最终while循环弹出顺序是堆内频率从低到高（相对于Top K而言是逆序），但题目不要求返回顺序，故可接受
   - **若需有序**：应改为大顶堆存储结果，或最后对ret按频率排序


**易错提醒**
- ⚠️ **比较器方向反置**：`lhs.second > rhs.second`才是小顶堆（频率大的排后面），若写成`<`则变成大顶堆，最终返回的是频率最低的k个元素而非最高，导致WA
- ⚠️ **lambda构造函数传参**：`priority_queue<..., decltype(compare)> min_heap(compare)`必须传入compare实例，decltype仅指定类型，漏传参会导致编译错误（C++20前需显式构造）
- ⚠️ **push后检查size**：必须先`push(e)`再判断`size()>k`，顺序反了会导致先pop空堆或错误地pop旧元素；且判断条件必须是`>k`而非`>=k`，否则当size==k时错误地pop，最终只剩k-1个元素
- ⚠️ **结果顺序非频率序**：最终ret中是按堆弹出顺序（频率从小到大），若题目要求按频率降序输出，需额外排序或改用大顶堆收集结果

**复杂度分析**
时间复杂度： O(nlogk)
空间复杂度： O(n)

</details>


---
## 代码实现

**方法一：桶排序哈希法**
<details close> 
<summary><b>👉 点击展开</b></summary>


```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 阶段1: 统计频率 + 追踪最高频
        unordered_map<int, int> lookup;   // 值 → 频率映射
        int max_freq = INT_MIN;           // 记录最高频率，用于确定桶大小
        
        for (const auto e : nums) {
            ++lookup[e];                  // 统计当前元素频率
            max_freq = max(max_freq, lookup[e]);  // 动态更新最高频
        }

        // 阶段2: 建立频率桶（索引=频率，值=具有该频率的元素列表）
        // ⚠️ 大小为max_freq+1，因为频率范围是[1, max_freq]，索引0闲置
        vector<vector<int>> buckets(max_freq + 1); 
        
        // 意图: 将哈希表的<值,频率>转置为桶的<频率,[值列表]>
        for (const auto& e : lookup) {
            buckets[e.second].push_back(e.first);  // 频率e.second的桶加入元素e.first
        }
         
        // 阶段3: 从高频往低频收集结果，直到凑够k个
        // 题目保证答案唯一且必然存在某次insert后恰好等于k
        vector<int> ret;
        for (int i = max_freq; ret.size() < k; --i) {
            // 意图: 整桶倒入结果（该桶内所有元素频率相同且都满足Top K要求）
            // 注意: 题目唯一性保证此处无需桶内排序或筛选
            ret.insert(ret.end(), buckets[i].begin(), buckets[i].end());
        }
        
        return ret; 
    }
};
```
</details>

---
**方法二：小顶堆维护Top K**
<details>
<summary><b>👉点击展开</b></summary>

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 阶段1: 统计各元素出现频率
        unordered_map<int, int> lookup;   // 值 → 频率
        for (const auto e : nums) {
            ++lookup[e]; 
        }

        // 阶段2: 定义小顶堆比较器（频率小的优先级高，位于堆顶）
        // 意图: lhs.second > rhs.second 表示"左边频率大则排后面"，构建小顶堆
        auto compare = [&lookup](pair<int, int> lhs, pair<int, int> rhs) mutable { 
            return lhs.second > rhs.second;  // ⚠️ 小顶堆: 频率大的被认为"小于"，排在下方
        }; 
        
        // 初始化小顶堆，需传入比较器实例
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> min_heap(compare); 

        // 阶段3: 维护大小为k的堆
        for (const auto& e : lookup) {
            min_heap.push(e);           // 压入当前<值,频率>
            if (min_heap.size() > k) {  // ⚠️ 超界时弹出堆顶（当前k个中最小的频率）
                min_heap.pop();         // 挤掉门槛，保留更高的k个
            }
        }

        // 阶段4: 收集结果（此时堆中恰好k个元素，频率最低的位于堆顶）
        // 注意: 弹出顺序是频率从低到高（相对于Top K），题目不要求顺序故可直接返回
        vector<int> ret;
        while (!min_heap.empty()) {
            ret.push_back(min_heap.top().first);  // 取元素值（pair.first）
            min_heap.pop();
        }

        return ret; 
    }
};
```
</details>
