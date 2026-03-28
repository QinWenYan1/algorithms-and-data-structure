# 二叉树前序遍历 — preorder traversal  

- **题目（LeetCode 144）**： [🔗 题目](https://leetcode.cn/problems/binary-tree-preorder-traversal/description/)  
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

**DFS递归法**：
<details> <summary>点击展开</summary>
利用函数调用栈隐式实现深度优先搜索，严格遵循"中 → 左 → 右"的访问顺序。

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

</details>

---

**DFS迭代法**：
<details> <summary>点击展开</summary>
利用栈的 LIFO 特性手动维护遍历状态，将递归的隐式函数调用栈转为显式数据结构。
核心策略是倒序入栈——前序要"中左右"，入栈则按"右左"压入，保证弹出顺序符合预期。后序列就要“左右”压入。

* **为什么先压右？** 栈是后进先出，若要先访问左子树，必须先把右子树压在栈底，左子树压在栈顶

* **为什么不用判空入栈？** 代码中在压入前加了 `if(curr->right)` 判断，避免 `null` 指针入栈减少无效操作；也可弹出后统一判空，但会浪费栈空间

**关键点**
1. **倒序入栈（右先于左）**
   - **机制**：前序遍历顺序为"根-左-右"，栈的弹出顺序与压入顺序相反
   - **反例**：若先压 `left` 后压 `right`，弹出顺序变为"根-右-左"，结果完全错误
   - **代码对应**：`s.push(curr->right)` 必须严格在 `s.push(curr->left)` 之前

2. **弹出即访问**
   - **机制**：栈顶节点弹出后立即记录值，保证"根"在最前被处理
   - **场景**：每次循环 `curr = s.top()` 后立刻 `ret.push_back`，确保当前子树的根先于其子节点被访问

3. **子节点判空优化**
   - **机制**：压入前检查 `if(curr->right)` 而非无条件压入
   - **优势**：避免栈中堆积大量 nullptr，减少无效 pop 操作；若先压入再弹出判空，栈空间会被撑大
   - **代码对应**：两个 `if` 条件确保只有有效节点入栈

4. **栈初始化启动**
   - **机制**：先压入根节点，让 `while(!s.empty())` 进入循环
   - **边界处理**：即使 `root` 为 `nullptr`，压入后弹出时 `if(curr)` 会跳过，正确返回空数组

**易错提醒**
- ⚠️ **压栈顺序颠倒**：先压 `left` 后压 `right` 会导致遍历顺序变成"根-右-左"，输出完全错误（如 `1,null,2` 的树会输出 `[1,2]` 变成正确是巧合，但 `[1,2,3]` 的树会变成 `[1,3,2]`）
- ⚠️ **忘记判空入栈**：若直接 `s.push(curr->right)` 而不检查空，栈中会堆积 nullptr，虽然 `if(curr)` 能过滤，但增加 O(n) 次无效出栈操作，极端情况栈空间浪费一倍
- ⚠️ **循环内漏判空**：若删除 `if(curr)`，当栈顶为 nullptr 时 `curr->val` 会触发空指针解引用，直接 RE

</details>


---
## 代码实现

**DFS递归法**
<details><summary>点击展开</summary>

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
</details>

---

**DFS迭代法**
<details><summary>点击展开</summary>

```cpp
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {

        //初始化
        stack<TreeNode*> s; 
        vector<int> ret; 
        s.push(root); 

        //开始遍历：前序入栈处理顺序 - 右左中
        while (!s.empty()){
            TreeNode *curr = s.top(); 
            s.pop(); 
            if(curr) {
                ret.push_back(curr->val); 
                if(curr->right) s.push(curr->right); 
                if(curr->left) s.push(curr->left); 
            }

        }
        return ret; 
    }
};
```

</details>