# 最小子串 — min window 

- **题目（LeetCode 904）**： [🔗 题目](https://leetcode.cn/problems/minimum-window-substring/description/)  
- **难度**：困难
- **解析 / 学习链接**：  
  - [🧠 文字解析 灵茶山艾府](https://leetcode.cn/problems/minimum-window-substring/solutions/2713911/liang-chong-fang-fa-cong-o52mn-dao-omnfu-3ezz) 
  - [🧠 文字解析 力扣官方](https://leetcode.cn/problems/minimum-window-substring/solutions/257359/zui-xiao-fu-gai-zi-chuan-by-leetcode-solution)


---

## 关键点（精简）

* 这道题本质上和[水果成篮](./arr_vec_15_total_fruit.md)的做法完全一致：
  * 先通过挪动右边的index来发现符合条件的`string`
  * 然后通过挪动左边的index来确定在满足情况的状态下，发现最小长度的`string`
  * 然后记录现在能得到的最小的长度
  * 然后开始寻找下一个符合条件的`string`
* 这道题主要难点是代码实现上有一些复杂：
  1. 判断是否符合条件的方式是通过两个`unordered_map`来相互比较实现
  2. 每一次挪动左边的index， 我们都需要去更新`len`, 以及现有最小的左边`index`

* **代码优化**：
  * 这道题的优化点就是， 每一次我们判断当前string是否依然覆盖的时候， 需要去对两个`unordered_map`遍历
  * 我们可以使用两个变量去记录现在有多少个字符被覆盖或者未覆盖来判断实现相同目的
  * 不过不管优不优化，两者总题复杂度都为O(n)


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

---
## 代码实现(优化版)


```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        // 特殊情况处理
        if(t.size() > s.size() || s.empty() || t.empty()) return "";
        
        // 使用局部变量，避免成员变量被多个测试用例共享
        unordered_map<char, int> tTable, sTable;
        int left = 0, right = 0;
        int minLen = INT_MAX, minLeft = 0;
        int required = 0; // 记录需要满足的字符种类数
        int formed = 0;   // 记录当前已满足的字符种类数
        
        // 建立t的哈希表
        for(const auto &c : t) tTable[c]++;
        required = tTable.size();
        
        while(right < s.size()) {
            char c = s[right];
            
            // 扩大窗口
            sTable[c]++;
            
            // 如果当前字符在t中，且数量刚好达到要求
            if(tTable.count(c) && sTable[c] == tTable[c]) {
                formed++;
            }
            
            // 当窗口满足条件时，尝试收缩窗口
            while(left <= right && formed == required) {
                char leftChar = s[left];
                
                // 更新最小窗口
                if(right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minLeft = left;
                }
                
                // 收缩窗口
                sTable[leftChar]--;
                if(tTable.count(leftChar) && sTable[leftChar] < tTable[leftChar]) {
                    formed--;
                }
                left++;
            }
            
            right++;
        }
        
        return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
    }
};
```
