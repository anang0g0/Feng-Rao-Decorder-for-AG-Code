#include <stdio.h>

#define N  9   //the dimension of equation
#define M  16

//unsigned short gf[8]={0,1,2,4,3,6,7,5};
//unsigned short fg[8]={0,1,2,4,3,7,5,6};
//sa
unsigned short gf[16]={0,1,2,4,8,3,6,12,11,5,10,7,14,15,13,9};
unsigned short fg[16]={0,1,2,5,3,9,6,11,4,15,10,8,7,14,12,13};



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

int Inv(unsigned char b){
  int i;

      for(i=0;i<M;i++){
        if(gf[mlt(i,b)]==1)
          return i;
      }

    }


void vec_diff(unsigned short a[N], unsigned short b[N]){
    /* Calcurate the difference of two vectors. Be caution that b[N] changes.*/
    for (int i = 0; i < N; i++){
        b[i] ^= a[i];
    }
}

int main(){
  unsigned short m[N][N] = {
  { gf[0] ,gf[2], gf[9], gf[1], gf[0], gf[10], gf[3], gf[1], gf[5]},
  { gf[9], gf[1], gf[10], gf[3], gf[1], gf[2], gf[15], gf[10], gf[5]},
  {gf[11], gf[0], gf[3], gf[1], gf[5], gf[15], gf[10], gf[5], gf[13]},
  {gf[10], gf[3], gf[2], gf[15], gf[10], gf[11], gf[15], gf[9], gf[2]},
  {gf[3], gf[1], gf[15], gf[10], gf[5], gf[15], gf[9], gf[2], gf[6]},
  {gf[1], gf[5], gf[10], gf[5], gf[13], gf[9], gf[2], gf[6], gf[0]},
  {gf[2], gf[15], gf[11], gf[15], gf[9], gf[3], gf[4], gf[3], gf[15]},
  {gf[15], gf[10], gf[15], gf[9], gf[14], gf[3], gf[15], gf[8]},
  {gf[10], gf[5], gf[9], gf[2], gf[6], gf[3], gf[15], gf[8], gf[3]}
  }; //{{7,2,5}, {2,5,2},{5,2,7}};    // The matrix
  unsigned short b[N] = {gf[11],gf[0],gf[11],gf[9],gf[1],gf[0],gf[10],gf[3],gf[1]}; //{5,7,0};
  unsigned short mm[N]={0};

    printf("The coefficient matrix is : \n");
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%d ", m[i][j]);
            if (j == N-1){
                printf("\n");
            }
        }
    }

    printf("\nUse Gauss method to solve equations : \n");
    for (int i = 0; i < N; i++){
        for (int j = i+1; j < N; j++){
	  unsigned short coef = mlt(fg[m[j][i]] , Inv(fg[m[i][i]]));
            unsigned short del[N];

            for (int k = 0; k < N; k++){
	      del[k] = gf[mlt(fg[m[i][k]] , coef)];
            }
	    //for(int ii=0;ii<N;ii++)
	    //mm[ii]=m[j][ii];
            vec_diff(del, m[j]);
            b[j] ^= gf[mlt(fg[b[i]] , coef)];
        }
    }

    for (int i = N -1; i >= 0; i--){
      unsigned short x = gf[Inv(fg[m[i][i]])];
      m[i][i] = gf[mlt(fg[m[i][i]], fg[x])];
      b[i] = gf[mlt(fg[b[i]],fg[x])];

        for (int j = 0; j < i; j++){
	  b[j] ^= gf[mlt(fg[b[i]],fg[m[j][i]])];
            m[j][i] = 0;
        }
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%d ", m[i][j]);
            if (j == N - 1){
                printf("\n");
            }
        }
    }

    for (int i = 0; i < N; i++){
        printf("%d ", b[i]);
    }

    return 0;
}
