///////////////////////////////////////////////////////////////////////////
//
// (over finite field) Gauss-Jordan法による逆行列
//
#include <stdio.h>


#define MAXN 10
#define N 16


//unsigned short gf[8]={0,1,2,4,3,6,7,5};
//unsigned short fg[8]={0,1,2,4,3,7,5,6};

//elements of GF16
unsigned char gf[N]={0,1,2,4,8,9,11,15,7,14,5,10,13,3,6,12};
//index of GF16
unsigned char fg[N]={0,1,2,13,3,10,14,8,4,5,11,6,15,12,9,7};
unsigned char c[10][10]={0};

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

int Inv(unsigned char b){
  int i;

      for(i=0;i<N;i++){
        if(gf[mlt(i,b)]==1)
          return i;
      }

    }



int matinv(){
  unsigned char a[15][MAXN]= {
 
     {gf[2], gf[11],gf[15],gf[3], gf[4], gf[3], gf[4], gf[12],gf[3], gf[10]},
     {gf[11],gf[0] ,gf[2], gf[9], gf[1], gf[0], gf[10],gf[3], gf[1], gf[5]},
     {gf[0], gf[9], gf[1], gf[10],gf[3], gf[1], gf[2], gf[15],gf[10],gf[5]},
     {gf[1], gf[3], gf[1], gf[15],gf[10],gf[5], gf[15],gf[9], gf[2], gf[6]},
     {gf[10],gf[2], gf[15],gf[11],gf[15],gf[9], gf[3], gf[4], gf[3], gf[15]},
     {gf[1], gf[10],gf[5], gf[9], gf[2], gf[6], gf[3], gf[15],gf[8], gf[3]},
     {gf[5], gf[5], gf[13],gf[2], gf[6], gf[0], gf[15],gf[8], gf[3], gf[10]},
     {gf[5], gf[2], gf[3], gf[15],gf[8], gf[3], gf[10],gf[0], gf[14],gf[13]},
     {gf[0], gf[1], gf[5], gf[10],gf[5], gf[13],gf[9], gf[2], gf[6], gf[0]},
     {gf[3], gf[15],gf[10],gf[15],gf[9], gf[2], gf[4], gf[3], gf[15],gf[8]},
     
     {gf[2], gf[1], gf[0], gf[3], gf[1], gf[5], gf[15],gf[10],gf[5], gf[13]},   
     {gf[10],gf[9], gf[2], gf[3], gf[15],gf[8], gf[3], gf[10],gf[0], gf[14]},
     {gf[9], gf[10],gf[3], gf[2], gf[15],gf[10],gf[11],gf[15],gf[9], gf[2]},
     {gf[15],gf[15],gf[9], gf[4], gf[3], gf[15],gf[12],gf[3], gf[10],gf[0]},
     {gf[13],gf[6], gf[0], gf[8], gf[8], gf[10],gf[0], gf[14],gf[13],gf[3]}
};
//{{7,2,5},{2,5,2},{5,2,7}}; //={{1,2,0,1},{1,1,2,0},{2,0,1,1},{1,2,1,1}}; //入力用の配列
unsigned char inv_a[10][10]; //ここに逆行列が入る
unsigned char buf; //一時的なデータを蓄える
 unsigned char b[10][10]={0};
int i,j,k; //カウンタ
 int n=10;

 for(i=0;i<n;i++){
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

 return 0;
}


int main(){
  
    int i,j;
    double b[4];


    //  det();
    matinv();
  
    return 0;
}
