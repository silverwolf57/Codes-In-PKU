/*约瑟夫问题
题目描述
约瑟夫问题：有ｎ只猴子，按顺时针方向围成一圈选大王（编号从１到ｎ），从第１号开始报数，一直数到ｍ，数到ｍ的猴子退出圈外，剩下的猴子再接着从1开始报数。就这样，直到圈内只剩下一只猴子时，这个猴子就是猴王，编程求输入ｎ，ｍ后，输出最后猴王的编号。

关于输入
每行是用空格分开的两个整数，第一个是 n, 第二个是 m ( 0 < m,n <=300)。最后一行是（表示输入结束）：
0 0

关于输出
对于每行输入数据（最后一行除外)，输出数据也是一行，即最后猴王的编号

例子输入
6 2
12 4
8 3
0 0
例子输出
5
1
7
提示信息
所给的数据中，m 未必比 n 小！*/
#include <iostream>
int main() {
    int n,m;
	while(std::cin>>n>>m){
	    if(n==0&&m==0){
	        break;
	    }
	    int a[n],counter=0,rest=n;
	    for(int i=0;i<n;i++){
	        a[i]=i+1;
	    }
	    int dead_point=0;
	    for(int rest=n;rest>1;rest--){
	        dead_point=(dead_point+m-1)%rest;
	        if(dead_point!=rest-1){
	        for(int j=dead_point;j<rest-1;j++){
	            a[j]=a[j+1];
	        }
	        }
	    }
	    std::cout<<a[0]<<std::endl;
	}
	return 0;
}
