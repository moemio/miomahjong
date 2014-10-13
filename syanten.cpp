#include "defs.h"
#include "syanten.h"

using namespace std;

SYANTEN::SYANTEN( int *a, int n)
{
	int i;
	for (i=0;i<34;i++)
		c[i]=0;
	n_mentsu     = 0;
	n_tatsu      = 0;
	n_toitsu     = 0;
	n_jidahai    = 0;
	f_n4         = 0;
	f_koritsu    = 0;

	min_syanten = 8;
	
	//if (n==136){
	//	for(n=0;n<136;++n) if(a[n]) ++c[n>>2];
	//} else if (n==34) {
		for(i=0;i<34;i++) c[i]=a[i];
	//} else {
	//	for(n-=1;n>=0;--n) ++c[a[n]>>2];
	//}
#ifdef MIO_DEBUG_SYANTEN
	debug_mentsu = 0;
	debug_toitsu = 0;
	debug_tatsu = 0;
	debug_jidahai = 0;
#endif
}

void SYANTEN::updateResult()
{
	SYANTEN *e = this;
	int ret_syanten = 8-e->n_mentsu*2-e->n_tatsu-e->n_toitsu;
	int n_mentsu_kouho = e->n_mentsu+e->n_tatsu;
	if (e->n_toitsu) {
		n_mentsu_kouho+=e->n_toitsu-1;
	} else if (e->f_n4 && e->f_koritsu) {
		if ((e->f_n4|e->f_koritsu)==e->f_n4) ++ret_syanten;
	}
	if (n_mentsu_kouho>4) ret_syanten+=(n_mentsu_kouho-4);
	if (ret_syanten!=-1 && ret_syanten<e->n_jidahai) ret_syanten=e->n_jidahai;
	if (ret_syanten<e->min_syanten){
		e->min_syanten = ret_syanten;
#ifdef MIO_DEBUG_SYANTEN
		e->debug_mentsu = e->n_mentsu;
		e->debug_toitsu = e->n_toitsu;
		e->debug_tatsu = e->n_tatsu;
		e->debug_jidahai = e->n_jidahai;
#endif
	}
}


void SYANTEN::i_anko(int k)    { this->c[k]-=3; ++this->n_mentsu;}
void SYANTEN::d_anko(int k)    { this->c[k]+=3; --this->n_mentsu;}
void SYANTEN::i_toitsu(int k)  { this->c[k]-=2; ++this->n_toitsu;}
void SYANTEN::d_toitsu(int k)  { this->c[k]+=2; --this->n_toitsu;}
void SYANTEN::i_syuntsu(int k) { --this->c[k]; --this->c[k+1]; --this->c[k+2]; ++this->n_mentsu;}
void SYANTEN::d_syuntsu(int k) { ++this->c[k]; ++this->c[k+1]; ++this->c[k+2]; --this->n_mentsu;}
void SYANTEN::i_tatsu_r(int k) { --this->c[k]; --this->c[k+1]; ++this->n_tatsu;}
void SYANTEN::d_tatsu_r(int k) { ++this->c[k]; ++this->c[k+1]; --this->n_tatsu;}
void SYANTEN::i_tatsu_k(int k) { --this->c[k]; --this->c[k+2]; ++this->n_tatsu;}
void SYANTEN::d_tatsu_k(int k) { ++this->c[k]; ++this->c[k+2]; --this->n_tatsu;}
void SYANTEN::i_koritsu(int k) { --this->c[k]; this->f_koritsu|=(1<<k);}
void SYANTEN::d_koritsu(int k) { ++this->c[k]; this->f_koritsu&=~(1<<k);}

int SYANTEN::count34()
{
	int *c = this->c;
	return c[ 0]+c[ 1]+c[ 2]+c[ 3]+c[ 4]+c[ 5]+c[ 6]+c[ 7]+c[ 8]+
	       c[ 9]+c[10]+c[11]+c[12]+c[13]+c[14]+c[15]+c[16]+c[17]+
		   c[18]+c[19]+c[20]+c[21]+c[22]+c[23]+c[24]+c[25]+c[26]+
		   c[27]+c[28]+c[29]+c[30]+c[31]+c[32]+c[33];
}

int SYANTEN::scan713(int& lpz)
{
	SYANTEN *e = this;
	int syanten=e->min_syanten;
	int *c = e->c;
	int n13 = (c[ 0]>=2)+(c[ 8]>=2)+
	          (c[ 9]>=2)+(c[17]>=2)+
			  (c[18]>=2)+(c[26]>=2)+
			  (c[27]>=2)+(c[28]>=2)+(c[29]>=2)+(c[30]>=2)+(c[31]>=2)+(c[32]>=2)+(c[33]>=2);
	int m13 = (c[ 0]!=0)+(c[ 8]!=0)+
	          (c[ 9]!=0)+(c[17]!=0)+
			  (c[18]!=0)+(c[26]!=0)+
			  (c[27]!=0)+(c[28]!=0)+(c[29]!=0)+(c[30]!=0)+(c[31]!=0)+(c[32]!=0)+(c[33]!=0);
	int n7 = n13+
			  (c[ 1]>=2)+(c[ 2]>=2)+(c[ 3]>=2)+(c[ 4]>=2)+(c[ 5]>=2)+(c[ 6]>=2)+(c[ 7]>=2)+
			  (c[10]>=2)+(c[11]>=2)+(c[12]>=2)+(c[13]>=2)+(c[14]>=2)+(c[15]>=2)+(c[16]>=2)+
			  (c[19]>=2)+(c[20]>=2)+(c[21]>=2)+(c[22]>=2)+(c[23]>=2)+(c[24]>=2)+(c[25]>=2);
	int m7 = m13+
			  (c[ 1]!=0)+(c[ 2]!=0)+(c[ 3]!=0)+(c[ 4]!=0)+(c[ 5]!=0)+(c[ 6]!=0)+(c[ 7]!=0)+
			  (c[10]!=0)+(c[11]!=0)+(c[12]!=0)+(c[13]!=0)+(c[14]!=0)+(c[15]!=0)+(c[16]!=0)+
			  (c[19]!=0)+(c[20]!=0)+(c[21]!=0)+(c[22]!=0)+(c[23]!=0)+(c[24]!=0)+(c[25]!=0);
	
	int s7 = 6-n7+(m7<7?7-m7:0);
	int s13 = 13-m13-(n13?1:0);
	//cout << "in 713! stm:" << syanten << "  s7:" << s7 << "  s13:" << s13 << endl;
	syanten = MIN(syanten,s7);
	syanten = MIN(syanten,s13);
	lpz = s7<s13?7:13;
	return syanten;
}

void SYANTEN::removeJihai(int nc)
{
	SYANTEN *e = this;
	int *c = e->c;
	int j_n4=0;
	int j_koritsu=0;
	int i;
	for(i=27;i<34;++i) switch(c[i]) {
		case 4: {++e->n_mentsu; j_n4|=(1<<(i-18)); j_koritsu|=(1<<(i-18)); ++e->n_jidahai; break;}
		case 3: {++e->n_mentsu; break;}
		case 2: {++e->n_toitsu; break;}
		case 1: {j_koritsu|=(1<<(i-18));break;}
		}
	if (e->n_jidahai && (nc%3)==2) --e->n_jidahai;

	if (j_koritsu) {
		e->f_koritsu|=(1<<27);
		if ((j_n4|j_koritsu)==j_n4) e->f_n4|=(1<<27);
	}
}

void SYANTEN::scanNormal(int init_mentsu)
{
	SYANTEN *e = this;
	int *c = e->c;
	e->f_n4|=
		((c[ 0]==4)<< 0)|((c[ 1]==4)<< 1)|((c[ 2]==4)<< 2)|
		((c[ 3]==4)<< 3)|((c[ 4]==4)<< 4)|((c[ 5]==4)<< 5)|
		((c[ 6]==4)<< 6)|((c[ 7]==4)<< 7)|((c[ 8]==4)<< 8)|
		((c[ 9]==4)<< 9)|((c[10]==4)<<10)|((c[11]==4)<<11)|
		((c[12]==4)<<12)|((c[13]==4)<<13)|((c[14]==4)<<14)|
		((c[15]==4)<<15)|((c[16]==4)<<16)|((c[17]==4)<<17)|
		((c[18]==4)<<18)|((c[19]==4)<<19)|((c[20]==4)<<20)|
		((c[21]==4)<<21)|((c[22]==4)<<22)|((c[23]==4)<<23)|
		((c[24]==4)<<24)|((c[25]==4)<<25)|((c[26]==4)<<26);
	this->n_mentsu += init_mentsu;
	e->Run(0);
}

void SYANTEN::Run(int depth)
{
	SYANTEN *e = this;
	++e->n_eval;
	if (e->min_syanten==-1) return;
	int *c = e->c;
	for(;depth<27&&!c[depth];++depth);
	if (depth==27) return e->updateResult();
	
	int i=depth;
	if (i>8) i-=9;
	if (i>8) i-=9;
	switch (c[depth]) {
	case 4: {
		e->i_anko(depth);
		if (i<7&&c[depth+2]) {
			if (c[depth+1]) {e->i_syuntsu(depth); e->Run(depth+1); e->d_syuntsu(depth);}
			e->i_tatsu_k(depth); e->Run(depth+1); e->d_tatsu_k(depth);
		}
		if (i<8 && c[depth+1]) { e->i_tatsu_r(depth); e->Run(depth+1); e->d_tatsu_r(depth);}
		e->i_koritsu(depth); e->Run(depth+1); e->d_koritsu(depth);
		e->d_anko(depth);

		e->i_toitsu(depth);
		if (i<7&&c[depth+2]) {
			if (c[depth+1]) {e->i_syuntsu(depth); e->Run(depth); e->d_syuntsu(depth);}
			e->i_tatsu_k(depth); e->Run(depth+1); e->d_tatsu_k(depth);
		}
		if (i<8&&c[depth+1]) {e->i_tatsu_r(depth); e->Run(depth+1); e->d_tatsu_r(depth);}
		e->d_toitsu(depth);
		break;}
	case 3: {
		e->i_anko(depth); e->Run(depth+1); e->d_anko(depth);

		e->i_toitsu(depth);
		if (i<7&&c[depth+1]&&c[depth+2]) {
			e->i_syuntsu(depth); e->Run(depth+1); e->d_syuntsu(depth);
		} else {
			if (i<7&&c[depth+2]) { e->i_tatsu_k(depth); e->Run(depth+1); e->d_tatsu_k(depth);}
			if (i<8&&c[depth+1]) { e->i_tatsu_r(depth); e->Run(depth+1); e->d_tatsu_r(depth);}
		}
		e->d_toitsu(depth);
		if (i<7&&c[depth+2]>=2&&c[depth+1]>=2) { e->i_syuntsu(depth);
			e->i_syuntsu(depth); e->Run(depth); e->d_syuntsu(depth); e->d_syuntsu(depth);}
		break;}
	case 2: {
		e->i_toitsu(depth); e->Run(depth+1); e->d_toitsu(depth);
		if (i<7&&c[depth+2]&&c[depth+1]) {e->i_syuntsu(depth); e->Run(depth); e->d_syuntsu(depth);}
		break; }
	case 1: {
		if (i<6&&c[depth+1]==1&&c[depth+2]&&c[depth+3]!=4) {
			e->i_syuntsu(depth); e->Run(depth+2); e->d_syuntsu(depth);
		} else {
		//	e->i_koritsu(depth); e->Run(depth+1); e->d_koritsu(depth);
			e->i_koritsu(depth); e->Run(depth+1); e->d_koritsu(depth);

			if (i<7&&c[depth+2]) {
				if (c[depth+1]) {e->i_syuntsu(depth); e->Run(depth+1); e->d_syuntsu(depth);}
				e->i_tatsu_k(depth); e->Run(depth+1); e->d_tatsu_k(depth);
			}
			if (i<8&&c[depth+1]) {e->i_tatsu_r(depth); e->Run(depth+1); e->d_tatsu_r(depth);}
		}
		break;}
	}
}

void calcSyanten(int a[], int n, bool bSkip713, int syanten[], int& lpz)
{
	SYANTEN *st = new SYANTEN(a,n);
	int nc = st->count34();
	if (nc>14) {syanten[0]=-2;syanten[1]=-2;return;}
	if (!bSkip713 && nc>=13) syanten[0]=st->scan713(lpz);
	st->removeJihai(nc);
	double imt = ((14-(float)nc)/3);
	int init_mentsu=(int)floor(imt);
	st->scanNormal(init_mentsu);
	syanten[1]=st->min_syanten;
#ifdef MIO_DEBUG_SYANTEN
	 cout << endl;
	 cout << "mentsu: " << st->debug_mentsu << endl;
	 cout << "toitsu: " << st->debug_toitsu << endl;
	 cout << "tatsu: " << st->debug_tatsu << endl;
	 cout << "jidahai: " << st->debug_jidahai << endl;
#endif
}

int count_syanten_all(int tehai[])
{
	int is713;
	int syanten[2]={8,8};
	calcSyanten(tehai, 34, 0, syanten, is713);
	return MIN(syanten[0],syanten[1]);
}

int count_syanten_no713(int tehai[])
{
	int is713;
	int syanten[2]={8,8};
	calcSyanten(tehai, 34, 0, syanten, is713);
	return syanten[1];
}
