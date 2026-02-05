# 最小子串 — min window 

- **题目（LeetCode 904）**： [🔗 题目](https://leetcode.cn/problems/minimum-window-substring/description/)  
- **难度**：困难
- **解析 / 学习链接**：  
  - [🧠 文字解析 灵茶山艾府](https://leetcode.cn/problems/fruit-into-baskets/solutions/3042744/hua-dong-chuang-kou-ha-xi-biao-pythonjav-uzmw/) 


---

## 关键点（精简）

* 这道题本质上和[水果成篮](./arr_vec_15_total_fruit.md)d的做法完全一致
  * 先通过挪动右边的index来发现符合条件的`string`
  * 然后通过挪动左边的index来确定在满足情况的状态下，发现最小长度的`string`
  * 然后记录现在能得到的最小的长度
  * 然后开始寻找下一个符合条件的`string`
* 这道题主要难点是代码实现上有一些复杂
  1. 判断是否符合条件的方式是通过两个`unordered_map`来相互比较实现
  2. 每一次挪动左边的index， 我们都需要去更新`len`, 以及现有最小的左边`index`







---
## 代码实现

```cpp
class Solution {

    unsigned len = INT_MAX, currLeft = 0, currRight = 0 ; //记录长度， 和药输出的的substring的位置的index 
    unsigned left = 0, right = 0; //每一轮滑动窗口使用的index遍历，尝试寻找该轮出现过符合目标的的最短substirng


    unordered_map<char, unsigned> sTable, tTable; 

    bool isCovered(){ //用来检查我们现在遍历的substring是否已经全部覆盖t了

        for (const auto &e : tTable){
            if(sTable.find(e.first) != sTable.end() && sTable.find(e.first)->second >= e.second) continue; 
            else return false; 
        }

        return true; 
    }

   void updateLen(unsigned &len, unsigned &left, unsigned &right){

        if (len > right - left + 1){//当这种情况出现的时候，我们才更新指针和长度记录

            len = right - left + 1; 
            currLeft = left - 1; 
            currRight = right; 

        }

    }

public:
    string minWindow(string s, string t) {

        //特殊情况处理: 一种是空， 一种是t比s还长
        if(t.size() > s.size() || s.empty() || t.empty()) return "";


        //先建立t的单词频率查询表
        for (const auto &e : t) ++ tTable[e]; 

        //开始正式遍历
        size_t end = s.size(); 

        while (right != end){

            ++sTable[s[right++]]; //依次将单词加入到s的单词频率查询表格当中

            while(isCovered() && left != right ){ //如果已经全部遍历， 那么就收缩left来寻找这个最小的复合条件的substring
                
                --sTable[s[left++]]; //通过left来删除查询表中的单词频率
                updateLen(len, left, right); //更新长度

            }

            //这个时候刚刚退出，那么我们得到的是这一轮遍历得到的最小的长度的substring, 并且已经更新完了

        }

        return (len == INT_MAX)? "" : s.substr(currLeft, len); 

    }

};
```
