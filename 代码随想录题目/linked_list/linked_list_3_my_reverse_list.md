# 反转链表 — Reverse list

- **题目（LeetCode 206）**： [🔗 题目](https://leetcode.cn/problems/reverse-linked-list/description/)  
- **难度** 简单
- **解析 / 学习链接**：   
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0206.%E7%BF%BB%E8%BD%AC%E9%93%BE%E8%A1%A8.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1nB4y1i7eL/)

---
## 关键点（精简）


**一句话总结**
**三指针迭代法**：使用`curr`、`nxt`、`nextStep`三个指针，每次断开并反转当前节点与前一个节点的指向，逐步向前推进直到链表完全反转。



**改进点**

1. **更直观**：变量名`prev`、`curr`、`nextTemp`语义更清晰
2. **更简洁**：用`prev=nullptr`初始化，让第一个节点的反转与后续节点完全一致，消除特殊处理
3. **更统一**：统一处理所有情况，没有提前将`head->next`设为`nullptr`的额外操作

**核心逻辑**：每次循环只做一件事——**把当前节点的next指针指向前一个节点**，然后三个指针整体向前移动一步。

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
    ListNode* reverseList(ListNode* head) {

        //总体思路: 1. 两个两个的迭代处理， 直到nxt为nullptr后停下，停下的时候curr的几点就是头节点了
        //处理两种特殊情况: 当元素数量少于2个的时候，可以直接不动
        if (head == nullptr || head->next == nullptr) return head; 

        //接下来起码有两个元素
        ListNode *curr = head, *nxt = curr->next, *nextStep = nxt->next;  
        curr->next = nullptr;

        while(nxt){ //开始迭代遍历， 进行交换
            ListNode *nextStep = nxt->next; 
            nxt->next = curr; 
            curr = nxt; 
            nxt = nextStep; 
        }

        head = curr; 
        return head; 

    }
};
```

---

## **代码实现（优化版本）**
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode *prev = nullptr, *curr = head;
    
    while(curr) {
        ListNode *nextTemp = curr->next;  // 保存下一个节点
        curr->next = prev;                // 反转当前节点指向
        prev = curr;                      // 前驱节点前进
        curr = nextTemp;                  // 当前节点前进
    }
    
    return prev;  // 最后prev就是新的头节点
}
```