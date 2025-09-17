/*点评赛车
题目描述
4名专家对4款赛车进行评论
1）A说：2号赛车是最好的；
2）B说：4号赛车是最好的；
3）C说：3号赛车不是最好的；
4）D说： B说错了。
事实上只有1款赛车最佳，且只有1名专家说对了，其他3人都说错了。
请编程输出最佳车的车号，以及说对的专家。

关于输入
无输入。

关于输出
输出两行。第一行输出最佳车的车号（1-4中的某个数字）。第二行输出说对的专家（A-D中的某个字母）。

例子输入
例子输出
1
A*/
#include <iostream>
using namespace std;
int main() {
    int thisCar=1;
    char people='A';
    while (thisCar<=4){
        if ((thisCar==2)+(thisCar==4)+(thisCar!=3)+!(thisCar==4)==1){
            cout<<thisCar<<endl;
            break;
        }
        thisCar++;
    } 
    people+=thisCar;
    cout<<people<<endl;
	return 0;
}
