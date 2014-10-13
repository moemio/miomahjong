#include "defs.h"

BAKYOU::BAKYOU()
{
	int i,j;
	for (i=0;i<34;i++)
		nokori[i]=4;
	cout << "run me!" << endl;
	jun=1;
	bafuu=27;
	jifuu=27;
	kyoku=1;
	
	for(i=0;i<3;i++){ // aka 0m 0p 0s
		for(j=0;j<4;j++) {
			is_aka_river[j][i]=0;
			is_aka_naki[j][i]=0;
		}
		is_aka_dorahyouji[i]=0;
		is_aka_tehai[i]=0;
	}
	river.resize(4);
	for(i=0;i<4;i++) {

		n_naru[i] = 0;
		n_naki_kan[i]=0;
		n_naki_kotsu[i]=0;
		n_naki_syuntsu[i]=0;

		riichi[i] = 0;
		river[i].clear();
		for(j=0;j<34;j++) {
			naru_chii[i][j]=0;
			naru_pon[i][j]=0;
			naru_kan[i][j]=0;
			naru_ankan[i][j]=0;
		}
	}
	
	//zero memory

	dora.clear();
	ura.clear();
	n_dora=0;
	yama_ptr=1;

	stat.act_stat=-1;

}
BAKYOU::~BAKYOU()
{
	dora.clear();
	ura.clear();
	cout << "run free" << endl;

}

void BAKYOU::deru(int dhai) { --nokori[dhai]; }

bool BAKYOU::isMenchin(int p) { return !n_naru[p]; }

bool BAKYOU::isGenbutsu(int p, int n) { 
	bool ata=false;
	for(int i=0;i<22;i++)
		if (river[p][i]==n) { ata=true; break; }
	return ata;
}
