# 不同路径 2 — Unique Paths 2

- **题目（LeetCode 62）**： [🔗 题目](https://leetcode.cn/problems/unique-paths-ii/description/)  
- **难度**：简单
- **解析 / 学习链接**：  
  - [🧠 文字解析（代码随想录/Carl）](https://programmercarl.com/0063.%E4%B8%8D%E5%90%8C%E8%B7%AF%E5%BE%84II.html)  
  - [🎥 视频讲解（Bilibili）](https://www.bilibili.com/video/BV1Ld4y1k7c6?vd_source=7923b10dbf11c28879c337d8e0bfa8de&spm_id_from=333.788.player.switch&trackid=web_related_0.router-related-2206146-5nk2d.1765021945121.579)

---
## 关键点（精简）

  * 问题分析:
    * **`dp`数组定义**：
      * 由于是一个而为地图，故我们使用二维数组`dp[][]`来表示， 其值`dp[i][j]`表示的就是在i,j这个位置有多少种走法
    * **递推公式**:
      * 如果我们要到`dp[i][j]`这个位置的话，我们要么从`dp[i-1][j]`或者dp`[i][j-1]`到达
      * 所以我们能得到公式`dp[i][j] = dp[i-1][j]+dp[i][j-1]` 
      * 而不是`dp[i][j] = dp[i-1][j]+1`，因为我们这里的`dp`表示的是多少种不同路径
      * 但是这道题，我们还要加一个前提条件: 如果dp[i][j]检查为障碍的话，我们就不进行递推公式
    * **初始化**: 
      * 因为本题只能像右边或下边移动
      * 因为`dp[i][j]`其实是由上面和左边初始化来的，那么不难想，最上边一排和最左列都需要初始化
      * 初始化值为1
      * 本题还有关键点：当在最左边和最右边的时候如果由石头挡住那么石头后面的格子是不可能到达的
      * 也就是：我们只需要初始化最左和最右边出现石头前的格子为1即可， 遇到石头就停止
    * **遍历顺序**:
      * 由于我们都知道`dp[i][j]`都是由上面和左面推导出来的, 遍历顺序就应该**从上到下从左到右**遍历

---
## 代码实现

```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

        int x_size = obstacleGrid[0].size();
        int y_size = obstacleGrid.size(); 

        vector<vector<int>> dp(y_size, vector<int>(x_size, 0)); 


        //初始化
        for(int x = 0; (x < x_size) && (obstacleGrid[0][x] == 0); ++x) dp[0][x] = 1; 
        for(int y = 0; (y < y_size) && (obstacleGrid[y][0] == 0); ++y) dp[y][0] = 1;


        for(int y = 1 ; y < y_size; ++y){

            for(int x = 1; x < x_size; ++x){

                if (obstacleGrid[y][x] != 1){

                    dp[y][x] = dp[y-1][x] + dp[y][x-1];

                }

            }

        }

        return dp[y_size-1][x_size-1]; 

        
    }
};
```
* 时间复杂度: O(mn)
* 空间复杂度: O(mn)
* 另外一定要注意: 
    * 初始化时迭代条件`(x < x_size) &&(obstacleGrid[0][x] == 0);`与 `(obstacleGrid[0][x] == 0)&&(x < x_size);`两者的差异
    * 第二个有**越界**的可能
* 同理， 我们还可以使用滚动数组来优化:

```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

        int x_size = obstacleGrid[0].size();
        int y_size = obstacleGrid.size(); 
        int value_to_y = 1; 

        vector<int> dp(x_size, 0); 

        //特殊情况
        if(obstacleGrid[0][0] == 1 || obstacleGrid[y_size-1][x_size-1] == 1) return 0;

        //初始化
        for(int x = 0; (x < x_size) && (obstacleGrid[0][x] == 0); ++x) dp[x] = 1;  


        for(int y = 1 ; y < y_size; ++y){

            if( obstacleGrid[y][0] == 1){ value_to_y = 0; }
            dp[0] = value_to_y;

            for(int x = 1; x < x_size; ++x){

                if (obstacleGrid[y][x] != 1){

                    dp[x] = dp[x] + dp[x-1];

                }else{

                    dp[x] = 0; 

                }

            }

        }

        return dp[x_size-1]; 

    }
};
```