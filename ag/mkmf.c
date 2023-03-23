#include <stdio.h>

#include "global-p.h"
#include "struct-p.h"
//#include "chash-p.c"

#define Pr 3
#define O 27
#define ORD 27
#define EXP 3

unsigned short pp[13][4] = {{0, 0, 9, 2}, {0, 0, 11, 2}, {0, 0, 16, 3}, {0, 0, 15, 2}, {0, 0, 1, 2}, {0, 1, 0, 2}, {0, 0, 1, 1}, {0, 0, 1, 2}, {1, 1, 2, 2}, {0, 0, 1, 2}, {0, 0, 21, 5}, {0, 0, 30, 3}, {0, 0, 1, 4}};
unsigned short gf[O], fg[O];
extern vec setpol(unsigned short f[], int n);


// 多項式の次数(default)
int deg(vec a)
{
    int n = 0;

    for (int i = 0; i < DEG; i++)
    {
        if (a.x[i] > 0 && a.x[i] <= N)
        {
            n = i;
        }
    }

    return n;
}

// 多項式を表示する（vec型）
void printpol(vec g)
{
    int n;
    vec f = {0};
    f = g;
    n = deg(g);

    for (int i = n; i > -1; i--)
    {
        if (f.x[i] > 0)
            printf("%dx^%d+", f.x[i], i);
    }
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
    vec g={0};

    n = deg(r);
    for (int i = 0; i < n + 1; i++)
        g.x[i] = (r.x[i] * a) % Pr;

    return g;
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

void makefg()
{
    for (int j = 0; j < O; j++)
    {
        fg[gf[j]] = j;
    }

    printf("unsigned short fg[%d]={", O);
    for (int i = 0; i < O; i++)
        printf("%d,", fg[i]);
    printf("};\n");

    return;
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

vec dick[O];
unsigned short val[N] = {0};
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

void de()
{

    for (int i = 0; i < O; i++)
    {
        printpol((dick[i]));
        printf(", %d, %d lueda\n", xtrace(dick[i], Pr), i);
    }
}

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


int mlt(int x, int y)
{

    if (x == 0 || y == 0)
        return 0;

    return ((x + y - 2) % (N - 1)) + 1;
}

int mltn(int n, int x)
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


int main(){
mkmf();
makefg();
de();
}
