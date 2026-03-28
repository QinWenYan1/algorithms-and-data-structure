# 二叉树后序遍历 — postorder traversal  

- **题目（LeetCode 145）**： [🔗 题目](https://leetcode.cn/problems/binary-tree-postorder-traversal/submissions/712884637/)  
- **难度**：简单
- **解析 / 学习链接**： 
    * DFS递归法：
        - [🧠 文字解析（代码随想录）- 递归法](https://programmercarl.com/%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E9%80%92%E5%BD%92%E9%81%8D%E5%8E%86.html#%E6%80%9D%E8%B7%AF)
        - [🎥 视频讲解（代码随想录）- 递归法 ](https://www.bilibili.com/video/BV1Wh411S7xt/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)
    * DFS迭代法：
        - [🧠 文字解析（代码随想录）- 迭代法](https://programmercarl.com/%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E8%BF%AD%E4%BB%A3%E9%81%8D%E5%8E%86.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
        - [🎥 视频讲解（代码随想录）- 迭代法](https://www.bilibili.com/video/BV15f4y1W7i2?vd_source=7923b10dbf11c28879c337d8e0bfa8de&spm_id_from=333.788.videopod.sections)

---
## 关键点（精简）

**DFS迭代法**
笔记请移步[前序遍历](./binary_tree_1_preorder_traversal.md)查阅

**DFS遍历法**

**逆序模拟法（根右左 → 反转得后序）**：利用栈实现"根-右-左"的遍历（前序遍历的镜像变体），最后将结果数组反转，即得"左-右-根"的后序序列。

- **为什么不直接写后序？** 后序遍历非递归实现需要标记节点访问状态（区分第一次遇到还是第二次遇到），代码复杂；而"根右左"与前序类似，只需调换压栈顺序即可实现，最后 O(n) 反转即可得到后序
- **双栈思维**：第一个栈负责产生"根右左"序列，结果数组的 `reverse` 操作等效于第二个栈的倒序输出

**关键点**
1. **入栈顺序"左先于右"**
   - **机制**：栈是 LIFO，要得到"根右左"的弹出顺序，必须**先压左子树，再压右子树**
   - **反例**：若先压 `right` 后压 `left`，会得到"根左右"（前序），反转后变成"右左根"，完全错误
   - **代码对应**：`s.push(temp->left)` 必须严格在 `s.push(temp->right)` 之前

2. **反转是关键步骤**
   - **机制**：栈产生的是"根右左"（Root-Right-Left），反转后变为"左右根"（Left-Right-Root）即后序
   - **后果**：若忘记 `reverse`，输出的是"根右左"（类似逆前序），检查点会 WA
   - **代码对应**：`reverse(ret.begin(), ret.end())` 必须在 return 前执行

3. **弹出后统一判空**
   - **机制**：`if(temp)` 在 `pop()` 之后，过滤掉栈中可能存在的 `nullptr`（虽然此代码逻辑下 `root` 为空时只压入一次 `nullptr`，但统一判空更安全）
   - **场景**：输入空树 `root=nullptr` 时，栈初始压入 `nullptr`，弹出后 `if(temp)` 跳过，返回空数组，正确

4. **时间复杂度隐藏项**
   - **反转开销**：`reverse` 操作是 O(n)，整体时间复杂度仍是 O(n)，但常数因子比递归版略大



**易错提醒**
- ⚠️ **入栈顺序颠倒**：先压 `right` 后压 `left` 会导致遍历序列变成"根左右"，反转后得到"右左根"，与中序/后序都不匹配，完全 WA
- ⚠️ **忘记 `reverse`**：`reverse` 一行若遗漏，返回的是"根右左"序列，后序遍历检查点全错
- ⚠️ **判空时机错位**：若在 `pop()` 前判空（如 `while(!s.empty() && s.top())`），会导致非空节点无法处理；此代码 `pop()` 后判空是正确的，但需注意 `temp` 为 `nullptr` 时不能解引用

**记忆口诀**
*后序非递归难写，根右左序来替代；先压左孩再压右， reverse 一下得正解。*



---
## 代码实现
**DFS递归法**
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

**DFS迭代法**

```cpp
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret; 
        stack<TreeNode *> s; 
        s.push(root); 

        //开始迭代 - 按照右左压入
        while (!s.empty()){
            TreeNode * temp = s.top();  
            s.pop(); 
            if(temp){ //root不是nullptr
                ret.push_back(temp->val); 
                if(temp->left) s.push(temp->left); 
                if(temp->right) s.push(temp->right);
            }    
        }
        reverse(ret.begin(), ret.end());
        return ret; 
    }
};
```