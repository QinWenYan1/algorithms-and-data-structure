# 比较含退格的字符串 — backspace compare

- **题目（LeetCode 844）**： [🔗 题目](https://leetcode.cn/problems/backspace-string-compare/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析 （御三五）](https://leetcode.cn/problems/backspace-string-compare/) 


---

## 关键点（精简）

* 本人的思路依旧是：
    * 使用双指针将输入转换为新字符串
    * `quickPtr`遍历输入
    * `slowPtr`指向的是新字符应该插入的位置
    * 最后`slowPtr`慢指针指向本新字符串的尾后位置
    * 最后再通过比较两个新的字符串确认
* 这里有逆序遍历+双指针的[另一种思路](https://leetcode.cn/problems/backspace-string-compare/)，可以阅读一下
* 两种方法仔时间复杂度上没有区别



---
## 代码实现

```cpp
class Solution {
public:
    bool backspaceCompare(string s, string t) {

        unsigned tails = 0, tailt = 0; 
        string outcomeS = transform(s, tails);
        string outcomeT = transform(t, tailt);
        return compare(outcomeS, tails, outcomeT, tailt);  
        
    }

private:

    string &transform(string &original, unsigned &slowPtr){

        //双指针思路, 慢指针指向实际应该插入的地方， 快指针指向遍历位置
        for (unsigned quickPtr = 0; quickPtr != original.size(); ++quickPtr){

            if (original[quickPtr] == '#'){ //退格
                if ( slowPtr != 0 ) --slowPtr; 
            }else{
                //记入到新的字符串中
                original[slowPtr] = original[quickPtr];
                ++slowPtr;
            }

        }

        return original; //slowPtr是尾后位置

    }

    bool compare(string &s, unsigned indexs, string &t, unsigned &indext){

        if (indexs != indext) return false; 
        for (unsigned i = 0; i != indext; ++i){
            if(s[i] != t[i]) return false; 
        }

        return true; 

    }

};
```
