#include <vector>

class AI_GEN {
public:
	int tehai[34];
	int c[34];
	vector<DAPAI> dapai;
	class BAKYOU *bak;
	
	int check_dapai();
	int check_dapai_2();

	int kiru();
	int check();
	class AI_ACTION *act;

	AIPAI aipai[34];	
	
	PARAMS params;

	AI_GEN();
	~AI_GEN();

};

