
class SYANTEN {
  public:
	
	int n_eval;
	int c[34];
	int n_mentsu;
	int n_tatsu;
	int n_toitsu;
	int n_jidahai;
	int f_n4;
	int f_koritsu;
	
	int min_syanten;
	
	void updateResult();
	//void init( int a[], int n );
	SYANTEN (int* , int );
	~SYANTEN();
	int scan713(int&);
	void scanNormal(int init_mentsu);
	void removeJihai(int nc);
	void Run(int depth);
	void i_anko(int k);
	void d_anko(int k);
	void i_toitsu(int k);
	void d_toitsu(int k);
	void i_syuntsu(int k);
	void d_syuntsu(int k);
	void i_tatsu_r(int k);
	void d_tatsu_r(int k);
	void i_tatsu_k(int k);
	void d_tatsu_k(int k);
	void i_koritsu(int k);
	void d_koritsu(int k);
	int count34();
#ifdef MIO_DEBUG_SYANTEN	
	 int debug_mentsu;
	 int debug_toitsu;
	 int debug_tatsu;
	 int debug_jidahai;
#endif
};
int count_syanten_all(int tehai[]);
int count_syanten_no713(int tehai[]);
