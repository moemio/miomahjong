

class AGARI_PART {
public:
	
	int c[34];
	int tehai[34];
	int n_syuntsu;
	int n_kotsu;
	int n_mentsu;
	int atama;	
	int isatama;
	int kotsu[34];
	int syuntsu[34];
	int yaku[46];
	int fan;
	int fu;
	int score;
	BAKYOU * bak;
	vector<PATTERN> pattern;
	int maxp;
	void countScore(PATTERN &part, BAKYOU *bakyou);
	void Run(int depth);
	
	AGARI_PART(int c[], BAKYOU * bak);
	~AGARI_PART();
	
	void d_kotsu(int k);
	void i_kotsu(int k);
	void i_syuntsu(int k);
	void d_syuntsu(int k);
	void i_atama(int k);
	void d_atama(int k);
	
	void wari();
	void removeJihai();
	void updateResult();
	string hai2str(int hai);
	void printFan(PATTERN &part);
	bool isKokushi;
	bool isChiitoi;
	void TokuHandan(); // 7 13
	
};
