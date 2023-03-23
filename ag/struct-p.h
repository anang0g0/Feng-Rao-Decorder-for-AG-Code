
/* -*- mode: C; coding:utf-8 -*- */
#include <stdlib.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


// monomial
typedef struct
{
  short n; // 単項式の次数
  short a; // 単項式の係数
} oterm;

// polynomial
typedef struct
{
  oterm t[DEG]; // 単項式の配列として多項式を表現する
} OP;

typedef struct
{
  short x[M]; // 配列の添字を次数に、配列の値を係数に持つ多項式の表現
} vec;

// GF(23^3)
typedef struct
{
  unsigned short b0 : 5;
  unsigned short b1 : 5;
  unsigned short b2 : 5;
  unsigned short flag : 1;
} data;

// GF(3^7)
typedef struct
{
  unsigned short b0 : 2;
  unsigned short b1 : 2;
  unsigned short b2 : 2;
  unsigned short b3 : 2;
  unsigned short b4 : 2;
  unsigned short b5 : 2;
  unsigned short b6 : 2;
  unsigned short b7 : 2;
  // unsigned short u;
} T2;

// GF(5^5)
typedef struct
{
  unsigned short b0 : 3;
  unsigned short b1 : 3;
  unsigned short b2 : 3;
  unsigned short b4 : 3;
  unsigned short b5 : 3;
  bool b : 1;
  // unsigned short u;
} TX;

typedef union
{
  data fugo;
  unsigned short u;
  bool b;
} uni;

typedef struct
{
  OP q;
  OP r;
} rem;

typedef struct
{
  short v[M];
  int f;
} MT;

// extra gcd
typedef struct
{
  OP u; // inverse of polynomial?
  OP v; // error locater
  OP d; // gcd
} EX;

typedef union
{ // test(SIMN)
  unsigned long long int u[K / 4];
  short s[K];
} SU;

typedef union
{
  __uint128_t z[K / 16];
  unsigned long long int u[K / 8];
  unsigned int t[K / 4];
  short x[K / 2];
  unsigned char d[K];
} arrayul;


typedef union
{
  short x[K][M];
  uni d[K][M];
  bool b;
} MTX;

typedef union
{
  char x[K * EXP][M];
  uni d[K*EXP/2][M];
  bool b;
} CTX;
