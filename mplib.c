#include <stdio.h>
#include <stdlib.h>
//#include "gf256.h"


#define V 3
#define P 1024
#define Q 2
#define N Q*Q*Q
#define K 2048



typedef struct  {

unsigned short n[V];
unsigned short a;

} mterm;

typedef struct {

mterm x[P];

} MP;

typedef struct {

  unsigned short z[V][150000];

} PO;


unsigned short gf[8]={0,1,2,4,3,6,7,5};
unsigned short fg[8]={0,1,2,4,3,7,5,6};

//unsigned char gf[N]={0,1,2,4,8,9,11,15,7,14,5,10,13,3,6,12};
//unsigned char fg[N]={0,1,2,13,3,10,14,8,4,5,11,6,15,12,9,7};
/*
unsigned char gf[32]={
0,1,2,4,8,16,23,25,5,10,20,
31,9,18,19,17,21,29,13,26,3,
6,12,24,7,14,28,15,30,11,22,
27};
unsigned char fg[32]={0,1,2,20,3,8,21,24,4,12,9,29,22,18,25,27,5,15,13,14,10,16,30,6,23,7,19,31,26,17,28,11};
*/

//unsigned char gf[64]={0,1,2,4,8,16,32,33,35,39,47,63,31,62,29,58,21,42,53,11,22,44,57,19,38,45,59,23,46,61,27,54,13,26,52,9,18,36,41,51,7,14,28,56,17,34,37,43,55,15,30,60,25,50,5,10,20,40,49,3,6,12,24,48};

//unsigned char fg[64]={0,1,2,59,3,54,60,40,4,35,55,19,61,32,41,49,5,44,36,23,56,16,20,27,62,52,33,30,42,14,50,12,6,7,45,8,37,46,24,9,57,38,17,47,21,25,28,10,63,58,53,39,34,18,31,48,43,22,15,26,51,29,13,11};

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
unsigned short fg[N]={0};
*/

unsigned int cnt=0;
PO p;
mterm base[K]={0};


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


unsigned short oinv(unsigned short a){
  int i;


  for(i=0;i<N;i++){
    if(gf[mlt(fg[a],i)]==1)
      return (unsigned short)i;
  }

}


void vec_diff(unsigned short a[N], unsigned short b[N]){
    /* Calcurate the difference of two vectors. Be caution that b[N] changes.*/
    for (int i = 0; i < N; i++){
        b[i] ^= a[i];
    }
}

int gauss(){
  unsigned short m[N][N] = {{7,2,5}, {2,5,2},{5,2,7}};    // The matrix
  unsigned short b[N] = {5,7,0};
  unsigned short mm[N]={0};

    printf("The coefficient matrix is : \n");
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%d ", m[i][j]);
            if (j == N-1){
                printf("\n");
            }
        }
    }

    printf("\nUse Gauss method to solve equations : \n");
    for (int i = 0; i < N; i++){
        for (int j = i+1; j < N; j++){
	  unsigned short coef = mlt(fg[m[j][i]] , oinv(fg[m[i][i]]));
            unsigned short del[N];

            for (int k = 0; k < N; k++){
	      del[k] = gf[mlt(fg[m[i][k]] , coef)];
            }
	    //for(int ii=0;ii<N;ii++)
	    //mm[ii]=m[j][ii];
            vec_diff(del, m[j]);
            b[j] ^= gf[mlt(fg[b[i]] , coef)];
        }
    }

    for (int i = N -1; i >= 0; i--){
      unsigned short x = gf[oinv(fg[m[i][i]])];
      m[i][i] = gf[mlt(fg[m[i][i]], fg[x])];
      b[i] = gf[mlt(fg[b[i]],fg[x])];

        for (int j = 0; j < i; j++){
	  b[j] ^= gf[mlt(fg[b[i]],fg[m[j][i]])];
            m[j][i] = 0;
        }
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%d ", m[i][j]);
            if (j == N - 1){
                printf("\n");
            }
        }
    }

    for (int i = 0; i < N; i++){
        printf("%d ", b[i]);
    }

    return 0;
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
	c+=z.n[j];
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

    u=mlt(mlt(mltn(a.n[0],i),mltn(a.n[1],j)),mlt(mltn(a.n[2],k),a.a));

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
   //   printf("%d %d %d\n",i,j,k);
   
   p.z[0][count]=i;
   p.z[1][count]=j;
   p.z[2][count]=k;
   
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
     
     p.z[0][count]=i;
     p.z[1][count]=j;
     p.z[2][count]=k;
     
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
	  //  printf("%d %d %d\n",i,j,k);
	  
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


mterm obase(int a,int b){
  int i,j,k;
  mterm c;

  c.n[0]=a;
  c.n[1]=b;
  
  return c;


}

int bases(int a){
  int i=0,j=0,count=0;
  

    for(i=0;i<8;i++){
      for(j=0;j<4;j++){
	if(i+j<a){
	  base[count].n[0]=i;
	  base[count++].n[1]=j;
	}
	if(count>400)
	  break;	
      }
    }
    
    //  printf("count=%d\n",count);
    //  exit(1);
    
    return count;
}

int test(unsigned short x,unsigned short y){
  int count=0,f1,f2,f3;

  f1=gf[mlt(x,x)];
  f2=gf[mlt(3,x)];
  f3=gf[mlt(6,y)];

  if((f1^f2^f3)==0){
    printf("%d %d\n",gf[x],gf[y]);
    count++;
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

MP set_curve(unsigned short a[9][4],int x){
  MP s={0};
  int i,j;

  
  for(i=0;i<x;i++){
    for(j=0;j<V;j++){
      s.x[i].n[j]=a[i][j];
    }
    s.x[i].a=a[i][3];
  }
 

  return s;
}




int main(void){
  int i,j,k=0,a,b,count=0,x,y,z;
  unsigned int u=0,v=0;
  MP s={0};
  unsigned short H[65][137]={0};
  
  
  //gfQ*Q
  unsigned short hl[3][4]={{Q+1,0,0,1},{0,Q+1,0,1},{0,0,Q+1,1}};
  //gf256
  unsigned short el[4][4]={{0,2,1,1},{1,1,1,1},{3,0,0,1},{0,0,3,1}};
  //gf256
  unsigned short el2[5][4]={{0,2,1,1},{1,1,1,1},{3,0,0,1},{0,0,3,1},{2,0,1,1}};
  //gf8
  unsigned short sc[4][4]={{3,2,0,1},{2,4,0,1},{0,1,0,1},{4,0,0,1}};
  //gf8
  unsigned short kl[3][4]={{3,1,0,1},{0,3,1,1},{1,0,3,1}};
  //gfQ*Q
  unsigned short he[3][4]={{Q+1,0,0,1},{0,Q,0,1},{0,1,0,1}};
  //gf16 g=21 #N=121
  unsigned short gu[5][4]={{7,4,0,1},{6,8,0,1},{4,1,0,1},{0,2,0,1},{8,0,0,1}};
  //gf32 g=75 #N=497
  unsigned short ge[6][4]={{15,8,0,1},{14,16,0,1},{12,1,0,1},{8,2,0,1},{0,4,0,1},{16,0,0,1}};
  //gf64 g=217 #N=
  unsigned short gg[7][4]={{31,8,0,1},{30,16,0,1},{28,32,0,1},{24,1,0,1},{16,2,0,1},{0,4,0,1},{32,0,0,1}};
  //gf256
  unsigned short gd[9][4]={{127,8,0,1},{126,16,0,1},{124,32,0,1},{120,64,0,1},{112,128,0,1},{96,1,0,1},{64,2,0,1},{0,4,0,1},{128,0,0,1}};
  //gf128 
  unsigned short cc[8][4]={{63,8,0,1},{62,16,0,1},{60,32,0,1},{56,64,0,1},{48,1,0,1},{32,2,0,1},{0,4,0,1},{64,0,0,1}};

  unsigned short lo[3][4]={{2,0,0,1},{1,0,0,3},{0,1,0,6}};
  unsigned short lk[6][4]={{0,2,0,1},{0,1,0,3},{0,0,1,6},{3,1,0,1},{0,3,1,1},{1,0,3,1}};
  //gf32
  unsigned short ts[3][4]={{2,2,5,1},{7,0,2,1},{0,9,0,1}};
  //gf128
  unsigned short tt[3][4]={{3,1,10,1},{13,0,1,1},{0,14,0,1}};
  //gf512
  unsigned short gt[10][4]={{255,16,0,1},{254,32,0,1},{252,64,0,1},{248,128,0,1},{240,256,0,1},{224,1,0,1},{192,2,0,1},{128,4,0,1},{0,8,0,1},{256,0,0,1}};

  PO t={0};

  //s=define_curve();
  
  s=set_curve(sc,4);

  u=mtrace(s);
  v=u;
  printf("count=%d\n\n",u);
  //     exit(1);

  for(i=0;i<u;i++){
    printf("%d,%d %d\n",gf[p.z[0][i]],gf[p.z[1][i]],gf[p.z[2][i]]);
    //    t.z[0][i]=p.z[0][i];
    //t.z[1][i]=p.z[1][i];
    //t.z[2][i]=p.z[2][i];
  }
  //  exit(1);

  
    v=bases(10);
  printf("bases=%d\n",v);
  //  u=count;
  //  exit(1);
  for(i=0;i<22;i++){
    printf("(%d,%d)\n",base[i].n[0],base[i].n[1]);
    base[i].a=1;
  }
  //  exit(1);
  for(i=0;i<22;i++){
    for(j=0;j<29;j++){
      //      if(p.z[0][j]>0)
      H[i][j]=fg[otrace(base[i],p.z[0][j],p.z[1][j],1)];
    }
  }
  for(i=0;i<22;i++){
    printf("(%d,%d): ",base[i].n[0],base[i].n[1]);
    for(j=1;j<29;j++)
      printf("%d ",H[i][j]);
    printf("\n");
  }

  //  exit(1);
  /*
  for(i=0;i<3;i++){
    for(j=0;j<u;j++)
      p.z[i][j]=0;
  }
  */
  /*
  s=set_curve(lo,3);

  u=mtrace(s);

  printf("count=%d\n\n",u);
  //    exit(1);

  for(i=0;i<u;i++)
    printf("%d,%d %d\n",gf[p.z[0][i]],gf[p.z[1][i]],gf[p.z[2][i]]);

  count=0;
  for(i=0;i<v;i++){
    for(j=0;j<u;j++){
      if(t.z[0][i]==p.z[0][j] && t.z[1][i]==p.z[1][j] && t.z[2][i]==p.z[2][j]){
	printf("intersection points=%d %d %d\n",gf[t.z[0][i]],gf[t.z[1][i]],gf[t.z[2][i]]);
	  count++;
      }
    }
  }
  printf("%d\n",count);
  exit(1);
  */

  

  printf("%d\n",fg[gf[5]^gf[2]^gf[6]]);
  
  return 0;
}
