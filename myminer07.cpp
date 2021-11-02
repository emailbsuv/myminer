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
int randptr,tmp[11][1025],rtmp[11][1025],mainroots[12][1025],childroots[1025][12][10],roots[256],randcnt,randbytes[256],rootscnt,rootptr;
	char *stm1;char *stm11;
int mainroots2[12][1025],childroots2[1025][12][10];
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
	int i = ((rand()<<1) % 256)&255;
	int i1 = randbytes[i];
	randbytes[i] ^= randbytes[((i+1)%256)&255];
	randbytes[((i+1)%256)&255] ^= randbytes[((i+2)%256)&255];
	return i1&15;
}
void findroots(int rootlevel){
	rootscnt=0;
	int tmp1=0;
	roots[0]=0;
	
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
void findroots2(int rootlevel){
	rootscnt=0;
	int tmp1=0;
	roots[0]=0;
	
	for(int z1=0;z1<256;z1++){
	tmp1=0;
		for(int z=9;z>=0;z--)rtmp[z][rootptr]^=rtmp[(z+1)%10][rootptr];
		for(int z2=0;z2<10;z2++)tmp1^=rtmp[z2][rootptr];
		if(tmp1==z1){
			roots[rootscnt]=z1;
			childroots2[rootptr][rootlevel/2][rootscnt]=z1;
			rootscnt++;
		}
	}
	mainroots2[rootlevel][rootptr]=rootscnt;
	mainroots2[rootlevel+1][rootptr]=roots[0];
}
void deroot(int level){
	if(level==2)for(int z=0;z<10;z++)rtmp[z][rootptr]=tmp[z][rootptr];
//	for(int z1=0;z1<mainroots[level/2][rootptr];z1++)for(int z=9;z>=0;z--)rtmp[z][rootptr]^=rtmp[(z+1)%10][rootptr];
	for(int z1=0;z1<mainroots[level/2][rootptr];z1++)for(int z=0;z<10;z++)rtmp[z][rootptr]^=rtmp[(z+1)%10][rootptr];
}
void deroot2(int level){
	if(level==0)for(int z=0;z<10;z++)rtmp[z][rootptr]=tmp[z][rootptr];
//	for(int z1=0;z1<mainroots[level/2][rootptr];z1++)for(int z=9;z>=0;z--)rtmp[z][rootptr]^=rtmp[(z+1)%10][rootptr];
	for(int z1=mainroots2[level/2][rootptr]-1;z1>=0;z1--)for(int z=9;z>=0;z--)rtmp[z][rootptr]^=rtmp[(z+1)%10][rootptr];
}
void deroot3(int level){
	if(level==0)for(int z=0;z<10;z++)rtmp[z][rootptr]=tmp[z][rootptr];
//	for(int z1=0;z1<mainroots[level/2][rootptr];z1++)for(int z=9;z>=0;z--)rtmp[z][rootptr]^=rtmp[(z+1)%10][rootptr];
	for(int z1=mainroots[level/2][rootptr]-1;z1>=0;z1--)for(int z=9;z>=0;z--)rtmp[z][rootptr]^=rtmp[(z+1)%10][rootptr];
}
void trap(int l1){
	memset(stm1,0,400000);
	memset(stm11,0,1000);
	
	rootptr=0;
	int plusone=0;
	for(int i=0;i<1024;i++){
		memset(stm11,0,1000);
		lstrcat(stm11,intToStr(rootptr));lstrcat(stm11,"\t");
		for(int z=0;z<10;z++){lstrcat(stm11,intToStr(rtmp[z][rootptr]));lstrcat(stm11," ");}
		while(strlen(stm11)<55)lstrcat(stm11," ");
		lstrcat(stm1,stm11);
		lstrcat(stm1,"\t");
//		for(int z=0;z<10;z++)rtmp[z][rootptr]=tmp[z][rootptr];
		findroots(0);
		if(mainroots[0][rootptr]!=1)for(int z=0;z<mainroots[0][rootptr];z++){lstrcat(stm1,intToStr(childroots[rootptr][0][z]));lstrcat(stm1," ");}
		else {
			for(int z=0;z<mainroots[0][rootptr];z++){lstrcat(stm1,intToStr(childroots[rootptr][0][z]));lstrcat(stm1," ");}
			deroot(2);
			findroots(2);
			lstrcat(stm1,"\t | \t");
			//if(mainroots[2][rootptr]!=1)
				for(int z=0;z<mainroots[2][rootptr];z++){lstrcat(stm1,intToStr(childroots[rootptr][1][z]));lstrcat(stm1," ");}
			//else
				if(mainroots[2][rootptr]==1)
			{
				deroot(4);
				findroots(4);
				lstrcat(stm1,"\t | \t");
				//if(mainroots[4][rootptr]!=1)
					for(int z=0;z<mainroots[4][rootptr];z++){lstrcat(stm1,intToStr(childroots[rootptr][2][z]));lstrcat(stm1," ");}
				if(mainroots[4][rootptr]==1)
				{
					deroot(6);
					findroots(6);
					lstrcat(stm1,"\t | \t");
							for(int z=0;z<mainroots[6][rootptr];z++){lstrcat(stm1,intToStr(childroots[rootptr][3][z]));lstrcat(stm1," ");}
						if(mainroots[6][rootptr]==1)
						{
							deroot(8);
							findroots(8);
							lstrcat(stm1,"\t | \t");


							if(mainroots[8][rootptr]!=1)
								for(int z=0;z<mainroots[8][rootptr];z++){lstrcat(stm1,intToStr(childroots[rootptr][4][z]));lstrcat(stm1," ");}
							else
							{
								if(l1==1){
									for(int z=0;z<10;z++)rtmp[z][rootptr]=tmp[z][rootptr];
									findroots(0);
									deroot3(0);
									findroots(2);
									deroot3(2);
									findroots(4);
									deroot3(4);
									findroots(6);
									deroot3(6);
									findroots(8);
									deroot3(8);
									for(int z=0;z<10;z++)tmp[z][rootptr]=rtmp[z][rootptr];
								}
								lstrcat(stm1,"+1");
								plusone++;
							}
						}
				}
			}
		}
		lstrcat(stm1,"\r\n");	

		rootptr++;
	}
	memset(stm1,0,100000);
	  char buffer [20];
//  if(plusone!=0)gcvt ((double)(100/(double)(1024/plusone)),4,buffer); else gcvt ((double)(0.000000),4,buffer);
  if(plusone!=0)gcvt ((double)(plusone),4,buffer); else gcvt ((double)(0.000000),4,buffer);

	lstrcat(stm1,buffer);
	lstrcat(stm1," %%- plusone\r\n");
    printf(stm1);
}
void trap2(){
	memset(stm1,0,400000);
	memset(stm11,0,1000);
	
	rootptr=0;
	int plusone=0;
	for(int i=0;i<1024;i++){
		findroots2(0);
		if(mainroots2[0][rootptr]==1)
		{
			deroot2(0);
			findroots2(2);
			if(mainroots2[2][rootptr]==1)
			{
				deroot2(2);
				findroots2(4);
				if(mainroots2[4][rootptr]==1)
				{
					deroot2(4);
					findroots2(6);
					if(mainroots2[6][rootptr]==1)
					{
						deroot2(6);
						findroots2(8);
						if(mainroots2[8][rootptr]==1)
						{
							//for(int z=0;z<10;z++)tmp[z][rootptr]=rtmp[z][rootptr];
							plusone++;
						}
					}
				}
			}
		}
	    rootptr++;
	}
	memset(stm1,0,100000);
	  char buffer [20];
//  if(plusone!=0)gcvt ((double)(100/(double)(1024/plusone)),4,buffer); else gcvt ((double)(0.000000),4,buffer);
  if(plusone!=0)gcvt ((double)(plusone),4,buffer); else gcvt ((double)(0.000000),4,buffer);

	lstrcat(stm1,buffer);
	lstrcat(stm1," %%- plusone\r\n");
    printf(stm1);
}

int main(int argc, char *argv[]){
	rdtsc();
	srand(time(0));
	rootptr=0;
	for(int i=0;i<1024;i++){
		initrandbytes();
		for(int z=0;z<10;z++){
			rtmp[z][rootptr]=getrandbyte();
			tmp[z][rootptr]=rtmp[z][rootptr];
		}
		rootptr++;
	}
	int c=0;
	for(int i=0;i<16;i++)
	for(int i1=0;i1<16;i1++)
	for(int i2=0;i2<16;i2++)
	for(int i3=0;i3<16;i3++)
	if(getrandbyte()==getrandbyte()==getrandbyte()==getrandbyte())c++;

	printf(intToStr(c));
	
/*	stm1 = (char *)malloc(400000);
	stm11 = (char *)malloc(1000);
	
trap(1);
	for(int i=0;i<1024;i++)for(int z=0;z<10;z++)rtmp[z][i]=tmp[z][i];

trap(2);
	for(int i=0;i<1024;i++)for(int z=0;z<10;z++)rtmp[z][i]=tmp[z][i];
trap2();
	free(stm1);
	free(stm11);
*/
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
