#include <stdio.h>
#define N 64

/*X^9+Y^9+Z^9=0*/
static int c[N] = 
  {0, 1, 2, 4, 8, 16, 32, 3, 6, 12, 24, 48, 35, 5, 10, 20, 40, 19, 38, 15, 
   30, 60, 59, 53, 41, 17, 34, 7, 14, 28, 56, 51, 37, 9, 18, 36, 11, 22, 44, 
   27, 54, 47, 29, 58, 55, 45, 25, 50, 39, 13, 26, 52, 43, 21, 42, 23, 46, 
   31, 62, 63, 61, 57, 49, 33};


int bin(),k,lx[513],ly[513],lz[513],mlt();

main(){
  int x,y,z,d[513][16],l;

  k=0;
  z=0;x=0;y=1;
  bin(x,y,z);

  z=0;x=1;
  for(y=0;y<N;y++)
    bin(x,y,z);
  

  z=1;
  for(x=0;x<N;x++){
    for(y=0;y<N;y++)
      bin(x,y,z);
  }

/*
for(k=0;k<513;k++){
d[k][0]=1;
d[k][1]=mlt(lx[k],lx[k]);
d[k][2]=mlt(lx[k],ly[k]);
d[k][3]=mlt(ly[k],ly[k]);
d[k][4]=mlt(lx[k],d[k][1]);
d[k][5]=mlt(d[k][1],ly[k]);
d[k][6]=mlt(lx[k],d[k][3]);
d[k][7]=mlt(ly[k],d[k][3]);
d[k][8]=mlt(d[k][1],d[k][1]);
d[k][9]=mlt(d[k][4],ly[k]);
d[k][10]=mlt(d[k][1],d[k][3]);
d[k][11]=mlt(d[k][2],d[k][3]);
d[k][12]=mlt(d[k][3],d[k][3]);
d[k][13]=mlt(d[k][8],lx[k]);
d[k][14]=mlt(d[k][8],ly[k]);
d[k][15]=mlt(d[k][4],d[k][3]);
}

for(l=0;l<16;l++){
	for(k=0;k<513;k++)
	printf("%b ",c[d[k][l]]);

printf("\n");
}
*/

}



bin(int x,int y,int z)
{
  int i,j,f1,f2,f3,h;

  f1=c[mlt(mlt(mlt(mlt(x,x),mlt(x,x)),mlt(mlt(x,x),mlt(x,x))),x)];
  f2=c[mlt(mlt(mlt(mlt(y,y),mlt(y,y)),mlt(mlt(y,y),mlt(y,y))),y)];
  f3=c[mlt(mlt(mlt(mlt(z,z),mlt(z,z)),mlt(mlt(z,z),mlt(z,z))),z)];
  

  if((f1^f2^f3)==0){
    lx[k]=x;
    ly[k]=y;
    lz[k]=z;
    k++;
    printf("%d %d %d ",c[x],c[y],c[z]); 
    printf("%d\n",k);
  }

}


int mlt(int x,int y)
{
  if(x==0 || y==0){
    return(0);
  }
  return((x+y-2)%(N-1))+1;
}


void mimier()
{
  static char *mime64[64]=
    {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R",
       "S","T","U","V","W","X","Y","Z",
       "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q",
       "r","s","t","u","v","w","x","y",
       "z","0","1","2","3","4","5","6","7","8","9","+","/"};
  unsigned int a;
  char *filename;
  int c,d[4];
  FILE *p,*q;
  int *buff,i;

  *p=fopen("rb",filename);
  *q=fopen("w","Output.txt");

  while(c!=EOF){
    c=fread(3,buff,p); /* 24-bit read */
    d[0]=struoul("111111000000000000000000",(char **)NULL,2);
    d[1]=strtoul("000000111111000000000000",(char **)NULL,2);
    d[2]=strtoul("000000000000111111000000",(char **)NULL,2);
    d[3]=strtoul("000000000000000000111111",(char **)NULL,2);
    d[0]=((d[0]&c)<<18);
    d[1]=((d[1]&c)<<12);
    d[2]=((d[2]&c)<<6);
    d[3]=( d[3]&c);
    
    for(i=0;i<4;i++)
      fwrite(mime64[d[i]],q);
  }

  fclose(*p);

}

