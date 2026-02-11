# 链表相交 — get intersection node 

- **题目（LeetCode 160）**： [🔗 题目](https://leetcode.cn/problems/intersection-of-two-linked-lists-lcci/description/)  
- **难度**: 简单
- **解析 / 学习链接**：   
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/%E9%9D%A2%E8%AF%95%E9%A2%9802.07.%E9%93%BE%E8%A1%A8%E7%9B%B8%E4%BA%A4.html#%E6%80%9D%E8%B7%AF)
   - [🧠 文字解析（krahets），推荐阅读， 双指针解法](https://leetcode.cn/problems/intersection-of-two-linked-lists-lcci/solutions/1190240/mian-shi-ti-0207-lian-biao-xiang-jiao-sh-b8hn)


---
## 关键点（精简）

#### 方法一

**长度对齐法**：先计算两个链表的长度，让长链表先走长度差步，使两个链表从同一距离末尾的位置开始同步遍历，找到第一个相同的节点。

**核心逻辑**
```
1. 分别遍历两个链表，计算长度lenA和lenB
2. 计算长度差：abs(lenA - lenB)
3. 长链表指针先走长度差步
4. 两个链表指针同时遍历，比较节点地址是否相同
```

---
#### 方法二
**双指针法（更优解法）**：两个指针分别遍历两个链表，走完自己的路后换到对方链表继续走，总会在交点相遇或同时走到尽头（`nullptr`）。


**核心逻辑**
```
1. 设链表A长度a，链表B长度b，公共部分长度c

2. 当遍历到交点时：
  指针A走的路径：a + (b - c)
  指针B走的路径：(a - c) + b

3. 也就是说两者走的路程是相等的

4. 如果存在交点(c>0)：两个指针会在交点相遇
5. 如果不存在交点(c=0)：两个指针会同时到达nullptr
```


---
## 代码实现

#### 方法一
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        //第一步我们需要先对其，然后才能一个对一个的去查找

        unsigned countA = 0, countB = 0; 
        ListNode *currA = headA, *currB = headB; 
        while(currA) {
            currA = currA->next;
            ++countA; 
        }
        while(currB) {
            currB = currB->next; 
            ++countB; 
        }

        //从头开始，将A，B对其

        currA = headA;
        currB = headB;
        //计算长度差
        bool aIsBigger = countA >= countB; 
        unsigned countDiff = (aIsBigger)? countA-countB : countB-countA; 
        if (aIsBigger) {
            while(countDiff--) currA = currA->next; 
        }else{
            while(countDiff--) currB = currB->next;
        }

        //现在完成对其操作，那么开始遍历检查
        while(currA){
            if (currA == currB) return currA; 
            currA = currA->next; 
            currB = currB->next; 
        }

        //没有发现交叉
        return nullptr; 

        
    }
};
```

#### 方法二
```cpp

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        
        ListNode *currA = headA, *currB = headB; 
        while (currA != currB){
            // 如果走到链表末尾，就转到另一个链表头部
            currA = (currA==nullptr)? headB: currA->next;
            currB = (currB==nullptr)? headA: currB->next;
        }
        // 最终一定会相交， 要么是节点上相交， 要没就是nullptr相交也就是没有
        return currA; 

    }
};
```
