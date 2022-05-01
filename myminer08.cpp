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
int randptr,rootscnt;int t[20];int roots[20][17],rtmp[8],randbytes[257];char *stm1,*stml1;int tmpptr;unsigned char tmp[20][8];
int rootsbuf[20][18][8];bool loaderror;int m; int t1;
char queuedata[78];
int stackw_roots[16][20][17],stackw_rootsbuf[16][20][18][8],stackw_cryptsaltdelta[16][2],curwbit,curwdelta;
unsigned char stackw_tmp[20][8];


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
	randbytes[randptr]^=randbytes[(randptr+2)%256];
	randbytes[randptr]^=randbytes[(randptr+3)%256];
	randbytes[randptr]^=randbytes[(randptr+4)%256];
	randbytes[randptr]^=randbytes[(randptr+5)%256];
	randbytes[randptr]^=randbytes[(randptr+6)%256];
	randbytes[randptr]^=randbytes[(randptr+7)%256];
	randbytes[randptr]^=randbytes[(randptr+8)%256];
	randptr=(randptr+1)%256;	
	return h;
}
void findroots(){
	rootscnt=0;
	int tmp1=0;
	
	for(int z1=0;z1<256;z1++){
	tmp1=0;
		for(int z=0;z<8;z++)rtmp[z]^=rtmp[(z+1)%8];
		for(int z2=0;z2<8;z2++)tmp1^=rtmp[z2];
		if(tmp1==z1){
			roots[tmpptr][rootscnt+1]=z1;
			
			for(int z=0;z<8;z++)
			rootsbuf[tmpptr][rootscnt+1][z]=rtmp[z];
			
			rootscnt++;
		}
	}
	roots[tmpptr][0]=rootscnt;
}
void a1(int i){

	stml1 = (char *)malloc(100);
	memset(stml1,0,100);
		
	for(int z=0;z<8;z++){lstrcat(stml1,charToStr(tmp[tmpptr][z]));lstrcat(stml1," ");}

	while (strlen(stml1)<32)lstrcat(stml1," ");
	lstrcat(stml1,"\t");
	lstrcat(stm1,stml1);
	
	memset(stml1,0,100);
	if(((int)((i+1)/4))*4 == (i+1))lstrcat(stml1,intToStr((roots[tmpptr][0]*roots[tmpptr-1][0]*roots[tmpptr-2][0]*roots[tmpptr-3][0])));
	while (strlen(stml1)<10)lstrcat(stml1," ");
	lstrcat(stm1,stml1);
	
	for(int z=0;z<roots[tmpptr][0];z++){lstrcat(stm1,intToStr(roots[tmpptr][z+1]));lstrcat(stm1," ");}
	lstrcat(stm1,"\r\n");	

	free(stml1);
	
}
void savesetup(){
  FILE *write_ptr;
  write_ptr = fopen("Вибачення.400GB","wb");
  tmpptr =0;
  for(int i=0;i<20;i++){
	fwrite(tmp[tmpptr],8,1,write_ptr); 
	tmpptr++;
  }
  fclose(write_ptr);  
}
bool loadsetup(){
  FILE *read_ptr;
  read_ptr = fopen("Вибачення.400GB","rb");
  if(!read_ptr)return false;
  tmpptr =0;
  for(int i=0;i<20;i++){
	fread(tmp[tmpptr],8,1,read_ptr); 
	tmpptr++;
  }
  fclose(read_ptr); 
  return true;  
}
bool checkerrorsinit(){
	bool error1=true,error2=true,error3=true,error4=true,error5=true;
	int i = 0;
	if((roots[i][0]==0)||(roots[i+1][0]==0)||(roots[i+2][0]==0)||(roots[i+3][0]==0)) error1 = false;
	//else if( ( ((roots[i][0]==0)?1:roots[i][0]) * ((roots[i+1][0]==0)?1:roots[i+1][0]) * ((roots[i+2][0]==0)?1:roots[i+2][0]) * ((roots[i+3][0]==0)?1:roots[i+3][0]) ) >100) error=true;
   
    i = 4;
	if((roots[i][0]==0)||(roots[i+1][0]==0)||(roots[i+2][0]==0)||(roots[i+3][0]==0)) error2 = false;
	//else if( ( ((roots[i][0]==0)?1:roots[i][0]) * ((roots[i+1][0]==0)?1:roots[i+1][0]) * ((roots[i+2][0]==0)?1:roots[i+2][0]) * ((roots[i+3][0]==0)?1:roots[i+3][0]) ) >100) error=true;
   
    i = 8;
	if((roots[i][0]==0)||(roots[i+1][0]==0)||(roots[i+2][0]==0)||(roots[i+3][0]==0)) error3 = false;
	//else if( ( ((roots[i][0]==0)?1:roots[i][0]) * ((roots[i+1][0]==0)?1:roots[i+1][0]) * ((roots[i+2][0]==0)?1:roots[i+2][0]) * ((roots[i+3][0]==0)?1:roots[i+3][0]) ) >100) error=true;
   
    i = 12;
	if((roots[i][0]==0)||(roots[i+1][0]==0)||(roots[i+2][0]==0)||(roots[i+3][0]==0)) error4 = false;
	//else if( ( ((roots[i][0]==0)?1:roots[i][0]) * ((roots[i+1][0]==0)?1:roots[i+1][0]) * ((roots[i+2][0]==0)?1:roots[i+2][0]) * ((roots[i+3][0]==0)?1:roots[i+3][0]) ) >100) error=true;
   
    i = 16;
	if((roots[i][0]==0)||(roots[i+1][0]==0)||(roots[i+2][0]==0)||(roots[i+3][0]==0)) error5 = false;
	//else if( ( ((roots[i][0]==0)?1:roots[i][0]) * ((roots[i+1][0]==0)?1:roots[i+1][0]) * ((roots[i+2][0]==0)?1:roots[i+2][0]) * ((roots[i+3][0]==0)?1:roots[i+3][0]) ) >100) error=true;
	
	return error1 || error2 || error3 || error4 || error5;
}
void initrtmp(){
	m=0;for(int i=0;i<20;i++)t[i]=0; t1=0;
	tmpptr=0;
	for(int i=0;i<20;i++){
		
		for(int z=0;z<8;z++){
			if(loaderror){
			  rtmp[z]=getrandbyte();tmp[tmpptr][z]=rtmp[z];
			} else
			rtmp[z]=tmp[tmpptr][z];
		}
		
		//int tmp1=0;
		//for(int z2=0;z2<8;z2++)tmp1^=rtmp[z2];
		//for(int z1=0;z1<(tmp1+1);z1++)for(int z=7;z>=0;z--){rtmp[z]^=rtmp[(z+1)%8];tmp[tmpptr][z]=rtmp[z];}
		
		
		findroots();
		a1(i);
		if(rootscnt>m)m=rootscnt;
		t[rootscnt]=(t[rootscnt])+1;
		tmpptr++;
	}
}
void cryptsalt(){
	for(int i=0;i<20;i++)
		for(int z=0;z<8;z++){
			tmp[i][z]=tmp[i][z]^tmp[(i+1)%20][z];
			tmp[i][z]=tmp[i][z]^tmp[(i+2)%20][z];
			tmp[i][z]=tmp[i][z]^tmp[(i+3)%20][z];
			tmp[i][z]=tmp[i][z]^tmp[(i+4)%20][z];
		}
}
void initstackw(){
	for(int i1=0;i1<16;i1++)for(int i2=0;i2<20;i2++)for(int i3=0;i3<17;i3++)stackw_roots[i1][i2][i3]=0;
	for(int i1=0;i1<16;i1++)for(int i2=0;i2<20;i2++)for(int i3=0;i3<18;i3++)for(int i4=0;i4<8;i4++)stackw_rootsbuf[i1][i2][i3][i4]=0;
	for(int i1=0;i1<16;i1++)for(int i2=0;i2<2;i2++)stackw_cryptsaltdelta[i1][i2]=0;
}
void pushstackw(){
	for(int i1=0;i1<15;i1++)for(int i2=0;i2<20;i2++)for(int i3=0;i3<17;i3++)stackw_roots[i1][i2][i3]=stackw_roots[i1+1][i2][i3];
	for(int i1=0;i1<15;i1++)for(int i2=0;i2<20;i2++)for(int i3=0;i3<18;i3++)for(int i4=0;i4<8;i4++)stackw_rootsbuf[i1][i2][i3][i4]=stackw_rootsbuf[i1+1][i2][i3][i4];
	for(int i1=0;i1<15;i1++)for(int i2=0;i2<2;i2++)stackw_cryptsaltdelta[i1][i2]=stackw_cryptsaltdelta[i1+1][i2];
	
	for(int i2=0;i2<20;i2++)for(int i3=0;i3<17;i3++)stackw_roots[15][i2][i3]=roots[i2][i3];
	for(int i2=0;i2<20;i2++)for(int i3=0;i3<18;i3++)for(int i4=0;i4<8;i4++)stackw_rootsbuf[15][i2][i3][i4]=rootsbuf[i2][i3][i4];
    for(int i2=0;i2<20;i2++)for(int i3=0;i3<8;i3++)stackw_tmp[i2][i3]=tmp[i2][i3];
	stackw_cryptsaltdelta[15][0]=curwdelta;
	stackw_cryptsaltdelta[15][1]=curwbit;
}
int main(int argc, char *argv[]){
	
	//int bitsforwrite = 0b0101010101010101;
	int bitsforwrite = 0b1111111111111111;
	//int bitsforwrite = 0b0000000000000000;
	int rootsptr5index=-1;
	int errorsintest1=0,errorsintest1_1=0;int tmp1t,tmp1s,tmp1t_1,tmp1s_1;
	int m1=0;FILE *read_ptr;
	rdtsc();
	srand(time(0));
	initstackw();
	
	if(argc>2){
		if(strlen(argv[2])<2){printf("Need file or folder to teleportate");return 0;}
			else
			{
				  read_ptr = fopen(argv[2],"rb");
				  if(!read_ptr){printf("Need file or folder to teleportate");return 0;}
				  fread(queuedata,78,1,read_ptr);fclose(read_ptr);
			}
	}
	if(strcmp(argv[1],"-trap")==0){
		loaderror = false;
		if(!loadsetup()){loaderror=true;initrandbytes();}
		
		stm1 = (char *)malloc(100000);
		memset(stm1,0,100000);
		
		initrtmp();
		loaderror = false;
			
		while(checkerrorsinit())
		{ lstrcat(stm1,"Error !\r\n"); cryptsalt();initrtmp();m1++;}	
		
		int tmp4[32],tmp4ptr;
		for(int i=0;i<16;i++){
			
			curwbit = (int)(bitsforwrite&1)==1?1:0;
			//lstrcat(stm1,intToStr(curwbit)); 
			bitsforwrite >>=1;
			
			if(curwbit==1){
				int tmp2[4][2],tmp3[4][16];
				for(int z2=31;z2>=0;z2--)tmp4[z2]=0;
				for(int i2=16;i2<20;i2++){
					for(int i4=0;i4<8;i4++)rtmp[i4]=tmp[i2][i4];
					int tmp1=0;
					for(int z2=0;z2<8;z2++)tmp1^=rtmp[z2];
					for(int z1=0;z1<(tmp1+1);z1++)for(int z=7;z>=0;z--){rtmp[z]^=rtmp[(z+1)%8];tmp[i2][z]=rtmp[z];}
					tmpptr=i2;findroots();
					
					tmp2[i2-16][0]=tmp1;tmp2[i2-16][1]=roots[tmpptr][0];
					for(int u1=0;u1<roots[tmpptr][0];u1++)tmp3[i2-16][u1]=roots[tmpptr][u1+1];
				}
				if((roots[16][0]*roots[17][0]*roots[18][0]*roots[19][0])>100){
					lstrcat(stm1,"\r\n E R R O R !!! ");
					lstrcat(stm1,intToStr((roots[16][0]*roots[17][0]*roots[18][0]*roots[19][0])));
					lstrcat(stm1,"\r\n");
					//goto ENDB;
				}
				for(int o1=0;o1<tmp2[0][1];o1++)
				for(int o2=0;o2<tmp2[1][1];o2++)
				for(int o3=0;o3<tmp2[2][1];o3++)
				for(int o4=0;o4<tmp2[3][1];o4++)
					if( (tmp3[0][o1]==tmp2[0][0]) && (tmp3[1][o2]==tmp2[1][0]) && (tmp3[2][o3]==tmp2[2][0]) && (tmp3[3][o4]==tmp2[3][0]) )rootsptr5index=(1+o1+o2*tmp2[0][1]+o3*tmp2[1][1]*tmp2[0][1]+o4*tmp2[2][1]*tmp2[1][1]*tmp2[0][1]);

				tmp1s=0;
				for(int i2=16;i2<20;i2++){
					for(int i4=0;i4<8;i4++)rtmp[i4]=tmp[i2][i4];
					for(int z2=0;z2<8;z2+=2){tmp1s^=rtmp[z2+1];tmp1s^=(rtmp[z2]<<8);}
				}
				tmp1s_1=rootsptr5index;
				tmp1s=(tmp1s&16383)^rootsptr5index;
				
				tmp4ptr=0;
				for(int i2=16;i2<20;i2+=2){
					for(int i4=0;i4<8;i4++){
						tmp4[tmp4ptr]=tmp[i2][i4];
						tmp4ptr++;
						tmp4[tmp4ptr]=tmp[i2+1][i4];
						tmp4ptr++;
					}
				}
				for(int i2=0;i2<(tmp1s+1);i2++)for(int z2=0;z2<32;z2++){tmp4[z2]^=tmp4[(z2+1)%32];}
				int tmp5[32];for(int z2=0;z2<32;z2++)tmp5[z2]=tmp4[z2];
				
			}
			//cryptsalt();for(int z2=31;z2>=0;z2--)tmp4[z2]=getrandbyte();
			
			errorsintest1=0;
			for(int i9=0;i9<16384;i9++){
				
				for(int z2=31;z2>=0;z2--){tmp4[z2]^=tmp4[(z2+1)%32];}
				tmp4ptr=0;
				for(int i2=16;i2<20;i2+=2){
					for(int i4=0;i4<8;i4++){
						tmp[i2][i4]=tmp4[tmp4ptr];
						tmp4ptr++;
						tmp[i2+1][i4]=tmp4[tmp4ptr];
						tmp4ptr++;
					}
				}
				
				for(int i7=16;i7<20;i7++){
					for(int i4=0;i4<8;i4++)rtmp[i4]=tmp[i7][i4];
					tmpptr=i7;
					findroots();
				}
				
				int rcount = (roots[16][0]*roots[17][0]*roots[18][0]*roots[19][0]);
				if((rcount<=100) && (rcount>0) ){

					tmp1t=0;
					for(int i2=16;i2<20;i2++){
						for(int i4=0;i4<8;i4++)rtmp[i4]=tmp[i2][i4];
						for(int z2=0;z2<8;z2+=2){tmp1t^=rtmp[z2+1];tmp1t^=(rtmp[z2]<<8);}
					}
					for(int y=1;y<=rcount;y++){
						tmp1t_1=(tmp1t&16383)^y;
						if(tmp1t_1==i9)errorsintest1++;
					}
					
				} else goto A16384;
				
			A16384:;
			}
			//if(errorsintest1>errorsintest1_1)errorsintest1_1=errorsintest1;
			if(errorsintest1>1)errorsintest1_1++;
    lstrcat(stm1,"\r\n= ");
	lstrcat(stm1,intToStr(errorsintest1)); 
			
			while(checkerrorsinit())
			{ cryptsalt();
				for(int i7=0;i7<20;i7++){
					for(int z=0;z<8;z++)rtmp[z]=tmp[i7][z];
					tmpptr=i7;
					findroots();
				}
			}
		} 
		 ENDB:lstrcat(stm1,"\r\n");
	}
	//savesetup();
	lstrcat(stm1,intToStr(errorsintest1_1));    
    lstrcat(stm1,"  errorsintest1\r\n");	
	lstrcat(stm1,intToStr(rootsptr5index));    
    lstrcat(stm1,"\r\n");
	lstrcat(stm1,intToStr(m1));    
    lstrcat(stm1,"\r\n");
	lstrcat(stm1,intToStr(m));    
    lstrcat(stm1,"\r\n");	
	for(int z=0;z<16;z++){lstrcat(stm1,intToStr(z));lstrcat(stm1," - ");lstrcat(stm1,intToStr(t[z]));(z<15)?lstrcat(stm1,", "):lstrcat(stm1,"");}
	lstrcat(stm1,"\r\n");	
	printf(stm1);

	free(stm1);

}
