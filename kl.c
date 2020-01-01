#include <stdio.h>

/* concatinated code golay[24,12,8]-klein[21,8,11]=[504,96,88] */

#define N 8


static int GF8[8] = {0, 1, 2, 4, 3, 6, 7, 5};
int count=0;
unsigned char bs[18][22];


/* klein code over GF(8) */



main(){
  int i,j,m;
  unsigned char x,y,z;
  

  //  scanf("%d",&m);
  /*
  if(m<2 || m>5){
    printf("1<m<6\n");
    exit(0);
  }
  */
z=1;
  for(x=0;x<N;x++){
    for(y=0;y<N;y++){
	if((GF8[mlt(mltn(3,x),y)]^GF8[mlt(mltn(3,y),z)]^GF8[mlt(x,mltn(3,z))])==0){
	 /* printf("%d %d %d\n",x,y,z); */
	  base(x,y,1,m); 
	  count++;
	}
      }
  }
printf("%d\n",count);

 exit(1);


 
  for(j=0;j<2*(m*2-1);j++){
    for(i=0;i<count;i++)
      printf("%u ",bs[j][i]);
    printf("\n");
  }
}



void base(int x,int y,int z,int m)
{

  
  
  switch(m){
  case 2:
    bs[0][count]=1;
    bs[1][count]=x;
    bs[2][count]=mlt(x,x);
    bs[3][count]=y;
    bs[4][count]=mlt(x,y);
    bs[5][count]=mlt(y,y);
    break;
    
  case 3:
    bs[0][count]=1;
    bs[1][count]=x;
    bs[2][count]=mlt(x,x);
    bs[3][count]=mltn(3,x);
    bs[4][count]=y;
    bs[5][count]=mlt(x,y);
    bs[6][count]=mlt(y,mltn(2,x));
    bs[7][count]=mlt(y,mltn(3,x));
    bs[8][count]=mlt(y,y);
    bs[9][count]=mlt(x,mltn(2,y));
    break;
    
  case 4:
    bs[0][count]=1;
    bs[1][count]=x;
    bs[2][count]=mlt(x,x);
    bs[3][count]=mltn(3,x);
    bs[4][count]=mltn(4,x);
    bs[5][count]=y;
    bs[6][count]=mlt(y,x);
    bs[7][count]=mlt(y,mltn(2,x));
    bs[8][count]=mlt(y,mltn(3,x));
    bs[9][count]=mlt(y,mltn(4,x));
    bs[10][count]=mlt(y,y);
    bs[11][count]=mlt(bs[10][count],x);
    bs[12][count]=mlt(bs[10][count],mltn(2,x));
    bs[13][count]=mlt(bs[10][count],mltn(3,x));
  break;
  
  case 5:
   bs[0][count]=1;
    bs[1][count]=x;
    bs[2][count]=mlt(x,x);
    bs[3][count]=mltn(3,x);
    bs[4][count]=mltn(4,x);
    bs[5][count]=mltn(5,x);
    bs[6][count]=y;
    bs[7][count]=mlt(x,y);
    bs[8][count]=mlt(y,mltn(2,x));
    bs[9][count]=mlt(y,mltn(3,x));
    bs[10][count]=mlt(y,mltn(4,x));
    bs[11][count]=mlt(y,mltn(5,x));
    bs[12][count]=mlt(y,mltn(6,x));
    bs[13][count]=mlt(y,y);
    bs[14][count]=mlt(bs[13][count],x);
    bs[15][count]=mlt(bs[13][count],mltn(2,x));
    bs[16][count]=mlt(bs[13][count],mltn(3,x));
    bs[17][count]=mlt(bs[13][count],mltn(4,x));
  }
  
}



/* 有限体上での掛け算 */
int mlt(int x,int y)
{
    if(x==0||y==0){
        return(0);
    }
    return ((x+y-2)%(N-1))+1;
}


/* 有限体上での累乗 */
int mltn(int n,int x)
{
int i,j;

i=x;
for(j=1;j<n;j++)
i=mlt(i,x);

return i;

}
