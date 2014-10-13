#include "defs.h"
#include "ai_general.h"
#include "syanten.h"
#include "tools.h"
#include "agari.h"
#include "calc.h"

AI_GEN::AI_GEN()
{
	bak=new BAKYOU();
	int i;
	for(i=0;i<34;i++) {
		tehai[i]=0;
	}
	act = new AI_ACTION;
	read_params(&params,"params");
}

AI_GEN::~AI_GEN()
{
	delete act;
	delete bak;
	cout << "free ai" << endl;
}

int AI_GEN::check_dapai_2()
{
	int *nok = bak->nokori;
	int cpai = bak->stat.cpai;
	int i,j;
	
	int cur_syanten = count_syanten_all(tehai);
	int cur_syanten_no713 = count_syanten_no713(tehai);
	int kiri_syanten, machi_syanten;
	double a,b,c,Ea,st,ist;

	for(i=0;i<34;i++) {
		aipai[i].E_syanten=0;
		aipai[i].E_machi_maisu=0;
		aipai[i].E_machi_pai=0;
		aipai[i].E_tot=0;
		if (tehai[i]) {
			--tehai[i];
			aipai[i].syanten_all = count_syanten_all(tehai);
			aipai[i].syanten_no713 = count_syanten_no713(tehai);
			if(aipai[i].syanten_all<0) aipai[i].syanten_all=0;
			if(aipai[i].syanten_no713<0) aipai[i].syanten_no713=0;
			aipai[i].isyanten_all = cur_syanten==aipai[i].syanten_all?1:-1;
			
			aipai[i].isyanten_no713 = cur_syanten_no713 - aipai[i].syanten_no713;
			aipai[i].maisu=0;
			for(j=0;j<34;++j) {
				aipai[i].mpai[j]=0;
				if (nok[j]) {
					++tehai[j];
					machi_syanten=count_syanten_all(tehai);
					if(machi_syanten<cur_syanten || agari_test(tehai)) {
						aipai[i].mpai[j]=1;
						aipai[i].maisu += nok[j];
					}
					--tehai[j];
				}
			}
			++tehai[i];

			a = params.syanten_f1_a;
			b = params.syanten_f1_b;
			c = params.syanten_f1_c;
			Ea= params.syanten_Ea;
			//st = aipai[i].isyanten_all>0?aipai[i].syanten_all:aipai[i].syanten_all-1;
			st = aipai[i].syanten_all;
			ist = aipai[i].isyanten_all;
			aipai[i].E_syanten=ist*(f1(a,b,c,st)+Ea);
			
			aipai[i].E_machi_maisu = aipai[i].maisu * params.maisu_p1;

			aipai[i].E_tot = aipai[i].E_syanten     +
			                 aipai[i].E_machi_maisu +
							 aipai[i].E_machi_pai;
#ifdef MIO_DEBUG_AI_ESYANTEN
			cout << endl << hai2str(i);
			cout << "   st : "  << st ;
			cout << "  ist : "  << ist ;
			cout << "  E : " << aipai[i].E_syanten << endl;
			cout << " Emaisu : " << aipai[i].E_machi_maisu << endl;
#endif
		}
	}

	return 0;
}

int AI_GEN::check_dapai()
{
	int *nok=bak->nokori;
	int cpai=bak->stat.cpai;
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
		cout << "  maisu: " << dapai[i].maisu << "  Etot: " << aipai[dapai[i].cpai].E_tot << endl;
#endif
		if (dapai[i].maisu>dapai[maxdp].maisu) maxdp=i;
	}
	return dapai[maxdp].cpai;
}

int AI_GEN::kiru()
{
	int i,kr;
	cout << endl << "##############    AI  TIME   ############" << endl;
	cout << "junmoku " << (bak->jun) << "  "; 
	cout << "tehai:  " << tehai2str(tehai);
	cout << "  syanpai: " << hai2str(bak->stat.cpai) << "     ";  // << endl;
	if (agari_test(tehai)) {
	
		act->Act=2;
	cout << "#########################################" << endl << endl;
		return 0;
	}
	if (bak->riichi[0]) {
		act->Act=0;
		act->cnum=bak->stat.cpai;
	cout << "#########################################" << endl << endl;
		return 0;
	}
	
	check_dapai_2();
	kr = check_dapai();
	
	act->cnum = kr;
	act->syanten = count_syanten_all(tehai);
	if (act->syanten==0)
		act->Act=6;
	else
		act->Act=0;
	cout << "#########################################" << endl << endl;
	return 0;
}


int AI_GEN::check()
{
	int cpai=bak->stat.cpai;
	++tehai[cpai];
	if (agari_test(tehai)) {
		act->Act=2;
		return 0;
	}
	return 0;

}
