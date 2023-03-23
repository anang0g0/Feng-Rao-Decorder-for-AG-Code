//学校で習った知識を使ったら問題解決できました。大学行っといてよかったｗ


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define D 4096
#define F 10
#define M 16

unsigned char gf[M]={0,1,2,4,8,9,11,15,7,14,5,10,13,3,6,12};
unsigned char fg[M]={0,1,2,13,3,10,14,8,4,5,11,6,15,12,9,7};


unsigned char cc[F][F]={0};
unsigned char bb[F][F]={0};
unsigned char cl[F][F]={0};
  
  //{{0,1,0,1},{1,0,0,1},{0,0,1,0},{0,0,1,1}};
//{{0,1,1,1},{1,0,1,1},{0,0,1,1},{1,0,0,1}}; //{{1,2,0,-1},{-1,1,2,0},{2,0,1,1},{1,-2,-1,1}}; //入力用の配列
unsigned char inv_a[F][F]; //ここに逆行列が入る
unsigned char buf; //一時的なデータを蓄える
int i,j,k; //カウンタ
int n=10;  //配列の次数



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

int inv2(int a,int b){
  int i=0;

  for(i=0;i<16;i++){
    if(b==gf[mlt(fg[a],i)])
      return i;
  }
    
}



unsigned long xor128(void)
{
  unsigned int a=0;
  static unsigned long x=123456789,y=362436069,z=521288629,w=88675123;
    unsigned long t;
    a=rand();
    t=(a^(a<<11));a=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
}


void g2(){
  int i,j,k;


  /*  
  for(i=0;i<F;i++){
    a[i][i]=1;
    bb[i][i]=1;
  }
  
  for(i=0;i<F;i++){
    for(j=i+1;j<F;j++){
      a[i][j]=xor128()%2;
      
    }  
  }
  */
  /*
  for(i=0;i<F;i++){
    for(j=0;j<F;j++)
      printf("%d,",a[i][j]);
    printf("\n");
  }
  printf("\n");
  
  for(i=0;i<F;i++){
    for(j=i+1;j<F;j++){
      bb[j][i]=xor128()%2;
    }
  }
    
  for(i=0;i<F;i++){
    for(j=0;j<F;j++)
      printf("%d,",bb[i][j]);
    printf("\n");
  }
  printf("\n");
  //    exit(1);
  
  for(i=0;i<F;i++){
    for(j=0;j<F;j++){
      for(k=0;k<F;k++){
	cc[i][j]^=bb[i][k]&a[k][j];
      }
    }
  }
  */
  /*
  for(i=0;i<F;i++){
    for(j=0;j<F;j++)
      printf("%d,",cc[i][j]);
    printf("\n");
  }
  printf("\n");
  */
}


void main(){
  int i,j,k,l,ii;
  unsigned char b[F][F]={0};
  unsigned char dd[2040]={0};
  unsigned int flg=0,count=0,c;
  time_t t;
  FILE *fq;


unsigned char a[F+5][F]={
     {gf[11],gf[0] ,gf[2], gf[9], gf[1], gf[0], gf[10],gf[3], gf[1], gf[5]},
     {gf[0], gf[9], gf[1], gf[10],gf[3], gf[1], gf[2], gf[15],gf[10],gf[5]},
     {gf[2], gf[1], gf[0], gf[3], gf[1], gf[5], gf[15],gf[10],gf[5], gf[13]},
     {gf[9], gf[10],gf[3], gf[2], gf[15],gf[10],gf[11],gf[15],gf[9], gf[2]},
     {gf[1], gf[3], gf[1], gf[15],gf[10],gf[5], gf[15],gf[9], gf[2], gf[6]},
     {gf[0], gf[1], gf[5], gf[10],gf[5], gf[13],gf[9], gf[2], gf[6], gf[0]},
     {gf[10],gf[2], gf[15],gf[11],gf[15],gf[9], gf[3], gf[4], gf[3], gf[15]},
     {gf[3], gf[15],gf[10],gf[15],gf[9], gf[2], gf[4], gf[3], gf[15],gf[8]},
     {gf[1], gf[10],gf[5], gf[9], gf[2], gf[6], gf[3], gf[15],gf[8], gf[3]},
     {gf[5], gf[5], gf[13],gf[2], gf[6], gf[0], gf[15],gf[8], gf[3], gf[10]},
     {gf[2], gf[11],gf[15],gf[3], gf[4], gf[3], gf[4], gf[12],gf[3], gf[10]},
     
     {gf[10],gf[9], gf[2], gf[3], gf[15],gf[8], gf[3], gf[10],gf[0], gf[14]},
     {gf[5], gf[2], gf[3], gf[15],gf[8], gf[3], gf[10],gf[0], gf[14],gf[13]},
     {gf[15],gf[15],gf[9], gf[4], gf[3], gf[15],gf[12],gf[3], gf[10],gf[0]},      
     
     

    

     {gf[13],gf[6], gf[0], gf[8], gf[8], gf[10],gf[0], gf[14],gf[13],gf[3]}


   
};
/*
  {gf[11],gf[0],gf[2],gf[9],gf[7],gf[6],gf[5],gf[9],gf[15],gf[14],gf[6]},
  {gf[10],gf[10],gf[13],gf[9],gf[8],gf[4],gf[5],gf[12],gf[11],gf[7],gf[8]},
  {gf[0],gf[2],gf[0],gf[3],gf[2],gf[6],gf[15],gf[9],gf[12],gf[11],gf[8]},
  {gf[12],gf[15],gf[5],gf[3],gf[13],gf[8],gf[4],gf[1],gf[0],gf[10],gf[10]},
  {gf[7],gf[5],gf[11],gf[13],gf[10],gf[13],gf[6],gf[14],gf[4],gf[5],gf[14]},
  {gf[6],gf[8],gf[7],gf[2],gf[15],gf[6],gf[15],gf[4],gf[10],gf[1],gf[11]},
  {gf[7],gf[5],gf[8],gf[4],gf[11],gf[6],gf[15],gf[7],gf[6],gf[8],gf[0]},
  {gf[10],gf[12],gf[0],gf[13],gf[7],gf[2],gf[10],gf[4],gf[7],gf[4],gf[14]},
  {gf[0],gf[10],gf[15],gf[13],gf[6],gf[6],gf[14],gf[11],gf[0],gf[6],gf[14]},
  {gf[10],gf[15],gf[6],gf[8],gf[3],gf[6],gf[1],gf[9],gf[14],gf[13],gf[0]}
  }; */
 
   
//  while(flg<F || count!=F*F-F){
    
    srand(clock()+time(&t));

    //gauss
    
    for(i=0;i<11;i++){
      printf("i=%d\n",i);
      for(j=0;j<10;j++){
	for(k=0;k<10;k++){
	  printf("%d ",fg[a[j][k]]);
	}
	printf("\n");
      }
      printf("\n");
      if(a[i][i]==0){
	for(j=0;j<10;j++)
	  a[i][j]^=a[i+1][j];
      }
      if(a[i][i]>0){
	c=Inv(fg[a[i][i]]);
      for(k=0;k<10;k++)
      a[i][k]=gf[mlt(fg[a[i][k]],c)];
      for(k=0;k<10;k++)
      printf("%d ",fg[a[i][k]]);
      printf("\n");
      for(k=i+1;k<10;k++){
	a[k][i]^=gf[mlt(fg[a[i][i]],fg[a[k][i]])];
	//for(j=i+1;j<10;j++)
	// a[j][i]^=gf[mlt(fg[a[j][i]],c)];	
      }
      
      }
    }
    printf("%d\n",fg[gf[mlt(2,15)]^gf[11]^gf[6]]);
    printf("%d\n",fg[gf[mlt(11,13)]^gf[13]]);
    printf("%d\n",fg[gf[gf[5]^gf[9]^gf[mlt(4,3)]^mlt(13,10)]^gf[8]^gf[mlt(9,14)]^gf[mlt(2,6)]^gf[11]]);
        exit(1);
    
    for(i=0;i<M;i++){
      for(j=0;j<M;j++){
	if((fg[gf[mlt(5,8)]^gf[13]])==3)
	printf("%d %d\n",i,j);
      }
    }
    
     exit(1);

     flg=0;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      //  printf("%d,",a[i][j]);
      cl[i][j]=a[i][j];
      dd[j]=a[i][j];

    }
    //  printf("\n");
  }

  
//単位行列を作る
for(i=0;i<n;i++){
 for(j=0;j<n;j++){
 inv_a[i][j]=(i==j)?1.0:0.0;
 }
}

 printf("\n");
 for(i=0;i<n;i++){
   for(j=0;j<n;j++)
     printf("%d,",a[i][j]);
   printf("\n");
 }

//掃き出し法
for(i=0;i<n;i++){
  if(a[i][i]==0){
  j=0;
  while(a[j][i]==0){
    j++;
  }
  //  printf("j=%d\n",j);
  
  //  exit(1);
 for(k=0;k<n;k++){
 a[i][k]^=a[j][k];
 inv_a[i][k]^=inv_a[j][k];
 }
  }
  //  exit(1);
  
 if(a[i][i]>0 && a[i][i]!=1){
   for(l=0;l<n+1;l++){
     a[i][l]=gf[mlt(Inv(fg[a[i][i]]),fg[a[i][l]])];
     inv_a[i][l]=gf[mlt(Inv(fg[inv_a[i][i]]),fg[inv_a[i][l]])];
   }
 }
 for(l=i+1;l<n;l++){
   if(a[l][i]>0){
     for(k=0;k<n+1;k++){
       a[l][k]^=a[i][k];
       inv_a[l][k]^=inv_a[i][k];
     }
   }
 }

 // printf("@%d\n",i);
 
 // printf("@i=%d\n",i);
 for(l=0;l<n;l++){
   for(k=0;k<n;k++)
     printf("%d,",a[l][k]);
   printf("\n");
 }

 //  exit(1);

 // for(l=0;l<n;l++){
   if(a[i][i]==1){
     for(k=i+1;k<n;k++){
       //       for(j=0;j<n;j++){
       // if(a[k][i]==1){
	 a[k][i]^=gf[mlt(fg[a[k][i]],fg[a[i][i]])];
	  inv_a[k][i]^=gf[mlt(fg[inv_a[k][i]],fg[inv_a[i][i]])];
	 //}
	 //       }
     }
   }
 }
// }
 
   printf("i=%d\n",i);
   for(l=0;l<n;l++){
     for(ii=0;ii<n;ii++)
       printf("%d,",fg[a[l][ii]]);
     printf("\n");
   }

   //   exit(1);
   for(l=0;l<n;l++){
     for(ii=0;ii<n;ii++)
       printf("%d, ",inv_a[l][ii]);
     printf("\n");
   }
     

 
 for(i=0;i<n;i++){
   for(j=0;j<n;j++)
     printf("\%d,",a[i][j]);
   printf("\n");
 }
 //    exit(1);
 

//逆行列を出力
for(i=0;i<n;i++){
 for(j=0;j<n;j++){
  printf(" %d,",inv_a[i][j]);
 }
 printf("\n");
 }
 
// exit(1);
//検算
 for(i=0;i<n;i++){
   for(j=0;j<n;j++){
     for(k=0;k<n;k++){
       b[i][j]^=gf[mlt(fg[cl[i][k]],fg[inv_a[k][j]])];
     }
   }
 }

 
 for(i=0;i<n;i++){
   for(j=0;j<n;j++)
     printf("%d,",b[i][j]);
   printf("\n");
  
 }
 exit(1);
 
 for(i=0;i<F;i++){
   //   printf("%d",b[i][i]);
   //printf("==\n");
  if(b[i][i]==1){
    //printf("baka");
     //   exit(1);
     flg++;
  } 
 }
 count=0;
 for(i=0;i<n;i++){
   for(j=0;j<n;j++){
     if(b[i][j]==0 && i!=j)
       count++;
   }   
 }
  
 //
 if(flg==F && count==F*F-F){
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      printf("%d",cl[i][j]);
      dd[j]=cl[i][j];
    }
  
    printf("\n");
  }
  

  //exit(1);
  for(i=0;i<n;i++){
    for(j=0;j<F;j++){
      printf("%d,",inv_a[i][j]);
      dd[j]=inv_a[i][j];
    }
    printf("\n");
  }
 
  for(i=0;i<n;i++){
    for(j=0;j<F;j++)
      printf("%d, ",b[i][j]);
    printf("\n");
  }
  //  exit(1);   
 }
  
 //  }
  /*
  fq=fopen("S.key","wb");
  for(i=0;i<n;i++){
    for(j=0;j<n;j++)
      dd[j]=cl[i][j];
    fwrite(dd,1,n,fq);
    
  }
  fclose(fq);
  
  fq=fopen("inv_S.key","wb");
  for(i=0;i<n;i++){
    for(j=0;j<n;j++)
      dd[j]=inv_a[i][j];
    fwrite(dd,1,n,fq);  
  }
  fclose(fq);
  */
  
}

