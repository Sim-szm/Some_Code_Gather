#include <stdio.h>
#include <stdlib.h>
void insert_Sort(int *array,int first,int count){
	int i,j,temp;
	for(i=first+1;i<count;i++){
		temp=array[i];
		j=i-1;
		while((j>=first)&&(array[j]>temp)){
			array[j+1]=array[j];
			j--;
		}
		array[j+1]=temp;
	}
}
int main(int argc,char *argv[]){
	int array[5]={2,1,5,3,4};
	int i=0;
	insert_Sort(array,0,5);
	printf("插入排序效率：\n");
	printf("时间复杂度：O(n^2)\n空间复杂度：O(n)\n需要额外空间O(1)\n");
	while(i<5){
		printf("%4d",array[i]);
		i++;
	}
	printf("\n");
	return 0;
}
