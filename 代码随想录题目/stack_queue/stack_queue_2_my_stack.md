# 用队列实现栈 — my stack

- **题目（LeetCode 225）**： [🔗 题目](https://leetcode.cn/problems/implement-stack-using-queues/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0225.%E7%94%A8%E9%98%9F%E5%88%97%E5%AE%9E%E7%8E%B0%E6%A0%88.html)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1Fd4y1K7sm/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）


**核心思路**
**单队列轮转发优化**：利用队列的 FIFO 特性，通过循环将前 n-1 个元素依次出队再入队，使最后一个元素（栈顶）旋转到队首位置，然后取出。

- 队列是 FIFO，栈是 LIFO
- **关键操作**：`pop`/`top` 时把前面的元素全部赶到队尾，让目标元素浮到队首

1. **轮转逻辑`(pop)`**  
   `size = n` 时，循环 `n-1` 次：把队首元素取出来塞回队尾。最后队首剩下的那个就是"栈顶"（最晚入队的元素）。

2. **`top()` 的复用与恢复**  
   调用 `pop()` 拿到栈顶值后，必须 `push(ret)` 放回去——因为栈只是查看顶部，不删除。若不复原，栈状态就错了。

3. **边界处理**  
   循环终止条件是 `size != 1`，确保只剩最后一个元素时停止，此时 `front()` 就是待出栈元素。



**易错提醒**
- ⚠️ **`top()`必须放回去**：`pop()` 会删除元素，查看栈顶后需 `push(ret)` 恢复状态，否则栈顶丢失
- ⚠️ **循环次数是 `size-1`**：若写 `while(!empty())` 会死循环，必须计数到只剩1个
- ⚠️ **`size`要先存下来**：`internal.size()` 在循环中会变，必须提前存到 `bound`


---
## 代码实现
```cpp
class MyStack {
    queue<int> internal;  // 底层队列：利用FIFO特性模拟LIFO
    
public:
    MyStack() = default;
    
    // 时间复杂度: O(1)
    // 新元素直接入队，暂时不做任何处理
    void push(int x) { 
        internal.push(x); 
    }
    
    // 时间复杂度: O(n)
    // 核心逻辑：轮转队列，使最后一个元素（栈顶）浮到队首
    // 操作：将前 n-1 个元素依次出队再入队（赶到队尾），此时队首即为栈顶，直接弹出
    int pop() {
        int size = internal.size();           // 先记录当前元素个数
        while (size > 1) {                    // 只留下最后一个元素（栈顶）
            int temp = internal.front();      // 取出队首元素
            internal.pop();
            internal.push(temp);              // 塞回队尾，完成一次轮转
            --size;
        }
        int topVal = internal.front();        // 此时队首就是栈顶（最晚入队的元素）
        internal.pop();                       // 将其移除
        return topVal;
    }
    
    // 时间复杂度: O(n)
    // 逻辑：调用pop()获取栈顶值，但必须将其重新入队以恢复栈状态（栈顶查看不删除元素）
    // 注意：这是查看操作，不能真正删除栈顶，所以要push回去
    int top() {  
        int topVal = pop();                   // 临时弹出栈顶（此时栈少了一个元素）
        internal.push(topVal);                // 关键：立即放回去，保持栈状态不变
        return topVal;
    }
    
    // 时间复杂度: O(1)
    bool empty() { 
        return internal.empty(); 
    }
};
```
