/*
 * =====================================================================================
 *
 *       Filename:  List_Test.c
 *        Version:  1.0
 *        Created:  2013年09月16日 10时44分23秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include "list.h"
#define fina_num 26
typedef struct data_base{
	int m_number;
	char m_char;
	struct list_head list;
}DATA_BASE;
static inline void __INIT_VALUE(struct list_head *head){
	int id=1;
	char chr='a';
	DATA_BASE *p;
	DATA_BASE *info=(DATA_BASE*)malloc(sizeof(DATA_BASE));
	info->m_number=1;
	info->m_char=chr;
	INIT_LIST_HEAD(&(info->list));
	printf("********** Init List Value *********** !\n");
	INIT_LIST_HEAD(head);
	list_add_tail(&(info->list),head);
	while(id<fina_num){
		chr++;
		id++;
		p=(DATA_BASE*)malloc(sizeof(DATA_BASE));
		p->m_char=chr;
		p->m_number=id;
		INIT_LIST_HEAD(&(p->list));
		list_add_tail(&(p->list),head);
	}
}
static inline void __FOR_EACH(struct list_head *pos,struct list_head *head){
	DATA_BASE *pop;
	list_for_each(pos,head){
		pop=list_entry(pos,DATA_BASE,list);
		printf("id = %d  :  value = '%c'\n",pop->m_number,pop->m_char);
	}
}
static inline void __DEL_DATA(struct list_head *head,int del_num){
	DATA_BASE *pop;
	printf("input del_num for delete element :\n");
	scanf("%d",&del_num);
	printf("********** Print List Value After delete del_num *********** \n");
	list_for_each_entry(pop,head,list){
		if(pop->m_number==del_num){
			list_del_rcu(&(pop->list));
		}
	}
}
static inline void __ADD_DATA(struct list_head *head){
	DATA_BASE *element=(DATA_BASE*)malloc(sizeof(DATA_BASE));
	DATA_BASE *pop;
	printf("input add_elemnt's m_number :");
	scanf("%d",&element->m_number);
	printf("input add_element's m_char :");
	getchar();
	scanf("%c",&(element->m_char));
	getchar();
	INIT_LIST_HEAD(&(element->list));
	list_for_each_entry(pop,head,list){
		if(pop->m_number==(element->m_number-1)){
			break;
		}
	}
	list_add_rcu(&(element->list),&(pop->list));
}
int main(int argc, char *argv[]){
	int del_num;
	struct list_head *pos;
	struct list_head *head=(struct list_head*)malloc(sizeof(struct list_head));
	__INIT_VALUE(head);
	printf("********** Print List Value *********** \n");
	__FOR_EACH(pos,head);
	__DEL_DATA(head,del_num);
	__FOR_EACH(pos,head);
	printf("********** STart add elemrnt ! ************\n");
	__ADD_DATA(head);
	__FOR_EACH(pos,head);
	return 0;
}


























