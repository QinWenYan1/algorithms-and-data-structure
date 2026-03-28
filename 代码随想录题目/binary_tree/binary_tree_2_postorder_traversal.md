# 二叉树后序遍历 — postorder traversal  

- **题目（LeetCode 145）**： [🔗 题目](https://leetcode.cn/problems/binary-tree-postorder-traversal/submissions/712884637/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E9%80%92%E5%BD%92%E9%81%8D%E5%8E%86.html#%E6%80%9D%E8%B7%AF)
  - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1Wh411S7xt/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）
笔记请移步[前序遍历](./binary_tree_1_preorder_traversal.md)查阅

---
## 代码实现

```cpp
class Solution {
    void traverse(TreeNode *root, vector<int> &ret){
        if(root != nullptr){
            traverse(root->left, ret);
            traverse(root->right, ret); 
            ret.push_back(root->val); 
        }
    }

public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result; 
        traverse(root, result); 
        return result; 
    }
};
```