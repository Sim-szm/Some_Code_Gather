#include <stdio.h>
#include <stdlib.h>
void Merge_Sort(int *array, int count){
                   /*非递归做法--迭代算法,
         	    将序列每相邻两个数字进行归并操作，形成floor(n/2)个序列，排序后每个序列包含两个元素
	            将上述序列再次归并，形成floor(n/4)个序列，每个序列包含四个元素重复步骤2，直到所有元素排序完毕
		    */
	int i,left_min,left_max,right_min,right_max,next;
	int *tmp=(int *)malloc(sizeof(int)*count);
	if(NULL==tmp){
		printf("Out of memory !");
		abort();
	}
	for(i=1;i<count;i*=2){
		for(left_min=0;left_min<count-i;left_min=right_max){
			left_max=right_min=left_min+i;
			right_max=left_max+i;	
			if(right_max>count)
				right_max=count;
			next=0;
			while (left_min < left_max && right_min < right_max)
                                tmp[next++] = array[left_min] > array[right_min] ? array[right_min++] : array[left_min++];
                        while (left_min < left_max)
                                array[--right_min] = array[--left_max];
                        while (next > 0)
                                array[--right_min] = tmp[--next];
		}
	}
}
void merge_sort(int *array,unsigned int first,unsigned int last){
	int mid=0;     /* 递归做法*/
	if(first<last){
		mid=(first&last)+((first^last)>>1);
		merge_sort(array,first,mid);
		merge_sort(array,mid,last);
	}
}
int main(int argc,char *argv[]){
	int array[5]={2,1,5,3,4};
	int i=0;
	printf("归并排序效率：\n");
	printf("时间复杂度：O(nlogn)\n空间复杂度：O(n)\n");
	Merge_Sort(array,5);
	while(i<5){
		printf("%4d",array[i]);
		i++;
	}
	printf("\n");
	return 0;
}
