# 二叉树中序遍历 — inorder traversal  

- **题目（LeetCode 94）**： [🔗 题目](https://leetcode.cn/problems/binary-tree-inorder-traversal/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
   - DFS递归法：
        * [🧠 文字解析（代码随想录）- 递归法](https://programmercarl.com/%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E9%80%92%E5%BD%92%E9%81%8D%E5%8E%86.html#%E6%80%9D%E8%B7%AF)
        * [🎥 视频讲解（代码随想录）- 递归法 ](https://www.bilibili.com/video/BV1Wh411S7xt/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

    - DFS迭代法：
        * [🧠 文字解析（代码随想录）- 迭代法](https://programmercarl.com/%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E8%BF%AD%E4%BB%A3%E9%81%8D%E5%8E%86.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
        * [🎥 视频讲解（代码随想录）- 迭代法](https://www.bilibili.com/video/BV1Zf4y1a77g?vd_source=7923b10dbf11c28879c337d8e0bfa8de&spm_id_from=333.788.videopod.sections)

---
## 关键点（精简）
**DFS递归**
笔记请移步[前序遍历](./binary_tree_1_preorder_traversal.md)查阅

**DFS遍历**

---
## 代码实现

```cpp
class Solution {
public:
    void traverse(TreeNode *root, vector<int> &ret){
        if(root != nullptr){
            traverse(root->left, ret); 
            ret.push_back(root->val); 
            traverse(root->right, ret); 
        }
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result; 
        traverse(root, result); 
        return result; 
    }   
};
```