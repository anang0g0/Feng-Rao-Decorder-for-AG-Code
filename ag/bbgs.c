#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "global-p.h"
#include "struct-p.h"
#include "chash-p.c"
// #include "oplib.c"
// 5-error-correction

// #define O 49 // 1331,2197,4913,6859,3125,2187,19683
// #define EXP 6
// #define Pr 7

unsigned short pp[16][4] = {{0, 0, 9, 2}, {0, 0, 11, 2}, {0, 0, 16, 3}, {0, 0, 15, 2}, {0, 0, 1, 2}, {0, 1, 0, 2}, {0, 0, 1, 1}, {0, 0, 1, 2}, {1, 1, 2, 2}, {0, 0, 1, 2}, {0, 0, 21, 5}, {0, 0, 30, 3}, {0, 0, 1, 4}, {0, 0, 2, 2}, {0, 0, 1, 2}, {0, 1, 0, 3}};
unsigned short HH[1024][1024] = {0};

typedef struct
{

    unsigned short n[V];
    unsigned short a;

} mterm;

typedef struct
{

    mterm x[2048];

} MP;

typedef struct
{

    unsigned char z[V][150000];

} PO;

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

// unsigned char gf[64] = {0, 1, 2, 4, 8, 16, 32, 33, 35, 39, 47, 63, 31, 62, 29, 58, 21, 42, 53, 11, 22, 44, 57, 19, 38, 45, 59, 23, 46, 61, 27, 54, 13, 26, 52, 9, 18, 36, 41, 51, 7, 14, 28, 56, 17, 34, 37, 43, 55, 15, 30, 60, 25, 50, 5, 10, 20, 40, 49, 3, 6, 12, 24, 48};
// unsigned char fg[64] = {0, 1, 2, 59, 3, 54, 60, 40, 4, 35, 55, 19, 61, 32, 41, 49, 5, 44, 36, 23, 56, 16, 20, 27, 62, 52, 33, 30, 42, 14, 50, 12, 6, 7, 45, 8, 37, 46, 24, 9, 57, 38, 17, 47, 21, 25, 28, 10, 63, 58, 53, 39, 34, 18, 31, 48, 43, 22, 15, 26, 51, 29, 13, 11};

// unsigned short gf[128]={0,1,2,4,8,16,32,64,65,67,71,79,95,127,63,126,61,122,53,106,21,42,84,105,19,38,76,89,115,39,78,93,123,55,110,29,58,116,41,82,101,11,22,44,88,113,35,70,77,91,119,47,94,125,59,118,45,90,117,43,86,109,27,54,108,25,50,100,9,18,36,72,81,99,7,14,28,56,112,33,66,69,75,87,111,31,62,124,57,114,37,74,85,107,23,46,92,121,51,102,13,26,52,104,17,34,68,73,83,103,15,30,60,120,49,98,5,10,20,40,80,97,3,6,12,24,48,96};
// unsigned short fg[128]={0,1,2,122,3,116,123,74,4,68,117,41,124,100,75,110,5,104,69,24,118,20,42,94,125,65,101,62,76,35,111,85,6,79,105,46,70,90,25,29,119,38,21,59,43,56,95,51,126,114,66,98,102,18,63,33,77,88,36,54,112,16,86,14,7,8,80,9,106,81,47,10,71,107,91,82,26,48,30,11,120,72,39,108,22,92,60,83,44,27,57,49,96,31,52,12,127,121,115,73,67,40,99,109,103,23,19,93,64,61,34,84,78,45,89,28,37,58,55,50,113,97,17,32,87,53,15,13};

unsigned short S[256][256] = {0};

unsigned int cnt = 0;
PO p;
mterm base[1024] = {0};

/*

*/

unsigned short
oinv(unsigned short a)
{
    int i;

    return N - fg[a] + 1;
    /*
      for (i = 0; i < N; i++)
        {
          if (gf[mlt (fg[a], i)] == 1)
        return (unsigned short) i;
        }
    */
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

    for (i = 0; i < 1024; i++)
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

MP mdivLT(MP f, mterm m)
{
    int i, j, k;
    MP g;
    mterm mm;

    g = f;

    for (i = 0; i < terms(f); i++)
    {
        m = term(f, i);
        if (degterm(mm) >= degterm(m))
        {
            for (j = 0; j < V; j++)
            {
                if (f.x[i].n[j] >= m.n[j])
                {
                    f.x[i].n[j] -= m.n[j];
                }
                else
                {
                    return g;
                }
            }
        }
        else
        {
            return f;
        }
    }
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

// OP型からベクトル型への変換
vec o2v(OP f)
{
    vec a = {0};
    int i;

    for (i = 0; i < K * E; i++)
    {
        if (f.t[i].a > 0 && f.t[i].n < K * E)
            a.x[f.t[i].n] = f.t[i].a;
    }

    return a;
}

// ベクトル型からOP型への変換
OP v2o(vec a)
{
    int i, j = 0;
    OP f = {0};

    // #pragma omp parallel for
    for (i = 0; i < K * E; i++)
    {
        if (a.x[i] > 0)
        {
            f.t[j].n = i;
            f.t[j++].a = a.x[i];
        }
    }

    return f;
}

void printm(MP f)
{
    int n = mdeg(f);
    int u = terms(f);

    for (int i = 0; i < u; i++)
    {
        printf("x^%d*y^%d+", f.x[i].n[0], f.x[i].n[1]);
    }
    printf("\n");
}

// 多項式を項ずつ掛ける
vec oterml(vec f, oterm t)
{
    vec h = {0};

    printpol(f);
    printf(" ==f\n");
    printf("t.a=%d\n", t.a);
    printf("t.n=%d\n", t.n);

    int k = deg(f) + 1;
    printf("k=%d\n", k);

    for (int i = 0; i < k; i++)
    {
        if (f.x[i] > 0)
        {
            h.x[i + t.n] = (f.x[i] * t.a) % Pr;
            printf("t+n=%d\n", i + t.n);
        }
    }

    return h;
}

// 多項式の足し算
vec vadd(vec a, vec b)
{
    vec c = {0};

    for (int i = 0; i < DEG; i++)
    {
        c.x[i] = (a.x[i] + b.x[i]) % Pr;
    }

    return c;
}

// 多項式の掛け算
vec vmul(vec f, vec g)
{
    int k, l, m;
    oterm t = {0};
    vec h = {0}, e = {0};

    l = deg(f);
    m = deg(g);

    for (int i = 0; i < 2; i++)
        printf("%d\n", g.x[i]);

    if (l >= m)
    {
        k = l;
    }
    else
    {
        k = m;
    }
    printpol(f);
    printf(" =f\n");
    printpol(g);
    printf(" =g\n");

    for (int i = 0; i < k + 1; i++)
    {
        t.a = g.x[i];
        t.n = i;

        if (t.a > 0 && t.a < O)
        {
            printf("t[%d]=%d,%d\n", i, t.a, t.n);
            e = oterml(f, t);
            printpol(e);
            printf(" =e\n");
            printpol(h);
            printf(" =h\n");
            h = vadd(h, e);
        }
    }
    printpol(h);
    printf(" =h2\n");

    return h;
}

vec confer(vec r, int a)
{
    int n;
    vec g = {0};

    n = deg(r);
    for (int i = 0; i < n + 1; i++)
        g.x[i] = (r.x[i] * a) % Pr;

    return g;
}

// 20200816:正規化したいところだがうまく行かない
// 多項式の足し算
OP oadd(OP f, OP g)
{
    vec a = {0}, b = {0}, c = {0};
    int i, j, k, l = 0;
    OP h = {0}, f2 = {0}, g2 = {0};

    // for(i=0;i<257;i++)
    //  printf("%d %d %d %d %d\n",i,f.t[i].a,f.t[i].n,g.t[i].a,g.t[i].n);

    //  exit(1);
    // printpol(f);
    // printf("\n");
    // f = conv(f);
    // exit(1);
    // g = conv(g);

    a = o2v(f);
    // exit(1);
    b = o2v(g);

    j = deg(o2v(f));
    l = deg(o2v(g));
    // printpol(o2v(f));
    // printf(" =f\n");
    // printpol(o2v(g));
    // printf(" =g\n");
    if (j >= l)
    {
        k = j + 1;
    }
    else
    {

        k = l + 1;
    }
    // for(i=0;i<k;i++)
    // printf("%d %d\n",i,b.x[i]);
    //   exit(1);

    for (i = 0; i < k; i++)
    {
        // if(f.t[i].a>0 || g.t[i].a>0)
        // h.t[i].a=f.t[i].a^g.t[i].a;
        c.x[i] = (a.x[i] + b.x[i]) % Pr;
        // if(a.x[i]>0 || b.x[i]>0)
        // printf("i=%d %d\n",a.x[i],b.x[i]);
    }
    //
    h = v2o(c);
    // printpol(o2v(h));
    // printf(" ==cclemon\n");

    return h;
}

unsigned short xtrace(vec g, unsigned short x)
{
    int d, z = 0;
    unsigned short u = 0;

    d = deg(g) + 1;

    for (int i = 0; i < d; i++)
    {
        u = 1;
        if (g.x[i] > 0)
        {
            for (int j = 0; j < i; j++)
                u = (u * x) % O;
            u = u * g.x[i] % O;
            z += u % O;
        }
    }

    return z % O;
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

vec dick[O] = {0};
unsigned short val[N] = {0}; //, a = {0}, cc = {0};
unsigned short plus(unsigned short a, unsigned short b)
{
    unsigned short u;
    if (a == 0 && b > 0)
        return b;
    if (b == 0 && a > 0)
        return a;
    if (a == 0 && b == 0)
        return 0;
    u = xtrace(vadd(dick[fg[a]], dick[fg[b]]), Pr);

    return u;
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

    k = 1;
    u = 0;
    for (i = 0; i < O; i++)
    {
        for (j = 0; j < O; j++)
        {
            u = 0;
            for (ii = 0; ii < n; ii++)
                u = plus(u, otrace(f.x[ii], i, j, 1));
            // u^=1;
            if (u % O == 0)
            {
                printf("%d %d %d\n", i, j, k);

                p.z[0][count] = i;
                p.z[1][count] = j;
                p.z[2][count] = 1;

                count++;
            }
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

int dbase(int a, int b, mterm *aa)
{
    int i, j, k, l, count = 0;
    int d[256][2] = {0};
    int bb[256][2] = {0};
    for (i = 0; i < b; i++)
    {
        for (j = 0; j < a; j++)
        {
            if (i + j < 11)
            {
                d[count][1] = i;
                d[count][0] = j;
                count++;
            }
        }
    }
    count = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 9; j++)
        {
            // printf("(%d,%d)\n",d[count][0],d[count][1]);
            aa[count] = obase(d[count][0], d[count][1]);
            aa[count].a = 1;
            count++;
        }
    }
    // exit(1);
    return count;
}

int mkbase(mterm *aa)
{
    int i, j, k, l, count;
    int d[256][2] = {0};
    int bb[256][2] = {0};

    count = 1;

    for (i = 0; i < 11; i++)
    {
        k = 0;
        j = i;
        while ((d[i][0] + d[i][1]) < i && i < 3)
        {
            d[k][0] = k;
            d[k][1] = j - k;
            printf("k1=%d %d\n", j - k, k);
            k++;
        }
        for (l = 0; l < k; l++)
        {
            bb[count][1] = d[l][1];
            bb[count++][0] = d[l][0];
            //    printf("a%d %d\n",d[l][0],d[l][1]);
        }

        if (i > 2)
        {
            l = i - 2;
            j = 2;
            while (d[i][0] + d[i][1] < i && l < 9)
            {
                d[k][1] = j;
                d[k][0] = l;
                k++;
                j--;
                l++;
                printf("k2=%d", k);
                if (j < 0)
                    break;
            }
            for (l = 0; l < k; l++)
            {
                bb[count][1] = d[l][1];
                bb[count++][0] = d[l][0];
                //    printf("a%d %d\n",d[l][0],d[l][1]);
            }
        }
    }

    for (i = 0; i < 27; i++)
        printf("d=%d %d\n", bb[i][0], bb[i][1]);
    // exit(1);

    for (i = 0; i < 27; i++)
    {
        // printf ("%d %d\n", bb[i][0], bb[i][1]);
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

// 多項式の次数(default)
int deg(vec a)
{
    int i, n = 0, flg = 0;

    // #pragma omp parallel for
    for (i = 0; i < DEG; i++)
    {
        if (a.x[i] > 0 && a.x[i] <= O)
        {
            n = i;
            // flg = 1;
        }
    }

    return n;
}

// 多項式を表示する（OP型）
void printpol(vec g)
{
    int i, n;
    vec f = (g);
    // f = conv(f);
    n = deg(f);
    // printf("n=%d\n", n);
    // printf("terms=%d\n", terms(f));
    // printf("deg=%d\n", odeg(f));

    for (i = n; i > -1; i--)
    {
        if (f.x[i] > 0)
            printf("%dx^%d+", f.x[i], i);
    }
}

unsigned short
v2a(oterm a)
{
    int i, j;

    if (a.a == 0)
        return 0;

    // printf("aa=%d\n",a.a);
    for (j = 0; j < M; j++)
    {
        if (gf[j] == a.a && a.a > 0)
        {
            // printf("j==%d\n",j);
            return j - 1;
        }
    }
}

void printsage(vec a)
{
    int i, j, k;
    oterm b;

    printf("poly=");
    for (i = 0; i < DEG; i++)
    {
        if (a.x[i] > 0)
        {
            b.a = a.x[i];
            b.n = i;
            j = v2a(b);
            // printf("%d,==ba\n",b.a);
            // printf ("X**%d+", i); //for GF2
            printf("B('a^%d')*x**%d+", j, i); // for GF(2^m)
        }
    }
}

// 配列の値を係数として多項式に設定する
vec setpol(unsigned short f[], int n)
{
    vec a = {0};

    for (int i = 0; i < n; i++)
    {
        a.x[n - 1 - i] = f[i];
    }

    return a;
}

vec synd(unsigned short zz[], int kk)
{
    unsigned short syn[K] = {0}, s = 0;
    int i, j, t1;
    vec f = {0};

    printf("in synd2\n");

    for (i = 0; i < K; i++)
    {
        // syn[i] = 0;
        s = 0;
        // #pragma omp parallel num_threads(16)
        for (j = 0; j < N; j++)
        {
            if (zz[j] > 0)
            {
                s = plus(s, gf[mlt(fg[zz[j]], fg[HH[i][j]])]);
                // printf("%d,%d %d %d", s, mat[j][i], zz[j], j);
                // printf(" ==sind\n");
            }
        }
        syn[K - 1 - i] = s;
        printf("syn%d,\n", syn[K - 1 - i]);
    }
    // printf ("\n");
    for (i = 0; i < K; i++)
        printf("%d,", fg[syn[i]]);
    printf("\n");
    // exit(1);

    f = setpol(syn, K);
    printpol((f));
    printf(" syn=============\n");
    printf("%d %d\n", fg[2], fg[26]);
    // exit(1);

    return f;
}

unsigned short minus(unsigned short a)
{
    int i;
    vec c = dick[fg[a]];
    vec b = {0}, d = (c);
    int k = deg((c)) + 1;
    unsigned short u = 0;
    OP f;

    for (i = 0; i < k; i++)
    {
        b.x[i] = (Pr - d.x[i]) % Pr;
        // printf("chen_b=%d\n",b.x[i]);
    }
    u = xtrace((b), Pr);

    return u;
}

// 多項式の代入値
unsigned short eval(vec f, unsigned short x)
{
    vec g = {0};
    unsigned short u = 0, s = 0;
    vec v = (f), h = {0};
    int d = deg((v)) + 1;

    for (int i = 1; i < d; i++)
    {
        if (v.x[i] > 0)
        {
            u = plus(u, gf[mlt(fg[v.x[i]], mltn(i, fg[x]))]);
            //
            // vtrace((oadd(dick[fg[u]], dick[mlt(fg[v.x[i]], mltn(i, x))])),x);
        }
    }
    if (v.x[0] > 0)
        u = plus(u, v.x[0]);

    return u;
}

void de()
{

    int i, j;
    for (i = 0; i < O; i++)
    {
        printpol((dick[i]));
        printf(", %d, %d lueda\n", eval(dick[i], Pr), i);
    }
}

// 20200816:正規化したいところだがうまく行かない
// 多項式の足し算
OP oadd2(OP f, OP g)
{
    // f = conv(f);
    // g = conv(g);
    // assert(op_verify(f));
    // assert(op_verify(g));

    vec a = {0}, b = {0}, c = {0};
    int i, j, k, l = 0;
    OP h = {0}, f2 = {0}, g2 = {0};

    a = o2v(f);
    b = o2v(g);

    // k=deg(o2v(f));
    // l=deg(o2v(g));

    for (i = 0; i < DEG; i++)
    {
        c.x[i] = plus(a.x[i], b.x[i]);
        // h.t[i].a=f.t[i].a^g.t[i].a;
    }
    h = v2o(c);
    // h=conv(h);
    // assert(op_verify(h));
    return h;
}
/*
// 多項式の掛け算
OP omul(OP f, OP g)
{
    // f=conv(f);
    // g=conv(g);

    // assert (op_verify (f));
    // assert (op_verify (g));
    int i, count = 0, k, l, m;
    oterm t = {0};
    cec h = {0}, e = {0}, r = {0};
    vec c = {0};

    l = deg(o2v(f));
    m = deg(o2v(g));

    // g = conv(g);
    for (i = 0; i < 2; i++)
        printf("%d\n", o2v(g).x[i]);
    //  exit(1);

    if (l >= m)
    {
        k = l;
    }
    else
    {
        k = m;
    }
    // printf("l=%d",l);
    // printf("m=%d",m);
    printpol((f));
    printf(" =f\n");
    printpol((g));
    printf(" =g\n");
    // exit(1);

    for (i = 0; i < k; i++)
    {
        t = g.t[i];
        if (t.a > 0)
        {
            printf("t[%d]=%d,%d\n", i, t.a, t.n);
            e = oterml(f, t);
            printpol((e));
            printf(" =e\n");
            printpol((h));
            printf(" =h\n");
            h = oadd2(h, e);
        }
    }
    printpol((h));
    printf(" =h2\n");

    // printpol(o2v(g));
    // printf(" =g\n");
    //    exit(1);
    // assert (op_verify (h));
    return h;
}
*/

// リーディグタームを抽出(default)
oterm LT(OP f)
{
    int i, k;
    oterm t = {0};

    // k = deg (o2v (f));
    for (i = 0; i < DEG; i++)
    {
        // printf("a=%d %d\n",f.t[i].a,f.t[i].n);
        if (f.t[i].a > 0)
        {
            t.n = f.t[i].n;
            t.a = f.t[i].a;
        }
    }

    return t;
}
/*
OP confer(OP f, int a)
{
    vec r;
    int n, i;
    OP g;

    r = o2v(f);
    n = deg(r);
    for (i = 0; i < n + 1; i++)
        r.x[i] = (r.x[i] * a) % Pr;
    g = v2o(r);

    return g;
}
*/
void makefg()
{
    unsigned short i, j, count = 0;

    // for (i = 0; i < O; i++)
    {
        for (j = 0; j < O; j++)
        {
            fg[gf[j]] = j;
        }
    }

    // exit(1);

    printf("unsigned short fg[%d]={", O);
    for (i = 0; i < O; i++)
        printf("%d,", fg[i]);
    printf("};\n");
    printf("count=%d\n", count);
    // exit(1);

    return;
}

// リーディグタームを抽出(defauvLT)
oterm vLT(vec f)
{

    oterm t = {0};

    for (int i = 0; i < DEG; i++)
    {
        if (f.x[i] > 0)
        {
            t.n = i;
            t.a = f.x[i];
        }
    }

    return t;
}

void mkmf()
{
    vec f = {0}, g = {0}, w = {0}, s = {0};
    vec b = {0}, a = {0}, d = {0}, v = {0};
    oterm o = {0};
    unsigned short ccp[4] = {0};

    if (O == 1331)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[0][i];
    }
    if (O == 2197)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[1][i];
    }
    if (O == 4913)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[2][i];
    }
    if (O == 6859)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[3][i];
    }
    if (O == 3125)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[4][i];
    }
    if (O == 2187)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[5][i];
    }
    if (O == 9)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[6][i];
    }
    if (O == 27)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[7][i];
    }
    if (O == 243)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[9][i];
    }
    if (O == 19683)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[8][i];
    }
    if (O == 12167)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[10][i];
    }
    if (O == 29791)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[11][i];
    }
    if (O == 49)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[12][i];
    }
    if (O == 125)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[13][i];
    }
    if (O == 729)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[14][i];
    }
    if (O == 343)
    {
        for (int i = 0; i < 4; i++)
            ccp[i] = pp[15][i];
    }

    g = (setpol(ccp, 4));
    for (int i = 0; i < 4; i++)
        printf("%d,", g.x[i]);
    printf("\n");

    printpol(g);
    printf("\n");
    b.x[0] = 0;
    a.x[0] = 1;

    v.x[1] = 1;
    v.x[0] = 0;
    printpol(g);
    printf(" =g\n");

    s = v;
    w = g;
    printpol(w);
    printf(" =w\n");
    printpol(g);
    printf(" =g\n");
    printpol(v);
    printf(" =s\n");

    vec c = {0};
    c.x[0] = 2;
    c.x[1] = 0;
    c.x[2] = 2;
    printf("err=%d\n", xtrace((c), Pr));
    printf("\n");

    gf[0] = 0;
    gf[1] = 1;
    dick[0] = b;
    dick[1] = a;
    for (int i = 2; i < EXP + 1; i++)
    {
        gf[i] = gf[i - 1] * Pr;
        dick[i] = vmul(v, dick[i - 1]);
        printpol(dick[i]);
        printf(" %d dick\n", gf[i]);
    }

    gf[EXP + 1] = xtrace(w, Pr);
    printf("\naa=%d\n", gf[Pr]);
    dick[EXP + 1] = w;
    int count = EXP + 1;
    for (int i = 0; i < EXP + 1; i++)
    {
        printpol(dick[i]);
        printf(" ==beef\n");
    }
    while (1)
    {
        printpol(g);
        printf(" ==beef %d\n", count);
        dick[count] = g;
        gf[count] = xtrace(g, Pr);
        printf("count2=%d %d ", count, gf[count]);
        printpol(g);
        printf(" =gg\n\n");
        if (gf[count] == 1)
        {
            printf("count!=%d\n", count);
        }

        g = vmul(g, s);
        printpol((g));
        printf(" =g\n\n");
        printf(" papaya\n");

        o = vLT(g);
        memset(d.x, 0, sizeof(d));

        if (o.n == EXP)
        {
            vec xx = (g);

            xx.x[EXP] = 0;
            f = w;
            g = xx;
            if (o.a > 0)
                f = confer(f, o.a);
            g = vadd(g, f);
        }

        count++;
        if (count == O)
            break;
    }

    printf("unsigned short gf[%d]={", O);
    for (int i = 0; i < O; i++)
        printf("%d,", gf[i]);
    printf("};");
    printf("\n");
}

MP bbgs(int n)
{
    int x, y, z = 1, w=1, u = 0, count = 0, zz = 1;
    MP bbgs = {0};
    for (int i = 0; i < n - 1; i++)
        zz *= Pr;
    // for (int i = 0; i < O; i++)
    {
        // for (int j = 0; j < O; j++)
        {
            u = 0;
            if (n == 2)
                w = 1;
            if (n > 2)
                w = Pr;
            for (int i = 0; i < n; i++)
            {
                w *= Pr;
                u = plus(u, plus(gf[mlt(mltn(z, y), oinv(mltn(w, x)))], 1));
                if (i == 1)
                    w = 1;
                printf("y^%d/x^%d+", w, z);
                z *= Pr;
            }
            printf("1\n");
            z = 1;
            for (int i = 0; i < n; i++)
            {
                w *= Pr;
                u = plus(u, plus(gf[mlt(mltn(z, y), oinv(mltn(w, x)))], 1));
                // printf("y^%d*x^%d+",w,zz-z);
                if (i < n)
                {
                    if (i == 1)
                        w = 1;
                    bbgs.x[i].n[0] = zz - z;
                    bbgs.x[i].n[1] = w;
                    bbgs.x[i].a = 1;
                    z *= Pr;
                }
            }

            w = 0;

            bbgs.x[n].n[0] = zz;
            bbgs.x[n].n[1] = w;
            bbgs.x[n].a = 1;

            // printf("x^%d*y^%d\n",zz,w);
        }
    }

    return bbgs;
}

int main(void)
{
    int i, j, k = 0, a, b, c, count = 0, x, y, z, g, n;
    unsigned int u = 0, v = 0, delta = 7, ips = 1;
    MP s = {0};

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
    // GF(64) #=113,g=3
    unsigned short g3[4][4] = {{3, 1, 0, 1}, {0, 3, 0, 1}, {0, 2, 0, 1}, {0, 0, 0, 1}};
    // g=6 GF(8)
    unsigned short g6[4][4] = {{4, 3, 0, 1}, {0, 4, 0, 1}, {1, 2, 0, 1}, {2, 0, 0, 1}};
    // gfQ*Q Hermitian
    unsigned short he[3][4] = {{Pr + 1, 0, 0, 1}, {0, Pr, 0, 1}, {0, 1, 0, 1}};
    // extention 3
    unsigned short hq[4][4] = {{Pr * Pr - 1, Pr, 0, 1}, {Pr * Pr - Pr, Pr * Pr, 0, 1}, {0, 1, 0, 1}, {Pr * Pr, 0, 0, 1}};
    // extention 4
    unsigned short hp[6][4] = {{Pr * Pr * Pr * Pr - 1, Pr, 0, 1}, {Pr * Pr * Pr - Pr, Pr * Pr, 0, 1}, {Pr * Pr * Pr * Pr - Pr * Pr, Pr * Pr * Pr, 0, 1}, {Pr * Pr * Pr * Pr - Pr * Pr * Pr, Pr * Pr * Pr * Pr, 0, 1}, {0, 1, 0, 1}, {Pr * Pr * Pr * Pr, 0, 0, 1}};
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

    unsigned short e1[27] = {0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0};
    unsigned char ee[64] = {0};
    MP curve = {0};
    curve = bbgs(E);
    printm(curve);
    exit(1);

    mkmf();
    makefg();
    de();
    // exit(1);

    PO t = {0};
    unsigned short ss[N * N] = {0};
    // unsigned short M[K][K] = { 0 };

    unsigned short sy[N * N] = {0};
    unsigned short SS[256][256] = {0};
    unsigned short dd[30][2] = {0};
    int l;
    unsigned short *B[256];
    unsigned short G[256][256] = {0};
    int ii, jj, kk;
    time_t pp;

    memset(S, 0, sizeof(S));
    //    memset(SS,0,sizeof(SS));

    for (i = 0; i < 256; i++)
    {
        for (j = 0; j < 256; j++)
        {
            SS[i][j] = 0;
            S[i][j] = 0;
        }
    }

    srand(clock() + time(&pp));

    i = 0;
    while (i < E)
    {
        ii = rand() % 16;
        jj = rand() % 63;
        if (ii > 0 && ee[jj] == 0 && jj > 0)
        {
            ee[jj] = ii;
            i++;
        }
    }

    // s=define_curve();

    // s = set_curve (he, 3);
    // s = set_curve(hq, 4);

    s = bbgs(E);
    printm(s);
    // exit(1);
    u = mtrace(s);
    //  v=u;
    printf("count=%d\n\n", u);
    exit(1);

    v = mkbase(aa);
    printf("mkcount=%d\n", v);
    //  exit(1);

    for (i = 0; i < u; i++)
    {
        printf("%d,%d %d\n", gf[p.z[0][i]], gf[p.z[1][i]], gf[p.z[2][i]]);
    }
    //  exit(1);

    unsigned short sk[256] = {0};

    for (i = 0; i < v; i++)
    {
#pragma omp parallel for
        for (j = 0; j < u; j++)
        {
            //      if(p.z[0][j]>0)
            HH[i][j] = fg[otrace(aa[i], p.z[0][j], p.z[1][j], 1)];
        }
    }

    for (i = 0; i < v; i++)
    {
        printf("(%d,%d): ", aa[i].n[0], aa[i].n[1]);
        for (j = 0; j < u; j++)
            printf("%d ", HH[i][j]);
        printf("\n");
    }

    // exit(1);
    //
    for (i = 0; i < U + 1; i++)
    {
        ss[i] = 0;
        // #pragma omp parallel for
        for (j = 0; j < 27; j++)
        {
            ss[i] = plus(ss[i], gf[mlt(fg[e1[j]], HH[i][j])]);
        }
        //    if(ss[i]>0)
        printf("syn[%d,%d]=%d\n", aa[i].n[0], aa[i].n[1], ss[i]);
        //      if(aa[i].n[0]==4){
        S[aa[i].n[0] + I][aa[i].n[1]] =
            plus(S[aa[i].n[0]][aa[i].n[1] - I + 1], S[aa[i].n[0]][aa[i].n[1] - I + 2]);
        //  printf("S[%d,%d]=%d\n",aa[i].n[0],aa[i].n[1],S[aa[i].n[0]][aa[i].n[1]]);
        //    }
    }
    printf("\n");
    //    printf("6=%d\n",13^4);
    exit(1);

    //    a=0;
    x = 0;
    j = 0;
    // printf("%d %d\n",p.z[0][0],p.z[1][0]);
    printf("v=%d\n", v);
    // exit(1);

    //    exit(1);

    for (i = 0; i < 27; i++)
    {
        S[aa[i].n[0]][aa[i].n[1]] = ss[i];
        //    for(j=0;j<2;j++)
        printf("%d", ss[i]);
        printf("\n");
    }
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 3; j++)
            printf("%d ", S[i][j]);
        printf("\n");
    }
    printf("\n\n");

    // param(U,6);
    exit(1);

    for (i = 0; i < U; i++)
    {
        for (k = 0; k < U; k++)
        {
            SS[i][k] = S[aa[i].n[0] + aa[k].n[0]][aa[i].n[1] + aa[k].n[1]];
            // printf("%d %d %d %d|",i,k,aa[i].n[i]+aa[k].n[0],aa[i].n[1]+aa[k].n[1]);
            printf("%2d,%2d ", aa[i].n[0] + aa[k].n[0],
                   aa[i].n[1] + aa[k].n[1]);
        }
        printf("\n");
    }
    // exit(1);

    //  printf("%d\n",fg[gf[5]^gf[2]^gf[6]]);

    return 0;
}
