# 开发商购买土地 — real estate developer buy property

- **题目（LeetCode 59）**： [🔗 题目](https://kamacoder.com/problempage.php?pid=1044)  
- **难度**：未知
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录/Carl）](https://programmercarl.com/kamacoder/0044.%E5%BC%80%E5%8F%91%E5%95%86%E8%B4%AD%E4%B9%B0%E5%9C%9F%E5%9C%B0.html#%E6%80%9D%E8%B7%AF)  
  

---
## 关键点（精简）
* 本题依然可以使用**前缀和**来解决
* 当然暴力解决也可以
* 只是要注意迭代的时候，是纵向的还是横向的迭代，还有迭代的数组大小


---
## 代码实现

```cpp
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {

int total = 0, mid = 0, max = 0;

//开始构建数据
int n = 0, m = 0;
cin >> n >> m;
vector<vector<int>> lands(n, vector<int>(m));

for (auto &e : lands) {
    for (auto &ei : e) {
        cin >> ei;
        total += ei;
    }
}

vector<int> horizontal(n);
for (int i = 0; i < n; ++i) {
    int temp = 0;
    for (const auto &e : lands[i]) {
        temp += e;
    }
    horizontal[i] = temp;
}

vector<int> vertical(m);
for (int i = 0; i < m; ++i) {
    int temp = 0;
    for (const auto &e : lands) {
        temp += e[i];
    }
    vertical[i] = temp;
}

//现在开始选出最优解
int result = INT_MAX;
int verticalCut = 0;
for (const auto e : vertical) {
    verticalCut += e; 
    result = min(result, abs(total - verticalCut - verticalCut));
}

int horizontalCut = 0; 
for (const auto e : horizontal) {
    horizontalCut += e; 
    result = min(result, abs(total - horizontalCut - horizontalCut));
}

cout << result << endl;
}
```