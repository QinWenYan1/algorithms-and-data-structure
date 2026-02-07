# 区间和 — interval sum

- **题目（LeetCode 59）**： [🔗 题目](https://kamacoder.com/problempage.php?pid=1070)  
- **难度**：未知
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录）](https://programmercarl.com/kamacoder/0058.%E5%8C%BA%E9%97%B4%E5%92%8C.html)  
  

---
## 关键点（精简）
* 如果只是单单读取数据写入到数组，然后总和是不行的
  - 时间复杂度非常高， 直接timeout
  - 比如查询m次，那么时间复杂度为O(mn)
* **前缀和策略**: 这种计算区间和问题会非常有用
  - 记录计算过的子数组之和，后续可以重复利用，从而降低累加计算次数
  - 例如对`vec[i]`这个数组做区间和，我可以用`p[i]`来表示数组上的区间和
  - `p[i]`即表示下标0到i的（闭区间）累加之和
  - `m`-`n`区间之和就可以用`p[n]`-`p[m-1]`表示
  - 这种方法就可以让时间复杂度大减到O(m), 当查询m次

---
## 代码实现

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

int main() {

  //构建vector
  int size = 0; 
  cin >> size; 
  vector<int> vec(size); 

  //读入元素，并计算其子向量在下标前的和
  int prev = 0; 
  for (int i = 0; i < size; ++i) { 

      int val = 0; 
      cin >> val; 
      prev += val; 
      //写入到元素里面
      vec[i] = prev; 
      
  }

  //写入结束现在开始读取数据，并打印

  int i = 0; 
  int j = 0; 

  while(cin >> i){

      if(i == 0 ){
          cin >> j; 
          cout << vec[j] << endl; 
          continue; 
      }else{
          cin >> j; 
          cout << vec[j] - vec[i-1] << endl;
          continue; 
      }

  }

}
```

C++ 代码 面对大量数据 读取 输出操作，**最好用`scanf` 和 `printf`，耗时会小很多**：

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

int main() {

  //构建vector
  int size = 0; 
  scanf("%d", &size); 
  vector<int> vec(size); 

  //读入元素，并计算其子向量在下标前的和
  int prev = 0; 
  for (int i = 0; i < size; ++i) { 

      int val = 0; 
      scanf("%d",&val); 
      prev += val; 
      //写入到元素里面
      vec[i] = prev; 
      
  }

  //写入结束现在开始读取数据，并打印

  int i = 0; 
  int j = 0; 

  while(scanf("%d", &i) == 1){

      if(i == 0 ){
          scanf("%d", &j); 
          printf("%d\n", vec[j]);
          continue; 
      }else{
          scanf("%d", &j); 
          printf("%d\n", vec[j] - vec[i-1]);
          continue; 
      }

  }

}
```

实验发现，使用`scanf`, `printf`版本运行需要46ms, 而`>>`, `<<`版本需要665ms