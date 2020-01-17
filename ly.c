#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "gf256.h"


#define V 3 //変数の数
#define P 1024
#define Q 4 //基礎体
#define N Q*Q //定義体
#define I Q+1 //曲線の次数
#define J 3
#define K I-2 //number h
#define H (K+1)*(K+2)/2 //シンドローム行列の横ベクトルの長さ
#define F (J-K+1)*(J-K+2)/2 //シンドローム行列の縦ベクトル



typedef struct  {

unsigned short n[V];
unsigned short a;

} mterm;

typedef struct {

mterm x[P];

} MP;

typedef struct {

  unsigned char z[V][150000];

} PO;


//unsigned short gf[8]={0,1,2,4,3,6,7,5};
//unsigned short fg[8]={0,1,2,4,3,7,5,6};

//nomal
unsigned char gf[N]={0,1,2,4,8,9,11,15,7,14,5,10,13,3,6,12};
unsigned char fg[N]={0,1,2,13,3,10,14,8,4,5,11,6,15,12,9,7};
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

//unsigned short gf[128]={0,1,2,4,8,16,32,64,65,67,71,79,95,127,63,126,61,122,53,106,21,42,84,105,19,38,76,89,115,39,78,93,123,55,110,29,58,116,41,82,101,11,22,44,88,113,35,70,77,91,119,47,94,125,59,118,45,90,117,43,86,109,27,54,108,25,50,100,9,18,36,72,81,99,7,14,28,56,112,33,66,69,75,87,111,31,62,124,57,114,37,74,85,107,23,46,92,121,51,102,13,26,52,104,17,34,68,73,83,103,15,30,60,120,49,98,5,10,20,40,80,97,3,6,12,24,48,96};
//unsigned short fg[128]={0,1,2,122,3,116,123,74,4,68,117,41,124,100,75,110,5,104,69,24,118,20,42,94,125,65,101,62,76,35,111,85,6,79,105,46,70,90,25,29,119,38,21,59,43,56,95,51,126,114,66,98,102,18,63,33,77,88,36,54,112,16,86,14,7,8,80,9,106,81,47,10,71,107,91,82,26,48,30,11,120,72,39,108,22,92,60,83,44,27,57,49,96,31,52,12,127,121,115,73,67,40,99,109,103,23,19,93,64,61,34,84,78,45,89,28,37,58,55,50,113,97,17,32,87,53,15,13};


unsigned int cnt=0;
PO p;
mterm base[1024]={0};


int mlt(int x, int y){

    if(x==0||y==0)
        return 0;
  
  return ((x+y-2)%(N-1))+1;
}


int mltn(int n,int x){
  int i,j;
  
  if(n==0){
    return 1;
  }
  if(x==0){
    return 0;
  }else{
  i=x;
  for(j=0;j<n-1;j++)
    i=mlt(i,x);
  
  return i;
  }
}


unsigned short oinv(unsigned short a){
  int i;


  for(i=0;i<N;i++){
    if(gf[mlt(fg[a],i)]==1)
      return (unsigned short)i;
  }

}

void param(int n,int g){
  int i,j,h,ij,t;

  //  g=6;
  j=I-2;
  //  ij=k+g-1;
  //  ij=1;
  //  exit(1);
  //    n-=4;
    for(j=I-2;I*j<n-1;j++){
      printf("h=%d~%d\n",I-2,j-I+2);
      printf("n=%d ",n);
      printf("j=%d\n",j);
      printf("k=%d\n",(I*j-g+1));
      //printf("k=%d\n",ij);
      printf("d=%d\n",I*j-2*g+2);
      //printf("d=%d\n",n-ij);
      printf("t=%d~%d\n",((I-2)*I-g+1)-1,((j-I+2)*I-g+1)-1);
      //  printf("t=%d\n",t);
      //      }
      //    j++;
      //    ij++;
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

int terms(MP f){
  int i,j,k=0,flg;

  for(i=0;i<P;i++){
    flg=0;
    for(j=0;j<V;j++){
      if(f.x[i].n[j]>0)
	flg=1;
    }
    if(flg==1)
      k++;
  }
  
  return k;
}

unsigned short degterm(mterm z){
int j,k;
//mterm z;
unsigned short c=0;

//   z=term(f,i);
    for(j=0;j<V;j++){
      if(z.n[j]>0)
	c+=z.n[j];
    }
    
    return c;
}
/*
unsigned int mdeg(MP f){
int i,j,k=0;
for(i=0;i<P;i++){
  if(j=degterm(f,i)>0 && k<j)
        k=j; 
    }
return k;
}
*/


MP mterml(MP f,mterm m){
  int i,j,k;
  
  for(i=0;i<terms(f);i++){
    for(j=0;j<V;j++)
      f.x[i].n[j]+=m.n[j];
    f.x[i].a=gf[mlt(fg[f.x[i].a],fg[m.a])];
  }

  return f;
}


mterm mLT(MP f){
  int i,j=0,k,l;
  mterm m={0},mm;

  
  for(i=0;i<terms(f);i++){
    mm=term(f,i);
      k=degterm(mm);
    if(j<K){
      m=f.x[i];
    }else if(j==k){
      for(l=0;l<V;l++)
	if(m.n[l]<f.x[i].n[l]){
	  m=f.x[i];
	  return m;
	}
      
    }
  }

  return m;
}


MP mdivLT(MP f,mterm m){
  int i,j,k;
  MP g;
  mterm mm;

  g=f;
  
  for(i=0;i<terms(f);i++){
    m=term(f,i);
    if(degterm(mm)>=degterm(m)){
      for(j=0;j<V;j++){
	if(f.x[i].n[j]>=m.n[j]){
	f.x[i].n[j]-=m.n[j];
	}else{
	  return g;
	}
      }
    }else{
      return f;
    }
  }
}

MP mdel(MP f,mterm m){
  int i,j,k;

  m=mLT(f);
  for(i=0;i<terms(f);i++){
    if(m.n[0]==f.x[i].n[0] && m.n[1]==f.x[i].n[1] && m.n[2]==f.x[i].n[1]){
      for(j=0;j<V;j++)
	f.x[i].n[j]=0;
    f.x[i].a^=m.a;
    }
  }

  return f;
}


MP lex(MP f){
  MP g={0};
  int i,j,k;
  mterm m={0};

  
  for(i=0;i<terms(f);i++){
    m=mLT(f);
    f=mdel(f,m);
    g.x[i]=m;
  }

  return g;
}


int rank(int mat[][100], int n){    
    int ltmp[100], tmp, a_tmp[100], b_tmp[100];
    int i, j, k;
    int count;
    int all_zero;

    for(i = 0; i < n; i++){
        all_zero = 0;
        if(mat[i][i] == 0){ 
            for(j = 0; j < n; j++){
                if(mat[j][i] != 0){
                    for(k = 0; k < n; k++){
                        tmp = mat[i][k];
                        mat[i][k] = mat[j][k];
                        mat[j][k] = tmp;
                    }
                } else if(j == n - 1)
                    all_zero = 1;
            }
        }



        if(!all_zero){      
            for(j = i + 1; j < n; j++){
                for(k = 0; k < n; k++){
		  a_tmp[k] = mlt(mat[i][k] , mat[j][i]);
		  b_tmp[k] = mlt(mat[j][k] , mat[i][i]);
                }
                for(k = 0; k < n; k++)
                    mat[j][k] = fg[gf[b_tmp[k]]^gf[a_tmp[k]]];
            }
        }
    }


    count = 0;
    for(i = 0; i < n; i++){
        if(mat[i][n] == 0)
            count++;
    }

    return (n - count);
}


int mdeg(MP f){
  int i,tmp=0,j,k;

  for(i=0;i<terms(f);i++){
    k=0;
    for(j=0;j<V;j++){
      tmp+=f.x[i].n[j];
      if(k<tmp)
	k=tmp;
      
    }
  }

  return k;

}

MP mtermul(MP f,mterm o){
  int i,j,k;

  for(i=0;i<terms(f);i++){
    for(j=0;j<V;j++)
      f.x[i].n[j]+=o.n[j];
    f.x[i].a=gf[mlt(fg[f.x[i].a],fg[o.a])];
  }

  return f;
}


unsigned short otrace(mterm a,int i,int j,int k){
    unsigned short u;

    if(i==0 || j==0)
      return a.a;
      
    u=mlt(mlt(mltn(a.n[0],i),mltn(a.n[1],j)),mlt(mltn(a.n[2],k),fg[a.a]));

return gf[u];
}


unsigned short itrace(mterm a,int i,int j,int k){
    unsigned short u;

    u=mlt(mlt(oinv(mltn(a.n[0],i)),oinv(mltn(a.n[1],j))),mlt(mltn(a.n[2],k),a.a));

return u;
}

unsigned int mtrace(MP f){
  int i,j,k,ii;
  unsigned int u,n,count=0,f1,f2,f3,f4;
mterm o[4];

 u=0;
 n=terms(f);


 /*
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
 */
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
  mterm c={0};

  c.n[0]=a;
  c.n[1]=b;
  
  return c;


}

int bases(int a){
  int i=0,j=0,count=0;
  

    for(i=0;i<N-1;i++){
      for(j=0;j<N-1;j++){
	//	if(i+j<a){
	  base[count].n[0]=i;
	  base[count++].n[1]=j;
	  //	}
	  if(count>N*N){
	    printf("baka\n");
	  break;
	  }
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
  int i,j,k=0,a,b,count=0,x,y,z,g;
  unsigned int u=0,v=0;
  MP s={0};
  unsigned char **HH;
  
  
  //gfQ*Q
  unsigned short hl[3][4]={{Q+1,0,0,1},{0,Q+1,0,1},{0,0,Q+1,1}};
  //gf256 g=1
  unsigned short el[4][4]={{0,2,1,1},{1,1,1,1},{3,0,0,1},{0,0,3,1}};
  //gf256 g=1
  unsigned short el2[5][4]={{0,2,1,1},{1,1,1,1},{3,0,0,1},{0,0,3,1},{2,0,1,1}};
  //gf8 g=6
  unsigned short sc[4][4]={{3,2,0,1},{2,4,0,1},{0,1,0,1},{4,0,0,1}};
  //gf8 g=3
  unsigned short kl[3][4]={{3,1,0,1},{0,3,1,1},{1,0,3,1}};
  //gfQ*Q
  unsigned short he[3][4]={{Q+1,0,0,1},{0,Q,0,1},{0,1,0,1}};
  //gf16 g=21 #N=121
  unsigned short gu[5][4]={{7,4,0,1},{6,8,0,1},{4,1,0,1},{0,2,0,1},{8,0,0,1}};
  //gf32 g=75 #N=497
  unsigned short ge[6][4]={{15,8,0,1},{14,16,0,1},{12,1,0,1},{8,2,0,1},{0,4,0,1},{16,0,0,1}};
  //gf64 g=212 #N=
  unsigned short gg[7][4]={{31,8,0,1},{30,16,0,1},{28,32,0,1},{24,1,0,1},{16,2,0,1},{0,4,0,1},{32,0,0,1}};
  //gf256 g=2413
  unsigned short gd[9][4]={{127,8,0,1},{126,16,0,1},{124,32,0,1},{120,64,0,1},{112,128,0,1},{96,1,0,1},{64,2,0,1},{0,4,0,1},{128,0,0,1}};
  //gf128 g=315
  unsigned short cc[8][4]={{63,8,0,1},{62,16,0,1},{60,32,0,1},{56,64,0,1},{48,1,0,1},{32,2,0,1},{0,4,0,1},{64,0,0,1}};

  unsigned short lo[3][4]={{2,0,0,1},{1,0,0,3},{0,1,0,6}};
  unsigned short lk[6][4]={{0,2,0,1},{0,1,0,3},{0,0,1,6},{3,1,0,1},{0,3,1,1},{1,0,3,1}};
  //gf32 g=26 #N=157
  unsigned short ts[3][4]={{2,2,5,1},{7,0,2,1},{0,9,0,1}};
  //gf128 g=78 #N=891
  unsigned short tt[3][4]={{3,1,0,1},{13,0,0,1},{0,14,0,1}};
  //gf512
  unsigned short gt[10][4]={{255,16,0,1},{254,32,0,1},{252,64,0,1},{248,128,0,1},{240,256,0,1},{224,1,0,1},{192,2,0,1},{128,4,0,1},{0,8,0,1},{256,0,0,1}};

  unsigned int bb[30][2]={{0,0},{1,0},{0,1},{2,0},{1,1},{0,2},{3,0},{2,1},{1,2},{0,3},{4,0},{3,1},{2,2},{1,3},{0,4},{5,0},{4,1},{3,2},{2,3},{1,4},{6,0},{5,1},{4,2},{3,3},{2,4},{7,0},{6,1},{5,2},{4,3},{3,4}};
  mterm aa[100]={0};
  unsigned char e[64]={0,0,0,0,0,2,0,0,0,4,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};



unsigned char ee[64]={4,0,0,0,0,0,0,0,0,11,0,0,2,0,0,0,0,0,6,0,0,0,0,0,12,0,0,0,0,0,9,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,3,0,0,0,0,7,0,0,0};




  PO t={0};
  unsigned short ss[N*N]={0};
  unsigned short M[K][K]={0};
  unsigned short S[F][H];
  unsigned short sy[N*N]={0};


  memset(S,0,sizeof(S));
  
      for(j=0;j<N*N;j++)
     ss[j]=0;
  
  
  //s=define_curve();

  HH=malloc(sizeof(unsigned short *)*N*N);
  for(i=0;i<N*N;i++)
    HH[i]=malloc(sizeof(unsigned short)*150000);
  
  s=set_curve(he,3);

  u=mtrace(s);
  //  v=u;
  printf("count=%d\n\n",u);
  //  exit(1);

  /*
  for(i=0;i<15*15+1;i++){
    printf("%d %d\n",bb[i][0],bb[i][1]);
    for(j=0;j<2;j++)
      aa[i]=obase(bb[i][0],bb[i][1]);
  }
  */

  for(i=0;i<u;i++){
    printf("%d,%d %d\n",gf[p.z[0][i]],gf[p.z[1][i]],gf[p.z[2][i]]);
    //    t.z[0][i]=p.z[0][i];
    //t.z[1][i]=p.z[1][i];
    //t.z[2][i]=p.z[2][i];
  }
  //  exit(1);

  
  v=bases(2*N);
  printf("bases=%d\n",v);
  //  exit(1);
    
  for(i=0;i<225;i++){
     printf("%d %d\n",base[i].n[0],base[i].n[1]);
    base[i].a=1;
  }
  //  u=count;
  
  /*
  for(i=0;i<30;i++){
    printf("(%d,%d)\n",aa[i].n[0],aa[i].n[1]);
    aa[i].a=1;
  }
  */
  //exit(1);
  
  for(i=0;i<v;i++){
#pragma omp parallel for
    for(j=0;j<u;j++){
      //      if(p.z[0][j]>0)
      HH[i][j]=fg[otrace(base[i],p.z[0][j],p.z[1][j],1)];
    }
  }
  printf("%d %d %d\n",base[0].n[0],base[0].n[1],base[0].a);
  //  exit(1);

  
  for(i=0;i<v;i++){
    // printf("(%d,%d): ",aa[i].n[0],aa[i].n[1]);
    for(j=0;j<u;j++)
      printf("%d ",HH[i][j]);
    printf("\n");
  }
  
  //
  for(i=0;i<v;i++){
    ss[i]=0;
    //#pragma omp parallel for
        for(j=0;j<64;j++){
	  ss[i]^=gf[mlt(fg[ee[j]],HH[i][j])];
          }
	//    if(ss[i]>0)
	printf("syn[%d,%d]=%d\n",base[i].n[0],base[i].n[1],ss[i]);
    
  }
    printf("\n");
    //exit(1);
    //    a=0;
    x=0;
    j=0;
    printf("%d %d\n",p.z[0][0],p.z[1][0]);
    printf("v=%d\n",v);
    //    exit(1);
    
    for(j=0;j<64;j++){
      sy[j]=0;
      x=0;
      for(i=0;i<v;i++){

	x^=gf[mlt(fg[ss[i]],oinv(otrace(base[i], p.z[0][j],p.z[1][j],1)))];
	      
      }
      printf("e=%d %d %d %d\n",x,j,otrace(base[i],p.z[0][j],p.z[1][j],1),ss[i]);
    }
    // printf("%d\n",3^12^2^9^12^8^5^1^7);
    // exit(1);

      
      //printf("e=%d %d\n",x,j);
      //    }
      //    for(j=0;j<u;j++){

      //printf("e=%d %d\n",x,j);
      //    }
    
    free(HH);
    exit(1);

  
  g=(I-1)*(I-2)/2;
  //  g=2413;
  param(u,g);

  //exit(1);
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

  

  //  printf("%d\n",fg[gf[5]^gf[2]^gf[6]]);
  
  return 0;
}
