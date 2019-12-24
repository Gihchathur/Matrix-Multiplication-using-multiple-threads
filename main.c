#include<stdio.h>
#include<pthread.h> 
#include<unistd.h> 
 #include <stdlib.h>
#include<time.h>


int MAX=100;



void *mult(void* arg) 
{ 
    int *data = (int *)arg; 
    int k = 0, i = 0; 
      
    int x = data[0]; 
    for (i = 1; i <= x; i++) 
           k += data[i]*data[i+x]; 
      
    int *p = (int*)malloc(sizeof(int)); 
         *p = k; 
      
//Used to terminate a thread and the return value is passed as a pointer 
    pthread_exit(p); 
} ;

void Threadmultification(int matA[MAX][MAX],int matB[MAX][MAX],int matC[MAX][MAX],int m1, int n1, int m2, int n2)
{

      
    int r1=m1,c1=n1,r2=m2,c2=n2,i,j,k; 
  
  
      
      
    int max = m1*n2; 
      
      
    //declaring array of threads of size m1*n2         
    pthread_t *threads; 
    threads = (pthread_t*)malloc(max*sizeof(pthread_t)); 
      
    int count = 0; 
    int* data = NULL; 
    for (i = 0; i < m1; i++) 
        for (j = 0; j < n2; j++) 
               { 
                 
               //storing row and column elements in data  
            data = (int *)malloc((20)*sizeof(int)); 
            data[0] = n1; 
      
            for (k = 0; k < n1; k++) 
                data[k+1] = matA[i][k]; 
      
            for (k = 0; k < m2; k++) 
                data[k+c1+1] = matB[k][j]; 
               
             //creating threads 
                pthread_create(&threads[count++], NULL,  
                               mult, (void*)(data)); 
                  
                    } 
      
    
    for (i = 0; i < max; i++)  
    { 
      void *k; 
        
      //Joining all threads and collecting return value  
      pthread_join(threads[i], &k); 
             
            
          int *p = (int *)k; 
      printf("%d ",*p); 
      if ((i + 1) % n2 == 0) 
          printf("\n"); 
    } 
  
     

}





void Normalmultification(int matA[MAX][MAX],int matB[MAX][MAX],int matC[MAX][MAX],int m1, int n1, int m2, int n2)
{
	
		for (int i = 0; i < m1; i++)
			for (int j = 0; j < n2; j++)
                		matC[i][j]=0;

		printf("\n");
		for (int i = 0; i < m1; i++){
			for (int j = 0; j < n2; j++){
				for (int z = 0; z < n1; z++)
				{

				    matC[i][j]+=matA[i][z]*matB[z][j];


				}


			}
        }


        for (int i = 0; i < m1; i++) {
			for (int j = 0; j < n2; j++)
			{

				printf("%d ", matC[i][j]);
			}
			printf("\n");
		}

        


}






// Driver Code
int main()
{
int m, n, p, q, c, d, j,k,i,h,sum = 0;
clock_t t; 

	int matA[MAX][MAX];
	int matB[MAX][MAX];
	int matC[MAX][MAX];

//point_backToInput:


	int m1=5, m2=5, n1=5, n2=5;
	printf("Enter first matrix m1 : ");
	scanf("%d",&m1);
	printf("Enter first matrix n1 : ");
	scanf("%d", &n1);
	printf("Enter first matrix m2 : ");
	scanf("%d", &m2);
	printf("Enter first matrix n2 : ");
	scanf("%d", &n2);



	if (n1 == m2)
	{
		printf("\n\n\t1.fill the matrix with the values given in a file\n\t2.Random matrix  : ");
		int a;
		scanf("%d",&a);
		if(a==1)
		{
			FILE *file1 = fopen("file_1.txt","r");
           FILE *file2 = fopen("file_2.txt","r");

              printf("\nMatrix 1\n");
              for (c = 0; c < m1; c++){
              for (d = 0; d < n1; d++){

              fscanf(file1,"%d",&h);
              printf("%d ",h);
             matA[c][d] = h;
            }
             printf("\n");
          }

          fclose(file1);

             printf("\nMatrix 2\n");
             for (c = 0; c < m2; c++){
              for (d = 0; d < n2; d++){

              fscanf(file2,"%d",&h);
              printf("%d ",h);
              matB[c][d] = h;
            }
             printf("\n");
          }
           fclose(file2);


t = clock();
			printf("\nNORMAL MULTIFICATION RESULTANT MATRIX IS :- \n");
			Normalmultification(matA,matB,matC,m1,n1,m2,n2); 
			t = clock()-t;
			double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
  			printf("NORMAL MULTIFICATION took %f seconds to execute \n", time_taken); 
			
			t = clock();
			
			printf("\n\nTHREAD MULTIFICATION RESULTANT MATRIX IS :- \n"); 
			Threadmultification(matA,matB,matC,m1,n1,m2,n2);
			t = clock()-t;
			time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
  			printf("Thread multification took %f seconds to execute \n", time_taken);



			}	

		else if(a==2)
		{

			for (int i = 0; i < m1; i++) {
			for (int j = 0; j < n1; j++)
			{
				matA[i][j] = rand() % 10;
				printf("%d ", matA[i][j]);
			}
			printf("\n");
		}
       		 printf("\n");
		for (int i = 0; i < m2; i++) {

			for (int j = 0; j < n2; j++)
			{
				matB[i][j] = rand() % 10;
				printf("%d ", matB[i][j]);
			}
			printf("\n");
		}
			t = clock();
			printf("\nNORMAL MULTIFICATION RESULTANT MATRIX IS :- \n");
			Normalmultification(matA,matB,matC,m1,n1,m2,n2); 
			t = clock()-t;
			double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
  			printf("NORMAL MULTIFICATION took %f seconds to execute \n", time_taken); 
			
			t = clock();
			
			printf("\n\nTHREAD MULTIFICATION RESULTANT MATRIX IS :- \n"); 
			Threadmultification(matA,matB,matC,m1,n1,m2,n2);
			t = clock()-t;
			time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
  			printf("Thread multification took %f seconds to execute \n", time_taken);


		}
		else
		{
		
		}
		


	}
	else
	{
		//system("cls");
		printf( "!!! This matrix are not matched for multification !!!");
		//goto point_backToInput;

	}



	return 0;
}
