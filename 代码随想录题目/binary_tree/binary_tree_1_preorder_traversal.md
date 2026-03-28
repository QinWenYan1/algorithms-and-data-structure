# 二叉树前序遍历 — preorder traversal  

- **题目（LeetCode 144）**： [🔗 题目](https://leetcode.cn/problems/binary-tree-preorder-traversal/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E9%80%92%E5%BD%92%E9%81%8D%E5%8E%86.html#%E6%80%9D%E8%B7%AF)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1Wh411S7xt/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）

**总体思路**
**递归DFS法**：利用函数调用栈隐式实现深度优先搜索，严格遵循"中 → 左 → 右"的访问顺序。

**关键点**
*   二叉树的3种DFS遍历顺序，所谓的序列都是以中间的节点为参考：
    1. 前序列：中，左，右
    2. 中序列：左，中，右
    3. 后序列：左，右，中

**易错提醒**
* 在写递归之前，想清楚这3点九不会错：
    1. 确定递归函数的**返回值**和**参数**
    2. 确定**终止条件**（递归基）
    3. 确定单个递归函数里的**逻辑**


---
## 代码实现

```cpp
class Solution {
public:
    void traverse(TreeNode *root, vector<int> &ret){
        if (root != nullptr) {//递归基
            ret.push_back(root->val); 
            traverse(root->left, ret);
            traverse(root->right, ret); 
        } 
    }

    vector<int> preorderTraversal(TreeNode* root) {

        //前置访问就是：中，左，右
        vector<int> result;
        traverse(root, result); 
        return result; 
        
    }
};
```