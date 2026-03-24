# 有效的括号 — is valid

- **题目（LeetCode 20）**： [🔗 题目](https://leetcode.cn/problems/valid-parentheses/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0020.%E6%9C%89%E6%95%88%E7%9A%84%E6%8B%AC%E5%8F%B7.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1AF411w78g/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）


**核心思路**
**栈匹配法**：利用栈的 LIFO 特性处理嵌套结构。遇到左括号时压入**对应的右括号**（而非左括号本身），遇到右括号时直接与栈顶比对。

- **为什么压右括号？** 这样遇到右括号时直接 `e == parser.top()` 比较即可，无需额外映射表
- **匹配逻辑**：左括号入栈"期待"对应的右括号，右括号出现时必须立即匹配栈顶

---

**关键点**
1. **对于输入字符串，三种不匹配情况**
   - **栈空遇右括号**：`parser.empty()` 时遇到右括号 → 右括号多余（如 `"())"`）
   - **栈顶不匹配**：`e != parser.top()` → 交叉嵌套错误（如 `"(])"`）
   - **遍历完栈非空**：`!parser.empty()` → 左括号多余（如 `"((()"`）

2. **提前压入对应右括号**  
   看到 `'('` 压入 `')'`，这样后续遇到 `')'` 直接比较相等即可，代码更简洁。

3. **返回值判定**  
   必须 `return parser.empty()`，仅遍历完还不够，需确保所有左括号都被匹配。



**易错提醒**
- ⚠️ **压入的是右括号**：若压入左括号，后续比较时需要映射关系（如 `'('` 对应 `')'`），增加复杂度
- ⚠️ **空栈检查顺序**：必须先判 `parser.empty()` 再判 `parser.top()`，否则空栈调用 `top()` 未定义行为（UB）
- ⚠️ **最后判空**：`return parser.empty()` 不能漏，否则 `"("` 会误返回 true





---
## 代码实现

```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> parser;  // 匹配栈：存储"期待出现的右括号"
        
        for (char e : s) {
            // 遇到左括号：压入对应的右括号（提前表示"期待这个右括号出现"）
            if (e == '(') parser.push(')'); 
            else if (e == '{') parser.push('}');
            else if (e == '[') parser.push(']'); 
            
            // 遇到右括号：必须立即匹配，否则非法
            else {
                // 情况1：栈空但还有右括号 → 右括号多余（如 "())"）
                if (parser.empty()) return false;
                
                // 情况2：栈顶与当前右括号不匹配 → 交叉错误（如 "(]"）
                if (e != parser.top()) return false;
                
                // 匹配成功：弹出已满足的期待
                parser.pop();
            }
        }
        
        // 情况3：遍历完但栈非空 → 左括号多余（如 "((()"）
        // 只有所有期待都被满足（栈空），才是合法字符串
        return parser.empty(); 
    }
};
```
