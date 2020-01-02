#include <stdio.h>
#include <stdlib.h>
//#include "gf256.h"


#define V 3
#define P 1024
#define Q 2
#define N Q*Q*Q*Q*Q*Q


typedef struct  {

unsigned short n[V];
unsigned short a;

} mterm;

typedef struct {

mterm x[P];

} MP;

typedef struct {

  unsigned int z[V][Q*Q*Q+1];

} PO;


//unsigned char gf[N]={0,1,2,4,5,7,3,6};
//unsigned char fg[N]={0,1,2,6,3,4,7,5};
//unsigned char gf[N]={0,1,2,4,8,9,11,15,7,14,5,10,13,3,6,12};
//unsigned char fg[N]={0,1,2,13,3,10,14,8,4,5,11,6,15,12,9,7};
/*
unsigned char gf[32]={
0,1,2,4,8,16,23,25,5,10,20,
31,9,18,19,17,21,29,13,26,3,
6,12,24,7,14,28,15,30,11,22,
27};
//unsigned char fg[32]={0,1,2,20,3,8,21,24,4,12,9,29,22,18,25,27,5,15,13,14,10,16,30,6,23,7,19,31,26,17,28,11};
*/

unsigned char gf[64]={
    0,1,2,4,8,16,32,33,35,39,47,
63,31,62,29,58,21,42,53,11,22,
44,57,19,38,45,59,23,46,61,27,
54,13,26,52,9,18,36,41,51,7,
14,28,56,17,34,37,43,55,15,30,
60,25,50,5,10,20,40,49,3,6,
12,24,48};
/*
unsigned char fg[64]={0,1,2,59,3,54,60,40,4,35,55,19,61,32,41,49,5,44,36,23,56,16,20,27,62,52,33,30,42,14,50,12,6,7,45,8,37,46,24,9,57,38,17,47,21,25,28,10,63,58,53,39,34,18,31,48,43,22,15,26,51,29,13,11};
*/
/*
unsigned char gf[128]={
0,1,2,4,8,16,32,64,65,67,71,
79,95,127,63,126,61,122,53,106,21,
42,84,105,19,38,76,89,115,39,78,
93,123,55,110,29,58,116,41,82,101,
11,22,44,88,113,35,70,77,91,119,
47,94,125,59,118,45,90,117,43,86,
109,27,54,108,25,50,100,9,18,36,
72,81,99,7,14,28,56,112,33,66,
69,75,87,111,31,62,124,57,114,37,
74,85,107,23,46,92,121,51,102,13,
26,52,104,17,34,68,73,83,103,15,
30,60,120,49,98,5,10,20,40,80,
97,3,6,12,24,48,96};
*/


unsigned int cnt=0;
PO p;



int mlt(int x, int y){

    if(x==0||y==0)
        return 0;
  
  return ((x+y-2)%(N-1))+1;
}


int mltn(int n,int x){
  int i,j;

if(n==0)
return 1;
  i=x;
    for(j=0;j<n-1;j++)
      i=mlt(i,x);

  return i;
}


mterm term(MP f,unsigned int i){

return f.x[i];

}

unsigned short degterm(MP f,int i){
int j,k;
mterm z;
unsigned short c=0;

    z=term(f,i);
    for(j=0;j<V;j++){
    if(z.n[j]>0)
    c++;
    }

return c;
}

unsigned int terms(MP f){
int i,j,k=0;

for(i=0;i<P;i++){
        if(degterm(f,i)>0)
        k++;
    }

return k;
}


unsigned short otrace(mterm a,int i,int j,int k){
    unsigned short u;

    u=mlt(mlt(mltn(a.n[0],i),mltn(a.n[1],j)),mltn(a.n[2],k));

return gf[u];
}

unsigned int mtrace(MP f){
  int i,j,k,ii;
  unsigned int u,n,count=0,f1,f2,f3,f4;
mterm o[4];

 u=0;
 n=terms(f);

 i=0;j=1;k=0;
 for(ii=0;ii<n;ii++)
   u^=otrace(f.x[ii],i,j,k);
 //u^=1;
 if(u==0){
   printf("%d %d %d\n",i,j,k);
   /*
   p.z[0][count]=i;
   p.z[1][count]=j;
   p.z[2][count]=k;
   */
   count++;

 }
 
 /*
 k=0;i=1;u=0;
 for(j=0;j<N;j++){
   for(ii=0;ii<n;ii++)
   u^=otrace(f.x[ii],i,j,k);
   //u^=1;
   if(u==0){
     printf("%d %d %d\n",i,j,k);
     
     //p.z[0][count]=i;
     //p.z[1][count]=j;
     //p.z[2][count]=k;
     
     count++;
   }
  u=0;
 }
 */

 k=1;u=0;
for(i=0;i<N;i++){
    for(j=0;j<N;j++){
        for(ii=0;ii<n;ii++)
      u^=otrace(f.x[ii],i,j,k);
	//u^=1;
        if(u==0){
	  printf("%d %d %d\n",i,j,k);
	  /*
	     p.z[0][count]=i;
	     p.z[1][count]=j;
	     p.z[2][count]=k;
	  */
            count++;
        }
    u=0;    
    }
}


return count;
}



MP define_curve(void){
int i,j,k;
MP s={0};

/*
//sc
s.x[0].n[0]=Q*Q-1;
s.x[0].n[1]=Q;
s.x[0].n[2]=1;
s.x[1].n[0]=Q;
s.x[1].n[1]=Q*Q;
s.x[2].n[0]=0;
s.x[2].n[1]=1;
s.x[2].n[2]=4;
s.x[3].n[0]=Q*Q;
s.x[3].n[1]=0;
s.x[3].n[2]=2;
*/

//hermite
 s.x[0].n[0]=Q+1;
 s.x[1].n[1]=Q+1;
 s.x[2].n[2]=Q+1;

 return s;
}

MP set_curve(unsigned short a[9][3],int x){
  MP s;
  int i,j;

  
  for(i=0;i<x;i++){
    for(j=0;j<V;j++){
      s.x[i].n[j]=a[i][j];
    }
  }

  return s;
}


int main(void){
  int i,j,k=0,f1,f2,f3,f4,count=0;
  unsigned int u=0;
  MP s;
  //gfQ*Q
  unsigned short hl[3][3]={{Q+1,0,0},{0,Q+1,0},{0,0,Q+1}};
  //gf256
  unsigned short el[4][3]={{0,2,1},{1,1,1},{3,0,0},{0,0,3}};
  //gf256
  unsigned short el2[5][3]={{0,2,1},{1,1,1},{3,0,0},{0,0,3},{2,0,1}};
  //gf8
  unsigned short sc[4][3]={{3,2,1},{2,4,0},{0,1,5},{4,0,2}};
  //gfQ*Q
  unsigned short he[3][3]={{Q,0,0},{0,Q+1,0},{1,0,0}};
  //gfQ*Q
  unsigned short gh[3][3]={{0,Q,0},{0,1,0},{Q*Q+1,0,0}};
  //gf16
  unsigned short gs[5][3]={{15,2,0},{14,4,0},{12,8,0},{8,1,0},{16,0,0}};
  //gf32
  unsigned short gc[6][3]={{31,2,0},{30,4,0},{28,8,0},{24,16,0},{16,1,0},{32,0,0}};
  //gf64
  unsigned short gg[7][3]={{63,4,0},{62,8,0},{60,16,0},{56,32,0},{48,1,0},{32,2,0},{64,0,0}};
  //gf256
  unsigned short gd[9][3]={{255,8,0},{254,16,0},{252,32,0},{248,64,0},{240,128,0},{224,1,0},{192,2,0},{128,4,0},{256,0,0}};

  
  //s=define_curve();
  s=set_curve(gg,7);
  
  u=mtrace(s);
  
  printf("count=%d\n\n",u);


  
  return 0;
}
