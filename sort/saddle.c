#include <stdio.h>
#include <stdlib.h>
#define M  4
#define N  5
void saddle(int A[][N],int n,int m){
	int i,j,k,l;
	int min,max;
	int flag=0;
  for( i = 0; i < m ;i++){
     for( j = 0; j < n; j++){
         min = A[i][j];
         for( k = 0 ;k < n; k++){
          if( min > A[i][k])
           break;
         }
         if( k == n){
         max = A[i][j];
         for( l = 0; l < m; l++){
           if( max < A[l][j])
            break;
         }
         if( l == n){
            printf("location( %d,%d ) : %d \n",i+1 , j+1 ,A[i][j]);
            flag = 1;
         }
        }
     }
  }
  if( flag == 0)
     printf("not find saddle point here !\n");
}
int main(void){
	int A[M ][N ]={6, 2, 9, 2, 3,
	               4, 3, 5, 4, 2,
                       9 ,6, 8, 6, 9,
	               2 ,0 ,4 ,5 ,6};
	saddle( A ,M ,N );
	return 0;
}
