/* Code writing 1993-2020 by Suvorov Bogdan
Address: Ukraine, Sumy region, Konotop city, village Novomutin, st.Metalistov 8
Phone mobile / WhatsApp / Viber / Duo: +380 98 8988692
Skype: live:emailbsuv
Telegram: @bogdansuvorov
Discord: https://discord.gg/qJNU8Yh
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>
#include <time.h>

int find(const char *s, const char *key)
{
	int len = strlen(key);
	int len2 = strlen(s);
	bool crc;
	if(len<len2)
	for(int i = 0; i<(len2-len); i++)
	{
		crc=true;
		for(int i1 = 0; i1<len; i1++)
		if(s[i+i1]!=key[i1])crc=false;

		if(crc) return 1;

	}
    return 0;
}
int clen;
char *cbuf;



void lstrcat(char *buff,const char *past)
{
	int len=0,len0,len1;
	len0=strlen(buff);
	len1=strlen(past);
	memcpy(buff+len0,past,len1);memset(buff+len0+len1,0,1);
}

inline char* intToStr(int i){
	static char strt[18]="";memset(strt,0,18);
	snprintf(strt, 17, "%ld", i);

	return (char *)strt;
}
inline bool strToInt(const char *s, int *i){
	char *endChar;
	setlocale(LC_NUMERIC, "C");
	int t = strtol(s, &endChar, 10);
	*i=t;
	if(*endChar!='\0')return false;

	return true;
}
inline int strToInt(const char *s){
	char *endChar;
	setlocale(LC_NUMERIC, "C");
	int t = strtol(s, &endChar, 10);
	if(*endChar!='\0')return -1;

	return t;
}
inline char* doubleToStr(double d,int precsion) {
	static char strotskok[18]="";
	memset(strotskok,0,18);
	snprintf(strotskok, 12, "%.*f", precsion,d);

	return (char *)strotskok;
}
inline char* timeToStr(const time_t st) {
	static char strtime1[28]="";
    tm stm1;
    time_t st1;
    st1=time(0);
	memset(strtime1,0,28);
	memset(&stm1,0,sizeof(struct tm));
	if(st==0)
	stm1=*localtime((const time_t *)&st1);
	else
	stm1=*localtime((const time_t *)&st);
	strftime(strtime1,27,"%d.%m.%Y %H:%M:%S ",&stm1);
	return (char *)strtime1;
}
inline char* gmtimeToStr(const time_t st) {
	static char gmstrtime[28]="";
     tm stm1;
     time_t st1;
    st1=time(0);
	memset(&gmstrtime,0,28);
	memset(&stm1,0,sizeof(struct tm));
	if(st==0)
	stm1=*gmtime((const time_t *)&st1);
	else
	stm1=*gmtime((const time_t *)&st);
	strftime(gmstrtime,27,"%d.%m.%Y %H:%M ",&stm1);
	return (char *)gmstrtime;
}
inline int rdtsc(){__asm__ __volatile__("rdtsc");}
inline char* substr(const char* S, const int pos, const int len){
	int i;
	char *SubS;
	if ( pos+len <= strlen(S)){
		SubS = (char *)malloc(len+1);
		for (i=0;i<len;i++) SubS[i] = S[pos+i];
		SubS[len] = (char) NULL;
	} else SubS = NULL;

	return (char *)SubS;
}
int randptr,roots[256],roots2[256],roots3[256],roots4[256],rtmp[256],randcnt,randcnt2,randbytes[65536],rootscnt,rootscnt2,rootscnt3,rootscnt4;
void initrandbytes(){
	for(int z1=0;z1<51;z1++){for(int z=0;z<65536;z++){randbytes[z]^=((rand()<<1) % 65536)&255;}}
	for(int z1=0;z1<5;z1++)for(int z=0;z<65536;z++)randbytes[z]^=(randbytes[(z+1)%65536]>>1)&255;
	randptr=0;randcnt=65535;randcnt2=0;
}
void findroots(){
	rootscnt=0;
	int tmp=0;
	for(int z=0;z<10;z++)rtmp[z]=randbytes[z];
	
	for(int z1=0;z1<256;z1++){
	tmp=0;
		for(int z=0;z<10;z++)rtmp[z]^=rtmp[(z+1)%10];
		for(int z2=0;z2<10;z2++)tmp^=rtmp[z2];
		if(tmp==z1){roots[rootscnt]=z1;rootscnt++;}
	}

}
void findroots2(){
	rootscnt2=0;
	int tmp=0;
	for(int z=0;z<10;z++)rtmp[z]=randbytes[z];
	
	for(int z1=0;z1<256;z1++){
	tmp=0;
		{for(int z=0;z<10;z++)rtmp[z]^=rtmp[(z+1)%10];for(int z=0;z<5;z++)rtmp[z]^=rtmp[(z+5)];}
		for(int z2=0;z2<10;z2++)tmp^=rtmp[z2];
		if(tmp==z1){roots2[rootscnt2]=z1;rootscnt2++;}
	}

}
void findroots3(){
	rootscnt3=0;
	int tmp=0;
	for(int z=0;z<10;z++)rtmp[z]=randbytes[z];
	
	for(int z1=0;z1<256;z1++){
	tmp=0;
		//for(int z3=0;z3<9;z3++)
		{for(int z=0;z<10;z++)rtmp[z]^=rtmp[(z+1)%10];for(int z=0;z<9;z+=2)rtmp[z]^=rtmp[(z+1)];}
		for(int z2=0;z2<10;z2++)tmp^=rtmp[z2];
		if(tmp==z1){roots3[rootscnt3]=z1;rootscnt3++;}
	}

}
void findroots4(){
	rootscnt4=0;
	int tmp=0;
	for(int z=0;z<10;z++)rtmp[z]=randbytes[z];
	
	for(int z1=0;z1<256;z1++){
	tmp=0;
		{for(int z=0;z<10;z++)rtmp[z]^=rtmp[(z+1)%10];for(int z=0;z<9;z+=3)rtmp[z]^=rtmp[(z+1)];}
		for(int z2=0;z2<10;z2++)tmp^=rtmp[z2];
		if(tmp==z1){roots4[rootscnt4]=z1;rootscnt4++;}
	}

}
void a1(){
	char *stm1;
	stm1 = (char *)malloc(1000);
	memset(stm1,0,1000);

	rdtsc();
	srand(time(0));
	initrandbytes();

	//lstrcat(stm1,"\[\033[0;0f\]");
//	lstrcat(stm1,"\e[1;32m");
	for(int z=0;z<10;z++){lstrcat(stm1,intToStr(randbytes[z]));lstrcat(stm1," ");}
	//lstrcat(stm1,"\r\n");
	while (strlen(stm1)<41)lstrcat(stm1," ");
	lstrcat(stm1,"\t");

	findroots();findroots2();findroots3();findroots4();
//	lstrcat(stm1,"\e[1;31m");
	for(int z=0;z<rootscnt;z++){lstrcat(stm1,intToStr(roots[z]));lstrcat(stm1," ");}
	//lstrcat(stm1," ");
/*	lstrcat(stm1,"\e[1;33m");
	for(int z=0;z<rootscnt2;z++){lstrcat(stm1,intToStr(roots2[z]));lstrcat(stm1," ");}
	//lstrcat(stm1," ");
	lstrcat(stm1,"\e[1;34m");
	for(int z=0;z<rootscnt3;z++){lstrcat(stm1,intToStr(roots3[z]));lstrcat(stm1," ");}
	//lstrcat(stm1," ");	
	lstrcat(stm1,"\e[1;35m");
	for(int z=0;z<rootscnt4;z++){lstrcat(stm1,intToStr(roots4[z]));lstrcat(stm1," ");}
*/	
	lstrcat(stm1,"\r\n");	

	printf(stm1);

	free(stm1);
}
int main(int argc, char *argv[]){
for(int z=0;z<20;z++)a1();
}
