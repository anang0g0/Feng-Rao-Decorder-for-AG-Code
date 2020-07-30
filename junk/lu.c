//学校で習った知識を使ったら問題解決できました。大学行っといてよかったｗ


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define D 4096
#define F 10
#define M 16

unsigned char gf[16]={0,1,2,4,8,3,6,12,11,5,10,7,14,15,13,9};
unsigned char fg[16]={0,1,2,5,3,9,6,11,4,15,10,8,7,14,12,13};

unsigned char cc[F][F]={0};
unsigned char bb[F][F]={0};
unsigned char cl[F][F]={0};
  
  //{{0,1,0,1},{1,0,0,1},{0,0,1,0},{0,0,1,1}};
//{{0,1,1,1},{1,0,1,1},{0,0,1,1},{1,0,0,1}}; //{{1,2,0,-1},{-1,1,2,0},{2,0,1,1},{1,-2,-1,1}}; //入力用の配列
unsigned char inv_a[F][F]; //ここに逆行列が入る
unsigned char buf; //一時的なデータを蓄える
int i,j,k; //カウンタ
int n=10;  //配列の次数
unsigned int c[10][10]={0};


int mlt(int x, int y){

    if(x==0||y==0)
        return 0;

  return ((x+y-2)%(M-1))+1;
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

int Inv(unsigned char b){
  int i;

      for(i=0;i<M;i++){
        if(gf[mlt(i,b)]==1)
          return i;
      }

    }

int inv2(int a,int b){
  int i=0;

  for(i=0;i<16;i++){
    if(b==gf[mlt(fg[a],i)])
      return i;
  }
    
}



unsigned long xor128(void)
{
  unsigned int a=0;
  static unsigned long x=123456789,y=362436069,z=521288629,w=88675123;
    unsigned long t;
    a=rand();
    t=(a^(a<<11));a=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
}


void g2(){
  int i,j,k;


  /*  
  for(i=0;i<F;i++){
    a[i][i]=1;
    bb[i][i]=1;
  }
  
  for(i=0;i<F;i++){
    for(j=i+1;j<F;j++){
      a[i][j]=xor128()%2;
      
    }  
  }
  */
  /*
  for(i=0;i<F;i++){
    for(j=0;j<F;j++)
      printf("%d,",a[i][j]);
    printf("\n");
  }
  printf("\n");
  
  for(i=0;i<F;i++){
    for(j=i+1;j<F;j++){
      bb[j][i]=xor128()%2;
    }
  }
    
  for(i=0;i<F;i++){
    for(j=0;j<F;j++)
      printf("%d,",bb[i][j]);
    printf("\n");
  }
  printf("\n");
  //    exit(1);
  
  for(i=0;i<F;i++){
    for(j=0;j<F;j++){
      for(k=0;k<F;k++){
	cc[i][j]^=bb[i][k]&a[k][j];
      }
    }
  }
  */
  /*
  for(i=0;i<F;i++){
    for(j=0;j<F;j++)
      printf("%d,",cc[i][j]);
    printf("\n");
  }
  printf("\n");
  */
}


void main(){
  int i,j,k,l,ii;
  unsigned char b[F][F]={0};
  unsigned char dd[2040]={0};
  unsigned int flg=0,count=0;
  time_t t;
  FILE *fq;


unsigned char a[F+5][F]={
     {gf[11],gf[0] ,gf[2], gf[9], gf[1], gf[0], gf[10],gf[3], gf[1], gf[5]},
     {gf[0], gf[9], gf[1], gf[10],gf[3], gf[1], gf[2], gf[15],gf[10],gf[5]},
     {gf[2], gf[1], gf[0], gf[3], gf[1], gf[5], gf[15],gf[10],gf[5], gf[13]},
     {gf[9], gf[10],gf[3], gf[2], gf[15],gf[10],gf[11],gf[15],gf[9], gf[2]},
     {gf[1], gf[3], gf[1], gf[15],gf[10],gf[5], gf[15],gf[9], gf[2], gf[6]},
     {gf[0], gf[1], gf[5], gf[10],gf[5], gf[13],gf[9], gf[2], gf[6], gf[0]},
     {gf[10],gf[2], gf[15],gf[11],gf[15],gf[9], gf[3], gf[4], gf[3], gf[15]},
     //{gf[3], gf[15],gf[10],gf[15],gf[9], gf[2], gf[4], gf[3], gf[15],gf[8]},
     //{gf[1], gf[10],gf[5], gf[9], gf[2], gf[6], gf[3], gf[15],gf[8], gf[3]},
     {gf[5], gf[5], gf[13],gf[2], gf[6], gf[0], gf[15],gf[8], gf[3], gf[10]},
     //{gf[2], gf[11],gf[15],gf[3], gf[4], gf[3], gf[4], gf[12],gf[3], gf[10]},
     
     {gf[10],gf[9], gf[2], gf[3], gf[15],gf[8], gf[3], gf[10],gf[0], gf[14]},
     {gf[5], gf[2], gf[3], gf[15],gf[8], gf[3], gf[10],gf[0], gf[14],gf[13]},
     {gf[15],gf[15],gf[9], gf[4], gf[3], gf[15],gf[12],gf[3], gf[10],gf[0]},      
     {gf[13],gf[6], gf[0], gf[8], gf[8], gf[10],gf[0], gf[14],gf[13],gf[3]}

  
  /*
     {gf[2], gf[1], gf[0], gf[3], gf[1], gf[5], gf[15],gf[10],gf[5], gf[13]},   
     {gf[2], gf[11],gf[15],gf[3], gf[4], gf[3], gf[4], gf[12],gf[3], gf[10]},
     {gf[11],gf[0] ,gf[2], gf[9], gf[1], gf[0], gf[10],gf[3], gf[1], gf[5]},
     {gf[0], gf[9], gf[1], gf[10],gf[3], gf[1], gf[2], gf[15],gf[10],gf[5]},
     {gf[1], gf[3], gf[1], gf[15],gf[10],gf[5], gf[15],gf[9], gf[2], gf[6]},
     {gf[0], gf[1], gf[5], gf[10],gf[5], gf[13],gf[9], gf[2], gf[6], gf[0]},
     {gf[10],gf[2], gf[15],gf[11],gf[15],gf[9], gf[3], gf[4], gf[3], gf[15]},
     {gf[1], gf[10],gf[5], gf[9], gf[2], gf[6], gf[3], gf[15],gf[8], gf[3]},
     {gf[5], gf[5], gf[13],gf[2], gf[6], gf[0], gf[15],gf[8], gf[3], gf[10]},
     {gf[15],gf[15],gf[9], gf[4], gf[3], gf[15],gf[12],gf[3], gf[10],gf[0]},
     {gf[10],gf[9], gf[2], gf[3], gf[15],gf[8], gf[3], gf[10],gf[0], gf[14]},
     {gf[5], gf[2], gf[3], gf[15],gf[8], gf[3], gf[10],gf[0], gf[14],gf[13]},
     {gf[3], gf[15],gf[10],gf[15],gf[9], gf[2], gf[4], gf[3], gf[15],gf[8]},
     {gf[9], gf[10],gf[3], gf[2], gf[15],gf[10],gf[11],gf[15],gf[9], gf[2]},
 
     {gf[13],gf[6], gf[0], gf[8], gf[8], gf[10],gf[0], gf[14],gf[13],gf[3]}
  */

   
};
/*
  {gf[11],gf[0],gf[2],gf[9],gf[7],gf[6],gf[5],gf[9],gf[15],gf[14],gf[6]},
  {gf[10],gf[10],gf[13],gf[9],gf[8],gf[4],gf[5],gf[12],gf[11],gf[7],gf[8]},
  {gf[0],gf[2],gf[0],gf[3],gf[2],gf[6],gf[15],gf[9],gf[12],gf[11],gf[8]},
  {gf[12],gf[15],gf[5],gf[3],gf[13],gf[8],gf[4],gf[1],gf[0],gf[10],gf[10]},
  {gf[7],gf[5],gf[11],gf[13],gf[10],gf[13],gf[6],gf[14],gf[4],gf[5],gf[14]},
  {gf[6],gf[8],gf[7],gf[2],gf[15],gf[6],gf[15],gf[4],gf[10],gf[1],gf[11]},
  {gf[7],gf[5],gf[8],gf[4],gf[11],gf[6],gf[15],gf[7],gf[6],gf[8],gf[0]},
  {gf[10],gf[12],gf[0],gf[13],gf[7],gf[2],gf[10],gf[4],gf[7],gf[4],gf[14]},
  {gf[0],gf[10],gf[15],gf[13],gf[6],gf[6],gf[14],gf[11],gf[0],gf[6],gf[14]},
  {gf[10],gf[15],gf[6],gf[8],gf[3],gf[6],gf[1],gf[9],gf[14],gf[13],gf[0]}
  }; */
 
   
//  while(flg<F || count!=F*F-F){
    
    srand(clock()+time(&t));

 for(i=0;i<n+1;i++){
   for(j=0;j<n;j++){
     //     a[i][j]=rand()%16;
     printf("%d,",a[i][j]);
   }
    printf("\n");
 }
 // printf("\n");
 for(i=0;i<n;i++){
   for(j=0;j<n;j++)
     c[i][j]=a[i][j];
 }
//単位行列を作る
for(i=0;i<n;i++){
 for(j=0;j<n;j++){
 inv_a[i][j]=(i==j)?1:0;
 }
}
//掃き出し法
for(i=0;i<n;i++){
  if(a[i][i]==0){
    for(j=0;j<n;j++){
      a[i][j]^=a[i+1][j];
      inv_a[i][j]^=inv_a[i+1][j];
    }
  }

  if(a[i][i]>0)
  buf=gf[Inv(fg[a[i][i]])];
 for(j=0;j<n;j++){
   a[i][j]=gf[mlt(fg[buf],fg[a[i][j]])];
   inv_a[i][j]=gf[mlt(fg[buf],fg[inv_a[i][j]])];
 }
for(j=0;j<n;j++){
 if(i!=j){
  buf=a[j][i];
  for(k=0;k<n;k++){
    a[j][k]^=gf[mlt(fg[a[i][k]],fg[buf])];
    inv_a[j][k]^=gf[mlt(fg[inv_a[i][k]],fg[buf])];
  }
 }
}
}
//逆行列を出力
for(i=0;i<n;i++){
 for(j=0;j<n;j++){
  printf(" %d",inv_a[i][j]);
 }
 printf("\n");
}
/*
 for(i=0;i<n;i++){
   for(j=0;j<n;j++)
     printf("%d ",a[i][j]);
   printf("\n");
 }
*/
//検算
 for(i=0;i<n;i++){
   for(j=0;j<n;j++){
     for(k=0;k<n;k++)
       b[i][j]^=gf[mlt(fg[c[k][j]],fg[inv_a[i][k]])];

     printf("%d,",b[i][j]);
   }
   printf("\n");
 }

 return;


  
}

