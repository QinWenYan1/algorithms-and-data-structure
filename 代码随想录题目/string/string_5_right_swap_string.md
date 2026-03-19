# 右旋字符串 — right swap string

- **题目（卡码网 55）**： [🔗 题目](https://kamacoder.com/problempage.php?pid=1065)  
- **难度**：未知

- **解析 / 学习链接**：
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/kamacoder/0055.%E5%8F%B3%E6%97%8B%E5%AD%97%E7%AC%A6%E4%B8%B2.html)
  
---
## 关键点（精简）

**挑战一下**： 是否能在时间复杂度O(n)，空间复杂度为O(1)的情况下完成？

**核心思路：三次反转法**  
整体反转 → 前k个反转 → 后n-k个反转，通过局部有序实现整体右旋。

**原理速记（示例：abcdefg 右旋2位）**
```
原串:          a b c d e f g
①整体反转:     g f e d c b a  (全部逆序)
②前k个反转:    f g e d c b a  (前2位恢复顺序)
③后n-k个反转:  f g a b c d e  (后5位恢复顺序)
结果: fgabcde ✓
```

**代码对应**
- `reverse(s.begin(), s.end())` —— 步骤①
- `reverse(s.begin(), s.begin()+len)` —— 步骤②（前len个）
- `reverse(s.begin()+len, s.end())` —— 步骤③（剩余部分）

**易错点**
- **左闭右开**：STL的 `reverse(first, last)` 不包含last，正好符合 `[begin, begin+len)` 的切分



---
## 代码实现

```cpp
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    int k;
    string s;
    cin >> k >> s;
    
    // 注意：实际做题时建议加上 k %= s.size() 防止 k > s.length() 导致越界
    
    // 三次反转法实现右旋（以 "abcdefg" 右旋2位为例）：
    
    reverse(s.begin(), s.end());           // 1. 整体反转: "gfedcba"
    reverse(s.begin(), s.begin() + k);     // 2. 反转前k个: "fgedcba" (右旋部分有序)
    reverse(s.begin() + k, s.end());       // 3. 反转剩余部分: "fgabcde" (剩余部分有序)
    
    cout << s << endl;
    return 0;
}
```