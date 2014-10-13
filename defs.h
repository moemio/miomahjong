#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;
#define PI 				3.14159265358979
#define SQR(x)        ((x)*(x))
#define MAX( x, y )   (((x) > (y)) ? (x) : (y))
#define MIN( x, y )   (((x) < (y)) ? (x) : (y))
#define inline __inline__

#define MIO_DEBUG
//#define MIO_DEBUG_SYANTEN
//#define MIO_DEBUG_TEST
#define MIO_DEBUG_PAILI
#define MIO_DEBUG_MAJ


#define MAX_LINE 1024
#define MAX_TOKENS 20


#define MIO mio cai bu ben ne ! mio zui cong ming le ! 

typedef struct
{
	double syanten_f1_a;
	double syanten_f1_b;
	double syanten_f1_c;
	double syanten_Ea;

	double maisu_p1;

}PARAMS;

typedef struct 
{
	int maisu;
	vector<int> mpai;
	int cpai;
}DAPAI;

typedef struct
{
	int maisu;
	int mpai[34];
	int cpai;

	int syanten_all;
	int syanten_no713;
	int isyanten_all;
	int isyanten_no713;
	
	double E_tot;
	
	double E_syanten;
	double E_machi_maisu;
	double E_machi_pai;
}AIPAI;

struct PATTERN {
	int c[34];
	int score;
	int score_oya;
	int score_ko;
	int kotsu[34];
	int syuntsu[34];
	int atama;
	int n_kotsu;
	int n_syuntsu;
	int n_naru;
	int naki_kotsu[34];
	int naki_syuntsu[34];
	int naki_n_kotsu;
	int naki_n_syuntsu;
	int fan;
	int fan_nodora;
	int fu;
	int fu_tmp;
	int yaku[46];
	int toitsu[34];
	bool isChiitoi;
	bool isKokushi;
	bool isYakuman;
	int yakuman_baisu;
};
enum ENUM_ACT {
	ACT_TEKIRI=0,
	ACT_TSUMOGIRI,
	ACT_TSUMO,
	ACT_CHII,
	ACT_PON,
	ACT_KAN,
	ACT_KAN_SELF
};
struct STAT_SP {
	int cpai;
	int act_stat; 
	bool isRiichi;
	int dacya; // 0:NaN   1: syacya  2: toicya  3: syancya
	bool isRed;
};


class BAKYOU {
  public:
  	
	int nokori[34];
	int jun;     // junmoku
	int bafuu;   
	int jifuu;
	int kyoku;   
	int honba;
	
	int naru_chii[4][34];
	int naru_pon[4][34];
	int naru_kan[4][34];
	int naru_ankan[4][34];

	vector< vector<int> > river;


	int tekiri[4][22];
	int score[4];

	int n_naru[4];
	int n_naki_kan[4];
	int n_naki_kotsu[4];
	int n_naki_syuntsu[4];
	
	int is_aka_river[4][3];
	int is_aka_dorahyouji[3];
	int is_aka_naki[4][3];
	int is_aka_tehai[3];


	int riichi[4];
	vector<int> dora;
	vector<int> ura;
	int n_dora;
	int yama_ptr;   // pointer of yama
	int dead_ptr;   // pointer of ryuukyoku , 136-14=122, if(kan) -=1;

	void deru(int dhai);
	bool isMenchin(int p);
	bool isGenbutsu(int p, int n);

	STAT_SP stat;

	BAKYOU();
	~BAKYOU();
};


class AI_v1 {
  public:
	class BAKYOU *bakyou;

	int AI_kiru(int tehai[], int syanpai);

};


struct AI_ACTION {
	int cnum;
	int syanten;
	int Act; // 0:tekiri  1:tsumogiri   2:tsumo  3: chii  4: pon  5: kan  6: riichi
};

void calcSyanten(int a[], int n, bool bSkip713, int syanten[], int& is713);
void calcAgariPart( int c[], BAKYOU * bak);
bool agari_test( int c[] );
void read_params(PARAMS *params, char* params_file);
