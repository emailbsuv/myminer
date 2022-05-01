/* Code writing 1993-2021 by Suvorov Bogdan
Skype: live:emailbsuv
Telegram: @bogdansuvorov
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <iostream>
char ttt[16777216*8];
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



// void lstrcat(char *buff,const char *past)
// {
	// int len=0,len0,len1;
	// len0=strlen(buff);
	// len1=strlen(past);
	// memcpy(buff+len0,past,len1);memset(buff+len0+len1,0,1);
// }
inline char* charToStr(char i)
{
	static char strt1[18]="";memset(strt1,0,18);
	snprintf(strt1, 17,"%d", (int)(unsigned char)i);

	return (char *)strt1;
}
inline char* ucharToStr(char i)
{
	static char strt1[18]="";memset(strt1,0,18);
	snprintf(strt1, 17,"%d", (int)(char)i);

	return (char *)strt1;
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
int randptr,rootscnt;int t[20];int roots[17],roots0[17],rtmp[8],rtmp0[8],rtmp1[8],rtmp2[8],rtmp3[8],randbytes[257];char *stm1,*stm11;unsigned char tmp[20][8];
int roots1[17],roots2[17],roots3[17],roots4[17],roots5[17],roots6[17],roots7[17],roots8[17],roots9[17],roots10[17];
int rootsbuf[17][8];


void initrandbytes(){
	int h=0;
	
	while(h==0)
	{
		for(int z1=0;z1<51;z1++){for(int z=0;z<256;z++){randbytes[z]^=((rand()<<1) % 256)&255;}}
		for(int z1=0;z1<5;z1++)for(int z=0;z<256;z++)randbytes[z]^=(randbytes[(z+1)%256]>>1)&255;
		for(int z=0;z<256;z++)if (randbytes[z]>127)h=1;
	}
	randptr=0;
	
}
int getrandbyte(){
	int h=randbytes[randptr];
	randbytes[randptr]^=randbytes[(randptr+1)%256];
	randptr=(randptr+1)%256;	
	return h;
}
void doroot(int y){
	for(int z1=0;z1<y;z1++)
	for(int z=0;z<8;z++)rtmp[z]^=rtmp[(z+1)%8];
}
void xorroots(){
	int tmp1=0;
	for(int z=0;z<8;z++)tmp1^=rtmp[z];
	
	for(int z1=0;z1<=tmp1;z1++)
		for(int z=7;z>=0;z--)rtmp[z]^=rtmp[(z+1)%8];
}
void findroots(){
	rootscnt=0;
	int tmp1=0;
	int rtmpQ[10];
	for(int z=0;z<8;z++)rtmpQ[z]=rtmp[z];
	
	for(int z1=0;z1<256;z1++){
	tmp1=0;
		for(int z=0;z<8;z++)rtmpQ[z]^=rtmpQ[(z+1)%8];
		for(int z2=0;z2<8;z2++)tmp1^=rtmpQ[z2];
		if(tmp1==z1){
			roots[rootscnt+1]=z1;
			
			for(int z=0;z<8;z++)
			rootsbuf[rootscnt][z]=rtmpQ[z];
			
			rootscnt++;
		}
	}
	roots[0]=rootscnt;
}
struct tmm{
	int min;
	int max;
};

tmm mm;
void minmax(){
	
	
}
int main(int argc, char *argv[]){

	rdtsc();
	srand(time(0));
	initrandbytes();
	stm1 = (char *)malloc(100000);
	stm11 = (char *)malloc(100);
	
	for(int i=0;i<2;i++){
		memset(stm1,0,100000);
		for(int i0=0;i0<61;i0++){
			memset(stm11,0,100);
			for(int z=0;z<8;z++){rtmp[z]=getrandbyte();	lstrcat(stm11,intToStr(rtmp[z]));lstrcat(stm11," ");}
			while(strlen(stm11)<35)lstrcat(stm11," ");lstrcat(stm11,"\t");
			lstrcat(stm1,stm11);
			xorroots();
			findroots();
			memset(stm11,0,100);
			for(int z=0;z<roots[0];z++){lstrcat(stm11,intToStr(roots[z+1]));lstrcat(stm11," ");}
			while(strlen(stm11)<35)lstrcat(stm11," ");lstrcat(stm11,"\t");
			lstrcat(stm1,stm11);
			for(int z=7;z>=0;z--)rtmp[z]^=rtmp[(z+1)%8];
			//rtmp[7]^=1;
			findroots();
			for(int z=0;z<roots[0];z++){lstrcat(stm1,intToStr(roots[z+1]));lstrcat(stm1," ");}
			
			lstrcat(stm1,"\r\n");
		}
		printf(stm1);
		SleepEx(300,0);
	}
	free(stm1);

}
