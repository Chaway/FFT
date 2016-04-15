#include <stdio.h>
#include <math.h>
#define T (2*M_PI)
#define N 64

double data[N];
double result[2][N];
double W[2][N];


void merge(int L,int n,int order)
{
  double re1,im1,re2,im2;
  int start = order * L;
//  printf("n = %d;order = %d\n",n,order);
  for(int i = 0;i < L/2 ; i++)
  {
     re1 = result[0][start + i] + result[0][start + i + L/2] * W[0][i << n] + result[1][start + i + L/2] * W[1][i << n];
     im1 = result[1][start + i] - result[0][start + i + L/2] * W[1][i << n] + result[1][start + i + L/2] * W[0][i << n];
     re2 = result[0][start + i] - result[0][start + i + L/2] * W[0][i << n] - result[1][start + i + L/2] * W[1][i << n];
     im2 = result[1][start + i] + result[0][start + i + L/2] * W[1][i << n] - result[1][start + i + L/2] * W[0][i << n];
     result[0][start + i] = re1;
     result[1][start + i] = im1;
     result[0][start + i + L/2] = re2;
     result[1][start + i + L/2] = im2;
  }

}


void fft(int first_index,int L,int n ,int order)
{
	if(L == 2)
	{   
  //          printf("n = %d;order = %d\n",n,order);
            result[0][2*order] = data[first_index] + data[first_index + N/2];
	    result[0][2*order + 1] = data[first_index] - data[first_index + N/2];
 //	    printf(" result[0][%d] =  %lf\n" , order,result[0][order]);
 //	    printf(" result[1][%d] =  %lf\n" , order,result[1][order]);

	}
	else
	{
            fft(first_index,L/2,n + 1,order << 1);
            fft(first_index + (1 << n), L/2 , n + 1 , (order << 1) + 1);
	    merge(L,n,order);
	}
}


void main()
{
   double  dt = T / N ;
   for(int index = 0 ;index < N; index ++)
   {
      data[index] = cos(index*dt) + 0.5*cos(2*index*dt) + 0.8*cos(5*index*dt);
   //   printf("data[%d] = %lf\n",index,data[index]);
   }
  
   for(int index = 0;index < N/2; index ++)
   {
      W[0][index] = cos(2*M_PI*index/N);  
      W[1][index] = sin(2*M_PI*index/N);
 //     printf("W[0][%d] = %lf ,W[1][%d] = %lf\n",index,W[0][index],index,W[1][index]);
   }

   fft(0,N,0,0);

   for(int index = 0;index < N;index ++)
   {
     printf("X[%d] = %lf + j%lf\n",index,result[0][index],result[1][index]);
   }
}
