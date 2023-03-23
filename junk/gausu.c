
/* ガウスの消去法（ピボット選択）*/
#include<stdio.h>
#include<math.h>


#define M 16


unsigned short gf[16]={0,1,2,4,8,3,6,12,11,5,10,7,14,15,13,9};
unsigned short fg[16]={0,1,2,5,3,9,6,11,4,15,10,8,7,14,12,13};


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


#define N 9  /* 行列の大きさ */
int main()
{
   int i, j, k, p;
   int a[N][N] =   {
     { gf[0] ,gf[2], gf[9], gf[1], gf[0], gf[10], gf[3], gf[1], gf[5]},
     { gf[9], gf[1], gf[10], gf[3], gf[1], gf[2], gf[15], gf[10], gf[5]},
     {gf[1], gf[0], gf[3], gf[1], gf[5], gf[15], gf[10], gf[5], gf[13]},
     {gf[10], gf[3], gf[2], gf[15], gf[10], gf[11], gf[15], gf[9], gf[2]},
     {gf[3], gf[1], gf[15], gf[10], gf[5], gf[15], gf[9], gf[2], gf[6]},
     {gf[1], gf[5], gf[10], gf[5], gf[13], gf[9], gf[2], gf[6], gf[0]},
     {gf[2], gf[15], gf[11], gf[15], gf[9], gf[3], gf[4], gf[3], gf[15]},
     {gf[15], gf[10], gf[15], gf[9], gf[14], gf[3], gf[15], gf[8]},
     {gf[10], gf[5], gf[9], gf[2], gf[6], gf[3], gf[15],gf[8], gf[3]}},
     b[N] = {gf[11],gf[0],gf[2],gf[9],gf[1],gf[0],gf[10],gf[3],gf[1]}, w[N];
     int pmax, s;
     
/* 前進消去（ピボット選択）*/

   for(k = 0; k < N-1; k++){  /* 第ｋステップ */
      p = k;
      pmax = a[k][k];
      for(i = k+1; i < N; i++){  /* ピボット選択 */
         if(a[i][k] > pmax){
            p = i;
            pmax = a[i][k];
         }
      }

 /* エラー処理：ピボットがあまりに小さい時はメッセージを表示して終了　*/
      if(pmax < 0){
         printf("too small pivot! \n");
         return(0);
      }
      if(p != k){  /* 第ｋ行と第ｐ行の交換　*/
         for(i = k; i < N; i++){
            /* 係数行列　*/
            s = a[k][i];
            a[k][i] = a[p][i];
            a[p][i] = s;
         }
         /* 既知ベクトル */
         s = b[k];
         b[k] = b[p];
         b[p] = s;
      }
/* 前進消去 */
      for(i = k +1; i < N; i++){ /* 第ｉ行 */
	w[i] = gf[mlt(fg[a[i][k]] , Inv(fg[a[k][k]]))];
         a[i][k] = 0;
         /* 第ｋ行を-a[i][k]/a[k][k]倍して、第ｉ行に加える */
         for(j = k + 1; j < N; j++){
	   a[i][j] = a[i][j] ^ gf[mlt(fg[a[k][j]], fg[w[i]])];
         }
         b[i] = b[i] ^ gf[mlt(fg[b[k]] ,fg[w[i]])];
      }
   }
/* 後退代入 */
      for(i = N - 1; i >= 0; i--){
         for(j = i + 1; j < N; j++){
	   b[i] = b[i] ^ gf[mlt(fg[a[i][j]] , fg[b[j]])];
            a[i][j] = 0;
         }
         b[i] = gf[mlt(fg[b[i]] , Inv(fg[a[i][i]]))];
         a[i][i] = 1;
      }
/* 解の表示 */
      for(i = 0; i < N; i++){
	printf("x[%2d] = %d\n",i+1,fg[b[i]]);
      }
      return(0);
}
