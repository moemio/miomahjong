#include "defs.h"
#include "tools.h"

using std::string;


string hai2str(int cpai)
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

string tehai2str(int tehai[])
{
	int i,j;
	string sth="";
	int tmp=0;
	for(i=0;i<9;i++) { if (tehai[i]) {
		tmp=1; for(j=0;j<tehai[i];j++) sth += ('1'+i); }}
	if (tmp==1) sth += 'm';
	tmp=0;
	for(i=0;i<9;i++) { if (tehai[i+9]) {
		tmp=1; for(j=0;j<tehai[i+9];j++) sth += ('1'+i); }}
	if (tmp==1) sth += 'p';
	tmp=0;
	for(i=0;i<9;i++) { if (tehai[i+18]) {
		tmp=1; for(j=0;j<tehai[i+18];j++) sth += ('1'+i); }}
	if (tmp==1) sth += 's';
	tmp=0;
	for(i=0;i<7;i++) { if (tehai[i+27]) {
		tmp=1; for(j=0;j<tehai[i+27];j++) sth += ('1'+i); }}
	if (tmp==1) sth += 'z';
	return sth;
}


int Tokenize(char* s, char*** tok)
{
    char test[MAX_LINE];
    char *sep = "\t \n!=";
    char *word;
    int count = 0;
    strncpy( test, s, MAX_LINE );
    for(word = strtok(test,sep); word; word = strtok(NULL,sep))
    {
        strncpy( (*tok)[count], word, MAX_LINE);
        count++;
    }
    return count;
}
