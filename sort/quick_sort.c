#include <stdio.h>
#include <stdlib.h>
void quick_Sort(int *array,int mnd,int count){
	int i,j,key;
	if (mnd>=count)
		return ;
	i=mnd;j=count;key=array[i];
	while(i<j){
		while(i<j&&array[j]>key)
			j--;
		if(i<j)
			array[i++]=array[j];
		while(i<j&&array[i]<key)
			i++;
		if(i<j)
			array[j--]=array[i];
	}
	array[i]=key;
	if(mnd<i-1)
		quick_Sort(array,mnd,i-1);
	if(i+1<count)
		quick_Sort(array,i+1,count);
}
int main(int argc, char *argv[]){
	int array[5]={2,4,3,1,5};
	int i=0;
	printf("快速排序效率：\n");
	printf("最差时间复杂度O(n^2)\n最优时间复杂度O(nlog n)\n平均时间复杂度O(nlog n)\n");
	quick_Sort(array,0,5-1);
	while(i<5){
		printf("%4d",array[i]);
		i++;
	}
	printf("\n");
	return 0;
}
