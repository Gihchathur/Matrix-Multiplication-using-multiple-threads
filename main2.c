#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <pthread.h>

int n=10;

#define nthreads 4


int a[1000][1000],b[1000][1000],c[1000][1000];

void *threadfun(void *arg) 
{
int *p=(int *)arg;
int i,j,k;
for(i=*p;i<(*p+(n/nthreads));i++)
for(j=0;j<n;j++)
for(k=0;k<n;k++)
c[i][j]=c[i][j]+a[i][k]*b[k][j];
}

int main()
{
clock_t t; 


for(n=10; n<1000; n+=10)
{
t = clock();

int i,j,k,r,rownos[nthreads];
pthread_t tid[nthreads];
for(i=0;i<n;i++){
for(j=0;j<n;j++){
a[i][j]=1;
b[i][j]=1;
}}

for(i=0;i<nthreads;i++)
{
rownos[i]=i*(n/nthreads);
pthread_create(&tid[i],NULL,threadfun,&rownos[i]);
}
for(i=0;i<nthreads;i++)
pthread_join(tid[i],NULL);
for(i=0;i<n;i++)
{
for(j=0;j<n;j++)
{

}
}

t = clock()-t;
double time_taken = ((double)t)/CLOCKS_PER_SEC; 
printf("%f \n", time_taken*1000); 
}
}
