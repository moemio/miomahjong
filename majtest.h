#include <vector>

class MAJ {
public:
	long seed;

	int pai[136];	
	int tehai[4][34];
	int aka_tehai[4][3];     // 0:m  1:p  2:s
	int aka_river[4][3];

	int maj_bafuu;
	int maj_kyoku;
	int maj_hajioya;
	int maj_oya;
	int maj_honba;
	int maj_n_dora;
	int ptr;
	int jun[4];
	int dead_ptr;
	int pos_ptr;
	
	int riichi[4];
	vector< vector<int> > river;

	int n_naki[4];
	

	int score[4];

	int clearGame();

	void rand_perm(int n, int perm[]);
	void init_pai( int hai[], long seed);
	
	void start_pai();
	void haipai(int oyapos);
	int check_aka(int cpai);	

	void syanpai(int pos);
	void dapai(int pos, int cpai, int isRed, bool isTekiri, bool isRiichi);
	void updateBakyou(BAKYOU *bak, int bakpos);
	void updateBakyou_2(BAKYOU *bak, int bakpos);
	void createBakyou(BAKYOU *bak, int bakpos);
	void checkAI();

	int gameLoop();
	STAT_SP stat;
	MAJ(long s);
	~MAJ();

};	
