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
int randptr,mainroots[5][513],childroots[513][3][10],roots[256],tmp[256][513],rtmp[256][513],randcnt,randbytes[256],rootscnt,rootptr, salt[16384];
void initrandbytes(){
	int h=0;
	while(h==0){
		for(int z1=0;z1<3;z1++){for(int z=0;z<256;z++){randbytes[z]^=((rand()<<1) % 256)&255;}}
		for(int z1=0;z1<2;z1++)for(int z=0;z<256;z++)randbytes[z]^=(randbytes[(z+1)%256]>>1)&255;
		for(int z=0;z<256;z++)if (randbytes[z]>127)h=1;
	}
	randptr=0;randcnt=255;
}
int getrandbyte(){
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
void deroot(int level){
	if(level==2)for(int z=0;z<10;z++)rtmp[z][rootptr]=tmp[z][rootptr];
//	for(int z1=0;z1<mainroots[level/2][rootptr];z1++)for(int z=9;z>=0;z--)rtmp[z][rootptr]^=rtmp[(z+1)%10][rootptr];
	for(int z1=0;z1<mainroots[level/2][rootptr];z1++)for(int z=0;z<10;z++)rtmp[z][rootptr]^=rtmp[(z+1)%10][rootptr];
}
void trap(){
	char *stm1;char *stm11;
	stm1 = (char *)malloc(100000);
	memset(stm1,0,100000);
	stm11 = (char *)malloc(1000);
	memset(stm11,0,1000);
		
	rootptr=0;
	int plusone=0;
	for(int i=0;i<256;i++){
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
			deroot(2);
			findroots(2);
			lstrcat(stm1,"\t | \t");
			if(mainroots[2][rootptr]!=1)
				for(int z=0;z<mainroots[2][rootptr];z++){lstrcat(stm1,intToStr(childroots[rootptr][1][z]));lstrcat(stm1," ");}
			else
			{
				lstrcat(stm1,"+1");
				plusone++;
			}
		}
		lstrcat(stm1,"\r\n");	

		rootptr++;
	}
	char buffer [20];
	gcvt ((double)(100/(double)(256/plusone)),4,buffer);
	lstrcat(stm1,buffer);
	lstrcat(stm1," %% - plusone\r\n");
	
	int d1,d2,d3;
//	d1=128,d2=256,d3=384;
	d1=64,d2=128,d3=192;

	int z1,z2,z3,z4,z01,z02,z03,z04;
	z1=0,z2=0,z3=0,z4=0;
	for(int i=0;i<d1;i++){
		if((mainroots[0][i]==1) & (mainroots[2][i]==1))z1=z1^mainroots[1][i];
		if((mainroots[0][i+d1]==1) & (mainroots[2][i+d1]==1))z2=z2^mainroots[1][i+d1];
		if((mainroots[0][i+d2]==1) & (mainroots[2][i+d2]==1))z3=z3^mainroots[1][i+d2];
		if((mainroots[0][i+d3]==1) & (mainroots[2][i+d3]==1))z4=z4^mainroots[1][i+d3];
	}
	lstrcat(stm1,intToStr(z1));lstrcat(stm1," ");
	lstrcat(stm1,intToStr(z2));lstrcat(stm1," ");
	lstrcat(stm1,intToStr(z3));lstrcat(stm1," ");
	lstrcat(stm1,intToStr(z4));lstrcat(stm1,"\r\n");
//================ WRITE 1 BIT======================

		for(rootptr=0;rootptr<256;rootptr++){
			findroots(0);
			if(mainroots[0][rootptr]==1){
				deroot(2);
				findroots(2);	
			} else mainroots[2][rootptr]=0;
		}
		for(int i=0;i<d1;i++){
			if((mainroots[0][i]==1) & (mainroots[2][i]==1))z1=z1^mainroots[1][i];
			if((mainroots[0][i+d1]==1) & (mainroots[2][i+d1]==1))z2=z2^mainroots[1][i+d1];
			if((mainroots[0][i+d2]==1) & (mainroots[2][i+d2]==1))z3=z3^mainroots[1][i+d2];
			if((mainroots[0][i+d3]==1) & (mainroots[2][i+d3]==1))z4=z4^mainroots[1][i+d3];
		}
		for(int i=0;i<d1;i++){
			tmp[0][i]^=salt[d1*z1+i];
			tmp[0][i+d1]^=salt[d1*z2+i];
			tmp[0][i+d2]^=salt[d1*z3+i];
			tmp[0][i+d3]^=salt[d1*z4+i];
		}
//END============= WRITE 1 BIT======================
	int trapcnt = 0;
	for(int i1=0;i1<256;i1++){
		for(int i=0;i<d1;i++)rtmp[0][i]=tmp[0][i]^salt[i+i1*d1];
		for(int i=0;i<d1;i++)rtmp[0][i+d1]=tmp[0][i+d1]^salt[i+i1*d1];
		for(int i=0;i<d1;i++)rtmp[0][i+d2]=tmp[0][i+d2]^salt[i+i1*d1];
		for(int i=0;i<d1;i++)rtmp[0][i+d3]=tmp[0][i+d3]^salt[i+i1*d1];
		for(rootptr=0;rootptr<256;rootptr++){
			findroots(0);
			if(mainroots[0][rootptr]==1){
				deroot(2);
				findroots(2);	
			} else mainroots[2][rootptr]=0;
		}

		z1=0,z2=0,z3=0,z4=0;
		for(int i=0;i<d1;i++){
			if((mainroots[0][i]==1) & (mainroots[2][i]==1))z1=z1^mainroots[1][i];
			if((mainroots[0][i+d1]==1) & (mainroots[2][i+d1]==1))z2=z2^mainroots[1][i+d1];
			if((mainroots[0][i+d2]==1) & (mainroots[2][i+d2]==1))z3=z3^mainroots[1][i+d2];
			if((mainroots[0][i+d3]==1) & (mainroots[2][i+d3]==1))z4=z4^mainroots[1][i+d3];
		}
/*		if(i1<d1){
			z01 = rtmp[0][i1];
			z02 = rtmp[0][i1+d1];
			z03 = rtmp[0][i1+d2];
			z04 = rtmp[0][i1+d3];
		} else if(i1<d2){
			z01 = rtmp[1][i1];
			z02 = rtmp[1][i1+d1];
			z03 = rtmp[1][i1+d2];
			z04 = rtmp[1][i1+d3];
		} else if(i1<d3){
			z01 = rtmp[2][i1];
			z02 = rtmp[2][i1+d1];
			z03 = rtmp[2][i1+d2];
			z04 = rtmp[2][i1+d3];
		} else {
			z01 = rtmp[3][i1];
			z02 = rtmp[3][i1+d1];
			z03 = rtmp[3][i1+d2];
			z04 = rtmp[3][i1+d3];
		}
*/
			z01 = rtmp[0][i1];
			z02 = rtmp[0][i1+d1];
			z03 = rtmp[0][i1+d2];
			z04 = rtmp[0][i1+d3];
		
		if((z1==z01)&(z2==z02)&(z3==z03)&(z4==z04))trapcnt++;
	}
	lstrcat(stm1,intToStr(trapcnt));lstrcat(stm1," = trapcnt\r\n");
	
    printf(stm1);
	free(stm1);
}
int main(int argc, char *argv[]){
	rdtsc();
	srand(time(0));
	rootptr=0;
	initrandbytes();
	for(int i=0;i<256;i++){
		for(int z=0;z<10;z++){
			rtmp[z][rootptr]=getrandbyte();
			tmp[z][rootptr]=rtmp[z][rootptr];
		}
		rootptr++;
	}
	for(int i=0;i<16384;i++)salt[i]=getrandbyte();
	
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
/*	char *stm1;
	stm1 = (char *)malloc(1000000);
	memset(stm1,0,1000000);
	int cnt=0;
	for(int i1=0;i1<65536;i1++){
		int z1,z2,z3,z4,z5,z6,z7,z8;
		for(int i=0;i<256;i++){
			z1 = getrandbyte();z2 = getrandbyte();z3 = getrandbyte();z4 = getrandbyte();z5 = getrandbyte();z6 = getrandbyte();z7 = getrandbyte();z8 = getrandbyte();
			if((z1==z2)&(z3==z4)&(z5==z6)&(z7==z8))cnt++;
		}
	}
	lstrcat(stm1,intToStr(cnt));lstrcat(stm1,"\r\n");
	printf(stm1);
	free(stm1);
	*/
}
