# 对称二叉树 — is symmetric

- **题目（LeetCode 101）**： [🔗 题目](https://leetcode.cn/problems/symmetric-tree/description/)  
- **难度**：简单
- **解析 / 学习链接**： 
   
    - [🧠 文字解析（代码随想录）](https://programmercarl.com/0101.%E5%AF%B9%E7%A7%B0%E4%BA%8C%E5%8F%89%E6%A0%91.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
    - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1ue4y1Y7Mf/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）

**核心思路**
- **递归镜像比较**：将单棵树的对称性问题转化为"两棵树是否互为镜像"的子问题。把根节点的左子树和右子树拆成独立的两棵树 $p$ 和 $q$，递归判断它们是否镜像相等。

    - **为什么拆成两棵子树？** 单棵树的对称性无法直接自递归定义，但"两棵树互为镜像"可以：根值相等，且 $p$ 的左子树与 $q$ 的右子树镜像、$p$ 的右子树与 $q$ 的左子树镜像（本题是交叉对应）

**关键点**
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

**复杂度分析**
| 指标 | 复杂度 | 说明 |
|------|--------|------|
| 时间 | **O(n)** | 每个节点只访问一次，每次比较 O(1) |
| 空间 | **O(h)** | 递归栈深度等于树高 h；最坏链状树 h=n，平衡树 h=log n |

**易错提醒**
- ⚠️ **递归参数顺序写反**：若写成 `isSameTree(p->left, q->left)` 会变成判断"相同树"（100 题逻辑），导致 WA
- ⚠️ **空指针解引用**：必须先判空再访问 `p->val`，否则 `nullptr` 解引用产生未定义行为（UB）
- ⚠️ **根节点为空**：`root` 为空时 `root->left` 不会执行（因为 `isSymmetric` 里直接调用，但空 root 在 LeetCode 通常单独处理，实际代码中若 root 为空会访问 `left` 导致 UB——需确保调用前 root 非空或加判空）

**记忆口诀**：*根等左右交叉比，空树相等返回真；递归镜像非相同，参数顺序莫弄混。*

**是否还有其他方法？**：
- 有，本地同样可以迭代法，思路也是一样的，详情见[文字解析（代码随想录）](https://programmercarl.com/0101.%E5%AF%B9%E7%A7%B0%E4%BA%8C%E5%8F%89%E6%A0%91.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
---
## 代码实现

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