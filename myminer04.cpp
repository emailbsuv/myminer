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
#include <string>

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
int randptr,mainroots[5][65],childroots[65][3][10],roots[256],tmp[256][65],rtmp[256][65],randcnt,randbytes[256],rootscnt,rootptr;
void initrandbytes(){
	int h=0;
	while(h==0){
		for(int z1=0;z1<51;z1++){for(int z=0;z<256;z++){randbytes[z]^=((rand()<<1) % 256)&255;}}
		for(int z1=0;z1<5;z1++)for(int z=0;z<256;z++)randbytes[z]^=(randbytes[(z+1)%256]>>1)&255;
		for(int z=0;z<256;z++)if (randbytes[z]>127)h=1;
	}
	randptr=0;randcnt=255;
}
int getrandbyte(){
	int h=0;
	while(h==0){
		for(int z1=0;z1<51;z1++){for(int z=0;z<256;z++){randbytes[z]^=((rand()<<1) % 256)&255;}}
		for(int z1=0;z1<5;z1++)for(int z=0;z<256;z++)randbytes[z]^=(randbytes[(z+1)%256]>>1)&255;
		for(int z=0;z<256;z++)if (randbytes[z]>127)h=1;
	}
	randptr=0;randcnt=255;	
	return randbytes[((rand()<<1) % 256)&255];
}
void findroots(int rootlevel){
	rootscnt=0;
	int tmp1=0;
	
	for(int z1=0;z1<256;z1++){
	tmp1=0;
		for(int z=0;z<10;z++)rtmp[z][rootptr]^=rtmp[(z+1)%10][rootptr];
		for(int z2=0;z2<10;z2++)tmp1^=rtmp[z2][rootptr];
		if(tmp1==z1){
			roots[rootscnt]=z1;
			childroots[rootptr][rootlevel/2][rootscnt]=z1;
			rootscnt++;
		}
	}
	mainroots[rootlevel][rootptr]=rootscnt;
	mainroots[rootlevel+1][rootptr]=roots[0];
}
void deroot(){
	for(int z=0;z<10;z++)rtmp[z][rootptr]=tmp[z][rootptr];
	for(int z1=0;z1<mainroots[1][rootptr];z1++){
		for(int z=9;z>=0;z--)rtmp[z][rootptr]^=rtmp[(z+1)%10][rootptr];
	}
}
void trap(){
	char *stm1;char *stm11;
	stm1 = (char *)malloc(100000);
	memset(stm1,0,100000);
	stm11 = (char *)malloc(1000);
	memset(stm11,0,1000);
	
	rootptr=0;
	for(int i=0;i<32;i++){
		memset(stm11,0,1000);
		lstrcat(stm11,intToStr(rootptr));lstrcat(stm11,"\t");
		for(int z=0;z<10;z++){lstrcat(stm11,intToStr(rtmp[z][rootptr]));lstrcat(stm11," ");}
		while(strlen(stm11)<55)lstrcat(stm11," ");
		lstrcat(stm1,stm11);
		lstrcat(stm1,"\t");
		findroots(0);
		if(mainroots[0][rootptr]!=1)for(int z=0;z<mainroots[0][rootptr];z++){lstrcat(stm1,intToStr(childroots[rootptr][0][z]));lstrcat(stm1," ");}
		else {
			for(int z=0;z<mainroots[0][rootptr];z++){lstrcat(stm1,intToStr(childroots[rootptr][0][z]));lstrcat(stm1," ");}
			deroot();
			findroots(2);
			lstrcat(stm1,"\t\t | \t\t");
			if(mainroots[2][rootptr]!=1)
				for(int z=0;z<mainroots[2][rootptr];z++){lstrcat(stm1,intToStr(childroots[rootptr][1][z]));lstrcat(stm1," ");}
			else
				lstrcat(stm1,"+1");
		}
		lstrcat(stm1,"\r\n");	

		rootptr++;
	}
    printf(stm1);
	free(stm1);
}
int main(int argc, char *argv[]){
	rdtsc();
	srand(time(0));
	rootptr=0;
	for(int i=0;i<32;i++){
		initrandbytes();
		for(int z=0;z<10;z++){
			rtmp[z][rootptr]=getrandbyte();
			tmp[z][rootptr]=rtmp[z][rootptr];
		}
		rootptr++;
	}
	
trap();
/*
	const char* s = "Hello Trap!\r\n";
	char s1;
	char *stm1;
	stm1 = (char *)malloc(100000);
	memset(stm1,0,100000);
	for(int i=0;i<strlen(s);i++){
		lstrcat(stm1,intToStr((char)(int)s[i]));
		s1 = (char)(int)s[i];
		lstrcat(stm1," ");
		for(int i1=0;i1<8;i1++){
			if((s1&128)==128)lstrcat(stm1,"1");else lstrcat(stm1,"0");
			s1=s1<<1;
		}
		lstrcat(stm1," ");
	}
	printf(stm1);
	free(stm1);
	*/
}
