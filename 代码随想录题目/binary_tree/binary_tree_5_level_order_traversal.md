# 二叉树层级遍历 — level order traversal 

- **题目（LeetCode 102）**： [🔗 题目](https://leetcode.cn/problems/binary-tree-level-order-traversal/description/)  
- **难度**：中等
- **解析 / 学习链接**： 
   
    - [🧠 文字解析（代码随想录）](https://programmercarl.com/0102.%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E5%B1%82%E5%BA%8F%E9%81%8D%E5%8E%86.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
    - [🎥 视频讲解（代码随想录）](https://www.bilibili.com/video/BV1GY4y1u7b2/?vd_source=7923b10dbf11c28879c337d8e0bfa8de)

---
## 关键点（精简）

**核心思路**
- **BFS 层固定法**：利用队列 FIFO 特性逐层展开，每次进入循环时**先固定当前层的节点数量**（`q.size()`），再一次性处理完该层所有节点。处理过程中将下一层节点入队，但**本次循环只消费固定数量**，从而天然按层分割。

    - **为什么先固定 size？** 因为循环内部会不断将子节点入队，`q.size()` 动态增长。若不提前固定，无法区分当前层与下一层的边界
    - **匹配逻辑**：每出队一个节点，将其子节点按先左后右入队，供下一轮固定 `size` 时消费

**步骤**
1. **固定层大小是分割层的唯一手段**
   - 进入 `while` 后立即 `int levelSize = q.size()`，随后 `for` 只循环这么多次
   - 反例：若直接用 `while(!q.empty())` 不加内层 for，所有节点将混为一谈，结果退化为单维数组
2. **对弹出元素进行读入**
    - 通过 `q.front()` 得到目标元素，并读入当前节点值，然后弹出 `q.pop()`
3. **先左后右入队保证顺序**
   - `node->left` 先于 `node->right` 入队，下一层出队时自然也是左子树先被访问
   - 代码对应：`if (node->left) q.push(node->left);` 必须写在右子树之前




**复杂度分析**
| 指标 | 复杂度 | 说明 |
|------|--------|------|
| 时间 | **O(n)** | 每个节点恰好入队一次、出队一次，操作均摊 O(1) |
| 空间 | **O(n)** | 队列最坏情况为完全二叉树最后一层，约 n/2 个节点 |

**易错提醒**

- ⚠️ **空栈/空队检查**：虽然本题 root 判空后入队，但若在别处复用模板时忘记 `if(root)`，会导致访问空指针
- ⚠️ **子节点入队顺序颠倒**：先 `right` 后 `left` 会导致每层结果左右翻转，不符合题意

**记忆口诀**
*根入队列 `size` 定，左先右后依次行；一层一维 `push` 进，空树自返不用惊。*



---
## 代码实现

```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> results;  // 存储最终层序结果
        queue<TreeNode*> q;           // BFS 辅助队列

        // 阶段1: 初始化
        if (root) q.push(root);       // 空树直接跳过，results 保持为空

        // 阶段2: 按层遍历
        while (!q.empty()) {
            // ⚠️ 必须先固定当前层节点数，否则无法区分层边界
            int levelSize = q.size(); 
            vector<int> temp;         // 收集当前层所有节点值

            // 只处理本次固定好的 levelSize 个节点
            for (int i = levelSize; i != 0; --i) {
                auto node = q.front();
                q.pop();

                temp.push_back(node->val);  // 记录当前节点

                // 先左后右入队，供下一层处理
                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }

            // 本层遍历完毕，整层压入答案
            results.push_back(temp);
        }

        return results;
    }
};
```