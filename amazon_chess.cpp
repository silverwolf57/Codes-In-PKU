#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cctype>
#include<cmath>
#include<stack>
#include<queue>
#include<cstring>


#define SIZE 8
#define EMPTY 0
#define BLACK 1
#define WHITE -1//设置为相反数利于变换
#define BLOCK 2
#define MAX_DEPTH 4 
int current_color;

// 8个方向移动
const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

//给出棋盘
int board[8][8];

//---原始权重数据
double w1[56] = { 0,0,0.074938141,2.113308430,1.829644322,1.657095432,1.844633341,1.709531188,1.947853684,1.597983241,1.290230632,1.167080998,0.580433190,0.053694796,-0.011891359,0.527658403,0.975054741,1.056464434,0.872889936,0.678786278,0.323303133,0.346939683,0.260094881,0.264616042,0.246926725,0.189162090,0.141057417,0.105003797,0.100303024,0.094548225,0.075991668,0.056678012,0.052921258,0.046266042,0.047984783,0.029863806,0.046501521,0.035372451,0.036930695,0.026028842,0.023727236,0.008815981,0.005980607,0.009275969,-0.003742765,-0.009044983,-0.010549444,-0.032312561,-0.012371800,-0.037411232,-0.032170087,-0.012665736,-0.025661280,0.030489521,0.038260937,-0.033962481 };
double w2[56] = { 0,0,-0.071123712,1.850196242,1.909757733,1.786974669,1.441033125,1.831614137,1.863318324,1.549122095,0.929738343,0.985552371,0.519130468,0.652193844,0.677611768,0.715636075,-0.022837769,0.100610048,-0.172568828,-0.087590173,0.244123191,0.132074401,0.141869083,0.097190522,0.033922136,0.084543742,0.094968185,0.085143305,0.066933967,0.070909552,0.083291963,0.085179411,0.069383688,0.058226194,0.060640641,0.065368392,0.054329056,0.054176800,0.042966656,0.044218585,0.038709428,0.031496748,0.023774918,0.015536518,0.010674691,0.005355561,0.008374230,0.010649841,0.012298613,0.012731116,0.006807683,0.003942049,0.000137917,-0.014996326,-0.007956794,-0.035135169 };
double w3[56] = { 0,0,0.285573512,1.067316651,-0.211924806,0.680028081,0.517808735,0.304819107,-0.360255659,0.283211440,-0.118919544,-0.320547521,-0.164136052,-0.199558660,-0.158322647,-0.134399980,-0.166122779,-0.147537082,-0.119008608,-0.115313880,-0.088800281,-0.144199789,-0.093452334,-0.098844223,-0.061869688,-0.042582039,-0.026260521,-0.000397748,-0.004830216,-0.015821418,0.015736405,0.018657653,0.027041025,0.018133903,0.027038572,0.051898617,0.024094300,0.032939505,0.027083304,0.032979585,0.024715593,0.048389383,0.051429220,0.049864184,0.065294459,0.079495110,0.070997894,0.100243673,0.052135076,0.094104849,0.087983906,0.061890475,0.079814047,-0.026632605,-0.043000557,0.082739472 };
double w4[56] = { 0,0,0.061070204,2.073594332,1.803056121,1.969837666,1.993263960,1.986328840,1.706978559,1.858220458,1.816977739,1.320441842,1.554476857,1.503799796,1.165330052,0.306896836,0.428119272,0.127804548,0.320249408,0.250915736,0.208399042,0.209280223,0.189255610,0.176422641,0.158465251,0.123073861,0.114771605,0.107638910,0.104587719,0.094095841,0.077729441,0.085181594,0.088369705,0.096417032,0.086386517,0.084225371,0.094143234,0.101544440,0.116312958,0.118276447,0.126188114,0.131197393,0.142377511,0.138548672,0.131359026,0.133364707,0.122829571,0.130566165,0.130473971,0.133546650,0.111887053,0.097306497,0.095673442,0.109085456,0.139188647,0.08377216 };
double w5[56] = { 0,0,0.107754663,-0.528144240,-1.379346251,-1.006276369,-0.825565398,-0.430609971,-0.473824382,-0.060512420,-0.942406714,-0.967272699,-0.992075503,-1.073423266,-0.858994186,-0.838604629,-0.738691866,-0.771107376,-0.667914927,-0.620147049,-0.567148566,-0.658371270,-0.578625798,-0.549303949,-0.488953888,-0.356694996,-0.272865117,-0.213500351,-0.175519645,-0.133494422,-0.070355214,-0.038640279,-0.043525659,-0.037141897,-0.031321511,-0.023366986,-0.021908367,-0.013590249,-0.019244174,-0.014974004,-0.009036653,-0.018890575,-0.004873865,-0.017690081,-0.012989196,-0.020389291,-0.031792857,-0.031873308,-0.028690575,-0.024877874,-0.033742540,-0.026430298,-0.027800240,-0.030750951,-0.021546466,-0.037860770 };
double w6[56] = { 0,0,-4.567995548,-3.716784000,-3.381752491,-2.938109636,-3.290686846,-2.702058077,-2.855453491,-2.595350504,-2.005551338,-1.637469649,-1.272953510,-1.047218084,-0.879562616,-0.746166408,-0.717715025,-0.592138231,-0.504874051,-0.366238832,-0.404548317,-0.305050164,-0.272765279,-0.249806121,-0.137687027,-0.254965365,-0.089192919,-0.171341106,-0.076427318,-0.220489189,-0.091823421,-0.180632398,-0.106192604,-0.145687878,-0.073370934,-0.149500415,-0.069663063,-0.189439490,-0.027017180,-0.123841494,-0.011969413,-0.017853998,0.068564072,0.002616666,0.172109649,0.157967970,0.158981338,0.351862490,0.168605193,0.400329232,0.361347109,0.220473915,0.434309691,-0.030947627,-0.074839503,0.44456172 };

//--- 内部评估参数
const double depthParameter[7] = { 0.0, 1.0, 0.5, 0.25, 0.125, 0.0625, 0.03125 };

//设置为40以防遇到距离的极端情况
const double cntParameter[40] = { 0.0, 1.0, 0.95, 0.9, 0.8, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };


//---基础数据结构


//给出坐标
struct cordinates{
	int x;
	int y;
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

//找出所有对应走法
std::vector<move> find_move(int current_board[SIZE][SIZE],int color) {
	std::vector<move> possible_ways;
	std::vector<cordinates> pieces;
	//找对应颜色棋子
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			current_board[i][j] = color;
			cordinates current_cordinates;
			current_cordinates.x = i;
			current_cordinates.y = j;
			pieces.push_back(current_cordinates);
		}
	}
	for (int i = 0; i < pieces.size(); ++i) {
		int sx = pieces[i].x, sy = pieces[i].y;
		for (int j = 0; j < 8; ++j) {
			for (int step1 = 1; ; ++step1) {
				int ex = sx + dx[j]*step1,ey=sx+dy[j]*step1;
				if (!is_valid(ex, ey) || board[ex][ey] != EMPTY)continue;
				//找到可行空格就继续搜索
				// 使用临时棋盘以防改变真实棋盘
				
			    //记录最初状态以便重置棋盘
				int first_state = board[sx][sy];
				int current_state = board[ex][ey];
				board[sx][sy] = EMPTY;
				board[ex][ey] = first_state;

				//放置障碍
				for (int p = 0; p < 8; ++p) {
					for (int step2 = 1;; ++step2) {
						int bx = ex + dx[p] * step2, by = ey + dy[p] * step2;
						if (!is_valid(bx, by) || board[bx][by] != EMPTY)break;
						if (is_valid(bx, by) && board[bx][by] == EMPTY) {
							possible_ways.push_back({ sx,sy,ex,ey,bx,by });
						}
					}
				}
				board[sx][sy] = first_state;
				board[ex][ey] = current_state;

			}
		}
	}
	return possible_ways;
}

//---进行评估函数计算



//求出每个棋子kingmove(一次走一个）到某个地方的最短路径
void king_bfs(int dis[SIZE][SIZE],int current_board[SIZE][SIZE],int color) {
	std::queue<cordinates> piece;

	//初始化距离棋盘
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (current_board[i][j] == EMPTY)dis[i][j] = 1000;
			else dis[i][j] = 0;
		}
	}

	//找出棋子位置并加入队列
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (current_board[i][j] == color) {
				piece.push({ i,j });
			}
		}
	}

	//进行BFS
	while (!piece.empty()) {
		cordinates curr = piece.front();
		piece.pop();
		int d = dis[curr.x][curr.y];
		if (d> 40)continue;
        
		for (int i = 0; i < 8; ++i) {
				int nx = curr.x + dx[i], ny = curr.y + dy[i];

				// 检查边界或障碍物
				if (is_valid(nx, ny) && current_board[nx][ny] == EMPTY) {

					//只考虑最短距离
					if (dis[nx][ny] > d + 1)dis[nx][ny] = d + 1;
					piece.push({ nx,ny });
				}
			}

		}
	
	//将未达的 1000 改为 -1
	for (int i = 0; i <SIZE; ++i) {
		for (int j = 0; j <SIZE; ++j) {
			if (dis[i][j] == 1000) {
				dis[i][j] = -1;
			}
		}
	}

}


// 计算从每个棋子到达每个空位的最少 Queen Moves 步数（一次走多个）
void queen_bfs(int dis[SIZE][SIZE], int player_color, const int current_board[SIZE][SIZE]) {
	std::queue<cordinates> piece;

	// 初始化距离地图 
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (current_board[i][j] == EMPTY) dis[i][j] = 1000;
			else dis[i][j] = 0;
		}
	}

	//找出棋子并加入队列
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (current_board[i][j] == player_color) {
				dis[i][j] = 0;
				piece.push({ i,j });
			}
		}
	}

	//BFS
	while (!piece.empty()) {
		cordinates curr = piece.front();
		piece.pop();
		int d = dis[curr.x][curr.y];
		if (d >= 40) continue;

		for (int dir = 0; dir < 8; ++dir) {
			// 沿着一个方向探索所有可达空位
			for (int step = 1; ; ++step) {
				
				int nx = curr.x + dx[dir] * step;
				int ny = curr.y + dy[dir] * step;

				// 检查边界或障碍物
				if (!is_valid(nx, ny) || current_board[nx][ny] != EMPTY) {
					// 遇到障碍物或边界，沿该方向的搜索停止
					break;
				}

				// 检查是否找到更短路径
				// 注意：直线上的所有空位都应该被标记为 d + 1，如果 d + 1 更短的话
				if (dis[nx][ny] > d + 1) {
					dis[nx][ny] = d + 1;
					piece.push({ nx, ny });
				}

				// 如果当前点 (nx, ny) 可达，那么它到起点的距离是 d+1。
				// 沿着这条直线上更远的点 (step+1) 也可以通过这一次 Queen Move 达到
				// 总距离仍然是 d+1，所以搜索继续沿着该方向进行。
			}
		}
	}

	// 将未达的 1000 改为 -1
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (dis[i][j] == 1000) dis[i][j] = -1;
		}
	}
}
//计算特征E(=所有空格的基于Kingmove的空格质量*距离权重/kingmove距离）
double compute_valueE(int color, int current_board[SIZE][SIZE]) {
	double score1 = 0, score2 = 0;
	int mobility[SIZE][SIZE];
	memset(mobility, 0, sizeof(mobility));
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (current_board[i][j] == EMPTY) {
				int cnt = 0;
				for (int k = 0; k < 8; ++k) {
						int nx = i + dx[k], ny = j + dy[k];
						if (is_valid(nx, ny)&&current_board[nx][ny] == EMPTY)cnt++;
					}
				mobility[i][j] = cnt;
			}
		}
	}

	//计算双方基于kingMove的最短到达距离
	int dis1[SIZE][SIZE];
	king_bfs(dis1, current_board, color);
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (dis1[i][j]>0&&dis1[i][j] < 40) {
				score1 += mobility[i][j] * cntParameter[dis1[i][j]] / dis1[i][j];
			}
		}
	}

	int dis2[SIZE][SIZE];
	king_bfs(dis2, current_board, -color);
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (dis2[i][j] > 0 && dis2[i][j] < 40) {
				score2 += mobility[i][j] * cntParameter[dis2[i][j]] / dis2[i][j];
			}
		}
	}

	return score1 - score2;




}

/*
double w7[56] = {
	// N_empty = 0 到 9 (残局)
		0.0001, 0.0001, 0.0001, 0.0002, 0.0003, 0.0004, 0.0005, 0.0006, 0.0007, 0.0008,
		// N_empty = 10 到 19
			0.0009, 0.0010, 0.0012, 0.0014, 0.0016, 0.0018, 0.0020, 0.0022, 0.0024, 0.0026,
			// N_empty = 20 到 29
				0.0028, 0.0030, 0.0032, 0.0034, 0.0036, 0.0038, 0.0040, 0.0042, 0.0044, 0.0046,
				// N_empty = 30 到 39 (中局)
					0.0050, 0.0060, 0.0070, 0.0080, 0.0090, 0.0100, 0.0110, 0.0120, 0.0130, 0.0140,
					// N_empty = 40 到 49
						0.0150, 0.0160, 0.0170, 0.0180, 0.0185, 0.0190, 0.0192, 0.0194, 0.0196, 0.0198,
						// N_empty = 50 到 55 (开局)
							0.0200, 0.0200, 0.0200, 0.0200, 0.0200, 0.0200
};*/

//计算特征G(=所有空格的基于Queenmove的空格质量*距离权重/Queenmove距离）
double compute_valueG(int color, int current_board[SIZE][SIZE], std::vector<cordinates>pieces1, std::vector<cordinates> pieces2) {
	double score1 = 0, score2 = 0;
	int mobility[SIZE][SIZE];
	memset(mobility, 0, sizeof(mobility));

	//计算空格质量
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (current_board[i][j] == EMPTY) {
				int cnt = 0;
				for (int k = 0; k < 8; ++k) {
					for (int step = 0;; ++step) {
						int nx = i + dx[k] * step, ny = j + dy[k] * step;
						if (!is_valid(nx, ny) || current_board[nx][ny] != EMPTY)break;
						else cnt++;
					}
				}
				mobility[i][j] = cnt;
			}
		}
	}

	//找出棋子
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (current_board[i][j] == color)pieces1.push_back({ i,j });
			if (current_board[i][j] == -color)pieces2.push_back({ i,j });
		}
	}

	//分别计算Kingmove距离
	for (int i = 0; i < pieces1.size(); ++i) {
		int sx=pieces1.size(),sy=
	}


}

int main() {
	//初始化棋盘

	//输入先手
	//输入回合和初始状态
}
