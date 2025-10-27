/*例题(13.8) 出书最多
题目描述

假定图书馆新进了m（10 ≤ m ≤ 999）本图书，它们都是由n（2 ≤ n ≤ 26）个作者独立或相互合作编著的。假设m本图书编号为整数（1到999），作者的姓名为字母（'A'到'Z'），请根据图书作者列表找出参与编著图书最多的作者和他的图书列表。
关于输入

第一行为所进图书数量m，其余m行，每行是一本图书的信息，其中第一个整数为图书编号，接着一个空格之后是一个由大写英文字母组成的没有重复字符的字符串，每个字母代表一个作者。
关于输出

输出有多行：
第一行为出书最多的作者字母；
第二行为作者出书的数量；
其余各行为作者参与编著的图书编号（按输入顺序输出）。
例子输入

11
307 F
895 H
410 GPKCV
567 SPIM
822 YSHDLPM
834 BXPRD
872 LJU
791 BPJWIA
580 AGMVY
619 NAFL
233 PDJWXK

例子输出

P
6
410
567
822
834
791
233*/

#include<iostream>
#include<vector>
#include<string>
int main(){
    int m,cnt[26]={0};
    std::cin>>m;
    std::vector<int> num(m);
    std::string author[1000];
    for(int i=0;i<m;i++){
        std::cin>>num[i]>>author[i];
        for(int j=0;j<author[i].length();j++){
            char c=author[i][j];
            cnt[c-'A']++;
        }
    }
    int max=-1;
    char name;
    for(int i=0;i<26;i++){
        if(cnt[i]>max){
            max=cnt[i];
            name=i+'A';
        }
    }
    std::cout<<name<<std::endl<<max<<std::endl;
    for(int i=0;i<m;i++){
        if(author[i].find(name)!=std::string::npos){
            std::cout<<num[i]<<std::endl;
        }
    }
    return 0;
}
