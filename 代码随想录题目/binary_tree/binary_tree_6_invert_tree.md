# 翻转二叉树 — invert tree

- **题目（LeetCode 226）**： [🔗 题目](https://leetcode.cn/problems/invert-binary-tree/description/)  
- **难度**：简单
- **解析 / 学习链接**： 
   
    - [🧠 文字解析（代码随想录）](https://programmercarl.com/0226.%E7%BF%BB%E8%BD%AC%E4%BA%8C%E5%8F%89%E6%A0%91.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
    - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1sP4y1f7q7/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）

**核心思路**
- **显式栈迭代法**：思路和 [前序遍历](binary_tree_1_preorder_traversal.md)，[后序遍历](./binary_tree_2_postorder_traversal.md) 完全一样，只是前者们都是打印操作处理，这道题就是 `swap` 处理
    - **翻转逻辑**：
        - 本题推荐前序和后序遍历的方式，中序遍历的方式可以，但是更复杂并且反直觉不推荐
        - 比如left root right 换边后 right root left, 你如果是先处理left, 处理 root，再处理 right的话，那么left会被处理两边

**步骤**
1. **初始根节点判空**
    - **机制解释**：入栈前检查 `root` 是否存在。
    - **场景/反例**：输入为空树 `[]` 时，若直接压栈会导致后续 `temp->left` 解引用空指针。
    - **代码对应**：`if (root) s.push(root);`

2. **子节点入栈判空**
    - **机制解释**：交换左右子树后，仅将非空的左右节点压入栈中。
    - **场景/反例**：叶子节点此时左右均为 `nullptr`，若不判空直接 `s.push`，下一轮循环 `top()` 取出必触发空指针解引用。
    - **代码对应**：`if (temp->left) s.push(temp->left);`

3. **临时变量交换**
    - **机制解释**：双指针值的互换。
    - **代码对应**：`swap(temp->left, temp->right);`

**复杂度分析**
| 指标 | 复杂度 | 说明 |
|------|--------|------|
| 时间 | **O(n)** | 每个节点只被访问且入栈、出栈一次 |
| 空间 | **O(n)** | 最坏情况（树退化为链表），栈需存储所有 n 个节点 |


**记忆口诀**：*根先入栈判空树，弹栈出顶换左右；非空子树皆压栈，迭代到底即翻转。*

---
## 代码实现
```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        stack<TreeNode*> s; 
        
        // 阶段1: 初始状态处理
        // ⚠️ 必须判空，否则空树压入nullptr导致后续解引用UB
        if (root) s.push(root); 
        
        // 阶段2: 迭代翻转
        while (!s.empty()) {
            auto temp = s.top(); 
            s.pop(); 

            // 意图: 交换当前节点的左右子树指针
            swap(temp->left, temp->right)

            // 阶段3: 将非空子节点压栈，等待后续处理
            // ⚠️ 必须判空，防止空指针入栈导致下轮循环RE
            if (temp->left) s.push(temp->left); 
            if (temp->right) s.push(temp->right); 
        }

        return root; 
    }
};
```
