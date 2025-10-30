/*题目描述

给定n个非负整数表示每个宽度为1的柱子的高度图，柱子之间可以承接雨水，计算按此排列的柱子，下雨之后能接多少雨水。

下图是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的柱子高度图，在这种情况下，可以接6个单位的雨水（蓝色部分表示雨水）。

关于输入

由n根柱子的高度（正整数）组成的数组；n不超过1000。
关于输出

一个正整数，表示能承接多少单位的雨水。
例子输入

0 1 0 2 1 0 1 3 2 1 2 1

例子输出

6*/
#include<iostream>
#include<algorithm>
#include<vector>
int main(){
    std::vector<int> height;
    int num;
    while(std::cin>>num){
        height.push_back(num);
    }
    int n=height.size();
    if(n<3){
        std::cout<<0;
        return 0;
    }
    int sum=0;
    for(int i=1;i<n-1;i++){
        int leftMax=height[i];
        int rightMax=height[i];
        for(int j=i;j>=0;j--){
            leftMax=std::max(leftMax,height[j]);
        }
        for(int j=i;j<n;j++){
            rightMax=std::max(rightMax,height[j]);
        }
        int waterLevel=std::min(leftMax,rightMax);
        if(waterLevel>height[i]){
            sum+=waterLevel-height[i];
        }
    }
    std::cout<<sum;
    return 0;
}
