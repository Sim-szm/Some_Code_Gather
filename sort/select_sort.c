#include <stdio.h>
#include <stdlib.h>
void select_Sort(int *array,int count){
	int i,j,max,temp;
	for(i=0;i<count-1;i++){
		max=i;
		for(j=i+1;j<count;j++){
			if(array[max]>array[j]){
				max=j;
			}
		}
		if(max!=i){
			temp=array[max];
			array[max]=array[i];
			array[i]=temp;
		}
	}
}
int main(int argc,char *argv[]){
	int array[5]={2,4,5,1,3};
	int i=0;
	select_Sort(array,5);
        printf("选择排序效率：\n");
	printf("时间复杂度：O(n^2)\n空间复杂度：O(n)\n");
	while(i<5){
		printf("%4d",array[i]);
		i++;
	}
	printf("\n");
	return 0;
}
