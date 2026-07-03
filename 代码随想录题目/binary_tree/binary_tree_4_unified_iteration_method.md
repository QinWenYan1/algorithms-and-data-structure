# 二叉树的统一迭代法 — unified iteration method  

- **难度**：简单
- **解析 / 学习链接**： 
    * ✅ [binary_tree_1_preorder_traversal.md](./binary_tree_1_preorder_traversal.md) - 前序遍历
    * ✅ [binary_tree_2_postorder_traversal.md](./binary_tree_2_postorder_traversal.md) - 后序遍历
    * ✅ [binary_tree_3_inorder_traversal.md](./binary_tree_3_inorder_traversal.md) - 中序遍历

---
## 关键点（精简）

**为什么三种迭代方法没有统一？**
- 在**后序遍历** [binary_tree_2_postorder_traversal.md](./binary_tree_2_postorder_traversal.md)中，我们提到中提到说**使用栈的话，无法同时解决访问节点（遍历节点）和处理节点（将元素放进结果集）不一致的情况**。
- 实际上，迭代方法是可以统一地使用一种方法的！但我们需要将访问的节点放入栈中，**把要处理的节点也放入栈中但是要做标记**。

**那么如何统一迭代方法？**
- **方法一**：就是要处理的节点放入栈之后，紧接着放入一个空指针作为标记。 这种方法可以叫做**空指针标记法**。
