#include <stdio.h>
#include <stdlib.h>
#ifndef BUBBLE_SORT
#define BUBBLE_SORT
void Bubble_Sort(int *array,int count){
	int i=count,j=0,temp=0;
	while(i>0){
		for(j=0;j<i-1;j++){
			if(array[j]>array[j+1]){
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
			}
		}
		i--;
	}
}
#endif
int main(int argc,char *argv[]){
	int array[5]={2,1,5,4,3};
	int i=0;
	printf("冒泡排序效率：\n");
	printf("时间复杂度：O(n^2)\n空间复杂度：O(n)\n");
	Bubble_Sort(array,5);
	while(i<5){
		printf("%4d",array[i]);
		i++;
	}
	printf("\n");
	return 0;
}
