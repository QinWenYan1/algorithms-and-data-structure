class Solution {
public:
    int fib(int n) {

        //我们通过爬阶梯的方式来计算
        int i = 0, j = 1; 

        //如果n是0的话需要返回0 
        if( !n ){ return i; }

        for(int iter = 1; iter < n; ++ iter){

            int old_i = i; 
            int new_i = j; 
            j = j+old_i; 
            i = new_i; 

        }

        return j;  
        
    }
}; 