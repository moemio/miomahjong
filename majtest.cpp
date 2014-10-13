#include "defs.h"
#include "majtest.h"
#include "tools.h"
#include "ai_general.h"
#include "agari.h"

MAJ::MAJ(long s) {
	int i;
	maj_bafuu=27;
	maj_kyoku=0;
	maj_hajioya = rand()%4;
	maj_honba=0;
	ptr=0;
	dead_ptr=122;
	pos_ptr=maj_hajioya;
	maj_oya=maj_hajioya;
	maj_n_dora=1;
	river.resize(4);
	for(i=0;i<4;++i) {
		score[i]=25000;
	}
	seed = s;
	cout << "seed: " << seed << endl;
	srand(seed);
}

MAJ::~MAJ() {

}

void MAJ::rand_perm(int n, int perm[])
{
	int i,j,t;
	for(i=0;i<n;i++)
		perm[i]=i;
	for(i=0;i<n;i++) {
		j = rand()%(n-i)+i;
		t = perm[j];
		perm[j] = perm[i];
		perm[i] = t;
	}
}

void MAJ::init_pai( int hai[], long seed)
{
	rand_perm(136, hai);
	ptr=0;
	dead_ptr=122;
	maj_n_dora=1;
	++maj_kyoku;
}

void MAJ::haipai(int oyapos)
{
	int i,j,k;
	int c0,c1,p;
	
	init_pai(this->pai, seed);
	ptr = 0;

	for(i=0;i<4;i++) {
		for(j=0;j<34;j++)
			tehai[i][j]=0;
		for(j=0;j<3;j++)
			aka_tehai[i][j]=0;
	}
	
	for(i=0;i<3;i++)
		for(j=0;j<4;j++) {
			p = (j+oyapos)%4;
			for(k=0;k<4;k++) {	
				c0=pai[ptr+k];
				c1=c0>>2;
				++tehai[p][c1];
				if (check_aka(c0)) aka_tehai[p][check_aka(c0)-1]=1;
			}
			ptr+=4;
		}
	for(i=0;i<4;++i) {
		p = (i+oyapos)%4;
		c0 = pai[ptr+i];
		c1 = c0>>2;
		++tehai[p][c1];
		if (check_aka(c0)) aka_tehai[p][check_aka(c0)-1]=1;
	}
	ptr+=4;

	jun[0]=0;jun[1]=0;jun[2]=0;jun[3]=0;
}

void MAJ::start_pai()
{
	cout << endl <<  "start. oya=" << maj_hajioya << endl;
	haipai(maj_oya);
	int i,j;
	for(i=0;i<4;++i) {
		river[i].clear();
		for(j=0;j<3;++j) {
			aka_tehai[i][j]=0;
			aka_river[i][j]=0;
		}
	}
	maj_n_dora=1;
	cout << " dora " << hai2str(pai[131]>>2) << endl;
	cout << endl << endl;
}

void MAJ::updateBakyou(BAKYOU *bak, int bakpos)
{
	int c=stat.cpai;
	if (stat.act_stat==ACT_TSUMO)
	{
		bak->stat=stat;
		bak->deru(c);

	} else if (stat.act_stat==ACT_TEKIRI || stat.act_stat==ACT_TSUMOGIRI) {

		--bak->nokori[c];
		bak->stat=stat;
		bak->river[stat.dacya].push_back(c);

	} else if (stat.act_stat==ACT_KAN) {


	} else if (stat.act_stat==ACT_KAN_SELF) {


	}
	bak->jun=jun[bakpos];
	int i;
	for(i=0;i<4;++i) {
		bak->riichi[i]=riichi[i];
	}
	if(bak->n_dora < maj_n_dora) {
		bak->n_dora = maj_n_dora;
		bak->dora.clear();
		bak->ura.clear();
		for(i=0;i<maj_n_dora;++i) {
			bak->dora.push_back(pai[131-i*2]>>2);
			bak->ura.push_back(pai[132-i*2]>>2);
		}
	}
}

void MAJ::checkAI()
{
	
}

void MAJ::updateBakyou_2(BAKYOU *bak, int bakpos)
{
	int i,j;
	if(bak->n_dora < maj_n_dora) {
		bak->n_dora = maj_n_dora;
		bak->dora.clear();
		bak->ura.clear();
		for(i=0;i<maj_n_dora;++i) {
			bak->dora.push_back(pai[131-i*2]>>2);
			bak->ura.push_back(pai[132-i*2]>>2);
		}
	}

	bak->jun = jun[bakpos];
	
	for(i=0;i<4;++i) {
		bak->riichi[i]=riichi[i];
		bak->n_naru[i]=n_naki[i];
	}
	bak->river = river;
	
}

void MAJ::createBakyou(BAKYOU *bak, int bakpos)
{
	int i;
	bak->bafuu = maj_bafuu;
	bak->n_dora = maj_n_dora;
	bak->dora.push_back(pai[131]>>2);
	bak->ura.push_back(pai[132]>>2);
	bak->honba = maj_honba;
	bak->jifuu = 27+(4+bakpos-maj_oya)%4;
	bak->kyoku = maj_kyoku;
	for(i=0;i<34;i++) {
		bak->nokori[i]-=tehai[bakpos][i];
	}
}

int MAJ::clearGame()
{
	int i,j;
	for(i=0;i<4;++i) {
		riichi[i]=0;

	}
	return 0;
}

int MAJ::gameLoop()
{
	bool Ryukyoku=false;
	int kr;
	this->start_pai();
	AI_GEN *ai0 = new AI_GEN();
		
	// 0 pos bak:
	BAKYOU *bak0 = ai0->bak;
	createBakyou(bak0,0);

	while(!Ryukyoku) {

		syanpai(pos_ptr);

		if (pos_ptr==0) {
			
			--tehai[0][stat.cpai];
	cout << "junmoku " << jun[0] << ": pos " << 0 << " tehai: " << tehai2str(tehai[0])
	     << "  tsumo " << hai2str(stat.cpai) << endl;
		 	++tehai[0][stat.cpai];


			updateBakyou(bak0,0);
			for(int i=0;i<34;i++)
				ai0->tehai[i]=tehai[0][i];
			ai0->kiru();
			kr = ai0->act->cnum;
			if (ai0->act->Act==2) {
				cout << "tsumo!" << endl;
				calcAgariPart(ai0->tehai, ai0->bak);
				break;
			}
			if (ai0->act->Act==6) {
				dapai(pos_ptr, kr, false, true, true);
				cout << "Riichi!" << endl;
			} else {
				dapai(pos_ptr, kr, false, true, false);
			}

		} else {
			dapai(pos_ptr, stat.cpai, stat.isRed, true, false);

			updateBakyou(bak0,0);

			for(int i=0;i<34;i++)
				ai0->tehai[i]=tehai[0][i];
			ai0->check();
			if (ai0->act->Act==2) {
				cout << "ron!" << endl;
				calcAgariPart(ai0->tehai, ai0->bak);
				break;
			}
		}
		if (ptr==dead_ptr) Ryukyoku=true;
	}
	if (Ryukyoku) cout << "Ryukyoku." << endl;
	delete ai0;
	
	clearGame();
}

void MAJ::syanpai(int pos)
{
	int cpai=pai[ptr]>>2;
	++tehai[pos][cpai];
	if(check_aka(cpai)) aka_tehai[pos][check_aka(cpai)-1]=1;
	stat.cpai=cpai;
	stat.act_stat=ACT_TSUMO;
	stat.isRiichi=false;
	stat.dacya=pos;
	stat.isRed=check_aka(cpai);
	++ptr;
	++jun[pos];

//	cout << "junmoku " << jun[pos] << ": pos " << pos << " tehai: " << tehai2str(tehai[pos])
//	     << "  tsumo " << hai2str(cpai) << endl;
}
void MAJ::dapai(int pos, int cpai, int isRed, bool isTekiri, bool isRiichi)
{
	--tehai[pos][cpai];
	if (isRed) {
		aka_tehai[pos][isRed]=0;
		aka_river[pos][isRed]=1;
	}
	
	int chak = check_aka(cpai);
	if( chak && tehai[pos][cpai]==0) aka_tehai[pos][chak]=0;  // for safe
	river[pos].push_back(cpai);
	stat.cpai = cpai;
	stat.act_stat = isTekiri?ACT_TEKIRI:ACT_TSUMOGIRI;
	stat.isRiichi=false;
	stat.dacya=pos;
	stat.isRed = isRed;
	++pos_ptr;

	if (isRiichi) {
		stat.isRiichi=true;
		riichi[pos]=jun[pos];
	}

	if (pos_ptr>=4) pos_ptr-=4;

	cout << "   pos " << pos << " da   " << hai2str(cpai) << endl;
}

int MAJ::check_aka(int cpai)
{
	if(cpai==16) return 1;
	if(cpai==52) return 2;
	if(cpai==88) return 3;
	return 0;
}
