#include <stdio.h>
//#include "gf256.h"

/* GF(256)��� �ȉ~�Ȑ��S �̗L���_���v�Z����.

   y^2+xy=x^3+1 or y^2+xy=x^3+x^2+1;

*/

#define N 64

//unsigned short gf[8]={0,1,2,4,3,6,7,5};
//unsigned short fg[8]={0,1,2,4,3,7,5,6};

unsigned char gf[64]={0,1,2,4,8,16,32,33,35,39,47,63,31,62,29,58,21,42,53,11,22,44,57,19,38,45,59,23,46,61,27,54,13,26,52,9,18,36,41,51,7,14,28,56,17,34,37,43,55,15,30,60,25,50,5,10,20,40,49,3,6,12,24,48};
unsigned char fg[64]={0,1,2,59,3,54,60,40,4,35,55,19,61,32,41,49,5,44,36,23,56,16,20,27,62,52,33,30,42,14,50,12,6,7,45,8,37,46,24,9,57,38,17,47,21,25,28,10,63,58,53,39,34,18,31,48,43,22,15,26,51,29,13,11};


int bin(),lx[289],ly[289],lz[289],k,count=0;

main(){
int x,y,z,f[289][8],l;

k=0;

x=0;y=1;z=0;
bin(x,y,z);

z=0;x=1;
for(y=0;y<N;y++)
bin(x,y,z);

z=1;
for(x=0;x<N;x++){
	for(y=0;y<N;y++)
	bin(x,y,z);
}

 printf("count=%d\n",count);
/*
f[0][0]=0;
for(k=0;k<289;k++){
f[k][0]=1;
f[k][1]=lx[k];
f[k][2]=mlt(lx[k],lx[k]);
f[k][3]=mlt(f[k][2],lx[k]);
f[k][4]=mlt(f[k][2],f[k][2]);
f[k][5]=ly[k];
f[k][6]=mlt(ly[k],lx[k]);
f[k][7]=mlt(ly[k],f[k][2]);
}


for(l=0;l<8;l++){
	for(k=0;k<289;k++)
	printf("%b ",gf8192[f[k][l]]);

printf("\n");
}
*/
printf("%d\n",k);
}





bin(int x,int y,int z)
{
  int i,j,f1,f2,f3,f4,f5,add(),mlt(),div();
  int a,b,p=0;
  int fnc,xx;
  
  
     f1=gf[mlt(mlt(x,x),mlt(y,x))];
     f2=gf[mlt(mlt(y,y),mlt(y,z))];
     f3=gf[mlt(mlt(y,y),mlt(z,z))];
     f4=gf[mlt(mlt(z,z),mlt(z,z))];
     
  
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
  
  if((f1^f2^f3^f4)==0){
    count++; 	
    printf("%d %d %d\n",x,y,z);
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
    //printf("a= %d b= %d : (%d,%d)\n",a,b,xx,fnc); /* intersection */

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


}



int add(int x,int y)
{
    int z;


    if(x==0){
        return(y);
    }
    else if(y==0){
        return(x);
    }
    else if(x > y){
        z=(gf[x-y+1]-1)+(y-1);
        z=(z%(N-1))+1;
    }
    else if(x < y){
        z=(gf[y-x+1]-1)+x-1;
        z=(z%(N-1))+1;
    }
    else{
        z=0;
    }
    return(z);
}



/* GF(N)��ł̏�Z */
int mlt(int x,int y)
{
    if(x==0||y==0){
        return(0);
    }
    return ((x+y-2)%(N-1))+1;
}



/* GF(N)��ł̏��Z */
int div(int x,int y)
{
    if(y==0){
        printf("***�ُ픭���I �O�ŏ��Z***\n");
        exit(1);
    }
    else if(x==0){
        return 0;
    }
    return ((x-y+15)%15)+1;
  }


int mltn(int n,int x)
{
  int i,j;
  
  i=x;
  for(j=1;j<n;j++)
    i=mlt(i,x);
  
  return i;
  
}


/* 
* MOV reduction; if weil pairing comptation is difficult then we use ideas developed by GMR.  
* hyperelliptic supersinguler curves
*/
void weil()
{






}
