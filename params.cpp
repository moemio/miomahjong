#include "defs.h"
#include "tools.h"

void read_params(PARAMS *params, char* params_file)
{

	FILE *fp;
	char *s;
	char **tmp;
	int c,i;
	fp = fopen(params_file, "r");
	s = (char*) malloc(sizeof(char)*MAX_LINE);
	tmp = (char**) malloc(sizeof(char*)*MAX_TOKENS);
	for(i=0;i<MAX_TOKENS;i++)
		tmp[i]=(char*)malloc(sizeof(char)*MAX_LINE);
	
	while (!feof(fp))
	{
		fgets(s,MAX_LINE,fp);
		c=Tokenize(s,&tmp);
		if(!strcmp(tmp[0],"syanten")) {
			params->syanten_f1_a = atof(tmp[1]);
			params->syanten_f1_b = atof(tmp[2]);
			params->syanten_f1_c = atof(tmp[3]);
			params->syanten_Ea = atof(tmp[4]);
		} else if(!strcmp(tmp[0],"maisu")) {
			params->maisu_p1 = atof(tmp[1]);
		}
	}
	cout << "maisu p1 " << params->maisu_p1;
	fclose(fp);
}
