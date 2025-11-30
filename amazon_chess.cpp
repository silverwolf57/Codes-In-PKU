#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cctype>
#include<cmath>
#include<stack>
#include<queue>

//给出棋盘大小，先后手等
#define size 8
#define choose_white 1
#define choose_black -1

int first;//确定先手
int rounds;//确定回合数
int dir_x[8] = { 1,1,1,-1,-1,-1,0,0 };//给出方向数组
int dir_y[8] = { 1,-1,0,-1,1,0,1,-1 };//给出方向数组
char board[8][8];//给出棋盘



//判断棋子是否在棋盘内
bool boundary_check(int x,int y) {
	if (x<0 || x>size || y<0 || y>size)return false;
	return true;
}

//判断移动是否合理
bool check_move(int x0,int y0,int x1, int y1, int x2, int y2,int round ) {
	if (board[x0][y0] != 'b' && board[x0][y0] != 'w')return false;
	if (board[x1][y1] != '0')return false;
	if (board[x2][y2] != '0')return false;
	if (!boundary_check(x1, y1) || !boundary_check(x2, y2))return false;
	return true;
}

//移动棋子
void move(int x0, int y0, int x1, int y1, int x2, int y2,int round) {
	if (check_move(x0, y0, x1, y1, x2, y2, round)) {
		board[x0][y0] = '0';
		if (round % 2 == 0) {
			board[x1][y1] = 'b';
		}
		else {
			board[x1][y1] = 'w';
		}
		board[x2][y2] == '#';
	}
}









int main() {
	//初始化棋盘

	//输入先手
	//输入回合和初始状态
}
