/*
 * =====================================================================================
 *       Filename:  shell_sort.c
 *    Description:  
 *        Version:  
 *        Created:  2012年09月03日 18时15分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  szm , xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 5
#define SWAP( x,y) {int t; t = x; x = y; y = t;}
void shellsort( int *number) {

	int i, j, k, gap, t;
	gap = MAX / 2;
	while( gap > 0) {
            for( k = 0; k < gap; k++) {
               for( i = k+gap; i < MAX; i+=gap) {
		   for( j = i - gap; j >= k; j-=gap) {
			if( number[j] > number[j+gap]) {
			     SWAP( number[j], number[j+gap]);
			}
		        else
			  break;
	           }
               }
	    }
	    printf( "\ngap = %d:", gap);
	    for( i = 0; i < MAX; i++)
	    printf( "%d ", number[i]);
	    printf( "\n");
	    gap /= 2;
	}
}
int main( int argc, char *argv[]) {

    int number[MAX] = {5,3,4,1,2};
    int i;
    printf( "排序前:");
    for( i = 0; i < MAX; i++) {
	printf( "%d ", number[i]);
    }
    shellsort( number);
    return 0;
}



