#include <stdio.h>
#include <stdlib.h>
#include "gf256.h"


#define V 3
#define P 1024
#define Q 16
#define N Q*Q


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
unsigned char gf[64]={
    0,1,2,4,8,16,32,33,35,39,47,
63,31,62,29,58,21,42,53,11,22,
44,57,19,38,45,59,23,46,61,27,
54,13,26,52,9,18,36,41,51,7,
14,28,56,17,34,37,43,55,15,30,
60,25,50,5,10,20,40,49,3,6,
12,24,48};
unsigned char fg[64]={0,1,2,59,3,54,60,40,4,35,55,19,61,32,41,49,5,44,36,23,56,16,20,27,62,52,33,30,42,14,50,12,6,7,45,8,37,46,24,9,57,38,17,47,21,25,28,10,63,58,53,39,34,18,31,48,43,22,15,26,51,29,13,11};
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


unsigned short otrace(mterm a,int i,int j,unsigned short k){
    unsigned short u,f1,f2,f3,f4,c,d,v=1;

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
 if(u==0){
   printf("%d %d %d\n",i,j,k);
   p.z[0][count]=i;
   p.z[1][count]=j;
   p.z[2][count]=k;
   count++;

 }

 k=0;i=1;u=0;
 for(j=0;j<N;j++){
   for(ii=0;ii<n;ii++)
   u^=otrace(f.x[ii],i,j,k);
   if(u==0){
     printf("%d %d %d\n",i,j,k);
     p.z[0][count]=i;
     p.z[1][count]=j;
     p.z[2][count]=k;
     count++;
   }
  u=0;
 }
 k=1;u=0;
for(i=0;i<N;i++){
    for(j=0;j<N;j++){
        for(ii=0;ii<n;ii++)
      u^=otrace(f.x[ii],i,j,k);
        if(u==0){
	  printf("%d %d %d\n",i,j,k);
	     p.z[0][count]=i;
	     p.z[1][count]=j;
	     p.z[2][count]=k;
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

MP set_curve(unsigned char a[3][3]){
  MP s;
  int i,j;

  
  for(i=0;i<3;i++){
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
 unsigned char c[3][3]={{Q+1,0,0},{0,Q+1,0},{0,0,Q+1}};
 
 //s=define_curve();
 s=set_curve(c);

u=mtrace(s);
printf("count=%d\n\n",u);




return 0;
}


