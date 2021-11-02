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
int randptr,roots[256],tmp[256],rtmp[256][65],randcnt,randbytes[256],rootscnt,rootptr;
void initrandbytes(){
	int h=0;
	while(h==0){
		for(int z1=0;z1<51;z1++){for(int z=0;z<256;z++){randbytes[z]^=((rand()<<1) % 256)&255;}}
		for(int z1=0;z1<5;z1++)for(int z=0;z<256;z++)randbytes[z]^=(randbytes[(z+1)%256]>>1)&255;
		for(int z=0;z<256;z++)if (randbytes[z]>127)h=1;
	}
	randptr=0;randcnt=255;
}
void findroots(){
	rootscnt=0;
	int tmp1=0;
	
	for(int z1=0;z1<256;z1++){
	tmp1=0;
		for(int z=0;z<10;z++)rtmp[z][rootptr]^=rtmp[(z+1)%10][rootptr];
		for(int z2=0;z2<10;z2++)tmp1^=rtmp[z2][rootptr];
		if(tmp1==z1){roots[rootscnt]=z1;rootscnt++;}
	}

}
void deroot(){
	for(int z=0;z<10;z++)rtmp[z][rootptr]=tmp[z];
	for(int z1=0;z1<randbytes[0];z1++){
		for(int z=9;z>=0;z--)rtmp[z][rootptr]^=rtmp[(z+1)%10][rootptr];
	}
}
void trap(){
	char *stm1;
	stm1 = (char *)malloc(100000);
	memset(stm1,0,100000);

	rdtsc();
	srand(time(0));
	rootptr=0;
	for(int i=0;i<64;i++){
		initrandbytes();
		lstrcat(stm1,intToStr(rootptr));lstrcat(stm1,"\t");
		for(int z=0;z<10;z++){lstrcat(stm1,intToStr(randbytes[z]));lstrcat(stm1," ");}

		while (strlen(stm1)<41)lstrcat(stm1," ");
		lstrcat(stm1,"\t");

		for(int z=0;z<10;z++){
			rtmp[z][rootptr]=randbytes[z];
			tmp[z]=rtmp[z][rootptr];
		}
		findroots();
		if(rootscnt!=1)for(int z=0;z<rootscnt;z++){lstrcat(stm1,intToStr(roots[z]));lstrcat(stm1," ");}
		else {
			for(int z=0;z<rootscnt;z++){lstrcat(stm1,intToStr(roots[z]));lstrcat(stm1," ");}
			deroot();
			findroots();
			lstrcat(stm1,"\t\t | \t\t");	
			for(int z=0;z<rootscnt;z++){lstrcat(stm1,intToStr(roots[z]));lstrcat(stm1," ");}
		}
		lstrcat(stm1,"\r\n");	

		rootptr++;
	}
    printf(stm1);
	free(stm1);
}
int main(int argc, char *argv[]){
trap();
}
