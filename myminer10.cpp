/* Code writing 1993-2022 by Suvorov Bogdan
Skype: live:.cid.a115b9ace28e8beb
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
int randptr,rootscnt;int roots[7][17],roots0[17],rtmp[8],xrtmp0[8][8],xrtmp[8][7][8],xrtmp2[8][7][8],randbytes[257];
int rootsbuf[17][8];

int k1=1024;//256;//

void initrandbytes(){
	int h=0;
	
	while(h==0)
	{
		for(int z1=0;z1<51;z1++){for(int z=0;z<256;z++){randbytes[z]^=((rand()<<1) % k1)&(k1-1);}}
		for(int z1=0;z1<5;z1++)for(int z=0;z<256;z++)randbytes[z]^=(randbytes[(z+1)%k1]>>1)&(k1-1);
		for(int z=0;z<256;z++)if (randbytes[z]>(k1/2))h=1;
	}
	randptr=0;
	
}
int getrandbyte(){
	int h=randbytes[randptr];
	randbytes[randptr]^=randbytes[(randptr+1)%256];
	randptr=(randptr+1)%256;	
	return h;
}
void xorroot(int i1){
	for(int i2=0;i2<7;i2++){
		int tmp1=0;
		for(int z=0;z<8;z++)tmp1^=xrtmp[i1][i2][z];
		
		for(int z1=0;z1<=tmp1;z1++)
			for(int z=7;z>=0;z--)xrtmp[i1][i2][z]^=xrtmp[i1][i2][(z+1)%8];
	}
}

int findroot(int i0){
	int tmp1=0,z;
	int rtmpQ[10];
	
	for(int i1=0;i1<7;i1++){
		roots[i1][0]=0;
		for(z=0;z<8;z++)rtmpQ[z]=xrtmp[i0][i1][z];	
		
		for(int z1=0;z1<k1;z1++){
		tmp1=0;
			for(z=0;z<8;z++)rtmpQ[z]^=rtmpQ[(z+1)%8];
			for(int z2=0;z2<8;z2++)tmp1^=rtmpQ[z2];
			if(tmp1==z1){
				roots[i1][roots[i1][0]+1]=z1;
				
				//for(int z=0;z<8;z++)rootsbuf[roots[0][0]][z]=rtmpQ[z];
				roots[i1][0]++;
			}
		}
	}
	int cnt=1; for(int i1=0;i1<7;i1++)cnt*=roots[i1][0];
	if(cnt>2800)cnt=-1;
	return cnt;
}
void dexorroot(int i1){
	int tmp1=0;
	for(int i2=0;i2<7;i2++){
		findroot(i1);
		for(int z=0;z<roots[i1][0];z++)tmp1=roots[i1][z+1];
		
		for(int z=0;z<8;z++)xrtmp2[i1][i2][z]=xrtmp[i1][i2][z];
		
		for(int z1=0;z1<=tmp1;z1++)
			for(int z=0;z<8;z++)xrtmp2[i1][i2][z]^=xrtmp2[i1][i2][(z+1)%8];
	}
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
	
	for(int z1=0;z1<k1;z1++){
	tmp1=0;
		for(int z=0;z<8;z++)rtmpQ[z]^=rtmpQ[(z+1)%8];
		for(int z2=0;z2<8;z2++)tmp1^=rtmpQ[z2];
		if(tmp1==z1){
			roots0[rootscnt+1]=z1;
			
			for(int z=0;z<8;z++)
			rootsbuf[rootscnt][z]=rtmpQ[z];
			
			rootscnt++;
		}
	}
	roots0[0]=rootscnt;
}
void find_gate_for_first_bit(int bit){
	bool flag=true;
	while(flag){
		int imax2=0,i9;
		rdtsc();
		srand(time(0));
		initrandbytes();
		
		for(int i0=0;i0<8;i0++){
			for(i9=0;i9<7;i9++){
				for(int z=0;z<8;z++){xrtmp2[i0][i9][z]=xrtmp[i0][i9][z]=getrandbyte();}
			}
		}			
		for(int i0=0;i0<8;i0++){
			if(i0==7)if(bit==1)xorroot(i0);
			int imax=findroot(i0);
			if(imax!=-1)		
				if(imax2<imax)imax2=imax;
				else {flag=false;break;}
		}
		if(imax2<65535)flag=false;
		if(flag)
		if(bit==1){
			dexorroot(7);
			for(int i0=0;i0<8;i0++){
				for(i9=0;i9<15;i9++){
					for(int z=0;z<8;z++){if(xrtmp2[i0][i9][z]!=xrtmp[i0][i9][z])flag=false;}
				}
			}
		}			
	}	
	
}
int main(int argc, char *argv[]){

	int y1=0;
	for(int i5=0;i5<64;i5++){	
		rdtsc();
		srand(time(0));
		initrandbytes();
		int i9,y2=0;
		long long imax2=0;
		for(int i0=0;i0<300;i0++){
			long long imax=1;
			for(i9=0;i9<7;i9++){
				for(int z=0;z<8;z++){rtmp[z]=getrandbyte();}
				xorroots();
				findroots();
				imax*=roots0[0];
				if((roots0[0]==0)){break;}
			}
			if(i9==7){
				y2++;
				if(imax2<imax)imax2=imax;
			}
		}
		if(imax2<6000)y1++;

		std::cout << std::to_string(y2) << ", imax " << (imax2<6000?" ":"") << std::to_string(imax2) << std::endl;
	}

	std::cout << std::to_string(float(100.0/(64.0/y1))) << " % hits"<< std::endl;

/* 	find_gate_for_first_bit(1);
	std::cout << "done"<< std::endl; */
	
}
