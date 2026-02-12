# 环形链表 — detect cycle 

- **题目（LeetCode 142）**： [🔗 题目](https://leetcode.cn/problems/linked-list-cycle-ii/description/)  
- **难度**: 中等
- **解析 / 学习链接**：   
  - [🧠 文字解析（灵茶山艾府）， 讲的非常好推荐](https://leetcode.cn/problems/linked-list-cycle-ii/solutions/1999271/mei-xiang-ming-bai-yi-ge-shi-pin-jiang-t-nvsq)

---
## 关键点（精简）
> 一句话总结思路：双指针 + floyd判圈算法


**什么是floyd判圈算法（Floyd's Cycle Detection）？**



**第一阶段：判断是否有环**
- 慢指针每次走1步，快指针每次走2步
- 如果链表有环，快指针一定会追上慢指针（相遇）
- 如果没环，快指针会先到达末尾

**第二阶段：找环的入口**
- 设头节点到入环口距离为 `a`，环长为 `c`
- 相遇时，慢指针走了 `b` 步，快指针走了 `2b` 步
- 相遇时，快指针比慢指针多走了 `k` 圈：`2b - b = kc`，即 `b = kc`

**关键结论**：慢指针在环内走了 `b - a = kc - a` 步到达相遇点。
- 这意味着从**相遇点再走 `a` 步**就能回到入环口
- 所以让**头节点**和**相遇点的慢指针**同时走，每次各走1步
- 它们必定在入环口相遇（都走了 `a` 步）





---
## 代码实现

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {

        //快指针一轮2步， 慢指针一轮1步
        ListNode *quickPtr = head, *slowPtr = head; 
        
        while(quickPtr && quickPtr->next){ //如果碰上nullptr说明没有环出现直接退出

            quickPtr = quickPtr->next->next; 
            slowPtr = slowPtr->next; 

            //这个时候相遇然后再走a步就到入口，那么将快指针重置为头节点
            //再走a步即可在入口节点相遇
            if (quickPtr == slowPtr){
                quickPtr = head; 
                while (quickPtr != slowPtr){
                    quickPtr = quickPtr->next;
                    slowPtr = slowPtr->next; 
                }
                return slowPtr; 
            }; 
            

        }
        return nullptr; 
    }
};
```
