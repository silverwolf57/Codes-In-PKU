#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cctype>
#include<cmath>
#include<stack>
#include<queue>
#include <fstream>
#include <cstdlib>
#include<cstring>
#include <chrono>

#define SIZE 8
#define EMPTY 0
#define BLACK 1
#define WHITE -1
#define BLOCK 2
#define MAX_DEPTH 2 // AI 搜索深度

int current_color; // 存储 AI 扮演的颜色

// 8个方向移动
const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

// --- 原始权重数据 (保持不变) ---
double w1[56] = { 0,0,0.074938141,2.113308430,1.829644322,1.657095432,1.844633341,1.709531188,1.947853684,1.597983241,1.290230632,1.167080998,0.580433190,0.053694796,-0.011891359,0.527658403,0.975054741,1.056464434,0.872889936,0.678786278,0.323303133,0.346939683,0.260094881,0.264616042,0.246926725,0.189162090,0.141057417,0.105003797,0.100303024,0.094548225,0.075991668,0.056678012,0.052921258,0.046266042,0.047984783,0.029863806,0.046501521,0.035372451,0.036930695,0.026028842,0.023727236,0.008815981,0.005980607,0.009275969,-0.003742765,-0.009044983,-0.010549444,-0.032312561,-0.012371800,-0.037411232,-0.032170087,-0.012665736,-0.025661280,0.030489521,0.038260937,-0.033962481 };
double w2[56] = { 0,0,-0.071123712,1.850196242,1.909757733,1.786974669,1.441033125,1.831614137,1.863318324,1.549122095,0.929738343,0.985552371,0.519130468,0.652193844,0.677611768,0.715636075,-0.022837769,0.100610048,-0.172568828,-0.087590173,0.244123191,0.132074401,0.141869083,0.097190522,0.033922136,0.084543742,0.094968185,0.085143305,0.066933967,0.070909552,0.083291963,0.085179411,0.069383688,0.058226194,0.060640641,0.065368392,0.054329056,0.054176800,0.042966656,0.044218585,0.038709428,0.031496748,0.023774918,0.015536518,0.010674691,0.005355561,0.008374230,0.010649841,0.012298613,0.012731116,0.006807683,0.003942049,0.000137917,-0.014996326,-0.007956794,-0.035135169 };
double w3[56] = { 0,0,0.285573512,1.067316651,-0.211924806,0.680028081,0.517808735,0.304819107,-0.360255659,0.283211440,-0.118919544,-0.320547521,-0.164136052,-0.199558660,-0.158322647,-0.134399980,-0.166122779,-0.147537082,-0.119008608,-0.115313880,-0.088800281,-0.144199789,-0.093452334,-0.098844223,-0.061869688,-0.042582039,-0.026260521,-0.000397748,-0.004830216,-0.015821418,0.015736405,0.018657653,0.027041025,0.018133903,0.027038572,0.051898617,0.024094300,0.032939505,0.027083304,0.032979585,0.024715593,0.048389383,0.051429220,0.049864184,0.065294459,0.079495110,0.070997894,0.100243673,0.052135076,0.094104849,0.087983906,0.061890475,0.079814047,-0.026632605,-0.043000557,0.082739472 };
double w4[56] = { 0,0,0.061070204,2.073594332,1.803056121,1.969837666,1.993263960,1.986328840,1.706978559,1.858220458,1.816977739,1.320441842,1.554476857,1.503799796,1.165330052,0.306896836,0.428119272,0.127804548,0.320249408,0.250915736,0.208399042,0.209280223,0.189255610,0.176422641,0.158465251,0.123073861,0.114771605,0.107638910,0.104587719,0.094095841,0.077729441,0.085181594,0.088369705,0.096417032,0.086386517,0.084225371,0.094143234,0.101544440,0.116312958,0.118276447,0.126188114,0.131197393,0.142377511,0.138548672,0.131359026,0.133364707,0.122829571,0.130566165,0.130473971,0.133546650,0.111887053,0.097306497,0.095673442,0.109085456,0.139188647,0.08377216 };
double w5[56] = { 0,0,0.107754663,-0.528144240,-1.379346251,-1.006276369,-0.825565398,-0.430609971,-0.473824382,-0.060512420,-0.942406714,-0.967272699,-0.992075503,-1.073423266,-0.858994186,-0.838604629,-0.738691866,-0.771107376,-0.667914927,-0.620147049,-0.567148566,-0.658371270,-0.578625798,-0.549303949,-0.488953888,-0.356694996,-0.272865117,-0.213500351,-0.175519645,-0.133494422,-0.070355214,-0.038640279,-0.043525659,-0.037141897,-0.031321511,-0.023366986,-0.021908367,-0.013590249,-0.019244174,-0.014974004,-0.009036653,-0.018890575,-0.004873865,-0.017690081,-0.012989196,-0.020389291,-0.031792857,-0.031873308,-0.028690575,-0.024877874,-0.033742540,-0.026430298,-0.027800240,-0.030750951,-0.021546466,-0.037860770 };
double w6[56] = { 0,0,0.013333333, 0.026666667, 0.040000000, 0.053333333,0.066666667, 0.080000000, 0.093333333, 0.106666667,0.120000000, 0.136000000, 0.152000000, 0.168000000, 0.184000000, 0.200000000,0.216000000, 0.232000000, 0.248000000, 0.264000000,0.280000000, 0.296000000, 0.312000000, 0.328000000, 0.344000000, 0.360000000,0.376000000, 0.392000000, 0.408000000, 0.424000000,0.440000000, 0.456000000, 0.472000000, 0.488000000, 0.504000000, 0.520000000,0.536000000, 0.552000000, 0.568000000, 0.584000000,0.600000000, 0.600000000, 0.600000000, 0.600000000, 0.600000000, 0.600000000,0.600000000, 0.600000000, 0.600000000, 0.600000000,0.600000000, 0.600000000, 0.600000000, 0.600000000, 0.600000000, 0.600000000 };
double w7[56] = { 0,0,-4.567995548,-3.716784000,-3.381752491,-2.938109636,-3.290686846,-2.702058077,-2.855453491,-2.595350504,-2.005551338,-1.637469649,-1.272953510,-1.047218084,-0.879562616,-0.746166408,-0.717715025,-0.592138231,-0.504874051,-0.366238832,-0.404548317,-0.305050164,-0.272765279,-0.249806121,-0.137687027,-0.254965365,-0.089192919,-0.171341106,-0.076427318,-0.220489189,-0.091823421,-0.180632398,-0.106192604,-0.145687878,-0.073370934,-0.149500415,-0.069663063,-0.189439490,-0.027017180,-0.123841494,-0.011969413,-0.017853998,0.068564072,0.002616666,0.172109649,0.157967970,0.158981338,0.351862490,0.168605193,0.400329232,0.361347109,0.220473915,0.434309691,-0.030947627,-0.074839503,0.44456172 };

// --- 内部评估参数 (保持不变) ---
const double depthParameter[7] = { 0.0, 1.0, 0.5, 0.25, 0.125, 0.0625, 0.03125 };
const double cntParameter1[40] = { 0.0, 1.0, 0.95, 0.9, 0.8, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
const double cntParameter2[40] = { 0.0, 1.00, 0.90, 0.70, 0.40, 0.20, 0.10, 0.05, 0.01,0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01, 0.01, };


// --- 基础数据结构 (保持不变) ---

struct cordinates {
	int x;
	int y;
};

struct move {
	int x0, y0, x1, y1, x2, y2; // 移动前的坐标, 移动后的坐标, 障碍物坐标
};

struct RatedMove {
	move m;
	double value;
};


// --- 基本函数 (保持不变) ---

bool is_valid(int x, int y) {
	return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

void apply_move(int current_board[SIZE][SIZE], move m, int color) {
	if (!is_valid(m.x0, m.y0) || current_board[m.x0][m.y0] != color) return;
	current_board[m.x0][m.y0] = EMPTY;
	current_board[m.x1][m.y1] = color;
	current_board[m.x2][m.y2] = BLOCK;
}

void undo_move(int current_board[SIZE][SIZE], move m, int color) {
	current_board[m.x0][m.y0] = color;
	current_board[m.x1][m.y1] = EMPTY;
	current_board[m.x2][m.y2] = EMPTY;
}

std::vector<move> find_move(int current_board[SIZE][SIZE], int color) {
	std::vector<move> possible_ways;
	std::vector<cordinates> pieces;

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (current_board[i][j] == color) {
				pieces.push_back({ i, j });
			}
		}
	}

	int size = pieces.size();
	for (int i = 0; i < size; ++i) {
		int sx = pieces[i].x, sy = pieces[i].y;

		for (int j = 0; j < 8; ++j) {
			for (int step1 = 1; ; ++step1) {
				int ex = sx + dx[j] * step1, ey = sy + dy[j] * step1;

				if (!is_valid(ex, ey) || current_board[ex][ey] != EMPTY) {
					break;
				}

				for (int p = 0; p < 8; ++p) {
					for (int step2 = 1; ; ++step2) {
						int bx = ex + dx[p] * step2, by = ey + dy[p] * step2;

						if (!is_valid(bx, by)) {
							break;
						}

						int cell_state = current_board[bx][by];

						if (cell_state != EMPTY) {
							if (bx == sx && by == sy) {
								possible_ways.push_back({ sx, sy, ex, ey, bx, by });
							}
							break;
						}

						possible_ways.push_back({ sx, sy, ex, ey, bx, by });
					}
				}
			}
		}
	}
	return possible_ways;
}


// --- BFS / 评估函数辅助 / 评估函数 (保持不变) ---
// (省略 King/Queen BFS 和 Evaluate 函数，以保持简洁，它们与上一个版本相同)

void king_bfs(int dis[SIZE][SIZE], int current_board[SIZE][SIZE], int color) {
	std::queue<cordinates> piece;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			dis[i][j] = 1000;
		}
	}
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (current_board[i][j] == color) {
				dis[i][j] = 0;
				piece.push({ i,j });
			}
		}
	}
	while (!piece.empty()) {
		cordinates curr = piece.front();
		piece.pop();
		int d = dis[curr.x][curr.y];
		if (d > 40) continue;
		for (int i = 0; i < 8; ++i) {
			int nx = curr.x + dx[i], ny = curr.y + dy[i];
			if (is_valid(nx, ny) && current_board[nx][ny] == EMPTY) {
				if (dis[nx][ny] > d + 1) {
					dis[nx][ny] = d + 1;
					piece.push({ nx,ny });
				}
			}
		}
	}
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (dis[i][j] == 1000) {
				dis[i][j] = -1;
			}
		}
	}
}

void queen_bfs(int dis[SIZE][SIZE], int current_board[SIZE][SIZE], int color) {
	std::queue<cordinates> piece;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			dis[i][j] = 1000;
		}
	}
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (current_board[i][j] == color) {
				dis[i][j] = 0;
				piece.push({ i,j });
			}
		}
	}
	while (!piece.empty()) {
		cordinates curr = piece.front();
		piece.pop();
		int d = dis[curr.x][curr.y];
		if (d >= 40) continue;
		for (int dir = 0; dir < 8; ++dir) {
			for (int step = 1; ; ++step) {
				int nx = curr.x + dx[dir] * step;
				int ny = curr.y + dy[dir] * step;
				if (!is_valid(nx, ny) || current_board[nx][ny] != EMPTY) {
					break;
				}
				if (dis[nx][ny] > d + 1) {
					dis[nx][ny] = d + 1;
					piece.push({ nx, ny });
				}
				else if (dis[nx][ny] < d + 1) {
					break;
				}
			}
		}
	}
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (dis[i][j] == 1000) dis[i][j] = -1;
		}
	}
}

double compute_valueE(int color, int current_board[SIZE][SIZE]) {
	double score1 = 0.0, score2 = 0.0;
	int mobility[SIZE][SIZE];
	memset(mobility, 0, sizeof(mobility));
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (current_board[i][j] == EMPTY) {
				int cnt = 0;
				for (int k = 0; k < 8; ++k) {
					int nx = i + dx[k], ny = j + dy[k];
					if (is_valid(nx, ny) && current_board[nx][ny] == EMPTY)cnt++;
				}
				mobility[i][j] = cnt;
			}
		}
	}
	int dis1[SIZE][SIZE];
	king_bfs(dis1, current_board, color);
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (dis1[i][j] > 0 && dis1[i][j] < 40) {
				score1 += mobility[i][j] * cntParameter1[dis1[i][j]] / dis1[i][j];
			}
		}
	}
	int dis2[SIZE][SIZE];
	king_bfs(dis2, current_board, -color);
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (dis2[i][j] > 0 && dis2[i][j] < 40) {
				score2 += mobility[i][j] * cntParameter1[dis2[i][j]] / dis2[i][j];
			}
		}
	}
	return score1 - score2;
}

double compute_valueF(int color, int current_board[SIZE][SIZE]) {
	double score1 = 0.0, score2 = 0.0;
	int mobility[SIZE][SIZE];
	memset(mobility, 0, sizeof(mobility));
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (current_board[i][j] == EMPTY) {
				int cnt = 0;
				for (int k = 0; k < 8; ++k) {
					for (int step = 1;; ++step) {
						int nx = i + dx[k] * step, ny = j + dy[k] * step;
						if (!is_valid(nx, ny) || current_board[nx][ny] != EMPTY)break;
						else cnt++;
					}
				}
				mobility[i][j] = cnt;
			}
		}
	}
	int dis1[SIZE][SIZE];
	queen_bfs(dis1, current_board, color);
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (dis1[i][j] > 0 && dis1[i][j] < 40) {
				score1 += mobility[i][j] * cntParameter2[dis1[i][j]] / dis1[i][j];
			}
		}
	}
	int dis2[SIZE][SIZE];
	queen_bfs(dis2, current_board, -color);
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (dis2[i][j] > 0 && dis2[i][j] < 40) {
				score2 += mobility[i][j] * cntParameter2[dis2[i][j]] / dis2[i][j];
			}
		}
	}
	return score1 - score2;
}


double evaluate(int current_board[SIZE][SIZE], int color) {

	int blank_cnt = 0;
	std::vector<cordinates> piece1, piece2;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (current_board[i][j] == EMPTY) {
				blank_cnt++;
			}
			else if (current_board[i][j] == color) {
				piece1.push_back({ i,j });
			}
			else if (current_board[i][j] == -color) {
				piece2.push_back({ i,j });
			}
		}
	}
	if (blank_cnt == 0)return 0.5;

	int king_dis1[SIZE][SIZE], king_dis2[SIZE][SIZE];
	int queen_dis1[SIZE][SIZE], queen_dis2[SIZE][SIZE];

	king_bfs(king_dis1, current_board, color);
	king_bfs(king_dis2, current_board, -color);
	queen_bfs(queen_dis1, current_board, color);
	queen_bfs(queen_dis2, current_board, -color);

	double a = 0.0, b = 0.0, c = 0.0, d = 0.0;

	double score12 = 0.0, score22 = 0.0;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (queen_dis1[i][j] > 0 && queen_dis1[i][j] < 40 && queen_dis2[i][j] < 0) {
				score12 += cntParameter1[queen_dis1[i][j]] / (double)queen_dis1[i][j];
			}
			else if (queen_dis1[i][j] < 0 && queen_dis2[i][j]>0 && queen_dis2[i][j] < 40) {
				score22 += cntParameter1[queen_dis2[i][j]] / (double)queen_dis2[i][j];
			}
			else if (queen_dis1[i][j] > 0 && queen_dis2[i][j] > 0) {
				if (queen_dis1[i][j] > queen_dis2[i][j]) {
					score22 += cntParameter1[queen_dis2[i][j]] / (double)queen_dis2[i][j];
				}
				else if (queen_dis1[i][j] < queen_dis2[i][j]) {
					score12 += cntParameter1[queen_dis1[i][j]] / (double)queen_dis1[i][j];
				}
			}
		}
	}
	a = score12 - score22;

	double score32 = 0.0, score42 = 0.0;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (king_dis1[i][j] > 0 && king_dis1[i][j] < 40 && king_dis2[i][j] < 0) {
				score32 += cntParameter1[king_dis1[i][j]] / (double)king_dis1[i][j];
			}
			else if (king_dis1[i][j] < 0 && king_dis2[i][j]>0 && king_dis2[i][j] < 40) {
				score42 += cntParameter1[king_dis2[i][j]] / (double)king_dis2[i][j];
			}
			else if (king_dis1[i][j] > 0 && king_dis2[i][j] > 0) {
				if (king_dis1[i][j] > king_dis2[i][j]) {
					score42 += cntParameter1[king_dis2[i][j]] / (double)king_dis2[i][j];
				}
				else if (king_dis1[i][j] < king_dis2[i][j]) {
					score32 += cntParameter1[king_dis1[i][j]] / (double)king_dis1[i][j];
				}
			}
		}
	}
	b = score32 - score42;

	std::vector<int> p1_reachable(7, 0), p2_reachable(7, 0);
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (queen_dis1[i][j] > 0 && queen_dis1[i][j] < 7)p1_reachable[queen_dis1[i][j]]++;
			if (queen_dis2[i][j] > 0 && queen_dis2[i][j] < 7)p2_reachable[queen_dis2[i][j]]++;
		}
	}
	for (int i = 1; i <= 6; ++i) {
		c += p1_reachable[i] * depthParameter[i];
		c -= p2_reachable[i] * depthParameter[i];
	}

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (king_dis1[i][j] > 0 && king_dis2[i][j] < 0)d += 1.0;
			if (king_dis2[i][j] > 0 && king_dis1[i][j] < 0)d -= 1.0;
		}
	}

	double E = compute_valueE(color, current_board);
	double e = E * 0.1;

	double F = compute_valueF(color, current_board);
	double f = F * 0.1;

	int index = std::min(blank_cnt, 55);
	double p1, p2, p3, p4, p5, p6, p7;
	p1 = w1[index];
	p2 = w2[index];
	p3 = w3[index];
	p4 = w4[index];
	p5 = w5[index];
	p6 = w6[index];
	p7 = w7[index];

	double score = a * p1 + b * p2 + c * p3 + d * p4 + e * p5 + f * p6 + p7;

	return 1.0 / (1.0 + exp(-score));
}


// --- AlphaBeta 算法 (保持不变) ---

double alphaBeta(int current_board[SIZE][SIZE], int depth, int player, double alpha, double beta) {
	if (depth == 0) {
		double eval = evaluate(current_board, current_color);
		return (player == current_color) ? eval : (1.0 - eval);
	}

	std::vector<move> possible_move = find_move(current_board, player);

	if (possible_move.empty()) {
		return (player == current_color) ? 0.0 : 1.0;
	}

	int size = possible_move.size();

	if (player == current_color) { // Max Player
		double max_value = -1e9;
		for (int i = 0; i < size; ++i) {
			apply_move(current_board, possible_move[i], current_color);
			double value = alphaBeta(current_board, depth - 1, -player, alpha, beta);
			undo_move(current_board, possible_move[i], current_color);

			max_value = std::max(max_value, value);
			alpha = std::max(alpha, max_value);

			if (beta <= alpha) break;
		}
		return max_value;

	}
	else { // Min Player
		double min_value = 1e9;
		for (int i = 0; i < size; ++i) {
			apply_move(current_board, possible_move[i], -current_color);
			double value = alphaBeta(current_board, depth - 1, -player, alpha, beta);
			undo_move(current_board, possible_move[i], -current_color);

			min_value = std::min(min_value, value);
			beta = std::min(beta, min_value);

			if (beta <= alpha) break;
		}
		return min_value;
	}
}

// --- 新增 / 修改的交互函数 ---

void initialize_board(int board[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			board[i][j] = EMPTY;
		}
	}
	// 初始布局
	board[0][2] = BLACK; board[2][0] = BLACK; board[5][0] = BLACK; board[7][2] = BLACK;
	board[0][5] = WHITE; board[2][7] = WHITE; board[5][7] = WHITE; board[7][5] = WHITE;
}

// 刷新清屏函数
void clear_screen() {
#ifdef _WIN32
	system("cls"); // Windows
#else
	system("clear"); // Linux / macOS
#endif
}

// 绘制棋盘 (使用制表符)
void print_board(const int board[SIZE][SIZE], int ai_color) {
	clear_screen(); // 每次绘制前清屏

	std::cout << "\n=================================================" << std::endl;
	std::cout << "        亚马逊棋 (Amazonas) 人机对弈 " << std::endl;
	std::cout << "=================================================" << std::endl;
	std::cout << "当前 AI 执: " << (ai_color == BLACK ? "B (BLACK)" : "W (WHITE)") << std::endl;
	std::cout << "人员执: \t" << (ai_color == BLACK ? "W (WHITE)" : "B (BLACK)") << std::endl;
	std::cout << "符号: B=黑棋\tW=白棋\t#=障碍\t. (或空格)=空位" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;

	// 打印列索引
	std::cout << "行\\列\t";
	for (int j = 0; j < SIZE; ++j) {
		std::cout << j << "\t";
	}
	std::cout << "\n";

	for (int i = 0; i < SIZE; ++i) {
		// 打印行索引
		std::cout << i << "\t";
		for (int j = 0; j < SIZE; ++j) {
			char symbol;
			if (board[i][j] == BLACK) symbol = 'B';
			else if (board[i][j] == WHITE) symbol = 'W';
			else if (board[i][j] == BLOCK) symbol = '#';
			else symbol = ' '; // 使用空格或点号表示空位
			std::cout << symbol << "\t"; // 使用制表符分隔
		}
		std::cout << std::endl;
	}
	std::cout << "-------------------------------------------------\n" << std::endl;
}

// 保存游戏状态
void save_game(const int current_board[SIZE][SIZE], int ai_color, int turn_id) {
	std::ofstream outfile("amazonas_save.txt");
	if (!outfile.is_open()) {
		std::cerr << "Error: 无法打开文件进行存盘。" << std::endl;
		return;
	}

	outfile << ai_color << std::endl;
	outfile << turn_id << std::endl;

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			outfile << current_board[i][j] << " ";
		}
		outfile << std::endl;
	}
	std::cout << " 游戏状态已成功保存到 amazonas_save.txt" << std::endl;
	outfile.close();
}

// 读取游戏状态
bool load_game(int current_board[SIZE][SIZE], int& ai_color, int& turn_id) {
	std::ifstream infile("amazonas_save.txt");
	if (!infile.is_open()) {
		std::cerr << "Error: 无法打开 amazonas_save.txt 文件。请先确保已存盘。" << std::endl;
		return false;
	}

	if (!(infile >> ai_color >> turn_id)) {
		std::cerr << "Error: 存盘文件格式错误。" << std::endl;
		infile.close();
		return false;
	}

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (!(infile >> current_board[i][j])) {
				std::cerr << "Error: 存盘文件棋盘数据不完整。" << std::endl;
				infile.close();
				return false;
			}
		}
	}
	std::cout << " 游戏状态已成功读取。AI 执 " << (ai_color == BLACK ? "BLACK" : "WHITE") << std::endl;
	infile.close();
	return true;
}

// 检查输入是否是 Queen Move
bool is_queen_move(int x0, int y0, int x1, int y1) {
	if (x0 == x1 && y0 == y1) return false; // 必须移动
	int dx_abs = std::abs(x1 - x0);
	int dy_abs = std::abs(y1 - y0);
	return dx_abs == 0 || dy_abs == 0 || dx_abs == dy_abs; // 横、竖、对角线
}

// 检查路径上是否有阻碍
bool is_path_clear(const int board[SIZE][SIZE], int x0, int y0, int x1, int y1) {
	if (!is_queen_move(x0, y0, x1, y1)) return false;

	int dx_dir = (x1 > x0) ? 1 : ((x1 < x0) ? -1 : 0);
	int dy_dir = (y1 > y0) ? 1 : ((y1 < y0) ? -1 : 0);

	int cx = x0 + dx_dir;
	int cy = y0 + dy_dir;

	while (cx != x1 || cy != y1) {
		if (board[cx][cy] != EMPTY) return false;
		cx += dx_dir;
		cy += dy_dir;
	}
	return true;
}


// 处理人员落子逻辑
bool get_and_apply_player_move(int board[SIZE][SIZE], int player_color) {
	int x0, y0, x1, y1, x2, y2;
	std::cout << "\n请 (行, 列) 输入您的走法 (x0 y0 x1 y1 x2 y2): ";

	if (!(std::cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2)) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "输入格式错误。请重新尝试。" << std::endl;
		return false;
	}

	// 1. 基本坐标和棋子校验
	if (!is_valid(x0, y0) || !is_valid(x1, y1) || !is_valid(x2, y2)) {
		std::cout << " 错误：坐标超出棋盘范围(0-7)。" << std::endl;
		return false;
	}
	if (board[x0][y0] != player_color) {
		std::cout << " 错误：(x0, y0) 处不是您的棋子 (" << (player_color == BLACK ? 'B' : 'W') << ")。" << std::endl;
		return false;
	}
	if (board[x1][y1] != EMPTY) {
		std::cout << " 错误：(x1, y1) 处目标位置不是空位。" << std::endl;
		return false;
	}
	if (board[x2][y2] != EMPTY && !(x2 == x0 && y2 == y0)) {
		std::cout << " 错误：(x2, y2) 障碍物位置非空且不是原棋子位置。" << std::endl;
		return false;
	}

	// 2. 移动路径校验
	if (!is_path_clear(board, x0, y0, x1, y1)) {
		std::cout << " 错误：(x0, y0) 到 (x1, y1) 的移动不符合 Queen Move 规则或路径被阻挡。" << std::endl;
		return false;
	}

	// 3. 障碍物放置路径校验 (临时应用移动，检查障碍物)
	move temp_move = { x0, y0, x1, y1, -1, -1 }; // 仅移动棋子
	int temp_board[SIZE][SIZE];
	memcpy(temp_board, board, sizeof(temp_board));

	// 临时应用棋子移动
	temp_board[x0][y0] = EMPTY;
	temp_board[x1][y1] = player_color;

	// 检查障碍物放置是否合法
	if (is_valid(x2, y2) && (board[x2][y2] == EMPTY || (x2 == x0 && y2 == y0))) {

		// 障碍物必须是 Queen Move 距离
		if (!is_queen_move(x1, y1, x2, y2)) {
			std::cout << " 错误：(x1, y1) 到 (x2, y2) 的障碍物放置不符合 Queen Move 规则。" << std::endl;
			return false;
		}

		// 障碍物路径必须清空 (除了原棋子位置 (x0, y0))
		int dx_dir = (x2 > x1) ? 1 : ((x2 < x1) ? -1 : 0);
		int dy_dir = (y2 > y1) ? 1 : ((y2 < y1) ? -1 : 0);

		int cx = x1 + dx_dir;
		int cy = y1 + dy_dir;

		while (cx != x2 || cy != y2) {
			// 检查路径上的点在原棋盘上是否是空位
			if (board[cx][cy] != EMPTY) {
				std::cout << " 错误：障碍物放置路径被阻挡 (经过: " << cx << ", " << cy << ")。" << std::endl;
				return false;
			}
			cx += dx_dir;
			cy += dy_dir;
		}

	}

	// 4. 最终应用走法
	move player_move = { x0, y0, x1, y1, x2, y2 };
	apply_move(board, player_move, player_color);
	std::cout << "人员走法已应用：(" << x0 << ", " << y0 << ") -> (" << x1 << ", " << y1 << "), 障碍物于 (" << x2 << ", " << y2 << ")" << std::endl;
	return true;
}


// --- 主函数 (实现菜单逻辑) ---

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int board[SIZE][SIZE] = {};
	int ai_color = EMPTY;
	int turnID = 0;
	bool game_started = false;

	clear_screen(); // 初始清屏
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "       亚马逊棋 (Amazonas) 人机对弈       " << std::endl;
	std::cout << "------------------------------------------" << std::endl;

	while (true) {
		// 在菜单循环开始时进行清屏，保证每次都是干净的菜单
		if (game_started) {
			print_board(board, ai_color);
		}
		else {
			clear_screen();
		}

		std::cout << "\n==========================================" << std::endl;
		std::cout << "回合ID: " << turnID << " | AI 执: " << (ai_color == BLACK ? "BLACK" : (ai_color == WHITE ? "WHITE" : "未开始")) << std::endl;
		std::cout << "--- 菜单 ---" << std::endl;
		std::cout << "1. 新开始 (New Game)" << std::endl;
		std::cout << "2. 读盘 (Load Game / 复盘)" << std::endl;
		std::cout << "3. 选择 (Make Move - 人员走一步，AI 自动走一步)" << std::endl;
		std::cout << "4. 存盘 (Save Game)" << std::endl;
		std::cout << "5. 结束 (Exit / 中途停止)" << std::endl;
		std::cout << "请输入您的选择 (1-5): ";

		int choice;
		if (!(std::cin >> choice)) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			clear_screen();
			std::cout << "输入无效，请重新输入。" << std::endl;
			continue;
		}

		if (choice == 5) {
			clear_screen();
			std::cout << "游戏结束，再见！" << std::endl;
			break;
		}

		switch (choice) {
		case 1: { // 新开始
			initialize_board(board);
			std::cout << "请选择您的颜色 (1 for BLACK, -1 for WHITE): ";
			int color_choice;
			if (!(std::cin >> color_choice) || (color_choice != BLACK && color_choice != WHITE)) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "颜色选择无效，默认为 WHITE。" << std::endl;
				ai_color = WHITE;
			}
			else {
				ai_color = color_choice;
			}
			current_color = ai_color;
			turnID = 1;
			game_started = true;

			print_board(board, ai_color);
			std::cout << "新游戏开始！AI 执 " << (ai_color == BLACK ? "BLACK" : "WHITE") << "，人员执 " << (ai_color == BLACK ? "WHITE" : "BLACK") << std::endl;

			if (ai_color == BLACK) {
				std::cout << "AI 执黑，第一步由 AI 走。正在计算..." << std::endl;
				// AI 的开局走法 
				move first_move = { 2, 0, 2, 6, 5, 6 }; // 开局走法
				apply_move(board, first_move, BLACK);
				std::cout << " AI 走法: 2 0 2 6 5 6" << std::endl;
				turnID++;
				print_board(board, ai_color);
			}

			break;
		}
		case 2: { // 读盘
			clear_screen();
			if (load_game(board, ai_color, turnID)) {
				current_color = ai_color;
				game_started = true;
				print_board(board, ai_color);
			}
			break;
		}
		case 3: { // 选择 (人走一步，AI 走一步)
			if (!game_started) {
				clear_screen();
				std::cout << "请先开始新游戏或读盘！" << std::endl;
				break;
			}

			int player_color = -ai_color;

			// --- 1. 人员走法 ---
			bool player_move_ok = get_and_apply_player_move(board, player_color);
			if (!player_move_ok) {
				// 走法无效时，不进行后续 AI 走法，重新回到菜单
				std::cout << "人员走法失败，请重新在菜单中选择 3 并输入正确的走法。" << std::endl;
				// 防止清屏太快，让用户看到错误信息
				std::cin.ignore(10000, '\n');
				std::cout << "按回车键继续..." << std::endl;
				std::cin.get();
				break;
			}

			// 检查人员走完后 AI 是否还有走法
			std::vector<move> ai_legal_moves_check = find_move(board, ai_color);
			if (ai_legal_moves_check.empty()) {
				print_board(board, ai_color);
				std::cout << "\n==========================================" << std::endl;
				std::cout << "🏆 AI (" << (ai_color == BLACK ? "BLACK" : "WHITE") << ") 无子可走，人员获胜！" << std::endl;
				std::cout << "==========================================" << std::endl;
				game_started = false;
				break;
			}

			// --- 2. AI 计算最佳走法 ---
			std::cout << "\nAI 正在计算最佳走法... (深度: " << MAX_DEPTH << ")" << std::endl;

			// Move Ordering 和 Alpha-Beta 搜索 (逻辑与前一版相同)
			std::vector<RatedMove> rated_moves;
			for (const auto& m : ai_legal_moves_check) {
				apply_move(board, m, ai_color);
				double eval_score = evaluate(board, ai_color);
				undo_move(board, m, ai_color);
				rated_moves.push_back({ m, eval_score });
			}
			std::sort(rated_moves.begin(), rated_moves.end(), [](const RatedMove& a, const RatedMove& b) {
				return a.value > b.value;
				});

			move best_move = rated_moves[0].m;
			double best_val = -1e9;
			int size = rated_moves.size();

			for (int i = 0; i < size; ++i) {
				const move& current_move = rated_moves[i].m;
				apply_move(board, current_move, ai_color);
				double eval = alphaBeta(board, MAX_DEPTH - 1, -ai_color, best_val, 1e9);
				undo_move(board, current_move, ai_color);

				if (eval > best_val) {
					best_val = eval;
					best_move = current_move;
				}
			}

			// --- 3. 应用并输出 AI 走法 ---
			apply_move(board, best_move, ai_color);
			turnID++;
			print_board(board, ai_color);
			std::cout << "\n AI 走法 (x0 y0 x1 y1 x2 y2): ";
			std::cout << best_move.x0 << " " << best_move.y0 << " " << best_move.x1 << " " << best_move.y1 << " " << best_move.x2 << " " << best_move.y2 << std::endl;
			std::cout << "AI 评估分数 (Sigmoid): " << best_val << std::endl;

			// 4. 检查 AI 走完后人员是否还有走法
			std::vector<move> player_moves_check = find_move(board, player_color);
			if (player_moves_check.empty()) {
				std::cout << "\n==========================================" << std::endl;
				std::cout << " 人员 (" << (player_color == BLACK ? "BLACK" : "WHITE") << ") 无子可走，AI 获胜！" << std::endl;
				std::cout << "==========================================" << std::endl;
				game_started = false;
			}

			break;
		}
		case 4: { // 存盘
			clear_screen();
			if (game_started) {
				save_game(board, ai_color, turnID);
			}
			else {
				std::cout << "未开始游戏，无法存盘。" << std::endl;
			}
			break;
		}
		default: {
			clear_screen();
			std::cout << "无效选项，请重新输入。" << std::endl;
			break;
		}
		}
	}
	return 0;
}
