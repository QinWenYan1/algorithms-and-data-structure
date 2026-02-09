# 设计链表 — My Linked List 

- **题目（LeetCode 707）**： [🔗 题目](https://leetcode.cn/problems/design-linked-list/)  
- **难度**：中等
- **解析 / 学习链接**：   
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/0707.%E8%AE%BE%E8%AE%A1%E9%93%BE%E8%A1%A8.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE)
  - [🎥 视频讲解（代码随想录）](bilibili.com/video/BV1FU4y1X7WD/)

---
## 关键点（精简）

**一句话概括**
使用**带虚拟头节点的单链表** + **长度变量**，统一所有操作的边界处理。

**1. 数据结构设计**
- **虚拟头节点**：`head->next`指向第一个真实节点
- **长度变量**：`len`记录节点数，快速判断索引有效性
- **双指针遍历**：`curr`和`nxt`配合移动
  * * 如何考虑自己写的遍历至某个节点是否正确： 考虑特殊情况如删除第0个节点

**2. 统一操作模式**
```
定位到目标位置的前一个节点(curr)
然后对curr->next进行操作
```
这样无论是增、删、查，都只需要处理`curr->next`指针

**3. 关键操作逻辑**
- **获取(get)**：移动到索引位置，返回节点值
- **头部添加**：直接在`head->next`插入
- **尾部添加**：遍历到末尾，在最后一个节点后插入
- **指定位置添加**：先定位到前一个节点，再插入
- **删除**：定位到前一个节点，跳过目标节点并删除

**4. 边界处理智慧**
- **虚拟头节点**：消除头节点操作的特殊性
- **长度检查**：操作前先用`len`判断索引是否有效
- **循环条件**：使用`count--`或`while(nxt)`控制移动次数

**为什么这样设计？**
1. **简化删除**：删除头节点和其他节点逻辑一致
2. **快速判断**：通过`len`立即知道索引是否越界
3. **代码复用**：`addAtHead/Tail`可复用`addAtIndex`逻辑
4. **内存安全**：删除时正确释放内存
---
## **设计精髓**
> **用虚拟头节点把"边界问题"变成"普通问题"**  
> **用长度变量把"越界检查"变成"常数时间判断"**

这种设计让链表的所有操作都遵循同一个模式，大幅降低实现复杂度。

---
## **代码优化**
> **添加尾指针，将 `addAtTail` 从 O(n) 优化到 O(1)，直接定位尾部插入无需遍历。**




---
## 代码实现（优化`addAtTail`版本）

```cpp
class MyLinkedList {

    struct Node{
        Node(int value = 0, Node* nxt = nullptr): value(value), next(nxt){} //默认构造函数 + 普通构造函数
        int value; 
        Node *next;
    };
    Node *_dummyHead; //虚拟头节点
    Node *_dummyTail; //优化addAtTail: 虚拟尾节点
    unsigned _len; //记录长度

public:

    MyLinkedList(): _dummyHead(new Node()), _len(0), _dummyTail(new Node()){ _dummyHead->next = _dummyTail; } //初始化
    
    int get(int index) {
        //建一个计数器来确定哪一个node是我们要找的
        int count = index; 
        Node *curr = _dummyHead, *nxt = _dummyHead->next; 

        if (index < _len ){
            //开始迭代遍历
            while(count--){
                curr = nxt; 
                nxt = curr->next;
            } 

            //找到遍历位置了, 返回值
            return nxt->value; 

        }
        return -1; 
    }
    
    void addAtHead(int val) {
        //创建新的节点， 并将其与虚拟节点的next和虚拟节点连接在一起
        Node *headEle = new Node(val, _dummyHead->next); 
        _dummyHead->next = headEle;
        ++_len;
    }
    
    void addAtTail(int val) { //O(n) -> O(1)
        Node *tail = _dummyTail; 

        //我们直接使用_dummyTail来进行添加
        Node * newNodePtr = new Node(); 
        tail->value = val; 
        tail->next = newNodePtr;
        _dummyTail = newNodePtr; 
        ++_len; 

    }
    
    void addAtIndex(int index, int val) {
        int count = index; 
        Node *curr = _dummyHead, *nxt = _dummyHead->next; 

        if (index <= _len ){ //判断index是否为合法的
            //开始迭代遍历
            while(count--){ 
                curr = nxt; 
                nxt = curr->next;
            } 

            //找到遍历位置了， 开始插入
            Node * newNodePtr = new Node(val, nxt); 
            curr->next = newNodePtr; 
            ++_len;

        }
        
    }
    
    void deleteAtIndex(int index) {
        int count = index; 
        Node *curr = _dummyHead, *nxt = _dummyHead->next; 

        if(_len > index){
            while (count--){ 
                curr = nxt; 
                nxt = curr->next;
            }
            //找到位置，立即删除
            curr->next = nxt->next; 
            delete nxt;
            --_len; 
        }
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
```

这里放一个未优化的`addAtTail`的对比一下:
```cpp
void addAtTail(int val) {
        Node *curr = _dummyHead, *nxt = _dummyHead->next; 

        //依旧遍历到相应位置，也就是尾部,
        //开始迭代遍历
        while(nxt){ //判断是不是尾部只需要看next是不是nullptr
            curr = nxt; 
            nxt = curr->next;
        } 

        Node * newNodePtr = new Node(val, nxt); 
        curr->next = newNodePtr;
        ++_len; 

    }
```