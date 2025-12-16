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
#define MAX_DEPTH 2 // AI Search Depth

int current_color; // Stores the color the AI is playing

// 8 directions for movement
const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

// --- Original Weight Data (Unchanged) ---
double w1[56] = { 0,0,0.074938141,2.113308430,1.829644322,1.657095432,1.844633341,1.709531188,1.947853684,1.597983241,1.290230632,1.167080998,0.580433190,0.053694796,-0.011891359,0.527658403,0.975054741,1.056464434,0.872889936,0.678786278,0.323303133,0.346939683,0.260094881,0.264616042,0.246926725,0.189162090,0.141057417,0.105003797,0.100303024,0.094548225,0.075991668,0.056678012,0.052921258,0.046266042,0.047984783,0.029863806,0.046501521,0.035372451,0.036930695,0.026028842,0.023727236,0.008815981,0.005980607,0.009275969,-0.003742765,-0.009044983,-0.010549444,-0.032312561,-0.012371800,-0.037411232,-0.032170087,-0.012665736,-0.025661280,0.030489521,0.038260937,-0.033962481 };
double w2[56] = { 0,0,-0.071123712,1.850196242,1.909757733,1.786974669,1.441033125,1.831614137,1.863318324,1.549122095,0.929738343,0.985552371,0.519130468,0.652193844,0.677611768,0.715636075,-0.022837769,0.100610048,-0.172568828,-0.087590173,0.244123191,0.132074401,0.141869083,0.097190522,0.033922136,0.084543742,0.094968185,0.085143305,0.066933967,0.070909552,0.083291963,0.085179411,0.069383688,0.058226194,0.060640641,0.065368392,0.054329056,0.054176800,0.042966656,0.044218585,0.038709428,0.031496748,0.023774918,0.015536518,0.010674691,0.005355561,0.008374230,0.010649841,0.012298613,0.012731116,0.006807683,0.003942049,0.000137917,-0.014996326,-0.007956794,-0.035135169 };
double w3[56] = { 0,0,0.285573512,1.067316651,-0.211924806,0.680028081,0.517808735,0.304819107,-0.360255659,0.283211440,-0.118919544,-0.320547521,-0.164136052,-0.199558660,-0.158322647,-0.134399980,-0.166122779,-0.147537082,-0.119008608,-0.115313880,-0.088800281,-0.144199789,-0.093452334,-0.098844223,-0.061869688,-0.042582039,-0.026260521,-0.000397748,-0.004830216,-0.015821418,0.015736405,0.018657653,0.027041025,0.018133903,0.027038572,0.051898617,0.024094300,0.032939505,0.027083304,0.032979585,0.024715593,0.048389383,0.051429220,0.049864184,0.065294459,0.079495110,0.070997894,0.100243673,0.052135076,0.094104849,0.087983906,0.061890475,0.079814047,-0.026632605,-0.043000557,0.082739472 };
double w4[56] = { 0,0,0.061070204,2.073594332,1.803056121,1.969837666,1.993263960,1.986328840,1.706978559,1.858220458,1.816977739,1.320441842,1.554476857,1.503799796,1.165330052,0.306896836,0.428119272,0.127804548,0.320249408,0.250915736,0.208399042,0.209280223,0.189255610,0.176422641,0.158465251,0.123073861,0.114771605,0.107638910,0.104587719,0.094095841,0.077729441,0.085181594,0.088369705,0.096417032,0.086386517,0.084225371,0.094143234,0.101544440,0.116312958,0.118276447,0.126188114,0.131197393,0.142377511,0.138548672,0.131359026,0.133364707,0.122829571,0.130566165,0.130473971,0.133546650,0.111887053,0.097306497,0.095673442,0.109085456,0.139188647,0.08377216 };
double w5[56] = { 0,0,0.107754663,-0.528144240,-1.379346251,-1.006276369,-0.825565398,-0.430609971,-0.473824382,-0.060512420,-0.942406714,-0.967272699,-0.992075503,-1.073423266,-0.858994186,-0.838604629,-0.738691866,-0.771107376,-0.667914927,-0.620147049,-0.567148566,-0.658371270,-0.578625798,-0.549303949,-0.488953888,-0.356694996,-0.272865117,-0.213500351,-0.175519645,-0.133494422,-0.070355214,-0.038640279,-0.043525659,-0.037141897,-0.031321511,-0.023366986,-0.021908367,-0.013590249,-0.019244174,-0.014974004,-0.009036653,-0.018890575,-0.004873865,-0.017690081,-0.012989196,-0.020389291,-0.031792857,-0.031873308,-0.028690575,-0.024877874,-0.033742540,-0.026430298,-0.027800240,-0.030750951,-0.021546466,-0.037860770 };
double w6[56] = { 0,0,0.013333333, 0.026666667, 0.040000000, 0.053333333,0.066666667, 0.080000000, 0.093333333, 0.106666667,0.120000000, 0.136000000, 0.152000000, 0.168000000, 0.184000000, 0.200000000,0.216000000, 0.232000000, 0.248000000, 0.264000000,0.280000000, 0.296000000, 0.312000000, 0.328000000, 0.344000000, 0.360000000,0.376000000, 0.392000000, 0.408000000, 0.424000000,0.440000000, 0.456000000, 0.472000000, 0.488000000, 0.504000000, 0.520000000,0.536000000, 0.552000000, 0.568000000, 0.584000000,0.600000000, 0.600000000, 0.600000000, 0.600000000, 0.600000000, 0.600000000,0.600000000, 0.600000000, 0.600000000, 0.600000000,0.600000000, 0.600000000, 0.600000000, 0.600000000, 0.600000000, 0.600000000 };
double w7[56] = { 0,0,-4.567995548,-3.716784000,-3.381752491,-2.938109636,-3.290686846,-2.702058077,-2.855453491,-2.595350504,-2.005551338,-1.637469649,-1.272953510,-1.047218084,-0.879562616,-0.746166408,-0.717715025,-0.592138231,-0.504874051,-0.366238832,-0.404548317,-0.305050164,-0.272765279,-0.249806121,-0.137687027,-0.254965365,-0.089192919,-0.171341106,-0.076427318,-0.220489189,-0.091823421,-0.180632398,-0.106192604,-0.145687878,-0.073370934,-0.149500415,-0.069663063,-0.189439490,-0.027017180,-0.123841494,-0.011969413,-0.017853998,0.068564072,0.002616666,0.172109649,0.157967970,0.158981338,0.351862490,0.168605193,0.400329232,0.361347109,0.220473915,0.434309691,-0.030947627,-0.074839503,0.44456172 };

// --- Internal Evaluation Parameters (Unchanged) ---
const double depthParameter[7] = { 0.0, 1.0, 0.5, 0.25, 0.125, 0.0625, 0.03125 };
const double cntParameter1[40] = { 0.0, 1.0, 0.95, 0.9, 0.8, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
const double cntParameter2[40] = { 0.0, 1.00, 0.90, 0.70, 0.40, 0.20, 0.10, 0.05, 0.01,0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01, 0.01, };


// --- Basic Data Structures (Unchanged) ---

struct cordinates {
	int x;
	int y;
};

struct move {
	int x0, y0, x1, y1, x2, y2; // Start coord, End coord, Block coord
};

struct RatedMove {
	move m;
	double value;
};


// --- Basic Functions (Unchanged) ---

bool is_valid(int x, int y) {
	return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

void apply_move(int current_board[SIZE][SIZE], move m, int color) {
	// Guard clause: ensures the piece is where it should be before moving
	if (!is_valid(m.x0, m.y0) || current_board[m.x0][m.y0] != color) return;

	// 1. Clear start
	current_board[m.x0][m.y0] = EMPTY;

	// 2. Move Queen to destination
	current_board[m.x1][m.y1] = color;

	// 3. Place block at arrow destination. (This is the operation that was potentially overwriting the Queen if validation failed)
	current_board[m.x2][m.y2] = BLOCK;
}

void undo_move(int current_board[SIZE][SIZE], move m, int color) {
	current_board[m.x1][m.y1] = EMPTY;

	// 如果箭射在起点，不要二次清空
	if (!(m.x2 == m.x0 && m.y2 == m.y0)) {
		current_board[m.x2][m.y2] = EMPTY;
	}

	current_board[m.x0][m.y0] = color;
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


// --- BFS / Evaluation Helper Functions (Unchanged) ---

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


// --- AlphaBeta Algorithm (Unchanged) ---

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

// --- Interface Functions (Optimized for ASCII) ---

void initialize_board(int board[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			board[i][j] = EMPTY;
		}
	}
	// Initial placement of Queens
	board[0][2] = BLACK; board[2][0] = BLACK; board[5][0] = BLACK; board[7][2] = BLACK;
	board[0][5] = WHITE; board[2][7] = WHITE; board[5][7] = WHITE; board[7][5] = WHITE;
}

// Simple clear screen simulation for terminal-like experience
void clear_screen() {
	// Note: system("cls") or system("clear") might not work in all environments,
	// using a large number of newlines as a fallback.
	for (int i = 0; i < 50; ++i) {
		std::cout << "\n";
	}
}

// Draw the board (using ASCII)
void print_board(const int board[SIZE][SIZE], int ai_color) {
	clear_screen();

	std::cout << "\n=================================================" << std::endl;
	std::cout << "          AMAZONAS AI VS HUMAN (8x8)           " << std::endl;
	std::cout << "=================================================" << std::endl;
	std::cout << "AI Color:  " << (ai_color == BLACK ? "B (BLACK)" : "W (WHITE)") << std::endl;
	std::cout << "Human Color: " << (ai_color == BLACK ? "W (WHITE)" : "B (BLACK)") << std::endl;
	std::cout << "Symbols: B=Black Queen | W=White Queen | #=Block | .=Empty" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;

	// Print column indices
	std::cout << "   ";
	for (int j = 0; j < SIZE; ++j) {
		std::cout << " " << j;
	}
	std::cout << "\n";

	// Print separator line
	std::cout << "  +";
	for (int j = 0; j < SIZE; ++j) {
		std::cout << "--";
	}
	std::cout << "+\n";


	for (int i = 0; i < SIZE; ++i) {
		// Print row index
		std::cout << i << " |";
		for (int j = 0; j < SIZE; ++j) {
			char symbol;
			if (board[i][j] == BLACK) symbol = 'B';
			else if (board[i][j] == WHITE) symbol = 'W';
			else if (board[i][j] == BLOCK) symbol = '#';
			else symbol = '.';
			std::cout << " " << symbol;
		}
		std::cout << " |\n";
	}

	// Print bottom separator line
	std::cout << "  +";
	for (int j = 0; j < SIZE; ++j) {
		std::cout << "--";
	}
	std::cout << "+\n";

	std::cout << "-------------------------------------------------\n" << std::endl;
}

// Save game state
void save_game(const int current_board[SIZE][SIZE], int ai_color, int turn_id) {
	std::ofstream outfile("amazonas_save.txt");
	if (!outfile.is_open()) {
		std::cerr << "Error: Could not open file for saving." << std::endl;
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
	std::cout << "Game state successfully saved to amazonas_save.txt" << std::endl;
	outfile.close();
}

// Load game state
bool load_game(int current_board[SIZE][SIZE], int& ai_color, int& turn_id) {
	std::ifstream infile("amazonas_save.txt");
	if (!infile.is_open()) {
		std::cerr << "Error: Could not open amazonas_save.txt. Please save a game first." << std::endl;
		return false;
	}

	if (!(infile >> ai_color >> turn_id)) {
		std::cerr << "Error: Saved file format error." << std::endl;
		infile.close();
		return false;
	}

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (!(infile >> current_board[i][j])) {
				std::cerr << "Error: Incomplete board data in saved file." << std::endl;
				infile.close();
				return false;
			}
		}
	}
	std::cout << "Game state successfully loaded. AI is " << (ai_color == BLACK ? "BLACK" : "WHITE") << std::endl;
	infile.close();
	return true;
}

// Check if move is Queen-like (horizontal, vertical, or diagonal)
bool is_queen_move(int x0, int y0, int x1, int y1) {
	if (x0 == x1 && y0 == y1) return false; // Must move
	int dx_abs = std::abs(x1 - x0);
	int dy_abs = std::abs(y1 - y0);
	return dx_abs == 0 || dy_abs == 0 || dx_abs == dy_abs;
}

// Check if the path is clear between start and end coordinates
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


// Handle player move input and validation
bool get_and_apply_player_move(int board[SIZE][SIZE], int player_color) {
	int x0, y0, x1, y1, x2, y2;
	std::cout << "\nEnter your move in format (r0 c0 r1 c1 rB cB): \n";
	std::cout << "r0, c0: current queen position\n";
	std::cout << "r1, c1: queen destination position\n";
	std::cout << "rB, cB: block (arrow) position\n";
	std::cout << "Input: ";

	// Robust input check
	if (!(std::cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2)) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Error: Invalid input format. Please try again." << std::endl;
		return false;
	}

	// 1. Basic coordinate and piece validation
	if (!is_valid(x0, y0) || !is_valid(x1, y1) || !is_valid(x2, y2)) {
		std::cout << " Error: Coordinates must be within range (0-7)." << std::endl;
		return false;
	}
	if (board[x0][y0] != player_color) {
		std::cout << " Error: (r0, c0) is not your Queen (" << (player_color == BLACK ? 'B' : 'W') << ")." << std::endl;
		return false;
	}
	if (board[x1][y1] != EMPTY) {
		std::cout << " Error: (r1, c1) destination must be empty." << std::endl;
		return false;
	}

	// *** FIX FOR DISAPPEARING PIECE BUG ***
	// If the queen's destination (r1, c1) is the same as the block's destination (rB, cB),
	// the block placement step in apply_move will overwrite the queen, causing it to disappear.
	if (x1 == x2 && y1 == y2) {
		std::cout << " Error: Block position (rB, cB) cannot be the same as the Queen's destination (r1, c1)." << std::endl;
		return false;
	}
	// *************************************

	// The block position (rB, cB) must be empty on the original board, or the queen's starting spot (which becomes empty).
	if (board[x2][y2] != EMPTY) {
		if (!(x2 == x0 && y2 == y0)) { // If not the starting spot, it must be EMPTY
			std::cout << " Error: (rB, cB) block position must be empty or the Queen's start position." << std::endl;
			return false;
		}
	}

	// 2. Queen movement path validation (x0 -> x1)
	if (!is_path_clear(board, x0, y0, x1, y1)) {
		std::cout << " Error: Queen move (r0, c0) to (r1, c1) is invalid or path is blocked." << std::endl;
		return false;
	}

	// 3. Block placement path validation (x1 -> x2)
	// We need to check the path from the new queen position (x1, y1) to the block position (x2, y2).

	// Check if the block placement is a valid Queen move distance from the new queen position (x1, y1)
	if (!is_queen_move(x1, y1, x2, y2)) {
		std::cout << " Error: Block placement (r1, c1) to (rB, cB) is not a valid Queen move distance." << std::endl;
		return false;
	}

	// Check path clearance for the block placement:
	// The path from (x1, y1) to (x2, y2) must be clear, only allowing the original queen start spot (x0, y0)
	// to be blocked if the path traverses it.

	int dx_dir = (x2 > x1) ? 1 : ((x2 < x1) ? -1 : 0);
	int dy_dir = (y2 > y1) ? 1 : ((y2 < y1) ? -1 : 0);

	int cx = x1 + dx_dir;
	int cy = y1 + dy_dir;

	while (cx != x2 || cy != y2) {
		// The path must only contain EMPTY cells on the original board, or the queen's *starting* position (x0, y0)
		if (board[cx][cy] != EMPTY && (cx != x0 || cy != y0)) {
			std::cout << " Error: Block placement path blocked by object at (" << cx << ", " << cy << ")." << std::endl;
			return false;
		}
		cx += dx_dir;
		cy += dy_dir;
	}

	// 4. Final application of the move
	move player_move = { x0, y0, x1, y1, x2, y2 };
	apply_move(board, player_move, player_color);
	std::cout << "Human move applied: (" << x0 << ", " << y0 << ") -> (" << x1 << ", " << y1 << "), Block at (" << x2 << ", " << y2 << ")" << std::endl;
	return true;
}


// --- Main Function (Menu Logic) ---

int main() {
	// Optimization for faster I/O
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int board[SIZE][SIZE] = {};
	int ai_color = EMPTY;
	int turnID = 0;
	bool game_started = false;

	clear_screen();
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "       AMAZONAS (QUEEN'S GAME) AI        " << std::endl;
	std::cout << "------------------------------------------" << std::endl;

	while (true) {
		if (game_started) {
			print_board(board, ai_color);
		}
		else {
			clear_screen();
			std::cout << "------------------------------------------" << std::endl;
			std::cout << "       AMAZONAS (QUEEN'S GAME) AI        " << std::endl;
			std::cout << "------------------------------------------" << std::endl;
		}

		std::cout << "\n==========================================" << std::endl;
		std::cout << "Turn ID: " << turnID << " | AI Color: " << (ai_color == BLACK ? "BLACK" : (ai_color == WHITE ? "WHITE" : "N/A")) << std::endl;
		std::cout << "--- MENU ---" << std::endl;
		std::cout << "1. Start New Game" << std::endl;
		std::cout << "2. Load Game" << std::endl;
		std::cout << "3. Make Move (Human -> AI)" << std::endl;
		std::cout << "4. Save Game" << std::endl;
		std::cout << "5. Exit" << std::endl;
		std::cout << "Enter your choice (1-5): ";

		int choice;
		if (!(std::cin >> choice)) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			clear_screen();
			std::cout << "Invalid input. Please enter a number." << std::endl;
			continue;
		}

		if (choice == 5) {
			clear_screen();
			std::cout << "Game exited. Goodbye!" << std::endl;
			break;
		}

		switch (choice) {
		case 1: { // Start New Game
			initialize_board(board);
			std::cout << "Select AI Color (1 for BLACK, -1 for WHITE): ";
			int color_choice;
			if (!(std::cin >> color_choice) || (color_choice != BLACK && color_choice != WHITE)) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "Invalid color choice. Defaulting AI to WHITE (-1)." << std::endl;
				ai_color = WHITE;
			}
			else {
				ai_color = color_choice;
			}
			current_color = ai_color;
			turnID = 1;
			game_started = true;

			print_board(board, ai_color);
			std::cout << "New game started! AI is " << (ai_color == BLACK ? "BLACK" : "WHITE") << ", Human is " << (ai_color == BLACK ? "WHITE" : "BLACK") << std::endl;

			if (ai_color == BLACK) {
				std::cout << "\nAI is BLACK and goes first. Calculating initial move..." << std::endl;
				// AI's hardcoded opening move (for speed)
				move first_move = { 2, 0, 2, 6, 5, 6 };
				apply_move(board, first_move, BLACK);
				std::cout << "AI Move: 2 0 2 6 5 6" << std::endl;
				turnID++;
				print_board(board, ai_color);
			}

			break;
		}
		case 2: { // Load Game
			clear_screen();
			if (load_game(board, ai_color, turnID)) {
				current_color = ai_color;
				game_started = true;
				print_board(board, ai_color);
			}
			break;
		}
		case 3: { // Make Move (Human -> AI)
			if (!game_started) {
				clear_screen();
				std::cout << "Please start a new game or load a game first!" << std::endl;
				break;
			}

			int player_color = -ai_color;

			// --- 1. Human Move ---
			bool player_move_ok = get_and_apply_player_move(board, player_color);

			// Handle invalid input or move
			if (!player_move_ok) {
				std::cout << "Human move failed. Press ENTER to return to menu and try again." << std::endl;
				// Wait for user to read the error
				std::cin.ignore(10000, '\n');
				std::cin.get();
				break;
			}

			// Check for game end condition after human move
			std::vector<move> ai_legal_moves_check = find_move(board, ai_color);
			if (ai_legal_moves_check.empty()) {
				print_board(board, ai_color);
				std::cout << "\n==========================================" << std::endl;
				std::cout << " VICTORY: AI (" << (ai_color == BLACK ? "BLACK" : "WHITE") << ") has no legal moves. Human WINS!" << std::endl;
				std::cout << "==========================================" << std::endl;
				game_started = false;
				break;
			}

			// --- 2. AI Calculation ---
			std::cout << "\nAI is calculating best move... (Depth: " << MAX_DEPTH << ")" << std::endl;

			// Move Ordering (Evaluate all immediate moves)
			std::vector<RatedMove> rated_moves;
			for (const auto& m : ai_legal_moves_check) {
				apply_move(board, m, ai_color);
				double eval_score = evaluate(board, ai_color);
				undo_move(board, m, ai_color);
				rated_moves.push_back({ m, eval_score });
			}
			// Sort for better alpha-beta pruning performance
			std::sort(rated_moves.begin(), rated_moves.end(), [](const RatedMove& a, const RatedMove& b) {
				return a.value > b.value;
				});

			move best_move = rated_moves[0].m;
			double best_val = -1e9;
			int size = rated_moves.size();

			// Alpha-Beta Search
			for (int i = 0; i < size; ++i) {
				const move& current_move = rated_moves[i].m;
				apply_move(board, current_move, ai_color);
				// Call AlphaBeta starting with depth-1 (one move was already applied)
				double eval = alphaBeta(board, MAX_DEPTH - 1, -ai_color, best_val, 1e9);
				undo_move(board, current_move, ai_color);

				if (eval > best_val) {
					best_val = eval;
					best_move = current_move;
				}
			}

			// --- 3. Apply and Output AI Move ---
			apply_move(board, best_move, ai_color);
			turnID++;
			print_board(board, ai_color);
			std::cout << "\nAI Move (r0 c0 r1 c1 rB cB): ";
			std::cout << best_move.x0 << " " << best_move.y0 << " " << best_move.x1 << " " << best_move.y1 << " " << best_move.x2 << " " << best_move.y2 << std::endl;
			std::cout << "AI Evaluation Score (Sigmoid): " << best_val << std::endl;

			// Check for game end condition after AI move
			std::vector<move> player_moves_check = find_move(board, player_color);
			if (player_moves_check.empty()) {
				std::cout << "\n==========================================" << std::endl;
				std::cout << " VICTORY: Human (" << (player_color == BLACK ? "BLACK" : "WHITE") << ") has no legal moves. AI WINS!" << std::endl;
				std::cout << "==========================================" << std::endl;
				game_started = false;
			}

			break;
		}
		case 4: { // Save Game
			clear_screen();
			if (game_started) {
				save_game(board, ai_color, turnID);
			}
			else {
				std::cout << "No game is currently in progress to save." << std::endl;
			}
			break;
		}
		default: {
			clear_screen();
			std::cout << "Invalid option, please re-enter." << std::endl;
			break;
		}
		}
	}
	return 0;
}
	return 0;
}
