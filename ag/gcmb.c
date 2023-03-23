#include <stdio.h>
#include <stdlib.h>

/* 組合せの生成: レジスタを使った高速版。 */

//#define N 23
//#define K 3
unsigned int count,count2;
typedef unsigned int set;
#define first(n) ((set) ((1U << (n)) - 1U))
typedef struct {
  int x[4096][3];
} tri;

unsigned int u[32],ss[256];

unsigned int model;

static unsigned short h2[8]={32884,16562,8424,4235,2135,1054,717,303
/*
0b1000000001110100,
0b0100000010110010,
0b0010000011101000,
0b0001000010001011,
0b0000100001010111,
0b0000010000011110,
0b0000001011001101,
0b0000000100101111
*/
};



set nextset(set x)
{
  set smallest,ripple,n_small,ones;
  
  smallest=x& -x;
  ripple=x+smallest;
  n_small=ripple & -ripple;
  ones=((n_small/smallest)>>1)-1;
  return ripple|ones;
}

tri ple={0};
int uu=0;
tri printest(set s,int N,int t1)
{
  int i,l,k=0;
  unsigned int b=0,j;
  char t[24];
  tri tt={0};

  for(i=1;i<=N;i++){
    if(k==t1)
      k=0;
    if(s&1){
      //printf("%d ",i);
      ple.x[uu][k++]=i;
      //printf("%d ",ple.x[uu][k]);
    }

/* b=b+u[i]; */
    s >>= 1;
  }

  //printf("\n"); 

/*
  j=itob(model^b,t);
  if(j==5){
    count2++;
    l=0;
    for(i=0;i<8;i++)
      l=(l<<1)+(itob(h2[i]&b,t)%2);

     printf("%u %b %d\n",l,b,j);

    if(ss[l]==0){
      ss[l]=b;
      count++;
      if(count==256)
	printf("%d\n",count2);

       printf("%u %u\n",l,b); 
    } 
    
       count++;
       printf("%u\n",count);
 }
   return j;
*/
  
  return ple;
}

//main()
tri aaa(int K, int N,int t1){
  int i,j;
  set x;
  
/*
  model==strtoul("1001001001001000",(char **)NULL,2);
  scanf("%u",&N);
  scanf("%u",&K);
  for(i=0;i<N;i++)
    u[i]=(1<<i);
  for(i=0;i<256;i++)
    ss[i]=0;
*/
 /* printf("%u %s\n",model,itoa(model,2)); */


  count=0;count2=0;
  i=1; x=first(K);
  while(! (x & ~first(N))){
    //printf("%4d:",i); 
    printest(x,N,t1);
    x=nextset(x); i++;
    uu++;
  }
//printf("uu=%d\n",uu);
//exit(1);

/*
  printf("%d\n",count);
  for(i=0;i<4096;i++){
    for(j=0;j<3;j++)
    printf("%d %u\n",i,ple.x[i][j]);
  }
  printf("%d\n",count2);
//exit(1);
*/
  return ple;

}


/*
int itob(int n,char s[])
{
  int i,j,k=0;
  
  for(i=(N-1),j=0;i>=0;i--,j++){
    s[j]=((n>>i) & 0x0001) + '0';
  }
  
  for(j=0;j<N;j++){
    if(s[j]-48==1)
      k++;
  }
  return k;
}
*/
