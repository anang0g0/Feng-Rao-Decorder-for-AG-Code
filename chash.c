
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//#include "4096.txt"
//#include "2048.h"
//#include "gf512.c"


#define N 256
#define M 256

typedef union {
  unsigned long long int u[8];
  unsigned char d[64];
} arrayul;

typedef struct a4 {
  unsigned char ar[4];
} array;

typedef struct a8 {
  unsigned char ar[8];
} array8;

typedef struct {
  unsigned int h[16];
} array16;

typedef struct aN {
  unsigned char ar[N];
} arrayn;

typedef struct pub {
  unsigned char a[N];
  unsigned char b[N];
} set;





unsigned char aa[64]; //={ 148, 246, 52, 251, 16, 194, 72, 150, 249, 23, 90, 107, 151, 42, 154, 124, 48, 58, 30, 24, 42, 33, 38, 10, 115, 41, 164, 16, 33, 32, 252, 143, 86, 175, 8, 132, 103, 231, 95, 190, 61, 29, 215, 75, 251, 248, 72, 48, 224, 200, 147, 93, 112, 25, 227, 223, 206, 137, 51, 88, 109, 214, 17, 172};



#define str_length 128
#define password_length 256

char password[password_length + 1];

void seed(void){
    /*
    * 変数宣言
    */
    char str[str_length + 1];
    time_t t;
    int i, j, k, rnd;
    char confirm[2];
    
    /*
    * 乱数の初期化
    */
    srand(clock()+time(&t));
  i=0;
  while(i<1000)
    i++;
    /*
    * 乱数生成とパスワードの生成
    */
    for(i = 0; i < str_length; i++) {
        for(j = 0; j < 2; j++) {
            k = i * 2 + j;
            do {
                rnd = rand();
                password[k] = str[i] + rnd;
            }while(!isalnum(password[k]));
        }
    }
    
    /*
    * NULL文字の挿入
    */
    password[password_length] = '\0';
    
    /*
    * パスワードの出力
    */
//    printf("生成パスワード：%s",password);
    
return;
  
}


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




#define SHR(n, x) ( (x)>>(n) )
#define ROTR(n, x) ( ( (x)>>(n) ) | ( (x)<<(64-n) ) )

#define Ch(x,y,z)  ( ( (x) & (y) ) ^ ( ~(x) & (z) ) )
#define Maj(x,y,z) ( ( (x) & (y) ) ^ (  (x) & (z) ) ^ ( (y) & (z) ) )

#define S512_0(x) ( ROTR(28 , x) ^ ROTR(34 , x) ^ ROTR(39, x) )
#define S512_1(x) ( ROTR(14 , x) ^ ROTR(18 , x) ^ ROTR(41, x) )
 
#define s512_0(x) ( ROTR( 1 , x) ^ ROTR( 8 , x) ^ SHR( 7 , x) )
#define s512_1(x) ( ROTR(19 , x) ^ ROTR(61 , x) ^ SHR( 6 , x) )


void SHA512_transform(unsigned long long H[],unsigned long long W[])
{
    static const unsigned long long K[80]=
    {
    0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
    0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
    0xd807aa98a3030242ULL, 0x12835b0145706fbeULL, 0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
    0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
    0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
    0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
    0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
    0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL, 0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
    0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
    0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
    0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
    0xd192e819d6ef5218ULL, 0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
    0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL, 0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
    0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
    0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
    0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
    0xca273eceea26619cULL, 0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
    0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL, 0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
    0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
    0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
    };

    unsigned long long T1, T2;
    unsigned long long x[8];
    int t;
    memcpy(x, H, 64);
#define ROUND(n,a,b,c,d,e,f,g,h)\
        T1=x[h]+S512_1(x[e])+Ch(x[e],x[f],x[g])+K[t+n]+W[t+n];\
        T2=S512_0(x[a])+Maj(x[a],x[b],x[c]);\
        x[d]=x[d]+T1;\
        x[h]=T1+T2

    for(t=0; t<80; t+=8){
        ROUND(0,0,1,2,3,4,5,6,7);
        ROUND(1,7,0,1,2,3,4,5,6);
        ROUND(2,6,7,0,1,2,3,4,5);
        ROUND(3,5,6,7,0,1,2,3,4);
        ROUND(4,4,5,6,7,0,1,2,3);
        ROUND(5,3,4,5,6,7,0,1,2);
        ROUND(6,2,3,4,5,6,7,0,1);
        ROUND(7,1,2,3,4,5,6,7,0);
    }
    H[0]+=x[0];
    H[1]+=x[1];
    H[2]+=x[2];
    H[3]+=x[3];
    H[4]+=x[4];
    H[5]+=x[5];
    H[6]+=x[6];
    H[7]+=x[7];
}


void SHA512_process(unsigned long long H[],unsigned long long W[])
{
    unsigned long *Buf=(unsigned long *)W;
    int t;
    for (t=0 ;t<16 ;t++) //little-endianをbig-endianに変換　big-endianの機種では不要
        W[t]=(unsigned long long)(Buf[t*2]<<24 | Buf[t*2]<<8 & 0xFF0000 | Buf[t*2]>>8 & 0xFF00 | Buf[t*2]>>24)<<32
            |(unsigned long long)(Buf[t*2+1]<<24 | Buf[t*2+1]<<8 & 0xFF0000 | Buf[t*2+1]>>8 & 0xFF00 | Buf[t*2+1]>>24);
    for (t=16 ;t<80 ; t++) W[t] = s512_1(W[t-2]) + W[t-7] + s512_0(W[t-15]) + W[t-16];
    SHA512_transform(H,W);
}


//残りの、128バイトより少ないバイトの処理、終了処理  
void SHA512_finish(unsigned long long H[],unsigned long long W[],unsigned long long FileLen)
{
    unsigned long *Buf=(unsigned long *)W;
    int t;
    int Witi=(FileLen%128)/8;
    int amari=(FileLen%8)*8; //64ビット中のデータのない余りビット数 
    for (t=0 ;t<=Witi ;t++) //little-endianをbig-endianに変換　big-endianの機種では不要
        W[t]=(unsigned long long)(Buf[t*2]<<24 | Buf[t*2]<<8 & 0xFF0000 | Buf[t*2]>>8 & 0xFF00 | Buf[t*2]>>24)<<32
            |(unsigned long long)(Buf[t*2+1]<<24 | Buf[t*2+1]<<8 & 0xFF0000 | Buf[t*2+1]>>8 & 0xFF00 | Buf[t*2+1]>>24);
    if (amari==0) W[Witi]=0x8000000000000000ULL; //メッセージの終わりに1ビットを立てる 
        else W[Witi]=W[Witi] & 0xFFFFFFFFFFFFFFFFULL<<(64-amari) | 0x8000000000000000ULL>>amari;
    Witi++;

    if(Witi>=15){  //最後に入れる「ファイル長」が入らないので、次のブロックを作る
        for (t=Witi; t<16 ; t++) W[t]=0;  //残りのブロックを0で埋める
        for (t=16 ; t<80 ; t++) W[t] = s512_1(W[t-2]) + W[t-7] + s512_0(W[t-15]) + W[t-16];
        SHA512_transform(H,W);
        Witi=0;
    }

    for(t=Witi;t<14; t++) W[t]=0; //残りのブロックを0で埋める
    W[14]=FileLen>>61; //「ファイル長」のバイトをビットに変換して入れる 
    W[15]=FileLen<<3;
    for (t=16 ; t<80 ; t++) W[t] = s512_1(W[t-2]) + W[t-7] + s512_0(W[t-15]) + W[t-16];
    SHA512_transform(H,W);
}


int SHA512(char *filename,unsigned long long H[])
{
    H[0]=0x6a09e667f3bcc908ULL;
    H[1]=0xbb67ae8584caa73bULL;
    H[2]=0x3c6ef372fe94f82bULL;
    H[3]=0xa54ff53a5f1d36f1ULL;
    H[4]=0x510e527fade682d1ULL;
    H[5]=0x9b05688c2b3e6c1fULL;
    H[6]=0x1f83d9abfb41bd6bULL;
    H[7]=0x5be0cd19137e2179ULL;
    
    unsigned long long W[80];
    FILE *fp;
    unsigned long Len;
    unsigned long long FileLen=0;//ファイル長

    if (!(fp=fopen(filename , "rb"))) return 1;
    while(1){
        Len=fread(W, 1, 128, fp);
        FileLen+=Len;
        if (Len!=128) break; 
        SHA512_process(H,W);
    }
    SHA512_finish(H,W,FileLen);
    if(ferror(fp)){//ファイルエラーが発生したかどうか調べる
        fclose(fp);
        return 1;
    }
    fclose(fp);
    return 0;
}

int mon(unsigned long long H[], unsigned long long W[80])
{
    H[0]=0x6a09e667f3bcc908ULL;
    H[1]=0xbb67ae8584caa73bULL;
    H[2]=0x3c6ef372fe94f82bULL;
    H[3]=0xa54ff53a5f1d36f1ULL;
    H[4]=0x510e527fade682d1ULL;
    H[5]=0x9b05688c2b3e6c1fULL;
    H[6]=0x1f83d9abfb41bd6bULL;
    H[7]=0x5be0cd19137e2179ULL;
    

    FILE *fp;
    unsigned long Len;
    unsigned long long FileLen=0;//ファイル長


        SHA512_process(H,W);

    SHA512_finish(H,W,FileLen);

    return 0;
}


int sha(int argc, char**argv)
{
    unsigned long long H[8]; //ハッシュ
    int t,i;
   typedef union a {
	unsigned long long l;
	unsigned char e[8];
	} hash;
hash bb[8];
  int count=0;

    if (SHA512(argv[1],H)){  //argv[1]はファイル名の先頭の番地 ファイル名からH[8]を求める。
        printf("ファイルエラーが発生しました");
    }else{
        printf("%s\n\n",argv[1]);  //argv[1]はファイル名の先頭の番地
        for (t=0; t<8; t++) { bb[t].l=H[t];}
	printf("\n\n");
	for (t=0; t<8; t++) {
          for(i=0;i<8;i++) { aa[count++]=bb[t].e[i]; }
	}
    }
    printf("\n\n");
//    system("PAUSE");


  return 0;

}


