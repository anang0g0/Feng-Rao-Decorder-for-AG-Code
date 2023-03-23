#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "global.h"
#include "struct.h"

// 5-error-correction

#define V 3 // 変数の数
#define P 1024
#define Q 4     // 基礎体
#define N Q *Q  // 定義体
#define I Q + 1 // 曲線の次数
#define J 3
#define K I - 2                         // number h
#define H (K + 1) * (K + 2) / 2         // シンドローム行列の横ベクトルの長さ
#define F (J - K + 1) * (J - K + 2) / 2 // シンドローム行列の縦ベクトル
#define U 26
#define E 6

typedef struct
{

    unsigned short n[V];
    unsigned short a;

} mterm;

typedef struct
{

    mterm x[P];
    int terms;

} MP;

typedef struct
{

    unsigned char z[V][150000];

} PO;

typedef struct
{

    unsigned short x[100][100];

} vMP;

// sage比較用
static const unsigned short gf[16] = {0, 1, 2, 4, 8, 3, 6, 12, 11, 5, 10, 7, 14, 15, 13, 9};
static const unsigned short fg[16] = {0, 1, 2, 5, 3, 9, 6, 11, 4, 15, 10, 8, 7, 14, 12, 13};

// static unsigned short gf[8] = {0, 1, 2, 4, 3, 6, 7, 5};
// static unsigned short fg[8] = {0, 1, 2, 4, 3, 7, 5, 6};

// unsigned short gf[8]={0,1,2,4,3,6,7,5};
// unsigned short fg[8]={0,1,2,4,3,7,5,6};
/*
//nomal
unsigned char gf[N] =
  { 0, 1, 2, 4, 8, 9, 11, 15, 7, 14, 5, 10, 13, 3, 6, 12 };
unsigned char fg[N] =
  { 0, 1, 2, 13, 3, 10, 14, 8, 4, 5, 11, 6, 15, 12, 9, 7 };

unsigned char gf[32]={
0,1,2,4,8,16,23,25,5,10,20,
31,9,18,19,17,21,29,13,26,3,
6,12,24,7,14,28,15,30,11,22,
27};
unsigned char fg[32]={0,1,2,20,3,8,21,24,4,12,9,29,22,18,25,27,5,15,13,14,10,16,30,6,23,7,19,31,26,17,28,11};
*/

// unsigned char gf[64]={0,1,2,4,8,16,32,33,35,39,47,63,31,62,29,58,21,42,53,11,22,44,57,19,38,45,59,23,46,61,27,54,13,26,52,9,18,36,41,51,7,14,28,56,17,34,37,43,55,15,30,60,25,50,5,10,20,40,49,3,6,12,24,48};
// unsigned char fg[64]={0,1,2,59,3,54,60,40,4,35,55,19,61,32,41,49,5,44,36,23,56,16,20,27,62,52,33,30,42,14,50,12,6,7,45,8,37,46,24,9,57,38,17,47,21,25,28,10,63,58,53,39,34,18,31,48,43,22,15,26,51,29,13,11};

// unsigned short gf[128]={0,1,2,4,8,16,32,64,65,67,71,79,95,127,63,126,61,122,53,106,21,42,84,105,19,38,76,89,115,39,78,93,123,55,110,29,58,116,41,82,101,11,22,44,88,113,35,70,77,91,119,47,94,125,59,118,45,90,117,43,86,109,27,54,108,25,50,100,9,18,36,72,81,99,7,14,28,56,112,33,66,69,75,87,111,31,62,124,57,114,37,74,85,107,23,46,92,121,51,102,13,26,52,104,17,34,68,73,83,103,15,30,60,120,49,98,5,10,20,40,80,97,3,6,12,24,48,96};
// unsigned short fg[128]={0,1,2,122,3,116,123,74,4,68,117,41,124,100,75,110,5,104,69,24,118,20,42,94,125,65,101,62,76,35,111,85,6,79,105,46,70,90,25,29,119,38,21,59,43,56,95,51,126,114,66,98,102,18,63,33,77,88,36,54,112,16,86,14,7,8,80,9,106,81,47,10,71,107,91,82,26,48,30,11,120,72,39,108,22,92,60,83,44,27,57,49,96,31,52,12,127,121,115,73,67,40,99,109,103,23,19,93,64,61,34,84,78,45,89,28,37,58,55,50,113,97,17,32,87,53,15,13};

unsigned short S[256][256] = {0};

unsigned int cnt = 0;
PO p;
mterm base[1024] = {0};

vMP m2v(MP a)
{
    int i, j;
    vMP b = {0};

    for (j = 0; j < P; j++)
    {
        if (a.x[j].a > 0)
            b.x[a.x[j].n[0]][a.x[j].n[1]] ^= a.x[j].a;
    }
    return b;
}

MP v2m(vMP f)
{
    int i, j, count = 0;
    MP g = {0};

    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 100; j++)
        {
            if (f.x[i][j] > 0)
            {
                g.x[count].a = f.x[i][j];
                g.x[count].n[0] = i;
                g.x[count].n[1] = j;
                count++;
            }
        }
    }
    g.terms = count;

    return g;
}

vMP madd(vMP a, vMP b)
{
    int i, j, k;
    vMP c = {0};

    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 100; j++)
            c.x[i][j] = a.x[i][j] ^ b.x[i][j];
    }

    return c;
}

// 多項式を表示する(default)
void printpol(vMP a)
{
    int i, n;

    //  n = mdeg(a);

    for (i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if (a.x[i][j] > 0)
            {
                printf("%dx^%dy^%d", a.x[i][j], i, j);
                // if (i > 0 || j >0)
                printf("+");
            }
        }
    }
    printf("\n");

    return;
}

int mlt(int x, int y)
{

    if (x == 0 || y == 0)
        return 0;

    return ((x + y - 2) % (N - 1)) + 1;
}

int mltn(int n, int x)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return x;
    return mlt(x, mltn(n - 1, x));
}

int mltn2(int n, int x)
{
    int i, j;

    if (n == 0)
    {
        return 1;
    }
    if (x == 0)
    {
        return 0;
    }
    else
    {
        i = x;
        for (j = 0; j < n - 1; j++)
            i = mlt(i, x);

        return i;
    }
}

mterm mtermul2(mterm a, mterm b)
{
    mterm c = {0};

    c.n[0] = a.n[0] + b.n[0];
    c.n[1] = a.n[1] + b.n[1];
    c.a = gf[mlt(fg[a.a], fg[b.a])];

    return c;
}

vMP vadd(vMP a, vMP b)
{
    int i, j, k;
    vMP c = {0};

    // printf("deg=%d %d\n",deg(a),deg(b));

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N; k++)
                c.x[i][j] ^= a.x[i][j] ^ b.x[j][k];
        }
    }

    return c;
}

vMP vmul(vMP f, vMP g)
{
    int i, j, k, l;
    vMP c = {0};

    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 100; j++)
        {
            if (f.x[i][j] > 0)
            {
                for (k = 0; k < 100; k++)
                {
                    for (l = 0; l < 100; l++)
                    {
                        if (g.x[k][l] > 0)
                            c.x[i + k][j + l] ^= gf[mlt(fg[f.x[i][j]], fg[g.x[k][l]])];
                    }
                }
            }
        }
    }

    return c;
}

MP mmul(MP a, MP b)
{
    int i, j, k, d = 0;
    MP c = {0};
    mterm t = {0};

    for (i = 0; i < 32; i++)
    {
        for (j = 0; j < 32; j++)
        {
            if (a.x[i].a > 0 && b.x[j].a > 0)
                c.x[d++] = mtermul2(a.x[i], b.x[j]);
        }
    }
    c = v2m(m2v(c));

    return c;
}

// 有限体の元の逆数
unsigned short
oinv(unsigned short a)
{
    int i;

    if (a == 0)
        return 0;

    return N - fg[a] + 1;

    printf("no return \n");

    exit(1);
}

// aに何をかけたらbになるか
unsigned short
equ(unsigned short a, unsigned short b)
{
    int i;

    return gf[mlt(oinv(a), fg[b])];
}

vMP coeff(vMP f, unsigned short a)
{
    int i, j;
    vMP b = {0};

    for (i = 0; i < 32; i++)
    {
        for (j = 0; j < 32; j++)
            b.x[i][j] = gf[mlt(fg[a], fg[f.x[i][j]])];
    }

    return b;
}

int inv2(int a, int b)
{
    int i = 0;

    for (i = 0; i < N; i++)
    {
        if (b == gf[mlt(fg[a], i)])
            return i;
    }
}

void param(int n, int g)
{
    int i, j, h, ij, t, delta, ips;

    //  g=6;
    j = I - 2;
    //  ij=k+g-1;
    //  ij=1;
    //  exit(1);
    //    n-=4;
    printf("n=%d ", n);
    printf("k=%d\n", U);
    printf("d=%d\n", U - g + 1);
    printf("t=%d~%d\n", (U - g) / 2);

    delta = 1;
    ips = 0;
    while (delta * I < Q * Q * Q)
    {
        for (ips = 0; ips < I; ips++)
        {
            if (U + ((I * (I - 1)) / 2) == delta * I + ips)
                printf("ips=%d delta=%d\n", ips, delta);
        }
        delta++;
    }
}

void vec_diff(unsigned short a[N], unsigned short b[N])
{
    /* Calcurate the difference of two vectors. Be caution that b[N] changes. */
    for (int i = 0; i < N; i++)
    {
        b[i] ^= a[i];
    }
}

int gauss()
{
    unsigned short m[N][N] = {{7, 2, 5}, {2, 5, 2}, {5, 2, 7}}; // The matrix
    unsigned short b[N] = {5, 7, 0};
    unsigned short mm[N] = {0};

    printf("The coefficient matrix is : \n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", m[i][j]);
            if (j == N - 1)
            {
                printf("\n");
            }
        }
    }

    printf("\nUse Gauss method to solve equations : \n");
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            unsigned short coef = mlt(fg[m[j][i]], oinv(fg[m[i][i]]));
            unsigned short del[N];

            for (int k = 0; k < N; k++)
            {
                del[k] = gf[mlt(fg[m[i][k]], coef)];
            }
            // for(int ii=0;ii<N;ii++)
            // mm[ii]=m[j][ii];
            vec_diff(del, m[j]);
            b[j] ^= gf[mlt(fg[b[i]], coef)];
        }
    }

    for (int i = N - 1; i >= 0; i--)
    {
        unsigned short x = gf[oinv(fg[m[i][i]])];
        m[i][i] = gf[mlt(fg[m[i][i]], fg[x])];
        b[i] = gf[mlt(fg[b[i]], fg[x])];

        for (int j = 0; j < i; j++)
        {
            b[j] ^= gf[mlt(fg[b[i]], fg[m[j][i]])];
            m[j][i] = 0;
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", m[i][j]);
            if (j == N - 1)
            {
                printf("\n");
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        printf("%d ", b[i]);
    }

    return 0;
}

mterm term(MP f, unsigned int i)
{

    return f.x[i];
}

int terms(MP f)
{
    int i, j, k = 0, flg;

    for (i = 0; i < P; i++)
    {
        flg = 0;
        for (j = 0; j < V; j++)
        {
            if (f.x[i].n[3] > 0)
                flg = 1;
        }
        if (flg == 1)
            k++;
    }

    return k;
}

unsigned short
degterm(mterm z)
{
    int j, k;
    // mterm z;
    unsigned short c = 0;

    //   z=term(f,i);
    for (j = 0; j < V; j++)
    {
        if (z.n[j] > 0)
            c += z.n[j];
    }

    return c;
}

// リーディグタームを抽出(default)
mterm vMT(vMP f)
{
    int i;
    mterm t = {0};

    // k = deg (o2v (f));
    for (i = 0; i < 32; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            // printf("a=%d %d\n",f.t[i].a,f.t[i].n);
            if (f.x[i][j] > 0)
            {
                t.n[i] = i;
                t.n[j] = j;
                t.a = f.x[i][j];
            }
        }
    }

    return t;
}

MP mterml(MP f, mterm m)
{
    int i, j, k;

    for (i = 0; i < terms(f); i++)
    {
        for (j = 0; j < V; j++)
            f.x[i].n[j] += m.n[j];
        f.x[i].a = gf[mlt(fg[f.x[i].a], fg[m.a])];
    }

    return f;
}

// リーディグタームを抽出(default)
mterm vLT(vMP f)
{
    int i, j, k = 0, count = 0;
    mterm t = {0}, tmp[100] = {0};

    // k = deg (o2v (f));
    for (i = 0; i < 32; i++)
    {
        for (j = 0; j < 32; j++)
        {
            //
            if (f.x[i][j] > 0)
            {
                printf("avlt=%d %d %d\n", i, j, f.x[i][j]);
                if (k < i + j)
                {
                    t.n[0] = i;
                    t.n[1] = j;
                    k = i + j;
                    t.a = f.x[i][j];
                }
                if (k == i + j)
                {
                    if (i >= j)
                    {
                        t.n[0] = i;
                        t.n[1] = j;
                        k = i + j;
                        t.a = f.x[i][j];
                        // count++;
                    }
                    if (i < j && k == j)
                    {
                        t.n[0] = i;
                        t.n[1] = j;
                        t.a = f.x[i][j];
                        k = i + j;
                    }
                }
            }
        }
    }

    return t;
}

int vdeg(vMP f)
{
    int i, j, n;

    n = vLT(f).n[0] + vLT(f).n[1];

    return n;
}

mterm mLT(MP f)
{
    int i, j = 0, k, l;
    mterm m = {0}, mm;

    for (i = 0; i < terms(f); i++)
    {
        mm = term(f, i);
        k = degterm(mm);
        if (j < K)
        {
            m = f.x[i];
        }
        else if (j == k)
        {
            for (l = 0; l < V; l++)
                if (m.n[l] < f.x[i].n[l])
                {
                    m = f.x[i];
                    return m;
                }
        }
    }

    return m;
}

mterm mdivLT(MP f, mterm m)
{
    int i, j, k;
    mterm g = {0};
    mterm mm = {0}; // vLT(m2v(f));
    printpol(m2v(f));
    for (i = 0; i < P; i++)
    {
        mm = f.x[i];
        if (mm.a == 0)
            break;
        printf("in glt1 %dx^%dy^%d\n", mm.a, mm.n[0], mm.n[1]);
        printf("in glt! %dx^%dy^%d\n", m.a, m.n[0], m.n[1]);
        if ((mm.n[0] >= m.n[0]) && (mm.n[1] >= m.n[1]))
        {
            g.n[0] = mm.n[0] - m.n[0];
            g.n[1] = mm.n[1] - m.n[1];
            g.a = equ(m.a, mm.a);
            break;
        }
    }
    /*
      if(mm.n[0]>=m.n[0]){
      g.n[0]=mm.n[0]-m.n[0];
      }else{
        g.n[0]=mm.n[0];
      }
      if(mm.n[1]>=m.n[1]){
      g.n[1]=mm.n[1]-m.n[1];
      }else{
        g.n[1]=mm.n[1];
      }
      g.a=gf[mlt(fg[mm.a],oinv(m.a))];
      */
    printf("in glt3 %dx^%dy^%d\n", g.a, g.n[0], g.n[1]);
    // exit(1);
    return g;
}

// 多項式の剰余を取る
MP mmod(MP f, MP g)
{
    MP h = {0};
    mterm b = {0}, c = {0};

    // printf("vmod-bl=%d k=%d\n",deg(f),deg(g));
    if (vdeg(m2v(f)) < vdeg(m2v(g)))
    {
        //    exit(1);
        return f;
    }

    b = vLT(m2v(g));

    printf("%dx^%dy^%d", b.a, b.n[0], b.n[1]);
    printf(" ==b\n");
    // exit(1);

    while (1)
    {

        c = mdivLT(f, b);
        if (c.a == 0)
            break;

        // h = fake(f, b);
        printf("%dx^%dy^%d", c.a, c.n[0], c.n[1]);
        printf(" ==c\n");

        h = mterml(g, c);
        f = v2m(madd(m2v(f), m2v(h)));
        if (vdeg(m2v(f)) < vdeg(m2v(g)))
        {
            break;
        }

        if (vdeg(m2v(g)) > vdeg(m2v(f)))
            break;

        if (vLT(m2v(f)).a == 0)
            break;
    }
    // if (c.a > 0)
    // f.x[0].a = c.a;

    printf("vmod-baka== %d %d\n", vdeg(m2v(f)), f.x[0].a);
    return f;
}

MP mdel(MP f, mterm m)
{
    int i, j, k;

    m = mLT(f);
    for (i = 0; i < terms(f); i++)
    {
        if (m.n[0] == f.x[i].n[0] && m.n[1] == f.x[i].n[1] && m.n[2] == f.x[i].n[1])
        {
            for (j = 0; j < V; j++)
                f.x[i].n[j] = 0;
            f.x[i].a ^= m.a;
        }
    }

    return f;
}

MP lex(MP f)
{
    MP g = {0};
    int i, j, k;
    mterm m = {0};

    for (i = 0; i < terms(f); i++)
    {
        m = mLT(f);
        f = mdel(f, m);
        g.x[i] = m;
    }

    return g;
}

int rank(int mat[][100], int n)
{
    int ltmp[100], tmp, a_tmp[100], b_tmp[100];
    int i, j, k;
    int count;
    int all_zero;

    for (i = 0; i < n; i++)
    {
        all_zero = 0;
        if (mat[i][i] == 0)
        {
            for (j = 0; j < n; j++)
            {
                if (mat[j][i] != 0)
                {
                    for (k = 0; k < n; k++)
                    {
                        tmp = mat[i][k];
                        mat[i][k] = mat[j][k];
                        mat[j][k] = tmp;
                    }
                }
                else if (j == n - 1)
                    all_zero = 1;
            }
        }

        if (!all_zero)
        {
            for (j = i + 1; j < n; j++)
            {
                for (k = 0; k < n; k++)
                {
                    a_tmp[k] = mlt(mat[i][k], mat[j][i]);
                    b_tmp[k] = mlt(mat[j][k], mat[i][i]);
                }
                for (k = 0; k < n; k++)
                    mat[j][k] = fg[gf[b_tmp[k]] ^ gf[a_tmp[k]]];
            }
        }
    }

    count = 0;
    for (i = 0; i < n; i++)
    {
        if (mat[i][n] == 0)
            count++;
    }

    return (n - count);
}

int mdeg(MP f)
{
    int i, tmp = 0, j, k;

    for (i = 0; i < terms(f); i++)
    {
        k = 0;
        for (j = 0; j < V; j++)
        {
            tmp += f.x[i].n[j];
            if (k < tmp)
                k = tmp;
        }
    }

    return k;
}

MP mtermul(MP f, mterm o)
{
    int i, j, k;

    for (i = 0; i < terms(f); i++)
    {
        for (j = 0; j < V; j++)
            f.x[i].n[j] += o.n[j];
        f.x[i].a = gf[mlt(fg[f.x[i].a], fg[o.a])];
    }

    return f;
}

unsigned short
otrace(mterm a, int i, int j, int k)
{
    unsigned short u;

    // if (i == 0 && j == 0)
    //   return 0;

    u =
        mlt(mlt(mltn(a.n[0], i), mltn(a.n[1], j)),
            mlt(mltn(a.n[2], k), fg[a.a]));

    if (a.n[0] == 0 && a.n[1] == 0 && a.n[2] == 0)
        return a.a;

    return gf[u];
}

unsigned short strace(unsigned short u, unsigned short v, int i, int j)
{
    int n = 0;

    n = gf[mlt(mltn(u, i), mltn(v, j))];

    return n;
}
unsigned short vtrace(vMP cv)
{
    unsigned int i, j, k, l, n = 0, m = 0, count = 0;

    for (k = 0; k < N; k++)
    {
        for (l = 0; l < N; l++)
        {
            n = 0;
            for (i = 0; i < 10; i++)
            {
                for (j = 0; j < 10; j++)
                {
                    if (cv.x[i][j] > 0)
                    {
                        n ^= strace(i, j, k, l);
                    }
                }
            }
            if (n == 0)
            {
                printf("%d %d %d\n", k, l, count);
                count++;
            }
        }
    }
}

unsigned int
mtrace(MP f)
{
    int i, j, k, ii;
    unsigned int u, n, count = 0, f1, f2, f3, f4;
    mterm o[4];

    u = 0;
    n = terms(f);
    printf("%d\n", n);
    // exit(1);

    /*
         i=0;j=1;k=0;
         for(ii=0;ii<n;ii++){
         u^=otrace(f.x[ii],0,1,0);
         printf("%d\n",u);
         }
    //     u^=1;
         if(u==0){
            printf("%d %d %d\n",0,1,0);
         p.z[0][count]=0;
         p.z[1][count]=1;
         p.z[2][count]=0;
         count++;
         }
       //exit(1);

         k=0;i=1;u=0;
         for(j=0;j<N;j++){
         for(ii=0;ii<n;ii++)
         u^=otrace(f.x[ii],1,j,0);
         //u^=1;
         if(u==0){
         printf("%d %d %d\n",1,j,0);
         p.z[0][count]=1;
         p.z[1][count]=j;
         p.z[2][count]=0;
         count++;
         }
         u=0;
         }
       //exit(1);
    */

    k = 1;
    u = 0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (ii = 0; ii < n; ii++)
                u ^= otrace(f.x[ii], i, j, 1);
            // u^=1;
            if (u == 0)
            {
                printf("%d %d %d\n", i, j, k);

                p.z[0][count] = i;
                p.z[1][count] = j;
                p.z[2][count] = 1;

                count++;
            }
            u = 0;
        }
    }

    return count;
}

mterm obase(int a, int b)
{
    int i, j, k;
    mterm c = {0};

    c.n[0] = a;
    c.n[1] = b;

    return c;
}

int bases(int a)
{
    int i = 0, j = 0, count = 0;

    for (i = 0; i < N - 1; i++)
    {
        for (j = 0; j < N - 1; j++)
        {
            //      if(i+j<a){
            base[count].n[0] = i;
            base[count++].n[1] = j;
            //    }
            if (count > N * N)
            {
                printf("baka\n");
                break;
            }
        }
    }

    //  printf("count=%d\n",count);
    //  exit(1);

    return count;
}

int mkbase(mterm *aa)
{
    int i, j, k, l, count;
    int d[256][2] = {0};
    int bb[256][2] = {0};

    count = 1;

    for (i = 0; i < 20; i++)
    {
        k = 0;
        j = i;
        while ((d[i][0] + d[i][1]) < i && i < 5)
        {
            d[k][1] = k;
            d[k][0] = j - k;
            printf("k1=%d %d\n", j - k, k);
            k++;
        }
        for (l = 0; l < k; l++)
        {
            bb[count][0] = d[l][0];
            bb[count++][1] = d[l][1];
            //    printf("a%d %d\n",d[l][0],d[l][1]);
        }

        if (i > 4)
        {
            l = i - 4;
            j = 4;
            while (d[i][0] + d[i][1] < i && l < N - 1)
            {
                d[k][0] = j;
                d[k][1] = l;
                k++;
                j--;
                l++;
                printf("k2=%d", k);
                if (j < 0)
                    break;
            }
            for (l = 0; l < k; l++)
            {
                bb[count][0] = d[l][0];
                bb[count++][1] = d[l][1];
                //    printf("a%d %d\n",d[l][0],d[l][1]);
            }
        }
    }

    for (i = 0; i < 15 * 15; i++)
        printf("d=%d %d\n", bb[i][0], bb[i][1]);
    // exit(1);

    for (i = 0; i < 15 * 15; i++)
    {
        printf("%d %d\n", bb[i][0], bb[i][1]);
        // for(j=0;j<N-1;j++){
        //   if(bb[i][0]+bb[i][1]<10){
        aa[i] = obase(bb[i][0], bb[i][1]);
        aa[i].a = 1;
        //      }
        // }
    }
    // exit(1);

    return count;
}

int test(unsigned short x, unsigned short y)
{
    int count = 0, f1, f2, f3;

    f1 = gf[mlt(x, x)];
    f2 = gf[mlt(3, x)];
    f3 = gf[mlt(6, y)];

    if ((f1 ^ f2 ^ f3) == 0)
    {
        printf("%d %d\n", gf[x], gf[y]);
        count++;
    }

    return count;
}

MP define_curve(void)
{
    int i, j, k;
    MP s = {0};

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

    // hermite
    s.x[0].n[0] = Q + 1;
    s.x[1].n[1] = Q + 1;
    s.x[2].n[2] = Q + 1;

    return s;
}

int more(int a, int b)
{
    int i, j, k;

    printf("in more\n");
    if (b >= I - 1)
    {
        return S[a][b] ^ S[a][b - I + 2];
    }
    else
    {
        printf("%d %d\n", S[a][b + I - 1], S[a][b + 1]);
        return S[a][b + I - 1] ^ S[a][b + 1];
    }
}

MP set_curve(unsigned short a[9][4], int x)
{
    MP s = {0};
    int i, j;

    for (i = 0; i < x; i++)
    {
        for (j = 0; j < V; j++)
        {
            s.x[i].n[j] = a[i][j];
        }
        s.x[i].a = a[i][3];
    }

    return s;
}

int bin(int x, int y, int z)
{
    int i, j, f1, f2, f3, f4, f5, add(), mlt();
    int a, b, p = 0;
    int fnc, xx, count = 0;

    f1 = gf[mlt(mlt(x, x), mlt(y, x))];
    f2 = gf[mlt(mlt(y, y), mlt(y, z))];
    f3 = gf[mlt(mlt(y, y), mlt(z, z))];
    f4 = gf[mlt(mlt(z, z), mlt(z, z))];

    /*

     * ( baby step gaint step )
     * void jac(int x,int y)

     */
    /*
  f1=gf[mlt(mlt(y,y),1)];
  f2=gf[mlt(mlt(x,y),1)];
  f3=gf[mlt(mlt(x,x),x)];
  f4=gf[mlt(mlt(1,1),1)];
  f5=gf[mlt(mlt(x,x),1)];
    */

    if ((f1 ^ f2 ^ f3 ^ f4) == 0)
    {
        count++;
        printf("%d %d %d\n", x, y, z);
    }
    //  printf("%d\n",count);
    /*
    for(a=0;a<N;a++){
      for(b=0;b<N;b++){
  fnc=add(mlt(a,x),b);
    if(y==fnc){
      for(xx=0;xx<N;xx++){
        fnc=add(mlt(a,xx),b);
    */
    //    if(((add(mlt(fnc,fnc),mlt(xx,fnc)))==(add(mltn(3,xx),1))) ){
    // printf("a= %d b= %d : (%d,%d)\n",a,b,xx,fnc); /* intersection */

    /*
    p=x;
    for(y=0;y<N;y++){
    if(add(add(mlt(y,y),mlt(p,y)),add(mltn(3,x),1))==0)
    printf("%d,%d\n",p,y);  jac(x,y)?
    }
    */
    //	    } /* if */
    //	  } /* for */
    //	  } /* if */

    //}
    // printf("\n");
    //    }

    /*
       lx[k]=x;
       ly[k]=y;
       lz[k]=z;
    */
    //  k++;
    //}

    return count;
}

// 多項式の商を取る
MP mdiv(MP f, MP g)
{

    int i;
    MP h = {0}, tt = {0};
    mterm b = {0}, c = {0};

    if (vLT(m2v(f)).n == 0 && vLT(m2v(g)).a == 0)
    {
        printf("baka^\n");
        // return f;
        exit(1);
    }
    if (vLT(m2v(g)).a == 0)
    {
        printf("0 baka\n");
        exit(1);
    }
    /*
    if (vLT(m2v(g)).n == 0 && vLT(m2v(g)).a > 1)
      return coeff(f, LT(g).a);
    */
    b = vLT(m2v(g));
    if (b.a == 1 && b.n[0] + b.n[1] == 0)
        return f;
    if (b.a == 0 && b.n[0] + b.n[1] == 0)
    {
        printf("baka in odiv\n");
        exit(1);
    }
    if (vdeg(m2v(f)) < vdeg(m2v(g)))
    {
        return f;
        //  a=LT(f);
    }

    i = 0;
    while (1)
    {
        c = mdivLT(f, b);
        // assert(c.n < DEG);
        tt.x[i] = c;
        i++;

        h = mterml(g, c);

        f = v2m(madd(m2v(f), m2v(h)));
        if (vdeg(m2v(f)) == vdeg(m2v(g)) && vLT(m2v(f)).a == vLT(m2v(g)).a)
        {
            printf("blake2\n");
            c.a = 1;
            // break;
        }

        if (c.a == 0)
            break;
    }

    return tt;
}

vMP arp(unsigned short cv[][4], int j)
{
    vMP c = {0};
    int i;

    for (i = 0; i < j; i++)
        c.x[cv[i][0]][cv[i][1]] = cv[i][3];

    return c;
}
typedef struct
{
    vMP a;
    vMP b;
} Pa;

Pa semi(Pa f, Pa g)
{
    Pa t;

    t.a = vmul(f.a, g.a);
    t.b = vadd(vmul(f.a, g.b), g.a);

    return t;
}

void printm(MTX a){
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++)
        printf("%d,",a.x[j][i]);
        printf("\n");
    }
}
void printwd(MTX c)
{
    for (int i = 0; i < 3; i++)
    {
        //printf("\n");
        for (int j = 0; j < 3; j++){
            if(c.x[i][j]>0)
            printf("%dx^%dy^%d+", c.x[i][j], i, j);
        }
    }
    printf("\n");
}

MTX mkcode()
{
    MTX c;
    int i,j;

    for (i = 0; i < 3; i++)
    {
        //printf("debug1\n");
        for (j = 0; j < 3; j++){
            //printf("debugi1 %d\n",j);
            c.x[i][j] = rand() % N;
        }
    }
    return c;
}

int main(void)
{
    int i, j, k = 0, a, b, c, count = 0, x, y, z, g, n;
    unsigned int u = 0, v = 0, delta = 7, ips = 1;
    MP s = {0};
    unsigned char **HH;
    unsigned short tmp[256][1] = {0};

    // gf256 g=1 elliptic
    unsigned short el[4][4] =
        {{0, 2, 1, 1}, {1, 1, 1, 1}, {3, 0, 0, 1}, {0, 0, 3, 1}};
    // gf256 g=1 elloptic
    unsigned short el2[5][4] =
        {{0, 2, 1, 1}, {1, 1, 1, 1}, {3, 0, 0, 1}, {0, 0, 3, 1}, {2, 0, 1, 1}};
    // gf8 g=6 Generalized Hermitian
    unsigned short sc[4][4] =
        {{3, 2, 0, 1}, {2, 4, 0, 1}, {0, 1, 0, 1}, {4, 0, 0, 1}};
    // gf64 GH
    unsigned short gr[4][4] = {{16, 15, 0, 1}, {1, 12, 0, 1}, {4, 0, 0, 1}, {0, 16, 0, 1}};
    // gf8 g=3 klein
    unsigned short kl[3][4] = {{3, 1, 0, 1}, {0, 3, 0, 1}, {1, 0, 0, 1}};
    unsigned short ha[4][4] = {{Q * Q - 1, Q * Q, 0, 1}, {Q * Q - Q, 1, 0, 1}, {Q * Q, 0, 0, 1}, {0, Q, 0, 1}};
    // GF(64) #=113,g=3
    unsigned short g3[4][4] = {{3, 1, 0, 1}, {0, 3, 0, 1}, {0, 2, 0, 1}, {0, 0, 0, 1}};
    // g=6 GF(8)
    unsigned short g6[4][4] = {{4, 3, 0, 1}, {0, 4, 0, 1}, {1, 2, 0, 1}, {2, 0, 0, 1}};
    // gfQ*Q Hermitian
    unsigned short he[3][4] = {{Q + 1, 0, 0, 1}, {0, Q, 0, 1}, {0, 1, 0, 1}};
    // gf16 g=21 #N=121 Generalized Hermitian
    unsigned short gu[5][4] =
        {{7, 4, 0, 1}, {6, 8, 0, 1}, {4, 1, 0, 1}, {0, 2, 0, 1}, {8, 0, 0, 1}};
    // gf32 g=75 #N=497 Generalized Hermitian
    unsigned short ge[6][4] =
        {{15, 8, 0, 1}, {14, 16, 0, 1}, {12, 1, 0, 1}, {8, 2, 0, 1}, {0, 4, 0, 1}, {16, 0, 0, 1}};
    unsigned short gh[4][4] = {{16, 15, 0, 1}, {1, 12, 0, 1}, {4, 0, 0, 1}, {0, 16, 0, 1}};
    // gf64 g=212 #N=2017 Generalized Hermitian
    unsigned short gg[7][4] =
        {{31, 8, 0, 1}, {30, 16, 0, 1}, {28, 32, 0, 1}, {24, 1, 0, 1}, {16, 2, 0, 1}, {0, 4, 0, 1}, {32, 0, 0, 1}};
    // gf256 g=2413 Generalized Hermitian
    unsigned short gd[9][4] =
        {{127, 8, 0, 1}, {126, 16, 0, 1}, {124, 32, 0, 1}, {120, 64, 0, 1}, {112, 128, 0, 1}, {96, 1, 0, 1}, {64, 2, 0, 1}, {0, 4, 0, 1}, {128, 0, 0, 1}};
    // gf128 g=315 Generalized Hermitian
    unsigned short cc[8][4] =
        {{63, 8, 0, 1}, {62, 16, 0, 1}, {60, 32, 0, 1}, {56, 64, 0, 1}, {48, 1, 0, 1}, {32, 2, 0, 1}, {0, 4, 0, 1}, {64, 0, 0, 1}};
    // gf256 y^(Q+1)=X^8+x^4+x^2+x kummer
    unsigned short ku[5][4] =
        {{0, 17, 0, 1}, {8, 0, 0, 1}, {4, 0, 0, 1}, {2, 0, 0, 1}, {1, 0, 0, 1}};
    // gf16 kummer
    unsigned short ku3[5][4] =
        {{0, 5, 0, 1}, {12, 0, 0, 1}, {9, 0, 0, 1}, {6, 0, 0, 1}, {3, 0, 0, 1}};
    // gf64 kummer g=56
    unsigned short ku4[5][4] =
        {{0, 9, 0, 1}, {40, 0, 0, 1}, {33, 0, 0, 1}, {12, 0, 0, 1}, {5, 0, 0, 1}};
    unsigned short lo[3][4] = {{2, 0, 0, 1}, {1, 0, 0, 3}, {0, 1, 0, 6}};
    unsigned short lk[6][4] =
        {{0, 2, 0, 1}, {0, 1, 0, 3}, {0, 0, 1, 6}, {3, 1, 0, 1}, {0, 3, 1, 1}, {1, 0, 3, 1}};
    // gf32 g=26 #N=157
    unsigned short ts[3][4] = {{2, 2, 5, 1}, {7, 0, 2, 1}, {0, 9, 0, 1}};
    // gf128 g=78 #N=891
    unsigned short tt[3][4] = {{3, 1, 0, 1}, {13, 0, 0, 1}, {0, 14, 0, 1}};
    // gf512 Generalized Hermitian
    unsigned short gt[10][4] =
        {{255, 16, 0, 1}, {254, 32, 0, 1}, {252, 64, 0, 1}, {248, 128, 0, 1}, {240, 256, 0, 1}, {224, 1, 0, 1}, {192, 2, 0, 1}, {128, 4, 0, 1}, {0, 8, 0, 1}, {256, 0, 0, 1}};
    // over gf128 suzuki #N=16384
    unsigned short su[4][4] =
        {{0, 128, 0, 1}, {0, 1, 0, 1}, {136, 0, 0, 1}, {9, 0, 0, 1}};
    // gf32 suzuki #N=1024
    unsigned short s2[4][4] =
        {{0, 32, 0, 1}, {0, 1, 0, 1}, {36, 0, 0, 1}, {5, 0, 0, 1}};
    // gf8 suzuki
    unsigned short s3[4][4] =
        {{0, 8, 0, 1}, {0, 1, 0, 1}, {10, 0, 0, 1}, {3, 0, 0, 1}};
    // y9 = x4 + x2 + x gf64 kummer
    unsigned short ku2[4][4] =
        {{0, 9, 0, 1}, {4, 0, 0, 1}, {2, 0, 0, 1}, {1, 0, 0, 1}};
    // y^9=x^2+x gf64 g=4
    unsigned short ku5[3][4] = {{0, 9, 0, 1}, {2, 0, 0, 1}, {1, 0, 0, 1}};
    unsigned short gl[6][4] = {{8, 16, 0, 1}, {12, 8, 0, 1}, {14, 4, 0, 1}, {15, 2, 0, 1}, {16, 0, 0, 1}, {0, 1, 0, 1}};

    unsigned int bb[256][2] = {0}; //{{0,0},{1,0},{0,1},{2,0},{1,1},{0,2},{3,0},{2,1},{1,2},{0,3},{4,0},{3,1},{2,2},{1,3},{0,4},{5,0},{4,1},{3,2},{2,3},{1,4},{6,0},{5,1},{4,2},{3,3},{2,4},{7,0},{6,1},{5,2},{4,3},{3,4}};
    mterm aa[1256] = {0};
    mterm oo = {0};
    unsigned int d[256][2] = {0};
    unsigned char e[64] =
        {0, 0, 0, 0, 0, 2, 0, 0, 0, 4, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0};

    // unsigned char ee[64]={0,1,2,3,4,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    //  unsigned char ee[150000]={0,0,0,0,12,0,0,0,0,11,0,0,2,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0};

    //  unsigned short ee[64]={0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,4,0,0,0,0,0,0,0,0,0,0};
    vMP f = {0}, ga = {0}, gi = {0};
    MP h = {0}, go;

    MTX xx;
    for (i = 0; i < 10; i++)
    {
        printf("%d\n",i);
        xx = mkcode();
        printwd(xx);
        printm(xx);
    }
    exit(1);

    s = set_curve(he, 3);
    for (i = 0; i < 10000; i++)
        u = mtrace(s);
    printf("count=%d\n", u);


    // f=arp(he,3);
    // vtrace(f);
    // exit(1);

    printpol(arp(kl, 3));
    // exit(1);
    unsigned short ab[][4] = {{1, 2, 0, 4}, {0, 0, 0, 1}};
    gi = arp(ab, 2);
    printf("%d\n", vLT(gi).a);
    // exit(1);
    unsigned short ff[][4] = {{2, 1, 0, 1}, {1, 2, 0, 1}, {0, 2, 0, 1}};
    f = arp(ff, 3);
    unsigned short aga[][4] = {{1, 1, 0, 2}, {0, 0, 0, 1}};
    ga = arp(aga, 2);
    printpol(gi);
    printpol(ga);
    h = mmod(v2m(ga), v2m(gi));
    printpol(m2v(h));
    exit(1);

    h = mmod(h, v2m(ga));
    printpol(m2v(h));
    // exit(1);
    h = mmod(v2m(f), v2m(gi));
    printpol(m2v(h));
    // exit(1);
    h = mmod(h, v2m(ga));
    printpol(m2v(h));
    exit(1);

    printpol((gi));
    printf("\n");
    h = v2m(gi);
    printpol(m2v(h));
    for (i = 0; i < 100; i++)
    {
        if (h.x[i].a > 0)
            printf("i==%d\n", i);
    }
    // exit(1);
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 100; j++)
        {
            if (f.x[i][j] > 0)
                printf("%d %d %d\n", i, j, f.x[i][j]);
        }
    }
    // exit(1);

    return 0;
}
