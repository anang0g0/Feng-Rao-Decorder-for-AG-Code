#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//#include "8192.h"
#include "global.h"
#include "struct.h"
#include "chash.c"
#include "param.h"

unsigned short g[K + 1] = {1,0,1,0,5};

// ランダム多項式の生成
static void
ginit(void)
{
    int j, count = 0, k = 0;
    unsigned short gg[K + 1] = {0};

    printf("in ginit\n");

    g[K] = 1;          // xor128();
    g[0] = rand() % N; // or N
    k = rand() % (K - 1);
    if (k > 0)
    {
        while (count < k)
        {
            printf("in whule\n");
            j = rand() % (K);
            if (j < K && j > 0 && g[j] == 0)
            {
                g[j] = rand() % N; // or N;
                count++;
            }
        }
    }

    for (j = 0; j < K + 1; j++)
        gg[j] = g[K - j];

    memcpy(g, gg, sizeof(g));
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

// 有限体の元の逆数
unsigned short
oinv(unsigned short a)
{
    int i;

    if (a == 0)
        return 0;
    if (a == 1)
        return a;
    return N - fg[a] + 1;

    printf("no return \n");

    //  exit(1);
}

// 多項式の次数(default)
int deg(vec a)
{
    int i, n = 0, flg = 0;

    // #pragma omp parallel for
    for (i = 0; i < DEG; i++)
    {
        if (a.x[i] > 0)
        {
            n = i;
            flg = 1;
        }
    }
    if (flg == 0)
        return 0;

    return n;
}

// 多項式を表示する(default)
void printpol(vec a)
{
    int i, n;

    n = deg(a);

    // printf ("baka\n");
    //  assert(("baka\n", n >= 0));

    for (i = n; i > -1; i--)
    {
        if (a.x[i] > 0)
        {
            printf("%u", a.x[i]);
            // if (i > 0)
            printf("x^%d", i);
            // if (i > 0)
            printf("+");
        }
    }
    //  printf("\n");

    return;
}

vec kof2(unsigned short c, vec f)
{
    int i, j, k;
    vec b = {0}, h = {0};
    OP g = {0};

    c = fg[c];
    printf("c=%d\n", c);
    // exit(1);
    b = f; // o2v(f);
    k = deg(b);
    printpol(b);
    printf(" =b debugi\n");
    for (i = 0; i < k + 1; i++)
    {
        h.x[i] = gf[mlt(c, fg[b.x[i]])];
    }
    // g = v2o(h);
    printpol(h);
    printf(" =h in kof2\n");
    return h;
}

vec vadd(vec a, vec b)
{
    int i;
    vec c = {0};

    // printf("deg=%d %d\n",deg(a),deg(b));

    for (i = 0; i < DEG; i++)
        c.x[i] = a.x[i] ^ b.x[i];

    return c;
}

int mul = 0, mul2 = 0;
vec vmul(vec a, vec b)
{
    int i, j, k, l;
    vec c = {0};
    if (deg(a) > 128 && deg(b) > 128)
        mul++;
    mul2++;

    k = deg(a);
    l = deg(b);

    for (i = 0; i < k + 1; i++)
    {
        for (j = 0; j < l + 1; j++)
        // if (a.x[i] > 0)
        {
            c.x[i + j] ^= gf[mlt(fg[a.x[i]], fg[b.x[j]])];
        }
    }

    return c;
}

unsigned short vb[K * 2][N] = {0};
unsigned short gt[K * 2][K * 2] = {0};

void van(int kk)
{
    int i, j, k;

    printf("van der\n");

    for (i = 0; i < N; i++)
        mat[i][0] = vb[0][i] = 1;
    // #pragma omp parallel for private(i, j)
    for (i = 1; i < kk; i++)
    {
        for (j = 0; j < N; j++)
        {
            vb[i][j] = gf[mltn(i, j)];
            printf("%d,", vb[i][j]);
            mat[j][i] = vb[i][j];
        }
        printf("\n");
    }
}

void ogt(unsigned short pp[], int kk)
{
    int i, j, k;
    OP w = {0};

#pragma omp parallel for private(i, j)
    for (i = 0; i < kk; i++)
    {
        for (j = 0; j < kk - i; j++)
        {
            gt[i][j + i] = g[j];
        }
    }
    for (i = 0; i < kk; i++)
    {
        for (j = 0; j < kk; j++)
            printf("%d,", gt[i][j]);
        printf("\n");
    }
    // exit(1);
}

// 配列の値を係数として多項式に設定する
OP setpol(unsigned short f[], int n)
{
    OP g;
    vec v = {0};
    int i;

    for (i = 0; i < n; i++)
    {
        v.x[n - 1 - i] = f[i];
    }

    g = v2o(v);

    return g;
}

OP mkpol()
{
    int i, j, k, fail, flg, l, ii = 0;
    OP w = {0};

    do
    {
        fail = 0;
        j = 0;
        k = 0;
        flg = 0;
        l = 0;
        memset(g, 0, sizeof(g));
        // memset(ta, 0, sizeof(ta));
        memset(w.t, 0, sizeof(w));
        ginit();
        ii++;
        if (ii > 100)
        {
            printf("erro=%d\n", ii);
            exit(1);
        }

        for (i = 0; i < K; i++)
        {
            if (g[K - 1] > 0)
                flg = 1;
            if (i % 2 == 1 && g[i] > 0 && i < K)
                k++;
        }

        // 偶数項だけにならないようにする
        if ((k > 0 && flg == 0) || (k > 1 && flg == 1))
        // if(k>0)
        {
            w = setpol(g, K + 1);
            j = 1;
            // if(isquad(w)==-1)
            // exit(1);
        }
        // exit(1);

    } while (j == 0);

    printpol(o2v(w));
    printf(" ==g\n");
    // exit(1);

    return w;
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
            printf("B('a^%d')*X**%d+", j, i); // for GF(2^m)
        }
    }
}

// 多項式の代入値
unsigned short
trace(OP f, unsigned short x)
{
    int i, d;
    unsigned short u = 0;

    d = deg(o2v(f));

    for (i = 0; i < d + 1; i++)
    {
        u ^= gf[mlt(fg[f.t[i].a], mltn(f.t[i].n, fg[x]))];
    }

    return u;
}

void vv(int kk)
{
    int i, j, k;
    OP r; // = mkpol();
    unsigned short tr[N];
    unsigned short ta[N] = {0};

    printf("van der\n");

    for (i = 0; i < N; i++)
    {
        mat[i][0] = vb[0][i] = 1;
    }
    // #pragma omp parallel for private(i, j)
    for (i = 1; i < kk; i++)
    {
        for (j = 0; j < N; j++)
        {
            vb[i][j] = gf[mltn(i, j)];
            // printf("%d,", vb[i][j]);
        }
        // printf("\n");
    }

aa:

    r = mkpol(); //setpol(g,K+1); //mkpol();
    for (i = 0; i < N; i++)
    {
        ta[i] = trace(r, i);
        if (ta[i] == 0)
        {
            printf("trace 0 @ %d\n", i);
            // fail = 1;
            goto aa;
        }
    }

    for (i = 0; i < N; i++)
    {
        tr[i] = oinv(ta[i]);
        // printf("%d,", tr[i]);
    }

    // memset(g, 0, sizeof(g));
    // g[0] = 1;

    // 多項式を固定したい場合コメントアウトする。
    //ogt(g, kk);

    // wait();

    // #pragma omp parallel for

    printf("\nすげ、オレもうイキそ・・・\n");
    // keygen(g);
    // exit(1);

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < kk; j++)
        {
            mat[i][j] = gf[mlt(fg[vb[j][i]], tr[i])];
        }
    }
    for (i = 0; i < K; i++)
    {
        for (j = 0; j < N; j++)
            printf("%d,", mat[j][i]);
        printf("\n");
    }
}

// Patterson & EEA 用（ランダム多項式、次元指定）
OP mkg(int kk)
{
    int i, j, k, l, ii = 0;
    OP w = {0};
    unsigned short tr[N] = {0};
    unsigned short ta[N] = {0};
    unsigned short po[K + 1] = {1, 0, 1, 0, 5};

aa:

    // printf("\n");

    // 既約性判定のためのBen-Orアルゴリズム。拡大体にも対応している。デフォルトでGF(8192)
    // 既約多項式しか使わない。

    l = -1;
    ii = 0;

    // while (l == -1)
    {
        w = mkpol();
        // l = ben_or(w);
        printf("irr=%d\n", l);
        if (ii > 300)
        {
            printf("too many error\n");
            exit(1);
        }
        ii++;
        //
    }

    // w = mkpol();
    memset(ta, 0, sizeof(ta));
    // g[0]=1;

    // 多項式の値が0でないことを確認
    for (i = 0; i < N; i++)
    {
        ta[i] = trace(w, i);
        if (ta[i] == 0)
        {
            printf("trace 0 @ %d\n", i);
            // fail = 1;
            goto aa;
        }
    }

    // 多項式を固定したい場合コメントアウトする。
    /*
  memset(ta, 0, sizeof(ta));
  w = setpol(po, K + 1);
  printpol(o2v(w));
  printf(" =poly\n");
//  exit(1);
  for (i = 0; i < N; i++)
  {    ta[i] = trace(w, i);
    if (ta[i] == 0)
    {
      printf("trace 0 @ %d\n", i);
      exit(1);
    }
  }
  */
    printpol(o2v(w));
    printf("\n");
    printsage(o2v(w));
    printf("\n");
    printf("sagemath で既約性を検査してください！\n");

    for (i = 0; i < N; i++)
    {
        tr[i] = oinv(ta[i]);
        // printf("%d,", tr[i]);
    }

    printpol(o2v(w));
    printf(" =irreducible\n");
    printsage(o2v(w));
    printf("\n");
    // wait();

    memset(vb, 0, sizeof(vb));
    memset(gt, 0, sizeof(gt));
    van(kk);
    ogt(po, kk);
    memset(mat, 0, sizeof(mat));

    printf("\nすげ、オレもうイキそ・・・\n");

    for (j = 0; j < N; j++)
    {
        for (i = 0; i < K; i++)
        {
            ma[j][i] = gf[mlt(fg[vb[i][j]], tr[j])];
        }
    }

    unsigned short s;
    for (i = 0; i < K; i++)
    {
        for (j = 0; j < N; j++)
        {
            s = 0;

            for (k = 0; k < K; k++)
                s ^= gf[mlt(fg[gt[k][i]], fg[ma[j][k]])];
            // printf("%d,",s);
            mat[j][i] = s;
        }
        printf("\n");
    }
    printf("\n");
    // exit(1);

    for (j = 0; j < N; j++)
    {
        for (i = 0; i < K; i++)
            printf("%d,", mat[j][i]);
        printf("\n");
    }
    printf("\n");
    // wait();

    return w;
}

void mkerr(unsigned short *z1, int num)
{
    int j, l;

    j = 0;

    memset(z1, 0, sizeof(z1));

    while (j < num)
    {
        l = rand() % N;
        // printf ("l=%d\n", l);
        if (0 == z1[l] && l>0)
        {
            z1[l] = 1;
            // printf("l=%d\n", l);
            j++;
        }
    }
}

OP synd(unsigned short zz[], int kk)
{
    unsigned short syn[K] = {0}, s = 0;
    int i, j, t1;
    OP f = {0};

    printf("in synd2\n");

    for (i = 0; i < kk; i++)
    {
        syn[i] = 0;
        s = 0;
        // #pragma omp parallel num_threads(16)
        for (j = 0; j < M; j++)
        {
            s ^= gf[mlt(fg[zz[j]], fg[mat[j][i]])];
        }
        syn[i] = s;
        // printf ("syn%d,", syn[i]);
    }
    // printf ("\n");

    f = setpol(syn, kk);
    printpol(o2v(f));
    printf(" syn=============\n");
    //  exit(1);

    return f;
}

// chen探索
void chen(vec f)
{
    vec e = {0};
    int i, count = 0, n, x = 0;
    unsigned short z;

    n = deg((f));
    for (x = 0; x < N; x++)
    {
        z = 0;
        for (i = 0; i < n + 1; i++)
        {
            if (f.x[i] > 0)
                z ^= gf[mlt(mltn(i, fg[x]), fg[f.x[i]])];
        }
        if (z == 0)
        {
            e.x[count] = x;
            count++;
            printf("change %d\n", (fg[x]));
        }
    }
    if(count<T){
        printf("few baka\n");
        exit(1);
    }
    //return e;
}

vec bma(unsigned short s[])
{
    int L = 0, m = -1, d[K] = {0}, k = 0, i, e;
    vec f = {0}, g = {0}, h, v, c = {0}, cc = {0};

    c.x[1] = 1;
    f.x[0] = g.x[0] = 1;

    while (k <= (2 * T - 1))
    {
        e = 0;
        for (i = 0; i < L; i++)
            e ^= gf[mlt(fg[f.x[i]], fg[s[k - i]])];
        printf("L=%d i=%d\n", L, i);
        d[k] = gf[mlt(fg[f.x[L]], fg[s[k - i]])] ^ e; // s[k] ^ e;
        printf("d[%d]=%d s[k]=%d\n", k, d[k], s[k]);

        printpol(f);
        printf("%d,%d====f\n", k, d[k]);
        if (d[k] > 0)
        {
            h = f;
            memset(v.x, 0, sizeof(v.x));
            v.x[k - m] = 1;
            unsigned short a;
            a = (m < 0) ? 1 : oinv(d[m]);
            cc = kof2(gf[mlt(fg[d[k]], a)], g);
            f = vadd(f, vmul(cc, v));
            if (L <= k / 2 + 1)
            {
                L = k + 1 - L;
                m = k;
                g = h;
            }
        }
        k++;
        // if(deg(f)==T)
        // break;
    }
    printpol(f);
    printf("==loc\n");
    if (deg(f) == T + 1)
    {
        for (i = 0; i < T + 1; i++)
            cc.x[i] = f.x[i + 1];
        chen(cc);
        return cc;
    }else if (deg(f) == T)
    {
        chen(f);
        return f;
    }else{
        printf("baka\n");
        exit(1);
    }

    //return f;
}

vec bms(unsigned short s[], int kk)
{
    int i, j, k, ll = 0, l, d[2 * K + 1] = {0};
    vec lo[2 * K + 1] = {0}, b[2 * K + 1] = {0}, t[2 * K + 1] = {0}, h = {0}, g = {0};
    vec v = {0}, x = {0};

    x.x[1] = 1;
    h = (x);
    v.x[0] = 1;
    // f = v2o(x);
    lo[0] = (v);
    b[0] = lo[0];
    ll = 0;
    for (j = 1; j < T * 2 + 1; j++)
    {
        v = (lo[j - 1]);
        k = 0;

        l = deg((lo[j - 1]));
        for (i = 1; i < l + 1; i++)
        {
            k ^= gf[mlt(fg[v.x[i]], fg[s[j - i]])];
            printf("v[%d]=%d %d %d\n", i, v.x[i], s[j - i], k);
        }
        d[j] = s[j] ^ k;
        printf("d[%d]=%d\n", j, d[j]);
        if (d[j] == 0)
        {
            lo[j] = lo[j - 1];
            b[j] = (vmul((b[j - 1]), (h)));
            // ll=j-1;
        }
        else // if (d[j] > 0)
        {
            g = (vmul(kof2(d[j], (h)), (b[j - 1])));
            t[j] = (vadd((lo[j - 1]), (g)));
            lo[j] = t[j];
            if (ll * 2 > (j - 1))
            {
                // lo[j]=t[j];
                b[j] = (vmul((b[j - 1]), (h)));
            }
            else // if(2*ll <= j)
            {
                // printpol(o2v(t[j]));
                // printf("==t[%d]\n", j);
                b[j] = (kof2(gf[oinv(d[j])], (lo[j - 1])));
                // lo[j]=t[j];
                ll = j - ll;

                if (j == 2 * T)
                {
                    lo[j - 1] = (vmul((lo[j - 2]), (h)));
                    break;
                }
            }
        }
        printf("l=%d\n", ll);
        k = 0;
        // printpol(o2v(b[j]));
        // printf(" ==b[%d]\n", j);
    }

    k = 0;
    int count = 0;
    // printpol(o2v(lo[j - 1]));
    // printf(" ==coef\n");
    if (deg((lo[j - 1])) == T)
    {
        chen((lo[j - 1]));
    }
    else
    {
        printf("baka==\n");
        exit(1);
    }

    return (lo[j - 1]);
}

typedef struct
{
    vec f;
    vec g;
} ymo;


vec bm_itr(unsigned short s[])
{
    vec U1[2][2] = {0}, U2[2][2][2] = {0};
    int i, j, k;
    ymo t = {0};

    U2[0][0][0].x[0] = 1; // f[0];
    U2[0][0][1].x[0] = 0; // fai[0];
    U2[0][1][0].x[0] = 0; // g[0];
    U2[0][1][1].x[0] = 1; // thi[0];
    int m = 0, d = deg(U2[0][0][0]), p = 2 * d - m - 1, myu = 0, e = 0;

    for (m = 0; m < K; m++)
    {
        d = deg(U2[0][0][0]);
        p = 2 * d - m - 1;
        myu = 0;
        for (i = 0; i <= d; i++)
            myu ^= gf[mlt(fg[U2[0][0][0].x[i]], fg[s[i + (m - d)]])];

        memset(U1, 0, sizeof(U1));
        if (myu == 0 || p >= 0)
        {
            U1[0][0].x[0] = 1;
            U1[1][0].x[0] = 0;
            U1[0][1].x[p] = myu;
            U1[1][1].x[0] = 1;
        }
        else
        {
            printf("anan\n");
            if (p < 0)
                p *= -1;
            U1[0][0].x[p] = 1;
            U1[0][1].x[0] = myu;
            U1[1][0].x[0] = gf[oinv(myu)];
            U1[1][1].x[0] = 0;
        }
        for (i = 0; i < 2; i++)
        {
            for (j = 0; j < 2; j++)
            {
                for (k = 0; k < 2; k++)
                {
                    U2[1][i][j] = vadd(U2[1][i][j], vmul(U1[i][k], U2[0][k][j]));
                    //printpol(U2[1][0][0]);
                    //printf(" %d %d %d ==U2\n", i, k, j);
                }
            }
        }

        for (i = 0; i < 2; i++)
        {
            for (j = 0; j < 2; j++)
                U2[0][i][j] = U2[1][i][j];
        }
        memset(U2[1], 0, sizeof(U2[1]));
    }

    d = deg(U2[0][0][0]) + 1;
    for (i = 0; i < d; i++)
        t.f.x[d - 1 - i] = U2[0][0][0].x[i];
    t.g = U2[0][1][0];
    vec ff={0};
    if(deg(t.f)==K/2+1){
        //t.f.x[0]=0;
        for(i=0;i<T;i++)
        ff.x[i+1]=t.f.x[i];
        t.f=ff;
    }
    if(deg(t.f)<T){
        printf("few baka\n");
        exit(1);
    }
    printsage(t.f);
    printf(" ==00\n");

    return t.f;
}


int main()
{
    int i, j;
    unsigned short s[K + 1] = {0}, z1[N] = {0};
    vec v = {0}, x = {0}, r = {0};
    OP f = {0};

    srand(clock());
    // mkg(K);
     van(K);          // RS-Code generate
    //vv(K);
    while(1){
    for(i=0;i<N;i++)
    z1[i]=0;
    mkerr(z1, T);    // generate error vector
    f = synd(z1, K); // calc syndrome
    x = o2v(f);      // transorm to vec
    //v = bma(x.x);    // Berlekamp-Massey Algorithm
    v=bm_itr(x.x);
    /*
    for (i = 0; i < K; i++)
        s[i + 1] = x.x[i];
    v = bms(s, K + 1);
    */
    printf("the errors below\n");
    for (i = 0; i < N; i++)
    {
        if (z1[i] > 0)
            printf("chan_ans=%d\n", i); // print answer
    }
    chen(v);
}
    printf("%d\n", deg(v));
    printpol(v); // print error locater polynomial
    printf("==bms\n");

    //chen((v)); // searching error position
    
    /*
    printf("%d\n", deg(r));
    printpol(r); // print error locater polynomial
    printf("\n");
    x = chen((r)); // searching error position
    printpol(r);
    printf("==bma\n");
    elo(x);
    */
    return 0;
}
