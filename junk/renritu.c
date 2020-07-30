/* ガウスの消去法（ピボット選択）*/
#include<stdio.h>
#include<math.h>
#define N 3
/* 行列の大きさ */
main() {
  int i, j, k, p;
  double a[N][N] = {{4,2,6},{1,1,2},{11,7,1}}, b[N] = {32,10,77}, w[N];
  double pmax, s;
  /* 前進消去（ピボット選択）*/
  for(k = 0; k < N-1; k++){
    /* 第ｋステップ */
    p = k; pmax = fabs( a[k][k] );
    for(i = k+1; i < N; i++){
      /* ピボット選択 */
      if(fabs( a[i][k] ) > pmax){ p = i; pmax = fabs( a[i][k] ); } }
    /* エラー処理：ピボットがあまりに小さい時はメッセージを表示して終了　*/
    if(fabs( pmax ) < 1.0e-12){
      printf("too small pivot! \n");
      return(0);
    }
    if(p != k){
      /* 第ｋ行と第ｐ行の交換　*/
      for(i = k; i < N; i++){
	/* 係数行列　*/
	s = a[k][i]; a[k][i] = a[p][i]; a[p][i] = s;
      }
      /* 既知ベクトル */
      s = b[k]; b[k] = b[p]; b[p] = s;
    }
    /* 前進消去 */
    for(i = k +1; i < N; i++){
      /* 第ｉ行 */
      w[i] = a[i][k] / a[k][k]; a[i][k] = 0.0;
      /* 第ｋ行を-a[i][k]/a[k][k]倍して、第ｉ行に加える */
      for(j = k + 1; j < N; j++){
	a[i][j] = a[i][j] - a[k][j] * w[i];
      }
      b[i] = b[i] - b[k] * w[i]; } }
  /* 後退代入 */
  for(i = N - 1; i >= 0; i--){
    for(j = i + 1; j < N; j++){
      b[i] = b[i] - a[i][j] * b[j]; a[i][j] = 0.0;
    }
    b[i] = b[i] / a[i][i]; a[i][i] = 1.0;
  }
  /* 解の表示 */
  for(i = 0; i < N; i++){
    printf("x[%2d] = %12.8lf\n",i+1,b[i]);
  }
  return(0);
} 
