# 替换数字 — Replace number 

- **题目（卡码网 54）**： [🔗 题目](https://kamacoder.com/problempage.php?pid=1064)  
- **难度**：未知

- **解析 / 学习链接**：
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/kamacoder/0054.%E6%9B%BF%E6%8D%A2%E6%95%B0%E5%AD%97.html#%E6%80%9D%E8%B7%AF)
  
---
## 关键点（精简）


1. **先扩容再处理**：统计数字个数计算最终长度（原长+数字数×5），一次性`resize`到位，避免中间插入的数据搬移开销。

2. **从后向前双指针**：快指针读原串末尾，慢指针写新串末尾，反向填充避免覆盖未处理字符，实现原地O(1)空间修改。

3. **避坑`size_t`下溢**：循环索引用**有符号`int`**（或`ptrdiff_t`），防止无符号整型`0-1`回绕成`MAX`导致死循环和段错误。

---
## 代码实现

```cpp
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

int main() {

  //输入单词
  string word;
  cin >> word;

  //我们先扩充整个字符串到对应的大小
  int counter = word.size(), quickPtr = word.size()-1;

  for (const auto e : word)
    if ('0' <= e && e <= '9')
      counter += 5;
  word.resize(counter); //扩张为处理后的大小

  //现在开始双指针 + 从后往前进行处理
  int slowPtr = word.size()-1; 
  while ( 0 <= quickPtr ){
    if( '0' <= word[quickPtr] && word[quickPtr] <= '9' ){//遇到数字了
        word[slowPtr--] = 'r'; 
        word[slowPtr--] = 'e'; 
        word[slowPtr--] = 'b'; 
        word[slowPtr--] = 'm'; 
        word[slowPtr--] = 'u';
        word[slowPtr--] = 'n';  
    }else{
        word[slowPtr--] = word[quickPtr]; 
    }
    -- quickPtr;
  }
  cout << word << endl; 
}
```
