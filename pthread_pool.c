/*
 * =====================================================================================
 *
 *       Filename:  pthread_pool.c
 *        Version:  1.0
 *        Created:  2013年08月08日 13时45分15秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm ,xianszm007@gmail.com
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

typedef struct work_queue{
	void *(*task_process)(void *arg);
	void *arg;
	struct work_queue *next;
}Work_task;

typedef struct {
	pthread_cond_t  ready_event;
	pthread_mutex_t task_queue_lock;
	Work_task *task_head;
	pthread_t *threadid_link;
	int max_thread_num;
	int current_queue_size;
	int destory_flag;
}Thread_pool;

static Thread_pool *thread_pool=NULL;

void *thread_routine(void *arg){
	printf("[ starting thread %lu ]\n",pthread_self());
	while(1){
		pthread_mutex_lock(&(thread_pool->task_queue_lock));
		while(thread_pool->current_queue_size==0 && !thread_pool->destory_flag){
			printf("[ task_queue is null ,thread %lu is waitting ! ]\n",pthread_self());
			pthread_cond_wait(&(thread_pool->ready_event),&(thread_pool->task_queue_lock));
		}
		if(thread_pool->destory_flag){
			pthread_mutex_unlock(&(thread_pool->task_queue_lock));
			printf("[ thread %lu will got over now !]\n",pthread_self());
			pthread_exit(NULL);
		}
		printf("[ thread %lu is starting work ]\n",pthread_self());
		assert(thread_pool->current_queue_size!=0);
		assert(thread_pool->task_head!=NULL);
		thread_pool->current_queue_size--;
		Work_task *work=thread_pool->task_head;
		thread_pool->task_head=work->next;
		pthread_mutex_unlock(&(thread_pool->task_queue_lock));
		(*(work->task_process))(work->arg);
		free(work);
		work=NULL;
	}
	pthread_exit(NULL);
}

void Thread_pool_init(int max_thread_num){
	int num;
	thread_pool=(Thread_pool *)malloc(sizeof(Thread_pool));
	pthread_mutex_init(&(thread_pool->task_queue_lock),NULL);
	pthread_cond_init(&(thread_pool->ready_event),NULL);
	thread_pool->task_head=NULL;
	thread_pool->destory_flag=0;
	thread_pool->max_thread_num=max_thread_num;
	thread_pool->current_queue_size=0;
	thread_pool->threadid_link=(pthread_t *)malloc(sizeof(pthread_t)*max_thread_num);
	for(num=0;num<max_thread_num;num++){
		pthread_create(&(thread_pool->threadid_link[num]),NULL,thread_routine,NULL);
	}
}
int Add_task_to_threadpool(void *(*task_process)(void *arg),void *arg){
	Work_task *new_work=(Work_task*)malloc(sizeof(Work_task));
	new_work->next=NULL;
	new_work->task_process=task_process;
	new_work->arg=arg;
	pthread_mutex_lock(&(thread_pool->task_queue_lock));
	Work_task *work=thread_pool->task_head;
	if(work!=NULL){
		while(work->next!=NULL)
		      work=work->next;
		work->next=new_work;
	}else
	      thread_pool->task_head=new_work;
	assert(thread_pool->task_head!=NULL);
	thread_pool->current_queue_size++;
	pthread_mutex_unlock(&(thread_pool->task_queue_lock));
	pthread_cond_signal(&(thread_pool->ready_event));
	return 0;
}
int destory_thread_pool(){
	int num;
	if(thread_pool->destory_flag)
	      return -1;
	thread_pool->destory_flag=1;
	pthread_cond_broadcast(&(thread_pool->ready_event));
	for(num=0;num<thread_pool->max_thread_num;num++)
	      pthread_join(thread_pool->threadid_link[num],NULL);
	free(thread_pool->threadid_link);
	Work_task *crew=NULL;
	while(thread_pool->task_head!=NULL){
		crew=thread_pool->task_head;
		thread_pool->task_head=thread_pool->task_head->next;
		free(crew);
	}
	pthread_mutex_destroy(&(thread_pool->task_queue_lock));
	pthread_cond_destroy(&(thread_pool->ready_event));
	free(thread_pool);
	thread_pool=NULL;
	return 0;
}
void *work_process(void *arg){
	printf("[ threadid is %lu , working with taskid %d ]\n",pthread_self(),*(int *) arg);
	sleep(2);
	printf("[ workid %d over here with threadid %lu ]\n",*(int *) arg,pthread_self());
	return NULL;
}
int main(int argc, char *argv[])
{
	int max_pthread_num=4;
	int work_routine_num=10;
	int tip;
	int *worknumber=(int *)malloc(sizeof(int)*work_routine_num);
	Thread_pool_init(max_pthread_num);
	for(tip=0;tip<work_routine_num;tip++){
		worknumber[tip]=tip;
		Add_task_to_threadpool(work_process,&worknumber[tip]);
	}
	sleep(5);
	destory_thread_pool();
	free(worknumber);
	return 0;
}

