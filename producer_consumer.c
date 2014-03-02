/*
 * =====================================================================================
 *
 *       Filename:  producer_consumer.c
 *        Version:  1.0
 *        Created:  2013年09月27日 10时12分10秒
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
#include <pthread.h>
#include <sys/types.h>
#define consumer_num 2
#define producer_num 8
typedef struct work{
	void *(*print_task)(void *arg);
	void *arg;
	struct work *next;
}Work_task;
typedef struct data{
	pthread_mutex_t mutex;
	pthread_cond_t awake;
	Work_task *task_head;
	int current_work_num;
	pthread_t *thread_link;
	pthread_t *creat;
	int flag;
}mutex_area;

static mutex_area *point=NULL;

void *print_task(void *arg){
	printf("consumer thread %lu print value: ' %d ' \n",pthread_self(),*(int*)arg);
	sleep(1);
	return NULL;
}
static inline void __INIT_AREA( ){
	point=(mutex_area*)malloc(sizeof(mutex_area));
	point->current_work_num=0;
	pthread_mutex_init(&(point->mutex),NULL);
	pthread_cond_init(&(point->awake),NULL);
	point->task_head=NULL;
	point->flag=0;
	point->creat=(pthread_t *)malloc(sizeof(pthread_t)*producer_num);
	point->thread_link=(pthread_t *)malloc(sizeof(pthread_t)*consumer_num);
}
void *producer_thread(void *arg){
	printf("this is producer thread :%lu ,set value: ' %d '\n",pthread_self(),*(int *)arg);
	Work_task *new_work=(Work_task*)malloc(sizeof(Work_task));
	new_work->next=NULL;
	new_work->arg=arg;
	new_work->print_task=print_task;
	pthread_mutex_lock(&(point->mutex));
	Work_task *start=point->task_head;
	if(start!=NULL){
		while(start->next!=NULL)
		      start=start->next;
		start->next=new_work;
	}else{
		point->task_head=new_work;
	}
	assert(point->task_head!=NULL);
	point->current_work_num++;
	pthread_mutex_unlock(&(point->mutex));
	pthread_cond_signal(&(point->awake));
	pthread_exit(NULL);
}
void *consumer_thread(void *arg){
	printf("this is consumer thread : %lu \n",pthread_self());
	while(1){
		pthread_mutex_lock(&(point->mutex));
		while(point->current_work_num==0&&!point->flag){
			pthread_cond_wait(&(point->awake),&(point->mutex));
		}
		if(point->flag){
			pthread_mutex_unlock(&(point->mutex));
			pthread_exit(NULL);
		}
		assert(point->current_work_num!=0);
		assert(point->task_head!=NULL);
		point->current_work_num--;
		Work_task* work=point->task_head;
		point->task_head=work->next;
		pthread_mutex_unlock(&(point->mutex));
		(*(work->print_task))(work->arg);
		free(work);
		work=NULL;
	}
	pthread_exit(NULL);
}
static inline void __DESTORY_AREA(){
	int num;
	point->flag=1;
	pthread_cond_broadcast(&(point->awake));
	for(num=0;num<consumer_num;num++){
		pthread_join(point->thread_link[num],NULL);
	}
	free(point->thread_link);
	free(point->creat);
	pthread_cond_destroy(&(point->awake));
	pthread_mutex_destroy(&(point->mutex));
	Work_task *wel=NULL;
	while(point->task_head!=NULL){
		wel=point->task_head;
		point->task_head=point->task_head->next;
		free(wel);
	}
	free(point);
	point=NULL;
}
int main(int argc, char *argv[]){
	int loop;
	__INIT_AREA();
	int *id=(int *)malloc(sizeof(int)*producer_num);
	for(loop=0;loop<producer_num;loop++){
		id[loop]=loop;
		pthread_create(&(point->creat[loop]),NULL,producer_thread,&id[loop]);
	}
	for(loop=0;loop<consumer_num;loop++){
		pthread_create(&(point->thread_link[loop]),NULL,consumer_thread,NULL);
	}
	sleep(5);
	__DESTORY_AREA();
	free(id);
	return 0;
}

