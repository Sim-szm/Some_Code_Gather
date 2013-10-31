#include <iostream>
#include <cstdlib>
void sift_heap(int *array,int ind,int len){
	int i=ind;
	int c=2*i+1;
	while(c<len){
		if(c+1<len&&array[c]<array[c+1]){
			c++;
		}
		if(array[i]>array[c]){
			break;
		}else{
			int tmp=array[i];
			array[i]=array[c];
			array[c]=tmp;
		}
		i=c;
		c=2*i+1;
	}
	return ;
}
void heap_sort(int *array,int count){
	for(int i=count/2;i>=0;i--){
		sift_heap(array,i,count);
	}
	for(int j=0;j<count;j++){
		int t=array[0];
		array[0]=array[count-j-1];
		array[count-j-1]=t;
		sift_heap(array,0,count-j-1);
	}
}
int main(int argc ,char *argv[]){
	int array[8]={4,6,2,1,3,7,8,5};
	int i=0;
	std::cout<<"堆排序效率：\n"<<std::cout<<"最差时间复杂度O(nlogn) \n最优时间复杂度 O(nlogn)\n平均时间复杂度(nlog n) \n最差空间复杂度O(n) total, O(1) auxiliary"<<std::endl;
	heap_sort(array,sizeof(array)/sizeof(*array));
	while(i<8){
		std::cout<<array[i]<<"   ";
		i++;
	}
	std::cout<<std::endl;
	return 0;
}
