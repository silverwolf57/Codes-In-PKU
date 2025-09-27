/*矩阵乘法
题目描述
根据矩阵乘法的原理，求出两个矩阵相乘后的新矩阵。
这里我们假定矩阵中每个元素都是正整数。

关于输入
第一行有三个正整数a, b, c(a, b, c < 500)。
接下来a行，每行b个整数，是左矩阵。
接下来b行，每行c个整数，是右矩阵。

关于输出
输出结果矩阵，共a行c列，同一行用空格分隔，每一行末尾不能有空格。

例子输入
2 2 1
1 2
3 4
1
1
例子输出
3
7*/
#include <iostream>
int main() {
	int a,b,c;
	std::cin>>a>>b>>c;
	int first[a][b],second[b][c],result[a][c];
	for(int i=0;i<a;i++){
	    for(int j=0;j<c;j++){
	        result[i][j]=0;
	    }
	}
	for(int i=0;i<a;i++){
	    for(int j=0;j<b;j++){
	        std::cin>>first[i][j];
	    }
	}
	for(int i=0;i<b;i++){
	    for(int j=0;j<c;j++){
	        std::cin>>second[i][j];
	    }
	}
	for(int i=0;i<a;i++){
	    for(int j=0;j<c;j++){
	        for(int k=0;k<b;k++){
	            result[i][j]+=first[i][k]*second[k][j];
	        }
	    }
	}
	for(int i=0;i<a;i++){
	    for(int j=0;j<c;j++){
	       if(j==0){
	              std::cout<<result[i][0];
	        }
	        else std::cout<<" "<<result[i][j];
	        }
	        
	    std::cout<<std::endl;
	}
	return 0;
}
