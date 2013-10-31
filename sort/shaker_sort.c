/*
 * =====================================================================================
 *       Filename:  shaker.c
 *    Description:  
 *        Version:  
 *        Created:  2012年09月03日 18时45分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  szm , xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 * =====================================================================================
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#define MAX 10
#define SWAP(x,y) {int t; t = x; x = y; y = t;} 
void shakerSort(int *number) {               /*双向冒泡排序*/ 
    int left = 0, right = MAX - 1, shift = 0; 
    while(left < right) { 
        // 向左進行冒泡排序 
        int i;
        for(i = left; i < right; i++) { 
            if(number[i] > number[i+1]) { 
                SWAP(number[i], number[i+1]); 
                shift = i; 
            } 
        } 
        right = shift; 
        // 向右進行冒泡排序 
        int k;
        for(k = right; k > left; k--) { 
            if(number[k] < number[k-1]) { 
                SWAP(number[k], number[k-1]); 
                shift = k; 
            } 
        } 
        left = shift; 
    } 
} 
int main(int argc ,char *argv[]) { 
    int number[10]={3,6,2,1,7,9,0,8,5,4};
    printf("排序前："); 
    int i;  
    for(i = 0; i < MAX; i++) { 
        printf("%d ", number[i]); 
    } 
    shakerSort(number); 
    printf("\n排序後："); 
    for(i = 0; i < MAX; i++) { 
        printf("%d ", number[i]); 
    } 
    printf("\n");
    return 0; 
} 


