# 交换链表中的节点 — Swap pairs

- **题目（LeetCode 24）**： [🔗 题目](https://leetcode.cn/problems/swap-nodes-in-pairs/description/)  
- **难度**: 中等
- **解析 / 学习链接**：   
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0024.%E4%B8%A4%E4%B8%A4%E4%BA%A4%E6%8D%A2%E9%93%BE%E8%A1%A8%E4%B8%AD%E7%9A%84%E8%8A%82%E7%82%B9.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1YT411g7br/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）

**一句话总结**
* **虚拟头节点 + 三指针迭代 + 直接模拟交换**：使用`prev`、`curr`、`nxt`三个指针，每次循环将相邻两个节点交换位置，然后指针向前移动两步继续下一对交换。

**核心交换逻辑**

```
初始状态：prev → curr → nxt → temp
交换后：prev → nxt → curr → temp
然后移动：prev = curr, curr = prev->next
```

**关键设计点**
1. **虚拟头节点**：统一处理头节点交换，避免特殊判断
2. **三指针追踪**：
   - `prev`：指向当前对的前一个节点
   - `curr`：指向当前对的第一个节点
   - `nxt`：指向当前对的第二个节点
3. **条件判断**：
    * `while((curr = prev->next) && (nxt = curr->next))`确保有完整的一对节点对可交换， 
    * 如果只有一个或者没有， 就不交换，直接退出


---
## 代码实现

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        
        //这种交换需要维护三个节点， 第一个是prev, curr, nxt, 需要将 
        // prev -> curr -> nxt 改为:
        // prev -> nxt -> curr
        //停止条件为curr和nxt其中有一个为nullptr

        //使用虚拟头节点, 统一处理操作
        ListNode *dummyhead = new ListNode(0 , head); 
        ListNode *prev = dummyhead, *curr, *nxt; 

        //需要保证起嘛还有两个节点，才能配对交换
        //不够了就退出
        //因此也适用于节点只有0个或者1个的情况
        while((curr = prev->next) && (nxt = curr->next)){ 
            //进行换位置
            curr->next = nxt->next; 
            prev->next = nxt; 
            nxt -> next = curr; 
            
            //移动三个节点
            prev = curr; 
            curr = prev->next; 
        }
        
        return dummyhead->next;
        
    }
};
```
