# 逆波兰表达式求值 — eval RPN  

- **题目（LeetCode 1047）**： [🔗 题目](https://leetcode.cn/problems/evaluate-reverse-polish-notation/)  
- **难度**：中等
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0150.%E9%80%86%E6%B3%A2%E5%85%B0%E8%A1%A8%E8%BE%BE%E5%BC%8F%E6%B1%82%E5%80%BC.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1kd4y1o7on/)

---
## 关键点

**栈缓存计算法**：利用栈的LIFO特性暂存操作数，遇到运算符时弹出**右操作数**（栈顶）与**左操作数**（新栈顶）进行计算。

- **就地修改的优势**：`parser.top() += rhs` 直接修改左操作数而非弹出后重新压入，省去一次栈操作，空间局部性更好


1. **右操作数先出机制**
   - **LIFO顺序**：先 `parser.top()` 再 `pop()` 得到的是**右**操作数（后入），此时新栈顶是**左**操作数
   - **代码体现**：`rhs = parser.top(); parser.pop(); parser.top() -= rhs;` 确保左减右

2. **就地修改技巧**
   - **机制**：不弹出左操作数，直接通过引用修改栈顶值
   - **对比**：标准写法需 `pop()`两次再 `push(result)`，本方法节省1次栈操作和内存写入
   - **适用场景**：加减乘除都满足 `lhs = lhs op rhs` 的赋值语义



**易错提醒**

- ⚠️ **减除顺序颠倒**：`parser.top()`是左操作数，`rhs`是右操作数。若混淆 `a-b` 与 `b-a`，测试用例 `["4","13","5","/","+"]`（预期6）会得到14
- ⚠️ **空栈取top()**：虽然题目保证输入有效，但若token以运算符开头（如`["+","1","2"]`），`parser.top()`调用时栈空导致**运行时错误（RE）**
- ⚠️ **stoi异常**：若数字字符串超出int范围（如`"2147483648"`），`stoi`抛出异常。本题约束在32位范围内，可忽略


---

## 代码实现

```cpp
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> parser;  // 阶段1: 初始化操作数栈
        int rhs = 0;        // 右操作数（Right Hand Side）
        
        // 阶段2: 遍历处理每个token
        for (const string &e : tokens) {
            // 意图: 识别数字（含负数）。负数如"-11"长度>1，单字符'-'是运算符
            if (e.size() > 1 || isdigit(e[0])) { 
                parser.push(stoi(e));  // 数字压栈，等待计算
                continue; 
            } 

            // 阶段3: 处理运算符
            rhs = parser.top(); 
            parser.pop();  // ⚠️ 先出的是右操作数（后入先出）
            
            // 意图: 就地修改左操作数（新栈顶），节省栈操作
            // 关键: parser.top()是左操作数，rhs是右操作数，顺序不能反
            if (e == "+") { 
                parser.top() += rhs;  // 左 = 左 + 右
            } else if (e == "*") {
                parser.top() *= rhs;  // 左 = 左 * 右
            } else if (e == "-") {
                parser.top() -= rhs;  // 左 = 左 - 右 ⚠️ 顺序关键
            } else {  // 除法
                parser.top() /= rhs;  // 左 = 左 / 右 ⚠️ 整数向零取整
            }
        }

        // 阶段4: 栈顶即为最终结果（题目保证输入有效，栈非空）
        return parser.top(); 
    }
};
```