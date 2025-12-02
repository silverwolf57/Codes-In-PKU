#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cctype>
#include<cmath>
#include<stack>
#include<queue>


#define SIZE 8
#define EMPTY 0
#define BLACK 1
#define WHITE -1
#define BLOCK 2
#define MAX_DEPTH 4 
int current_color;

// 王和皇后8个方向的增量 
const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

//给出棋盘
int board[8][8];


//---基础数据结构


//给出坐标
struct cordinates{
	int x，y;
};

//给出运行位置
struct move {
	int x0, x1, x2, y0, y1, y2;
};


//---基本函数


//检查是否在棋盘内
bool is_valid(int x,int y) {
	return x >= 0 && x <= SIZE && y >= 0 && y <= SIZE;
}

//用于放置棋子
void apply_move(int current_board[SIZE][SIZE],move m,int color) {
	current_board[m.x0][m.y0] = EMPTY;
	current_board[m.x1][m.y1] = color;
	current_board[m.x2][m.y2] = BLOCK;
}

//撤销操作便于回溯
void undo_move(int current_board[SIZE][SIZE], move m, int color) {
	current_board[m.x0][m.y0] = color;
	current_board[m.x1][m.y1] = EMPTY;
	current_board[m.x2][m.y2] = EMPTY;
}

//



int main() {
	//初始化棋盘

	//输入先手
	//输入回合和初始状态
}
