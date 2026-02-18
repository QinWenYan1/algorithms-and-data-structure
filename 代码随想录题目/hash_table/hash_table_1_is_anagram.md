# 有效的字母异位词 — Is Anagram

- **题目（LeetCode 242）**： [🔗 题目](https://leetcode.cn/problems/valid-anagram/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0242.%E6%9C%89%E6%95%88%E7%9A%84%E5%AD%97%E6%AF%8D%E5%BC%82%E4%BD%8D%E8%AF%8D.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)  
  - [🎥 视频讲解（代码随想录）](bilibili.com/video/BV1YG411p7BA/)

---
## 关键点（精简）

**方法一**

* **使用哈希表分别对字符串s做字符计数递增、t做递减，最后检查所有计数是否归零来判断是否为异位词。**
* 这样时间复杂度和空间复杂度都为O(N)

**方法二(优化)**

* 用数组替代哈希表，利用题目限定（小写字母）将空间复杂度从O(N)降到O(1)，同时获得更好的缓存局部性。

* **利用字符'a'到'z'的ASCII码连续的特性，通过 `s[i] - 'a'` 计算相对偏移量，将字符直接映射为数组下标（0-25）进行计数，无需关心具体ASCII值。**



---
## 代码实现

**方法一**
```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        //我们建立一个unordered map的来记录s出现的char
        //然后在遍历t的时候再一个一个消去知道最后如果所有key对应的value都为0那就是anagram 
        unordered_map<char, int> lookup; 
        for (const auto e : s) ++ lookup[e]; 
        for (const auto e : t) -- lookup[e]; 

        //检查阶段
        for (const auto e : lookup){
            if (e.second != 0 ) return false; 
        }
        return true; 
        
    }
};
```

**方法二**
```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        //我们建立一个array的来记录s出现的char
        //然后在遍历t的时候再一个一个消去知道最后如果所有array的元素都为0了说明是anagram
        array<int, 26> lookup{}; 
        //通过偏移量来计算映射
        for (const auto e : s) ++ lookup[e -'a']; 
        for (const auto e : t) -- lookup[e - 'a']; 

        //检查阶段
        for (const auto e : lookup){
            if (e != 0 ) return false; 
        }
        return true; 
        
    }
};
```
