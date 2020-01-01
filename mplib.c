#include <stdio.h>
#include <stdlib.h>
#include "chash.c"


#define V 2
#define P 1024
#define Q 2
#define N Q*Q*Q


typedef struct  {

unsigned short n[V];
unsigned short a;

} mterm;

typedef struct {

mterm x[P];

} MP;

MP s={0};

unsigned char gf[N]={0,1,2,4,5,7,3,6};
unsigned char fg[N]={0,1,2,6,3,4,7,5};
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

int cnt=0;

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

for(i=0;i<M;i++){
        if(degterm(f,i)>0)
        k++;
    }

return k;
}


unsigned short otrace(mterm a,int j,unsigned short k){
    int i;
    unsigned short u,f1,f2,f3,f4,c,d,v=1;

      u=mlt(mltn(a.n[0],j),mltn(a.n[1],k));

return gf[u];
}

unsigned short mtrace(MP f){
int i,j,k;
unsigned int u,count=0,f1,f2,f3,f4;
mterm o[4];

 u=0;
for(i=0;i<terms(f);i++){
    o[i]=term(f,i);
}


for(i=0;i<N;i++){
    for(j=0;j<N;j++){
        for(k=0;k<terms(f);k++)
            u^=otrace(o[k],i,j);
        if(u==0){
            printf("%d %d\n",i,j);
            count++;
        }
    u=0;
    }
}

//printf("count=%d\n",count);


return count;
}


int sc(int x,int y){
  int i,j,k,f1,f2,f3,f4,count=0;

	f1=gf[mlt(mltn(Q*Q-1,x),mltn(Q,y))];
	f2=gf[mlt(mltn(Q,x),mltn(Q*Q,y))];
	f3=gf[y];
	f4=gf[mltn(Q,x)];

	if((f1^f2^f3^f4)==0){
	  //l[0][count]=x;
	  //l[1][count++]=y;
	  cnt++;
	  printf("%d %d\n",gf[x],gf[y]);
	}
	//	return count;
}

void define_curve(void){
int i,j,k;

s.x[0].n[0]=Q*Q-1;
s.x[0].n[1]=Q;
s.x[1].n[0]=Q;
s.x[1].n[1]=Q*Q;
s.x[2].n[0]=0;
s.x[2].n[1]=1;
s.x[3].n[0]=Q*Q;
s.x[3].n[1]=0;

/*
s.x[0].n[0]=1;
s.x[1].n[0]=4;
s.x[2].n[1]=3;
*/

}

int main(void){
int i,j,k=0,f1,f2,f3,f4,count=0;
unsigned short u=0;


define_curve();

u=mtrace(s);
printf("count=%d\n\n",u);
//exit(1);

/*
count=0;
 for(i=0;i<N;i++){
   for(j=0;j<N;j++)
     sc(i,j);
 }
 printf("count=%d\n",cnt);

 exit(1);
*/
 
for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      
	f1=gf[mlt(mltn(Q*Q-1,i),mltn(Q,j))];
	f2=gf[mlt(mltn(Q,i),mltn(Q*Q,j))];
	f3=gf[j];
	f4=gf[mltn(Q*Q,i)];
      
	if((f1^f2^f3^f4)==0){
        printf("%d %d\n",i,j);
        count++;
    }
    }
}


/*
 for(i=0;i<N;i++){
    for(j=0;j<N;j++){
	f1=gf[mltn(4,i)];
	f2=gf[mltn(1,i)];
	f3=gf[mltn(5,j)];
    if(f1^f2^f3==0)
    count++;
    }
}
*/

 
printf("count=%d\n",count);


return 0;
}


