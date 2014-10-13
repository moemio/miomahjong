#include "defs.h"
#include "yaku.h"
#include "agari.h"

using namespace std;
using std::string;

string AGARI_PART::hai2str(int cpai)
{
	string sth="";
	char tp;
	if (cpai>=9) {cpai-=9;tp='p';}
	else tp='m';
	if (cpai>=9) {cpai-=9;tp='s';}
	if (cpai>=9) {cpai-=9;tp='z';}
	sth += ('1'+cpai);
	sth += tp;
	return sth;
}

AGARI_PART::AGARI_PART(int a[], BAKYOU * bk)
{
	n_mentsu=0;
	n_syuntsu=0;
	n_kotsu=0;
	atama=0;
	int i;
	for(i=0;i<34;++i){
		c[i]=a[i];
		tehai[i]=a[i];
		kotsu[i]=0;
		syuntsu[i]=0;
	}
	pattern.clear();
	for(i=0;i<46;++i)
		yaku[i]=0;
	bak = bk;
	isKokushi=0;
	isChiitoi=0;
}

void AGARI_PART::countScore(PATTERN &part, BAKYOU * bk)
{
	YAKU * yak = new YAKU(part, bk);
	yak->countFan();
}
void AGARI_PART::printFan(PATTERN &part)
{
	int i;
	int fan_tmp;

	cout << "dora : ";
	for(i=0;i<bak->n_dora;++i)
		cout << "  " << hai2str(bak->dora[i]);
	cout << endl;
	
	if (bak->riichi[0]) {
		cout << "ura : ";
		for (i=0;i<bak->n_dora;++i)
			cout << "  " << hai2str(bak->ura[i]);
		cout << endl;
		}

	if (part.isYakuman)	cout << "  " << part.yakuman_baisu << " bai YAKUMAN!" << endl;
	cout << "  " << part.fu_tmp << " -> " << part.fu << " fu  " << part.fan << " fan  " << endl;
	if (bak->jifuu==27) {
		cout << " Score: " << part.score;
		if(bak->stat.dacya=0) cout << " ( " << part.score_ko << " all )";
		cout << endl;
	}
	else { 
		cout << " Score: " << part.score ;
		if(bak->stat.dacya=0) cout << " ( " << part.score_oya << " , " << part.score_ko << " )";
		cout << endl;
	}
	for (i=0;i<46;++i)
		if (part.yaku[i]) 
			cout << "     " << YAKU_NAME[i] << "   " << part.yaku[i] << " Fan" << endl;
}
void AGARI_PART::updateResult()
{
	AGARI_PART *e = this;
	int i,j;
	PATTERN part;
	part.isYakuman=false;
	part.isChiitoi=false;
	part.isKokushi=false;
	part.yakuman_baisu=0;
	if ((e->n_mentsu + bak->n_naru[0])==4 && e->isatama  ) {
		cout << endl << "Agari pattern  ";
		// kotsu
		for (i=0;i<34;++i)
			if (e->kotsu[i]) cout << e->hai2str(i) << e->hai2str(i) << e->hai2str(i) << " ";
		// syuntsu
		for (i=0;i<34;++i)
			if (e->syuntsu[i])
				for (j=0;j<e->syuntsu[i];j++)
					cout << e->hai2str(i) << e->hai2str(i+1) << e->hai2str(i+2) << " ";
		cout << e->hai2str(e->atama) << e->hai2str(e->atama);
		cout << "   dora: ";
		for (i=0;i<bak->n_dora;++i)
			cout << e->hai2str(bak->dora[i]);
		cout << "   ura: ";
		for (i=0;i<bak->n_dora;++i)
			cout << e->hai2str(bak->ura[i]);
		cout << endl;
		
		part.n_kotsu=e->n_kotsu;
		part.n_syuntsu=e->n_syuntsu;
		part.naki_n_kotsu=bak->n_naki_kotsu[0];
		part.naki_n_syuntsu = bak->n_naki_syuntsu[0];
		for(i=0;i<34;++i) {
			part.c[i]=e->tehai[i];
			part.kotsu[i]=e->kotsu[i];
			part.syuntsu[i]=e->syuntsu[i];
		    part.naki_kotsu[i]=bak->naru_pon[0][i];
		    part.naki_syuntsu[i]=bak->naru_chii[0][i];

		    part.naki_kotsu[i] += bak->naru_kan[0][i];
		    part.kotsu[i]      += bak->naru_ankan[0][i];
		}
		part.atama=e->atama;

		e->countScore(part, bak);
		e->printFan(part); 
		e->pattern.push_back(part);
	}
/*	
	if (e->n_mentsu==4 && e->isatama) {
		cout << endl;
		cout << "---Agari partern " << endl;
		cout << "kotsu: " << e->n_kotsu << "    ";
		for (i=0;i<34;i++)
			if(e->kotsu[i]) cout << hai2str(i) << " ";
		cout << endl;
		cout << "syuntsu: " << e->n_syuntsu << "    ";
		for (i=0;i<34;i++)
			if(e->syuntsu[i]) cout << hai2str(i) << hai2str(i+1) << hai2str(i+2) << " ";
		cout << endl;
		cout << "atama:  " << hai2str(e->atama) << endl;

	}
*/

/*
	if (e->n_mentsu==4 && e->isatama) cout << "########Agari partern!" << endl;
	else cout << "----" << endl;
	cout << "mentsu: " << e->n_mentsu << endl;
	cout << "kotsu: " << e->n_kotsu << "    ";
	for (i=0;i<34;i++)
		if(e->kotsu[i]) cout << hai2str(i) << " ";
	cout << endl;
	cout << "syuntsu: " << e->n_syuntsu << "    ";
	for (i=0;i<34;i++)
		if(e->syuntsu[i]) cout << hai2str(i) << hai2str(i+1) << hai2str(i+2) << " ";
	cout << endl;
	if (e->isatama) cout << "atama: " << hai2str(e->atama) << endl;
	else cout <<"atama: nai" << endl;
*/
}

void AGARI_PART::Run(int depth)
{
	AGARI_PART *e = this;
	int *c = e->c;
	for (; depth<27&&!c[depth];++depth);
	e->updateResult();

	int i=depth;
	if (i>8) i-=9;
	if (i>8) i-=9;
	switch( c[depth] ) {
	case 4: {
		e->i_kotsu(depth);
		if (i<7&&c[depth+1]&&c[depth+2]) {
			e->i_syuntsu(depth); e->Run(depth+1); e->d_syuntsu(depth);
		}
		e->d_kotsu(depth);
		if (!e->isatama) {
			e->i_atama(depth);
			if (i<7&&c[depth+1]&&c[depth+2]) {
				e->i_syuntsu(depth); e->Run(depth); e->d_syuntsu(depth);  //marker : run(depth+1)
			}
			e->d_atama(depth);
		}
		break;}
	case 3:{
		e->i_kotsu(depth); e->Run(depth+1); e->d_kotsu(depth);

		if (!e->isatama) {
			e->i_atama(depth);
			if (i<7&&c[depth+1]&&c[depth+2]) {
				e->i_syuntsu(depth); e->Run(depth+1); e->d_syuntsu(depth);  }
			e->d_atama(depth);
		}
		if (i<7&&c[depth+1]>=2&&c[depth+2]>=2) {
			e->i_syuntsu(depth); e->Run(depth); e->d_syuntsu(depth); } //marker : run twice
		break;}
	case 2:{
		if (!e->isatama) {
			e->i_atama(depth); e->Run(depth+1); e->d_atama(depth); }
		if (i<7&&c[depth+1]&&c[depth+2]) {
			e->i_syuntsu(depth); e->Run(depth); e->d_syuntsu(depth); } //marker : run twice
		break;}	
	case 1:{
		if (i<7&&c[depth+1]&&c[depth+2]) {
			e->i_syuntsu(depth); e->Run(depth+1); e->d_syuntsu(depth); } 
	break;}
	}
}

void AGARI_PART::wari()
{
	this->Run(0);
	
}

void AGARI_PART::i_kotsu(int k)
	{this->c[k]-=3; ++this->n_mentsu; ++this->kotsu[k]; ++this->n_kotsu;}

void AGARI_PART::d_kotsu(int k)
	{this->c[k]+=3; --this->n_mentsu; --this->kotsu[k]; --this->n_kotsu;}

void AGARI_PART::i_syuntsu(int k)
	{--this->c[k];--this->c[k+1];--this->c[k+2]; ++this->n_mentsu; ++this->n_syuntsu; ++this->syuntsu[k];}

void AGARI_PART::d_syuntsu(int k)
	{++this->c[k];++this->c[k+1];++this->c[k+2]; --this->n_mentsu; --this->n_syuntsu; --this->syuntsu[k];}

void AGARI_PART::i_atama(int k)
	{this->c[k]-=2; this->atama=k; this->isatama = 1;}

void AGARI_PART::d_atama(int k)
	{this->c[k]+=2; this->isatama = 0;}


void AGARI_PART::removeJihai()
{
	AGARI_PART *e = this;
	int *c = e->c;
	int i;
	for(i=27;i<34;++i) {
		if (c[i]==2) e->i_atama(i);
		if (c[i]==3) e->i_kotsu(i);
	}	
}


bool isMentsu(int m)
{
	int a=(m&7), b=0, c=0;
	if (a==1 || a==4) b=c=1; else if (a==2) b=c=2;
	m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
	m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
	m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
	m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
	m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
	m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
	m>>=3, a=(m&7)-b;if (a!=0 && a!=3) return false;
	m>>=3, a=(m&7)-c;
	return a==0 || a==3;
}

bool isAtamaMentsu(int nn, int m)
{
	if (nn==0){
		if ((m&(7<< 6))>=(2<< 6) && isMentsu(m-(2<< 6))) return true;
		if ((m&(7<<15))>=(2<<15) && isMentsu(m-(2<<15))) return true;
		if ((m&(7<<24))>=(2<<24) && isMentsu(m-(2<<24))) return true;
	}else if (nn==1){
		if ((m&(7<< 3))>=(2<< 3) && isMentsu(m-(2<< 3))) return true;
		if ((m&(7<<12))>=(2<<12) && isMentsu(m-(2<<12))) return true;
		if ((m&(7<<21))>=(2<<21) && isMentsu(m-(2<<21))) return true;
	}else if (nn==2){
		if ((m&(7<< 0))>=(2<< 0) && isMentsu(m-(2<< 0))) return true;
		if ((m&(7<< 9))>=(2<< 9) && isMentsu(m-(2<< 9))) return true;
		if ((m&(7<<18))>=(2<<18) && isMentsu(m-(2<<18))) return true;
	}
	return false;
}

int cc2m(int c[], int d)
{
	return (c[d+0]<< 0)|(c[d+1]<< 3)|(c[d+2]<< 6)|
	       (c[d+3]<< 9)|(c[d+4]<<12)|(c[d+5]<<15)|
		   (c[d+6]<<18)|(c[d+7]<<21)|(c[d+8]<<24);
}

bool agari_test( int c[] )
{
	int j=(1<<c[27])|(1<<c[28])|(1<<c[29])|(1<<c[30])|(1<<c[31])|(1<<c[32])|(1<<c[33]);

	if (j>=0x10) return false;
	// Kokushi musou
	if (((j&3)==2) && (c[0]*c[8]*c[9]*c[17]*c[18]*c[26]*c[27]*c[28]*c[29]*c[30]*c[31]*c[32]*c[33]==2)) return true;
	// 7 tui tsu
	if (!(j&10) && (
			(c[ 0]==2)+(c[ 1]==2)+(c[ 2]==2)+(c[ 3]==2)+(c[ 4]==2)+(c[ 5]==2)+(c[ 6]==2)+(c[ 7]==2)+(c[ 8]==2)+
			(c[ 9]==2)+(c[10]==2)+(c[11]==2)+(c[12]==2)+(c[13]==2)+(c[14]==2)+(c[15]==2)+(c[16]==2)+(c[17]==2)+
			(c[18]==2)+(c[19]==2)+(c[20]==2)+(c[21]==2)+(c[22]==2)+(c[23]==2)+(c[24]==2)+(c[25]==2)+(c[26]==2)+
			(c[27]==2)+(c[28]==2)+(c[29]==2)+(c[30]==2)+(c[31]==2)+(c[32]==2)+(c[33]==2))==7) return true;
	if (j&2) return false;
	int n00 = c[ 0]+c[ 3]+c[ 6], n01 = c[ 1]+c[ 4]+c[ 7], n02 = c[ 2]+c[ 5]+c[ 8];
	int n10 = c[ 9]+c[12]+c[15], n11 = c[10]+c[13]+c[16], n12 = c[11]+c[14]+c[17];
	int n20 = c[18]+c[21]+c[24], n21 = c[19]+c[22]+c[25], n22 = c[20]+c[23]+c[26];
	int n0 = (n00+n01+n02)%3;
	if (n0==1) return false;
	int n1 = (n10+n11+n12)%3;
	if (n1==1) return false;
	int n2 = (n20+n21+n22)%3;
	if (n2==1) return false;
	if ((n0==2)+(n1==2)+(n2==2)+
			(c[27]==2)+(c[28]==2)+(c[29]==2)+(c[30]==2)+(c[31]==2)+(c[32]==2)+(c[33]==2)!=1) return false;
    int nn0=(n00*1+n01*2)%3, m0=cc2m(c, 0);
	int nn1=(n10*1+n11*2)%3, m1=cc2m(c, 9);
	int nn2=(n20*1+n21*2)%3, m2=cc2m(c,18);
	if (j&4) return !(n0|nn0|n1|nn1|n2|nn2) && isMentsu(m0) && isMentsu(m1) && isMentsu(m2);
	if (n0==2) return !(n1|nn1|n2|nn2) && isMentsu(m1) && isMentsu(m2) && isAtamaMentsu(nn0,m0);
	if (n1==2) return !(n2|nn2|n0|nn0) && isMentsu(m2) && isMentsu(m0) && isAtamaMentsu(nn1,m1);
	if (n2==2) return !(n0|nn0|n1|nn1) && isMentsu(m0) && isMentsu(m1) && isAtamaMentsu(nn2,m2);
	return false;
}

void AGARI_PART::TokuHandan()
{
	int *c = this->tehai;
	if (c[0]*c[8]*c[9]*c[17]*c[18]*c[26]*c[27]*c[28]*c[29]*c[30]*c[31]*c[32]*c[33]==2) isKokushi=true;
	if (((c[ 0]==2)+(c[ 1]==2)+(c[ 2]==2)+(c[ 3]==2)+(c[ 4]==2)+(c[ 5]==2)+(c[ 6]==2)+(c[ 7]==2)+(c[ 8]==2)+
		 (c[ 9]==2)+(c[10]==2)+(c[11]==2)+(c[12]==2)+(c[13]==2)+(c[14]==2)+(c[15]==2)+(c[16]==2)+(c[17]==2)+
		 (c[18]==2)+(c[19]==2)+(c[20]==2)+(c[21]==2)+(c[22]==2)+(c[23]==2)+(c[24]==2)+(c[25]==2)+(c[26]==2)+
		 (c[27]==2)+(c[28]==2)+(c[29]==2)+(c[30]==2)+(c[31]==2)+(c[32]==2)+(c[33]==2))==7) isChiitoi=true;
	PATTERN part;
	part.isChiitoi=false;
	part.isKokushi=false;
	part.isYakuman=false;
	part.yakuman_baisu=0;
	int i,j;
	for(i=0;i<34;++i) {
		part.c[i]=c[i];
		part.syuntsu[i]=0;
		part.kotsu[i]=0;
		part.naki_syuntsu[i]=0;
		part.naki_kotsu[i]=0;
	}
	part.n_syuntsu=0;
	part.n_kotsu=0;
	part.naki_n_syuntsu=0;
	part.naki_n_kotsu=0;
	part.n_naru=0;
	part.atama=-1;
	if (this->isChiitoi) {
		cout << endl << "Agari pattern  ";
		for(i=0;i<34;++i) {
			part.toitsu[i]=(c[i]==2);
			if (c[i]==2) cout << this->hai2str(i) << this->hai2str(i) << " ";
		}
		cout << endl;
		part.isChiitoi=true;
	
	countScore(part, bak);
	printFan(part); 
	pattern.push_back(part);

	}

	if (this->isKokushi) {
		cout << endl << "Agari pattern  ";
		for(i=0;i<34;++i)
			if (c[i]==1) cout << this->hai2str(i) << " ";
			else if (c[i]==2) j=i;
		cout << this->hai2str(j) << this->hai2str(j);
		part.atama=j;
		cout << endl;
		part.isKokushi=true;


	countScore(part, bak);
	printFan(part); 
	pattern.push_back(part);


	}
	

}

void calcAgariPart( int c[], BAKYOU * bak)
{
	AGARI_PART *e = new AGARI_PART(c, bak);

	cout << endl << "agari hai: " << e->hai2str(bak->stat.cpai) << endl;
	e->TokuHandan();	
	e->removeJihai();
	e->wari();
	int i,sc=0;
	//vector<PATTERN>::iterator it;
	for(i=0;i<e->pattern.size();++i) {
		if(e->pattern[i].score>sc) {
			sc=e->pattern[i].score;
			e->maxp=i;
		}
	}
	e->printFan(e->pattern[e->maxp]);
	cout << "size:" << e->pattern.size() << endl;
}

