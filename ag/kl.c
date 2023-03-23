
#include <stdio.h>
#include <stdlib.h>

//#include "gcmb.c"
/* Extend Binary Klein Code and Syndrome Decoding */

#define N 8

static int GF8[8] = {0, 1, 2, 4, 3, 6, 7, 5};
int countt = 0;
unsigned char bs[18][23];

// klein code
int kl[4][23] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6},
    {0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7},
    {0, 2, 3, 5, 1, 3, 7, 1, 5, 6, 3, 4, 6, 1, 2, 4, 2, 6, 7, 4, 5, 7, 7},
    {0, 2, 3, 5, 2, 4, 1, 3, 7, 1, 6, 7, 2, 5, 6, 1, 7, 4, 5, 3, 4, 6, 7}};

/* [24,12,12]-�g���S�[���C���� */
static short gt[24] = {
    0b100000000000,
    0b010000000000,
    0b001000000000,
    0b000100000000,
    0b000010000000,
    0b000001000000,
    0b000000100000,
    0b000000010000,
    0b000000001000,
    0b000000000100,
    0b000000000010,
    0b000000000001,
    0b101000111011,
    0b110100011101,
    0b011010001111,
    0b101101000111,
    0b110110100011,
    0b111011010001,
    0b011101101001,
    0b001110110101,
    0b000111011011,
    0b100011101101,
    0b010001110111};
//  0b111111111110};

unsigned int gol_ht[12] = {
    0b110111000101100000000000,
    0b011011100011010000000000,
    0b101101110001001000000000,
    0b010110111001000100000000,
    0b001011011101000010000000,
    0b000101101111000001000000,
    0b100010110111000000100000,
    0b110001011011000000010000,
    0b111000101101000000001000,
    0b011100010111000000000100,
    0b101110001011000000000010,
    0b111111111110000000000001};

/* [24,12,12]-�g���S�[���C���� */
unsigned int gol_gc[12] = {
    0b100000000000110111000101,
    0b010000000000011011100011,
    0b001000000000101101110001,
    0b000100000000010110111001,
    0b000010000000001011011101,
    0b000001000000000101101111,
    0b000000100000100010110111,
    0b000000010000110001011011,
    0b000000001000111000101101,
    0b000000000100011100010111,
    0b000000000010101110001011,
    0b000000000001111111111110};

/* klein code over GF(8) */

unsigned int kl_bin[22]={
0b100000000000000000110,
0b100100010100000000011,
0b100100110100000000000,
0b100100101100000000000,
0b100010100110000000000,
0b100010110110000000000,
0b100010111110000001000,
0b100110100101000010000,
0b100110101101000100000,
0b100110011101010000000,
0b100001110111110000000,
0b100001001111111000000,
0b100001011111110000000,
0b100101100010100101000,
0b100101010010110110000,
0b100101001010111100000,
0b100011010001000100000,
0b100011011001000101000,
0b100011111001000111000,
0b100111001011000111000,
0b100111101011000110000,
0b100111111011000101000,
//0b011111111111000111000,
};
/*
unsigned int kl_bin[22]={
0b100000000000,
0b100100010010,
0b100100110110,
0b100100101101,
0b100010100010,
0b100010110001,
0b100010111100,
0b100110100110,
0b100110101111,
0b100110011100,
0b100001110011,
0b100001001111,
0b100001011010,
0b100101100101,
0b100101010011,
0b100101001100,
0b100011010111,
0b100011011001,
0b100011111101,
0b100111001110,
0b100111101001,
0b100111111011,
//0b011111111111,
};
*/
/*
unsigned int kl_bin[23] = {
    0b100000000000,
    0b100100010010,
    0b100100110110,
    0b100100101101,
    0b100010100010,
    0b100010110001,
    0b100010111100,
    0b100110100110,
    0b100110101111,
    0b100110011100,
    0b100001110011,
    0b100001001111,
    0b100001011010,
    0b100101100101,
    0b100101010011,
    0b100101001100,
    0b100011010111,
    0b100011011001,
    0b100011111101,
    0b100111001110,
    0b100111101001,
    0b100111111011,
    0b011111111111};
*/
/* $BM-8BBN>e$G$N3]$1;;(B */
int mlt(int x, int y)
{
  if (x == 0 || y == 0)
  {
    return (0);
  }
  return ((x + y - 2) % (N - 1)) + 1;
}

/* $BM-8BBN>e$G$NN_>h(B */
int mltn(int n, int x)
{
  int i, j;

  i = x;
  for (j = 1; j < n; j++)
    i = mlt(i, x);

  return i;
}

void base(int x, int y, int z, int m)
{

  switch (m)
  {
  case 2:
    bs[0][countt] = 1;
    bs[1][countt] = GF8[x];
    bs[2][countt] = GF8[y];
    bs[3][countt] = GF8[mlt(x, x)];
    break;

  case 3:
    bs[0][countt] = 1;
    bs[1][countt] = x;
    bs[2][countt] = y;
    bs[3][countt] = mlt(x, x);
    bs[4][countt] = mlt(x, y); 
    bs[5][countt] = mlt(y, y);
    bs[6][countt] = mltn(3, x);
    //bs[7][countt] = mlt(y, mltn(2, x));
    //bs[8][countt] = mlt(x, mltn(2, y));
    //bs[9][countt] = mlt(y, mltn(4, x));
  

    break;

  case 4:
    bs[0][countt] = 1;
    bs[1][countt] = x;
    bs[2][countt] = mlt(x, x);
    bs[3][countt] = mltn(3, x);
    bs[4][countt] = mltn(4, x);
    bs[5][countt] = y;
    bs[6][countt] = mlt(y, x);
    bs[7][countt] = mlt(y, mltn(2, x));
    bs[8][countt] = mlt(y, mltn(3, x));
    bs[9][countt] = mlt(y, mltn(4, x));
    bs[10][countt] = mlt(y, y);
    bs[11][countt] = mlt(bs[10][countt], x);
    bs[12][countt] = mlt(bs[10][countt], mltn(2, x));
    bs[13][countt] = mlt(bs[10][countt], mltn(3, x));
    break;

  case 5:
    bs[0][countt] = 1;
    bs[1][countt] = x;
    bs[2][countt] = mlt(x, x);
    bs[3][countt] = mltn(3, x);
    bs[4][countt] = mltn(4, x);
    bs[5][countt] = mltn(5, x);
    bs[6][countt] = y;
    bs[7][countt] = mlt(x, y);
    bs[8][countt] = mlt(y, mltn(2, x));
    bs[9][countt] = mlt(y, mltn(3, x));
    bs[10][countt] = mlt(y, mltn(4, x));
    bs[11][countt] = mlt(y, mltn(5, x));
    bs[12][countt] = mlt(y, mltn(6, x));
    bs[13][countt] = mlt(y, y);
    bs[14][countt] = mlt(bs[13][countt], x);
    bs[15][countt] = mlt(bs[13][countt], mltn(2, x));
    bs[16][countt] = mlt(bs[13][countt], mltn(3, x));
    bs[17][countt] = mlt(bs[13][countt], mltn(4, x));
  }
}

int syndy()
{
  int i, j, k, l = 0, n = 0,c=0,m=0;
  int table[2097152] = {0};

/*
  for (i = 0; i < 22; i++)
  {
    l=kl_bin[i];
    if(table[l]==0){
    table[l]=1;
    c++;
    } else if (table[l] == 1){
    m++;
    }
  }
*/

  for(i=0;i<22;i++){
    for (j = 0; j < 22; j++)
    {
      if (table[kl_bin[i] ^ kl_bin[j]] == 0)
      {
        table[kl_bin[i]^kl_bin[j]]=1;
        c++;
      }else if (i!=j && table[kl_bin[i] ^ kl_bin[j]] == 1){
      m++;
      }
    }
  }
  
 for(i=0;i<22;i++){
  for(j=0;j<22;j++){
    for(k=0;k<22;k++){
    l=kl_bin[i]^kl_bin[j]^kl_bin[k];
    if(table[l]==0){
    table[l]=1;
    c++;
    }
    }
  }
}

  int countt = 0;
  for (i = 0; i < 2097152; i++)
  {
    if (table[i] > 0)
    {
      countt++;
    }
  }
  
  printf("kl=%d %d\n", c,countt);
}

int rev3(int a)
{
  int i = 0, j = 0, k = 0, l = 0;

  // printf("%d\n",a);

  k = a % 2;
  k = (k << 2);
  // printf("d%d\n",k);
  j ^= (a >> 2);

  // printf("a%d\n",j);
  l ^= (a >> 1) % 2;
  l = (l << 1);
  // printf("b%d\n",l);
  i = k ^ l ^ j;
  // printf("c%d\n",i);
  // exit(1);

  return i;
}


void golay()
{
  int i, j, k, m, c = 0, l = 0;
  //  unsigned short l = 0;
  int table[4096] = {0};

  for (i = 0; i < 23; i++)
  {
    l=gt[i];
    if(table[l]==0){
    //table[l]=1;
    //c++;
    } else if (table[l] == 1){
    m++;
    }
  }

  for(i=0;i<23;i++){
    l=gt[i];
    for (j = 0; j < 23; j++)
    {
      if (i!=j && table[l ^ gt[j]] == 0)
      {
        table[l^gt[j]]=1;
        c++;
      }else if (i!=j && table[l ^ gt[j]] == 1){
      m++;
      }
    }
  }
 
for(i=0;i<23;i++){
  for(j=0;j<23;j++){
    for(k=0;k<23;k++){
    l=gt[i]^gt[j]^gt[k];
    if(table[l]==0){
    table[l]=1;
    c++;
    }
    }
  }
}
  int countc=0;
  for(i=0;i<4096;i++){
    if(table[i]>0)
    countc++;
  }
  
  printf("set=%d %d %d\n", c,countc,m);
  // exit(1);
}

void bin()
{
  int i, j, k, l;

  printf("unsigned int kl_bin[22]={");
  for (i = 0; i < 23; i++)
  {
    printf("0b");
    for (j = 0; j < 7; j++)
    {
      l = 0;
      l = kl[j][i];
      // l=rev3(l);

      for (k = 0; k < 3; k++)
      {
        // while(l>0){
        printf("%d", l % 2);
        l = (l >> 1);
      }
    }
    printf(",\n");
  }
  printf("};\n");
  // printf("\n");
}

// x^3y + y^3 + x = 0
int main()
{
  int i, j, m, l = 0,count=0;
  unsigned char x, y, z;

  // l=rev3(6);
  // printf("%d\n",l);
  // exit(1);
  // scanf("%d",&m);
  /*
    if(m<2 || m>5){
      printf("1<m<6\n");
      exit(0);
    }
  */
   m=3;
  count = 0;
  z = 1;
  for (x = 0; x < N; x++)
  {
    for (y = 0; y < N; y++)
    {
      if ((GF8[mlt(mltn(3, x), y)] ^ GF8[mlt(mltn(3, y), z)] ^ GF8[mlt(x, mltn(3, z))]) == 0)
      {
        /* printf("%d %d %d\n",x,y,z); */
        base(x, y, 1, m);
        countt++;
      }
    }
  }
  printf("%d\n", countt);
  for(j=0;j<m*2-2;j++){
  for(i=0;i<22;i++)
  kl[j][i]=bs[j][i];
  }
  bin();
  golay();
  syndy();
  exit(1);

  m = 2;
  printf("int lk[4][22]={\n");
  for (j = 0; j < m * 3 - 2; j++)
  {
    printf("{");
    for (i = 0; i < countt + 1; i++)
      printf("%u,", kl[j][i]);
    printf("},\n");
  }
  printf("};\n");
}
