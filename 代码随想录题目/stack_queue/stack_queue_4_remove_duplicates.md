# 删除字符串中相邻重复项 — remove duplicates 

- **题目（LeetCode 1047）**： [🔗 题目](https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/1047.%E5%88%A0%E9%99%A4%E5%AD%97%E7%AC%A6%E4%B8%B2%E4%B8%AD%E7%9A%84%E6%89%80%E6%9C%89%E7%9B%B8%E9%82%BB%E9%87%8D%E5%A4%8D%E9%A1%B9.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV12a411P7mw/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）


**核心思路**
**字符串模拟栈**：利用 `string` 本身支持 `push_back()` / `pop_back()` / `back()` 的特性，将其当作栈使用，省去 `stack` 容器最后转换字符串的步骤。

- **消消乐机制**：遍历字符时，若与"栈顶"（字符串尾部）相同则消除（`pop_back()`），不同则入栈（`push_back()`）
- **连锁反应**：由于实时消除，新的栈顶可能继续与下一个字符匹配，无需额外处理


**关键点**
1. **用 string 替代 stack**  
   `ret.back()` 对应 `stack.top()`，`ret.pop_back()` 对应 `stack.pop()`。最终直接返回 `ret`，避免从 `stack` 逐个弹出再构造字符串的开销。

2. **检查非空**  
   必须先判断 `!ret.empty()` 再访问 `ret.back()`，否则空字符串调用 `back()` 导致未定义行为。

3. **实时压缩**  
   例如 `"abbaca"` 的处理过程：`a`→`ab`→`a`（遇到第二个b，bb消除）→`ac`→`ca`（遇到a，与栈顶c不同）→ 最终 `ca`

**易错提醒**
- ⚠️ **空栈检查**：`if (!ret.empty() && ret.back() == e)` 短路求值，`&&` 左侧为假时不会访问 `back()`，安全
- ⚠️ **不要先用 stack 再转换**：虽然 `stack<char>` 逻辑相同，但最后需要额外循环弹出构造字符串，不如直接用 `string` 优雅
- ⚠️ **这是"相邻"重复**：只消除紧挨着的相同字符，不相邻的不消除（如 `"aba"` 中两个a不相邻，结果不变）

---

## 代码实现



```cpp
class Solution {
public:
    string removeDuplicates(string s) {
        string ret;  // 用 string 模拟栈：支持 push_back/pop_back/back，且可直接作为结果返回
        
        for (char e : s) {
            // 情况1：栈非空 且 栈顶字符与当前字符相同 → 发现相邻重复，消除（出栈）
            if (!ret.empty() && ret.back() == e) {
                ret.pop_back();  // 消除栈顶（即消除当前这对相邻重复）
            }
            // 情况2：栈为空 或 栈顶与当前不同 → 当前字符入栈，等待后续匹配
            else {
                ret.push_back(e);  // 压入栈顶（字符串尾部）
            }
        }
        
        return ret;  // 栈中剩余字符即为消除所有相邻重复后的结果
    }
};
```
