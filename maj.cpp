#include <stdio.h>
#include <math.h>
#include <iostream>
#include "defs.h"
#include "agari.h"
#include "majtest.h"
#include "tools.h"
#include "syanten.h"

using namespace std;
using std::string;


bool agari_test( int c[] );
int zero_tehai(int hai[]);
int check_dapai(int tehai[], int nok[], vector<DAPAI> &dapai);

void randperm( int n, int perm[])
{
	int i,j,t;
	for (i=0;i<n;i++) 
		perm[i]=i;
	for (i=0;i<n;i++) {
		j = rand()%(n-i)+i;
		t = perm[j];
		perm[j] = perm[i];
		perm[i] = t;
	}
}

void init_pai( int hai[], long seed)
{
	cout << "seed:" << seed << endl;
	srand(seed);
	randperm( 136, hai );
}

int num2hai( int num)
{
	return num>>2;
}

///AITEST BEGIN///



int AI_kiru(int tehai[],int syanpai,BAKYOU *bak, AI_ACTION *act)
{
	int cpai = syanpai>>2;
	vector<DAPAI> dapai;
	int kiru;
	cout << "junmoku " << (bak->jun) << "  "; 
	cout << "bafu:" << bak->bafuu;
	cout << "tehai:  " << tehai2str(tehai);
	cout << "  syanpai: " << hai2str(cpai) << "     ";  // << endl;
	bak->deru(cpai);
	++tehai[cpai];
	if (agari_test(tehai))
	{
		act->Act=2;
		return 0;
	}
	
	kiru = check_dapai(tehai, bak->nokori, dapai);
	
	
	act->cnum = kiru;
	act->Act = 0;
	act->syanten = count_syanten_all(tehai);
	++bak->jun;
	return 0;
}

int AI_v2(int tehai[], BAKYOU *bak, AI_ACTION *act)
{
	
	int jun = bak->jun;
	int cpai = bak->stat.cpai;

	cout << "junmoku " << jun << "  ";

	return 0;
}

int AI_test2(int pai[])
{
	cout << endl << " ## AI test 02 ## " << endl ;
	
	return 0;
}


int check_dapai(int tehai[], int nok[], vector<DAPAI> &dapai)
{
	int i,j;
	dapai.clear();
	DAPAI dp;
	int ndapai=0;
	int cur_syanten = count_syanten_all(tehai);
	int kiru_syanten, matsu_syanten;
	for(i=0;i<34;i++) {
		if (tehai[i]) {
			--tehai[i];
			kiru_syanten = count_syanten_all(tehai);
			if (kiru_syanten==cur_syanten || kiru_syanten<=0) {
				dp.mpai.clear();
				dp.maisu=0;
				dp.cpai=i;
				for(j=0;j<34;j++) {
					if (nok[j]) {
						++tehai[j];
						matsu_syanten=count_syanten_all(tehai);
						if (matsu_syanten<cur_syanten || agari_test(tehai)) {
							dp.mpai.push_back(j);
							dp.maisu+= nok[j];
						}
						--tehai[j];
					}
				}
				dapai.push_back(dp);
				++ndapai;
			}
			++tehai[i];
		}
	}
	vector<int>::iterator it;
	int maxdp=0;
#ifdef MIO_DEBUG_PAILI
	cout << endl;
#endif
	for(i=0;i<ndapai;i++){
#ifdef MIO_DEBUG_PAILI
		cout << "     da " << hai2str(dapai[i].cpai) << "   machi  ";
		for(it=dapai[i].mpai.begin();it!=dapai[i].mpai.end();++it) 
			cout << hai2str(*it) << " ";
		cout << "  maisu: " << dapai[i].maisu << endl;
#endif
		if (dapai[i].maisu>dapai[maxdp].maisu) maxdp=i;
	}
	return dapai[maxdp].cpai;
}

int zero_tehai(int hai[])
{
	int i;
	for(i=0;i<34;i++)
		hai[i]=0;
	return 0;
}

int AI_test(int hai[])
{
	int tehai[34];
	int ptr=0,nth=0;
	int i;
	AI_ACTION *act = new AI_ACTION;
	BAKYOU * bak = new BAKYOU();
	for(i=0;i<34;i++)
		tehai[i]=0;
	for(i=0;i<13;i++) {
		++tehai[hai[i]>>2];
		--bak->nokori[hai[i]>>2];
	}
	ptr=13;

	while(ptr<122) {
		
		AI_kiru(tehai, hai[ptr], bak, act);
		switch (act->Act) {
			case 0: {
				cout << "da " << hai2str(act->cnum) << " " << act->syanten << " syanten." << endl;
				--tehai[act->cnum];
				break; }
			case 2: {
				cout << "agari!" << endl;
				ptr=122;
				break; }

		}
		++ptr;
	}
	return bak->jun;
}


///AITEST END///




int read_tehai( string strth, int c[] )
{
	int i,e=-1,l,t;
	int last;
	int h[3]={0,0,0};
	for (i=0;i<34;i++)
		c[i]=0;
	if (strth.empty()) return -1;
	l=strth.length();
	for (i=l-1;i>=0;i--) {		
		if (strth[i]=='m') e=0;
		else if (strth[i]=='p') e=1;
		else if (strth[i]=='s') e=2;
		else if (strth[i]=='z') e=3;
		else if (strth[i]>='0' && strth[i]<='9' ) {
			if (e==-1) return -5;
			t=strth[i]-'0';
			if (t==0) {
				if (e>=3) return -4;
				if (h[e]==0) {
					h[e]++; t=5;
				}
				else return -2;
			}
			t+=e*9-1;
			if (c[t]<4) c[t]++; else return -3;
			if (i==l-2) last=t;
		}
		else return -5;
	}
	return last;
}


int count_tehai( int c[] )
{
	int cth=0;
	for (int i=0; i<34; i++) 
		cth += c[i];
	return cth;
}

int main(int argc, char *argv[])
{
	int pai[136];
	int i;
	long seed=time(0);
	init_pai(pai, seed);

#ifdef MIO_DEBUG
	for (i=0;i<136;i++)
		cout << pai[i] << " ";
	cout << endl;
#endif

//AI_test(pai);

/*
int ave_jun=0;
int step = 10000;
for (i=1;i<step;i++)
{
init_pai(pai,i);
ave_jun += AI_test(pai);
}
cout << endl << "DONE. AVE JUN IS " << (float)ave_jun/step;
*/
#ifdef MIO_DEBUG_MAJ


	MAJ *maj = new MAJ(seed);
	maj->gameLoop();


#endif

#ifdef MIO_DEBUG_TEST
	int tehai[34];
	for (i=0;i<34;i++)
		tehai[i]=0;
	

	bool bIsAgari;
	int iQuit = 1,pStatus,nth;
	string inpstr;

	 cout << endl << "input 'q' to quit." ;
	 while (iQuit)
	 {
	 	inpstr.clear();
	 	cout << endl << "input paipai:" ;
	 	cin >> inpstr;
	 	if (inpstr=="q") iQuit=0;
	 	else {
	 		 pStatus = read_tehai( inpstr, tehai );
	 		 if (pStatus<0) {cout << "input error #" << pStatus << " !" ;return 0;}
	 		 nth = count_tehai( tehai ) ;
	 		 cout << "tehaisu: " << nth << endl;
			 if ((nth-2)%3==0) {
	 		 bIsAgari = agari_test( tehai );
	 		 if (bIsAgari){
			 	cout << "agari" << endl;
				// test yaku
				BAKYOU * bakyou = new BAKYOU();
				bakyou->dora.push_back(22);
				bakyou->ura.push_back(21);
				bakyou->n_dora=1;
				bakyou->stat.act_stat=ACT_TSUMO;
				bakyou->stat.cpai=pStatus;
				bakyou->stat.dacya=0;
				bakyou->riichi[0]=0;
				calcAgariPart( tehai, bakyou );
				}
	 		 else {
	 		 	int sts = count_syanten_all(tehai);	
				BAKYOU *bak = new BAKYOU;

				for(i=1;i<34;i++)
					bak->nokori[i]-=tehai[i];
				vector<DAPAI> dapai;

				check_dapai(tehai, bak->nokori, dapai);
	 		 	cout << "    " << sts 
	 		 	     << " syanten;" << endl;
	 		 }
			 }
	 	}
	 }
#endif

	return 0;
}

