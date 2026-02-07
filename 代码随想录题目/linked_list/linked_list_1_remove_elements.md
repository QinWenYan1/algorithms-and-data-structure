# 移除链表元素 — Remove elements

- **题目（LeetCode 203）**： [🔗 题目](https://leetcode.cn/problems/remove-linked-list-elements/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（灵茶山艾府），推荐观看](https://leetcode.cn/problems/remove-linked-list-elements/solutions/2806456/tao-lu-ru-he-you-ya-di-shan-chu-lian-bia-ah8z/) 
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0203.%E7%A7%BB%E9%99%A4%E9%93%BE%E8%A1%A8%E5%85%83%E7%B4%A0.html#%E6%80%9D%E8%B7%AF)
  - [🎥 视频讲解（代码随想录）](bilibili.com/video/BV18B4y1s7R9/)

---
## 关键点（精简）


**一句话概括**：使用**虚拟头节点**统一删除逻辑，避免处理头节点删除的特殊情况。

**关键三步**
1. **创建哨兵节点**：在链表头部前添加一个虚拟节点
2. **双指针遍历**：`curr`指向当前节点，`nxt`指向下一个待检查节点
3. **选择性删除**：发现目标值就跳过并删除该节点，否则正常移动
4. **终止条件**：当前元素`curr`的下一个节点已经为空的时候

**为什么用虚拟头节点？**
- 当需要删除头节点时，无需特殊处理
- 统一所有节点的删除逻辑：`curr->next = nxt->next`
- 最终返回`dummy->next`即可得到新链表头

## **核心逻辑**
```
while(还有下一个节点) {
    if(下一个节点值==目标值) {
        跳过并删除这个节点
    } else {
        指针正常后移
    }
}
```

**精髓**：通过虚拟头节点，让链表删除操作变得**标准化**，无论删除哪个位置的节点都使用相同逻辑。

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
    ListNode* removeElements(ListNode* head, int val) {

        ListNode *dummy = new ListNode(0); //创建哨兵开头， 方便之后进行删除操作
        dummy->next = head; //和head连上
        ListNode *curr = dummy, *nxt = nullptr; 

        while((nxt = curr->next)){ //如果下一个是nullptr就停止遍历

            if(nxt->val == val){ //进行删除
                curr->next = nxt->next; 
                delete nxt;  
            }else{ //如果不相等， 那么就往后面挪一个
                curr = nxt; 
            }

        }

        return dummy->next; 
        
    }
};
```