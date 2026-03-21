# 删除链表的倒数第N个节点 — remove Nth from end

- **题目（LeetCode 19）**： [🔗 题目](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/)  
- **难度**: 中等
- **解析 / 学习链接**：   
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0019.%E5%88%A0%E9%99%A4%E9%93%BE%E8%A1%A8%E7%9A%84%E5%80%92%E6%95%B0%E7%AC%ACN%E4%B8%AA%E8%8A%82%E7%82%B9.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1vW4y1U7Gf/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）


**一句话总结**
* **虚拟头节点+快慢双指针一次遍历**：
让快指针先走n步，然后快慢指针一起移动，当快指针到达末尾时，慢指针正好指向要删除节点的前一个位置， 并同时使用虚拟节点统一操作

## **核心逻辑**
```
1. 快指针先走n步
2. 快慢指针一起走，直到快指针到达最后一个节点
3. 此时慢指针指向倒数第n+1个节点（要删除节点的前一个）
4. 删除慢指针的下一个节点
```

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {

        //快慢指针， 快指针先移动， 然后两个共同一起移动，直到末尾即可
        ListNode *dummyhead = new ListNode(0, head);
        ListNode *prev = dummyhead, *curr = dummyhead;

        //先将curr移动到距离prev n的位置
        while(n--) curr=curr->next; 

        //接下来一起移动
        while(curr->next){
            prev = prev->next; 
            curr = curr->next; 
        }

        //到位置了， 开始删除
        auto del = prev->next; //记录删除节点
        prev->next = del->next; 
        delete del; 

        return dummyhead->next; 
        
    }
};
```
