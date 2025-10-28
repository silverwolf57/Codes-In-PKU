/*
扩号匹配问题
题目描述

   在某个字符串（长度不超过100）中有左括号、右括号和大小写字母；规定（与常见的算术式子一样）任何一个左括号都从内到外与在它右边且距离最近的右括号匹配。写一个程序，找到无法匹配的左括号和右括号：首先输出原来字符串，下一行是和原字符串等长的一行，标出不能匹配的括号，其中不能匹配的左括号用"$"标注,不能匹配的右括号用"?"标注
    
关于输入

第一行一个正整数n,表示数据的组数。后面n行，每组数据一行，包含一个字符串，只包含左右括号和大小写字母，字符串长度不超过100
关于输出

   对每组输出数据，输出两行，第一行包含原始输入字符，第二行由"$","?"和空格组成，与第一行等长，"$"和"?"表示与之对应的左括号和右括号不能匹配。
   注意：即使所有括号都匹配，第二行也要输出等长的一行空格
例子输入

2
((ABCD(x)
)(rttyy())sss)(

例子输出

((ABCD(x)
$$
)(rttyy())sss)(
?            ?$*/
#include<iostream>
#include<string>
int main(){
    int n;
    std::cin>>n;
    for(int i=0;i<n;i++){
        std::string str;
        std::cin>>str;
        int left[101]={0},right[101]={0};
        int len=str.length();
        for(int j=0;j<str.length();j++){
            if(str[j]=='(')left[j]=1;
            if(str[j]==')')right[j]=1;
        }
        std::cout<<str<<std::endl;
        while(str.rfind('(')!=std::string::npos){
            int index1=str.rfind('('),index2;
            bool test=false;
            for(int j=index1;j<len;j++){
                if(str[j]==')'){
                    index2=j;
                    test=true;
                    break;
                }
            }
            if(test){
                str[index1]='1';
                str[index2]='1';
                left[index1]=2;
                right[index2]=2;
            }else{
                str[index1]='1';
            }
        }
        for(int j=0;j<len;j++){
            if(left[j]==1){
                std::cout<<'$';
            }
            if(right[j]==1){
                std::cout<<'?';
            }
            if(right[j]!=1&&left[j]!=1){
                std::cout<<" ";
            }
        }
        std::cout<<std::endl;
    }
    return 0;
}
