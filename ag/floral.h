#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "8192.h"

// 符号のパラーメータの指定。通常[N,K,T]として、
// Nは符号の長さ、Kが符号の次元、Tは訂正エラー数
// を表す。ここではDは符号長にしている。
#define N 27  // 元の数
#define M 27  // 符号長　M<=N 3072
#define K (4) // 符号の次元
#define DEG (K * 2 + 1)
#define T (K / 2) // エラーの数
#define E (3)     // 拡大体の拡大次数
// #define D (2187) //符号長（短縮符号）
#define F K *E // 2040
#define BXP 5 //拡大体のビットサイズ
#define EXP 3  // degree
#define Pr 3   // 基礎体
// #define O 2197 // 1331,2197,4913,6859,3125,2187,19683
#define ORD 27 // 1331,2197,4913,6859,3125,2187,19683,29791

