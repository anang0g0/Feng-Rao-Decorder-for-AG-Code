#include <stdio.h>
#define N 64


static int gf[N] = 
  {0, 1, 2, 4, 8, 16, 32, 3, 6, 12, 24, 48, 35, 5, 10, 20, 40, 19, 38, 15, 
   30, 60, 59, 53, 41, 17, 34, 7, 14, 28, 56, 51, 37, 9, 18, 36, 11, 22, 44, 
   27, 54, 47, 29, 58, 55, 45, 25, 50, 39, 13, 26, 52, 43, 21, 42, 23, 46, 
   31, 62, 63, 61, 57, 49, 33};

//unsigned char gf[N]={0,1,2,4,8,9,11,15,7,14,5,10,13,3,6,12};
//unsigned char fg[N]={0,1,2,13,3,10,14,8,4,5,11,6,15,12,9,7};

//unsigned char gf[N]={0,1,2,4,5,7,3,6};
//unsigned char fg[8]={0,1,2,6,3,4,7,5};

int count=0,l[3][113],b[16][113],ml[10][10],i0=0,i1=0,i2=0,i3=0,i4=0,i5=0,i6=0,i7=0,i8=0,i9=0,id[10];





int f1bin(int x,int y,int z)
{
int i,j,k,h,f1,f2,f3,f4,f5;


	 f1=gf[y];
	 f2=gf[mlt(y,y)];
	 f3=gf[mlt(mlt(y,y),y)];
	 f4=gf[mlt(mlt(x,x),x)];
	 f5=gf[mlt(mlt(y,x),mlt(x,x))];
/*
	 f1=gf[mlt(mlt(y,z),mlt(z,z))];
	 f2=gf[mlt(mlt(y,y),mlt(z,z))];
	 f3=gf[mlt(mlt(y,y),mlt(y,z))];
	 f4=gf[mlt(mlt(x,x),mlt(x,z))];
	 f5=gf[mlt(mlt(y,x),mlt(x,x))];
*/
if((f1^f2^f3^f4^f5)==0)
{
/* chkmlp(x,y,z);
l[0][count]=x;
l[1][count]=y;
l[2][count]=z;
count++;
*/
 base(x,y,z); 
	 printf("%d %d %d\n",x,y,z); 
}

}


int f2bin(int x,int y,int z)
{
int i,j,k,f1,f2,f3,f4,f5,f6,f7,add(),mlt(),div(),c,h;

	 f1=gf[y];
	 f2=gf[mlt(y,y)];
	 f3=gf[mlt(x,y)];
	 f4=gf[mlt(mlt(y,y),y)];
	 f5=gf[mlt(mlt(y,y),x)];
	 f6=gf[mlt(mlt(x,x),x)];
	 f7=gf[mlt(mlt(x,y),mlt(y,y))];

if((f1^f2^f3^f4^f5^f6^f7)==0)
printf("%d %d\n",gf[x],gf[y]);

}


int f3bin(int x,int y,int z)
{
int i,j,k,f1,f2,f3,f4,f5,add(),mlt(),div(),c,h;


	 f1=gf[mltn(4,z)];
	 f2=gf[mlt(mltn(3,y),x)];
	 f3=gf[mlt(mltn(3,x),z)];

if((f1^f2^f3)==0){
printf("%d %d %d\n",x,y,z);
base(x,y);
}

}


int f4bin(int x,int y,int z)
{
int i,j,k,f1,f2,f3,f4,f5,add(),mlt(),div(),c,h;


	 f1=gf[mlt(mlt(z,z),mlt(z,z))];
	 f2=gf[mlt(mlt(x,x),mlt(z,z))];
	 f3=gf[mlt(mlt(x,x),mlt(x,z))];
	 f4=gf[mlt(mlt(x,y),mlt(y,y))];

if((f1^f2^f3^f4)==0){
chkmlp(x,y,z);
l[0][count]=x;
l[1][count]=y;
l[2][count++]=z;

 printf("%d %d %d\n",gf[x],gf[y],gf[z]); 
}

}

int sc(int x,int y){
	int i,j,k,f1,f2,f3,f4;

	f1=gf[mlt(mltn(3,x),mltn(2,y))];
	f2=gf[mlt(mltn(2,x),mltn(4,y))];
	f3=gf[y];
	f4=gf[mltn(4,x)];

	if((f1^f2^f3^f4)==0){
l[0][count]=x;
l[1][count++]=y;

printf("%d %d\n",gf[x],gf[y]);
}

}

int hl(int x,int y,int z){
int f1,f2,f3;

 f1=gf[mltn(5,x)];
 f2=gf[mltn(5,y)];
 f3=gf[mltn(5,z)];
 if((f1^f2^f3)==0)
   count++;

}



int base(int x,int y,int z)
{

b[0][count]=1;
b[1][count]=div(y,add(y,z)); /* i+j=1 */
b[2][count]=div(z,add(y,z));
b[3][count]=mlt(b[1][count],b[2][count]); /* i+j=2 */
b[4][count]=mlt(b[1][count],b[1][count]);
b[5][count]=mlt(b[2][count],b[2][count]);
b[6][count]=mlt(b[1][count],b[5][count]); /* i+j=3 */
b[7][count]=mlt(b[4][count],b[2][count]);
b[8][count]=mlt(b[1][count],b[4][count]);
b[9][count]=mlt(b[2][count],b[5][count]);
b[10][count]=mlt(b[2][count],b[8][count]); /* i+j=4 */
b[11][count]=mlt(b[1][count],b[9][count]);
b[12][count]=mlt(b[4][count],b[5][count]);
b[13][count]=mlt(b[4][count],b[4][count]);
b[14][count]=mlt(b[5][count],b[5][count]);
b[15][count]=mlt(b[4][count],b[9][count]); /* i+j=5 */
count++;

}


int chkmlp(int x,int y,int z)
{
int *mp;

	if(x==0)
	ml[0][i0++]=count;

	if(y==0)
	ml[1][i1++]=count;

	if(z==0)
	ml[2][i2++]=count;

	if(add(x,y)==0)
	ml[3][i3++]=count;

	if(add(x,z)==0)
	ml[4][i4++]=count;

	if(add(y,z)==0)
	ml[5][i5++]=count;

	if(add(x,add(y,z))==0)
	ml[6][i6++]=count;

	if(add(mlt(x,x),mlt(y,z))==0)
	ml[7][i7++]=count;

	if(add(mlt(y,y),mlt(x,z))==0)
	ml[8][i8++]=count;

	if(add(mlt(z,z),mlt(x,y))==0)
	ml[9][i9++]=count;

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

/* GF(16)��ł̏��Z */
int div(int x,int y)
{
    if(y==0){
        printf("***�ُ픭���I �O�ŏ��Z***\n");
return -1;
        /* exit(1); */
    }
    else if(x==0){
        return 0;
    }
    return ((x-y+(N-1))%(N-1))+1;
}


int mltn(int n,int x)
{
int i,j;

i=x;
for(j=1;j<n;j++)
i=mlt(i,x);

return i;

}



main(){
int x,y,z,e,n,ii,jj;

 count=0;
 
x=0;y=1;z=0;
f4bin(x,y,z);


z=0;x=1;
for(y=0;y<N;y++)
f4bin(x,y,z);
 

z=1;
for(x=0;x<N;x++){
  for(y=0;y<N;y++)
    f4bin(x,y,z);
}
printf("count=%d\n",count);

exit(1);


/*
id[0]=i0;id[1]=i1;id[2]=i2;id[3]=i3;id[4]=i4;id[5]=i5;id[6]=i6;id[7]=i7;id[8]=i8;id[9]=i9;

for(ii=0;ii<10;ii++){
printf("id=%d\n",id[ii]);
	for(jj=0;jj<id[ii];jj++)
	printf("%d %d %d\n",gf[l[0][ml[ii][jj]]],gf[l[1][ml[ii][jj]]],gf[l[2][ml[ii][jj]]]);
	 printf("%d %d %d\n",ml[ii][jj],ml[ii][jj],ml[ii][jj]); 

printf("\n");
}


printf("points\n");
for(n=0;n<3;n++){
	for(e=0;e<113;e++){
	printf("%d ",gf[l[n][e]]);

}
printf("\n");
}
*/

printf("gem\n");
for(n=0;n<15;n++){
	for(e=0;e<112;e++)
	printf("%d ",b[n][e]);

printf("\n");
}
/*
printf("binary\n");
for(n=0;n<10;n++){
	for(e=0;e<112;e++)
	printf("%b ",b[n][e]);

printf("\n");
}
*/

}
