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
**指针追踪+栈回溯法**：利用显式栈保存"待回溯"的父节点链，`curr` 指针负责线性下探到最左端。核心逻辑是"能左就左，到底就弹，弹完往右"。

- **为什么需要栈？** 中序遍历要先处理左子树再处理根，当走到最左端时，必须通过栈回溯找到父节点（根），否则无法向上返回
- **双轨机制**：`curr` 负责向下探索（左），`stack` 负责向上回溯（根），`curr->right` 负责横向转移（右）

**关键点**
1. **循环条件双保险**  
   `curr != nullptr || !s.empty()` 必须同时判断指针和栈：
   - **场景**：单支树（如只有左链），`curr` 会走到头变 `null`，但栈中还有未处理的父节点
   - **后果**：若只用 `!s.empty()`，左链走完后直接退出，漏掉栈中节点；若只用 `curr!=nullptr`，根节点入栈后无法进入循环体

2. **向左深入阶段（模拟递归进入）**  
   - **机制**：`if(curr!=nullptr)` 分支内持续 `s.push(curr)` 并 `curr=curr->left`
   - **代码意图**：模拟递归函数不断深入左子树的过程，沿途保存所有经过的节点（这些节点都还有"根-右"未处理）
   - **终止条件**：`curr` 变为 `null`，表示当前子树左边界已到底

3. **弹栈回溯阶段（模拟递归返回）**  
   - **机制**：`else` 分支内 `curr=s.top()` 弹出栈顶，记录值，然后 `curr=curr->right`
   - **为什么弹栈是访问根？** 栈顶保存的是当前最深层未处理子树的根节点，其左子树已在上一阶段处理完毕（或为空）
   - **转向右子树**：访问完根后，将 `curr` 指向右子树，开启下一轮"向左深入"（若右子树为空，会立即进入弹栈阶段回溯到上层）

4. **curr 的状态流转**  
   - **下探**：`curr = curr->left`（非空时）
   - **回溯**：`curr = s.top()`（空时）
   - **横跳**：`curr = curr->right`（访问后）



**易错提醒**
- ⚠️ **循环条件必须用 \|\|**：写成 `&&` 会导致 `curr` 走到底变 `null` 时直接退出，栈中节点全部漏掉；写成单一条件会在初始 `root=null` 时死循环或漏处理
- ⚠️ **压栈与左移顺序**：必须先 `s.push(curr)` 再 `curr=curr->left`，顺序反了会导致栈顶存的是左孩子，回溯时丢失父节点引用，结果完全错误
- ⚠️ **访问后必须转右**：`else` 分支内 `curr=curr->right` 若漏写或写成 `curr=null`，会导致死循环（永远处理同一个节点）或右子树丢失

**记忆口诀**
*curr向左一路压，到头弹出访问它；转右再来重复走，左根右序自然成。*


---
## 代码实现
**DFS递归**
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

**DFS遍历**
```cpp
class Solution {
public:
    
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret; 
        stack<TreeNode*> s; 
        TreeNode *curr=root; 

        //遍历顺序: 左中右
        while(curr!=nullptr || !s.empty()){
            if(curr!=nullptr){
                s.push(curr);
                curr = curr->left; //左
            }else {
                curr = s.top(); 
                s.pop(); 
                ret.push_back(curr->val); //中
                curr = curr->right;  //右
            }
        }
        return ret; 
     
    }   
};
```