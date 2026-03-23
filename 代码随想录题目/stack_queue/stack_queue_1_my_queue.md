# 用栈实现队列 — my queue

- **题目（LeetCode 232）**： [🔗 题目](https://leetcode.cn/problems/implement-queue-using-stacks/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0232.%E7%94%A8%E6%A0%88%E5%AE%9E%E7%8E%B0%E9%98%9F%E5%88%97.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1nY4y1w7VC/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）

**核心思路**
**双栈倒序法**：利用两个栈 (`sin`输入栈 / `sout`输出栈) 模拟队列的 FIFO 特性。栈是 LIFO，两次 LIFO 叠加即为 FIFO。

  - `sin`：只负责接收新元素（`push`）
  - `sout`：只负责输出元素（`pop`/`peek`）
  - **倒栈时机**：仅当 `sout` 为空时才将 `sin` 全部倒入 `sout`，确保队列顺序正确

**关键点**
1. **延迟搬运**  
   * 不要每次 `push`/`pop` 都倒栈，只在输出栈空了才一次性倒完。
   * 这样每个元素最多被搬运两次（进`sin`一次，进`sout`一次），均摊时间复杂度为 O(1)。
   * **时间复杂度**: 都为O(1)。`pop`和`peek`看起来像O(n)，实际上一个循环n会被使用n次，最后还是O(1)。

2. **`peek()` 的复用**  
   `pop()` 直接调用 `peek()` 获取队首元素，再 `sout.pop()` 移除，避免重复写倒栈逻辑。

3. **空队列判断**  
   必须 `sout.empty() && sin.empty()`，因为元素可能只在输入栈中。



---

### 易错提醒
- ⚠️ **倒栈条件**：`if (sout.empty())` 不能漏，否则顺序会乱（新元素会跑到队首）
- ⚠️ **倒栈必须倒完**：`while(!sin.empty())`，不能只倒一部分
- ⚠️ **内存管理**：LeetCode 环境下不需要手动 delete，但工业代码中注意智能指针或 RAII

---
## 代码实现

```cpp
class MyQueue {
    stack<int> sin;    // 输入栈：只负责接收新元素（队尾）
    stack<int> sout;   // 输出栈：只负责取出元素（队首）
    
public:
    MyQueue() = default;
    
    // 时间复杂度: O(1)
    // 新元素一律压入输入栈，此时不影响输出栈的顺序
    void push(int x) {
        sin.push(x);
    }
    
    // 时间复杂度: 均摊O(1)，最坏O(n)（仅在输出栈为空时触发倒栈）
    // 逻辑：复用peek()获取队首，然后将其从输出栈移除
    int pop() {
        int front = peek();  // 确保队首元素已在输出栈顶
        sout.pop();
        return front;
    }
    
    // 时间复杂度: 均摊O(1)，最坏O(n)
    // 关键逻辑：若输出栈为空，将输入栈所有元素倒入输出栈（顺序反转，实现FIFO）
    // 这样输入栈的栈底（最早进入的元素）会变成输出栈的栈顶
    int peek() {
        if (sout.empty()) {
            // 倒栈：把输入栈的元素全部转移到输出栈，顺序反转
            while (!sin.empty()) {
                sout.push(sin.top());
                sin.pop();
            }
        }
        return sout.top();  // 输出栈顶即为队列的队首
    }
    
    // 时间复杂度: O(1)
    // 队列为空的条件：两个栈都必须为空（元素可能在输入栈等待被转移）
    bool empty() {
        return sin.empty() && sout.empty();
    }
};
```
