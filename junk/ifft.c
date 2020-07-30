#include <stdio.h>
#include <math.h>
 
#define pi 3.1415926535         // 円周率

 // 離散フーリエ変換（読み込むファイル名, 書き込むファイル名）
int dft(char filename1[], char filename2[])
{  
        int i, k, n, N;
        int max = 100000;  // 読み込むデータ数の上限
        double Re[max+1], Im[max+1], re, im;

        FILE *fp1, *fp2;
    // ファイルオープン(フーリエ変換したいデータファイル, フーリエ変換後のデータ保存用ファイル)
        if((fp1=fopen(filename1,"r"))==NULL){
                printf("FILE1 not open\n");
        return -1;
        }
        if((fp2=fopen(filename2,"w"))==NULL){
                printf("FILE2 not open\n");
        return -1;
        }
        //データの読み込み
        for(N=0;N<max;N++) {
                if(fscanf(fp1,"%d, %lf, %lf", &i, &Re[N], &Im[N]) == EOF) {
                        N--;
                        break;
                }
        }
        //実数部分と虚数部分に分けてフーリエ変換
        for(k=0; k<N; k++) {
                double re = 0.0;
                double im = 0.0;
                for(n=0; n<N; n++) {
                        re += (Re[n]*cos(2*pi*k*n/N)-Im[n]*sin(2*pi*k*n/N))/N;
                        im += (Re[n]*sin(2*pi*k*n/N)+Im[n]*cos(2*pi*k*n/N))/N; 
                }
                fprintf(fp2,"%d, %f, %f\n", k, re, im);
        }
        fclose(fp1);
        fclose(fp2);
        return 0;
}

int main()
{
        // 離散フーリエ変換
        dft("fourier.csv", "inv_fourier.csv");
}
