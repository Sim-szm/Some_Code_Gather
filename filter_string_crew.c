/*
 * =====================================================================================
 *
 *       Filename:  filter_string_crew.c
 *        Version:  1.0
 *        Created:  2014年03月19日 19时13分34秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "filter_string_crew.h"

int init_worker_crew(crew_t *crew,int crew_size){
	int stu;
	if(crew_size>=work_crew_size){
		errno=EINVAL;
		return 1;
	}
	crew->count_crew_size=crew_size;
	crew->work_count=0;
	crew->first=NULL;
	crew->end=NULL;
	/* initialize the synchronization objects */
	do{
		if(pthread_mutex_init(&crew->mutex,NULL)!=0) break;
		if(pthread_cond_init(&crew->start,NULL)!=0) break;
		if(pthread_cond_init(&crew->done,NULL)!=0) break;
	}while(0);
	/* create thread for the crew */
	for(int index=0;index<work_crew_size;index++){
		crew->crew_member[index].thread_index=index;
		crew->crew_member[index].crew=crew;
		stu=pthread_create(&crew->crew_member[index].trhead_id,   \
					NULL,thread_routine,(void*)crew->&crew_member[index]);
		assert(stu==0);
	}
	return 0;
}

void *thread_routine(void *arg){
	int status;
	worker_p tran=(worker_t*)arg;
	crew_p crew=tran->crew;
	struct stat filestat;
	struct dirent *entry;
	work_p work,new_work;
	entry=(struct dirent*)malloc   \
	      (sizeof(struct dirent)+name_str_max);
	assert(entry!=NULL);
	pthread_mutex_lock(&crew->mutex);
	if(crew->work_count==0){
		pthread_cond_wait(&crew->start,&crew->mutex);
	}
	pthread_mutex_unlock(&crew->mutex);
	printf("crew %d starting !\n",tran->thread_index);
	/*Now there is work here, we should doing it !*/
	while(1){
		pthead_mutex_lock(&crew->mutex);
		if(crew->first==NULL){
			status=pthread_cond_wait(&crew->start,&crew->mutex);
			assert(status==0);
		}
		work=crew->first;
		crew->first=work->next;
	}
}
