# 对称二叉树 — is symmetric

- **题目（LeetCode 101）**： [🔗 题目](https://leetcode.cn/problems/symmetric-tree/description/)  
- **难度**：简单
- **解析 / 学习链接**： 
   
    - [🧠 文字解析（代码随想录）](https://programmercarl.com/0101.%E5%AF%B9%E7%A7%B0%E4%BA%8C%E5%8F%89%E6%A0%91.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
    - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1ue4y1Y7Mf/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）

**核心思路--递归**
- **递归镜像比较**：将单棵树的对称性问题转化为"两棵树是否互为镜像"的子问题。把根节点的左子树和右子树拆成独立的两棵树 $p$ 和 $q$，递归判断它们是否镜像相等。

    - **为什么拆成两棵子树？** 单棵树的对称性无法直接自递归定义，但"两棵树互为镜像"可以：根值相等，且 $p$ 的左子树与 $q$ 的右子树镜像、$p$ 的右子树与 $q$ 的左子树镜像（本题是交叉对应）


1. **镜像的递归定义**
   - 两棵树互为镜像必须同时满足：
     - 根值相等：`p->val == q->val`
     - 交叉递归：`isSameTree(p->left, q->right)`（左对右）
     - 交叉递归：`isSameTree(p->right, q->left)`（右对左）
   - 任一条件失败即非镜像

2. **空指针的合并判断**（递归基）
   - `if (p == nullptr || q == nullptr) return p == q;`
   - 这一行同时处理两种情况：都空时 `p == q` 为 true（返回 true）；一空一非空时 `p == q` 为 false（返回 false）
   - 换句话说：左右都为 `nullptr` 的时候，才返回 `true`, 否则一定不对称
   - 避免冗余分支，代码更简洁

3. **入口与递归分离**
   - `isSymmetric` 仅做一件事：将根拆成左右子树传入比较
   - `isSameTree` 负责真正的镜像递归逻辑，职责单一

- ⚠️ **递归参数顺序写反**：若写成 `isSameTree(p->left, q->left)` 会变成判断"相同树"（100 题逻辑），导致 WA
- ⚠️ **空指针解引用**：必须先判空再访问 `p->val`，否则 `nullptr` 解引用产生未定义行为（UB）
- ⚠️ **根节点为空**：`root` 为空时 `root->left` 不会执行（因为 `isSymmetric` 里直接调用，但空 root 在 LeetCode 通常单独处理，实际代码中若 root 为空会访问 `left` 导致 UB——需确保调用前 root 非空或加判空）

**复杂度分析**
| 指标 | 复杂度 | 说明 |
|------|--------|------|
| 时间 | **O(n)** | 每个节点只访问一次，每次比较 O(1) |
| 空间 | **O(h)** | 递归栈深度等于树高 h；最坏链状树 h=n，平衡树 h=log n |



**记忆口诀**：*根等左右交叉比，空树相等返回真；递归镜像非相同，参数顺序莫弄混。*

**核心思路--迭代**
- **镜像队列比较法**：利用队列的 FIFO 特性，每次同时取出**两个对称位置**的节点进行比对。将树按"镜像对"拆分成对入队，确保每一对出队节点都应在轴对称位置上。
    - **为什么成对入队？** 普通 BFS 按层遍历无法直接判断对称性，而将 `i` 的左子与 `j` 的右子、`i` 的右子与 `j` 的左子绑定入队，天然保证了后续取出的节点互为镜像位置
    - **为什么用迭代而非递归？** 避免了函数调用栈开销，且队列显式控制遍历顺序，更直观体现"镜像配对"思想


1. **入队顺序是核心**  
   - `i->left` 与 `j->right` 配对，`i->right` 与 `j->left` 配对  
   - 若顺序写反（如 `i->left` 配 `j->left`），则变成普通层序遍历，完全丧失对称判断能力

2. **双空节点是 `continue` 而非 `return true`**  
   - `i == nullptr && j == nullptr` 仅说明**这一对位置**对称，但队列中可能还有未检查的节点（如 `root=[1,2,2,null,3,null,3]`）  
   - 若此处 `return true` 会提前终止，导致漏判

3. **短路判定条件**  
   - `i == nullptr || j == nullptr || i->val != j->val` 三者任一满足立即返回 `false`  
   - 包含三种不对称场景：左空右不空、左不空右空、值不相等

- ⚠️ **入队顺序不可交换**：`q.push(i->left); q.push(j->right);` 与 `q.push(i->right); q.push(j->left);` 必须严格镜像，否则后续比较的是同侧节点而非对称节点
- ⚠️ **双空节点 continue**：若误写为 `return true`，测试用例 `[1,2,2,null,3,null,3]` 会错误返回 true（实际为 false）
- ⚠️ **初始压入左右子节点而非 root**：若将 `root` 自身入队，会导致奇数个节点时自相比对逻辑混乱；压入 `left` 和 `right` 才能形成正确的镜像对

**复杂度分析**
| 指标 | 复杂度 | 说明 |
|------|--------|------|
| 时间 | **O(n)** | 每个节点仅被访问一次，入队/出队/比较均为 O(1) |
| 空间 | **O(n)** | 最坏情况下队列存储最后一层节点，约 n/2 个指针 |


**记忆口诀**：*左对右，右对左，双双入队成镜像；双空继续单空假，值不等时早回家。*

---
## 代码实现

**核心思路--递归**
```cpp
class Solution {
    // 阶段1: 镜像递归判断（改编自 100. 相同的树）
    // 意图：判断两棵树 p 和 q 是否互为镜像，而非普通相同
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // 阶段2: 空树边界处理
        // 意图：合并判断"都空"和"一空一非空"两种情况
        // ⚠️ 必须前置判空，否则后续访问 val 会 UB
        if (p == nullptr || q == nullptr) {
            return p == q;  // 都空返回 true，否则返回 false
        }

        // 阶段3: 当前节点值比较 + 交叉递归
        // 意图：p 的左子树必须与 q 的右子树镜像（外侧对应）
        //       p 的右子树必须与 q 的左子树镜像（内侧对应）
        return p->val == q->val 
            && isSameTree(p->left, q->right)   // 左对右：外侧匹配
            && isSameTree(p->right, q->left);  // 右对左：内侧匹配
    }

public:
    // 阶段0: 入口函数
    // 意图：将单棵树对称问题拆分为"左右子树是否互为镜像"
    bool isSymmetric(TreeNode* root) {
        // ⚠️ 题目保证 root 非空时才能直接取 left/right
        // 若 root 为空，按题意应返回 true（空树对称）
        return isSameTree(root->left, root->right);
    }
};
```

**核心思路--迭代**
```cpp
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        // 阶段1: 初始化与边界
        queue<TreeNode*> q;
        if (!root) return true;  // 空树天然对称
        
        // 将根节点的左右子节点作为第一对镜像节点入队
        q.push(root->left);
        q.push(root->right);

        // 阶段2: 成对BFS遍历
        while (!q.empty()) {
            auto i = q.front(); q.pop();  // 左（或镜像左）侧节点
            auto j = q.front(); q.pop();  // 右（或镜像右）侧节点

            // 两者皆空：当前这对位置对称，继续检查其他节点
            if (i == nullptr && j == nullptr) continue;

            // ⚠️ 短路判定：单空、或值不等，直接判定不对称
            if (i == nullptr || j == nullptr || i->val != j->val) return false;

            // 阶段3: 镜像入队 —— 保证下一对出队节点仍互为对称位置
            // i的左子 与 j的右子 应为镜像
            q.push(i->left);
            q.push(j->right);

            // i的右子 与 j的左子 应为镜像
            q.push(i->right);
            q.push(j->left);
        }

        // 所有镜像对均通过检验
        return true;
    }
};
```
