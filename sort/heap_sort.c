/*
 * =====================================================================================
 *
 *       Filename:  heap_sort.c
 *        Version:  1.0
 *        Created:  2014年03月22日 14时39分44秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define left(i) ((2*(i))+1)
#define right(i) ((2*(i))+2)

void swap(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}
void max_heapify(int array[],int index,int heap_size){
	int l=left(index);
	int r=right(index);
	int largest,temp;
	if(l<heap_size&&array[l]>array[index])
	      largest=l;
	else
	      largest=index;
	if(r<heap_size&&array[r]>array[largest])
	      largest=r;
	if(largest!=index){
		swap(&array[largest],&array[index]);
		max_heapify(array,largest,heap_size);
	}

}
void build_max_heap(int array[],int heap_size){
	int index;
	for( index=(heap_size-2)/2;index>=0;index--){
		max_heapify(array,index,heap_size);
	}
}
void print(int array[],int heap_size){
	int index;
	for(index=0;index<heap_size;index++){
		printf("%d ",array[index]);
	}
	printf("\n");
}
void heap_sort(int array[],int heap_size){
	int i;
	build_max_heap(array,heap_size);
	for(i=heap_size-1;i>=0;i--){
		swap(&array[0],&array[i]);
		max_heapify(array,0,i);
	}
	print(array,heap_size);
}
int main(int argc, char *argv[]){
	int heap_size=11;
	int array[]={4,6,3,13,12,1,9,10,11,2,5};
	heap_sort(array,heap_size);
	return EXIT_SUCCESS;
}

