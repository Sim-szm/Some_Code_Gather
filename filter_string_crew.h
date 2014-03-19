/*
 * =====================================================================================
 *
 *       Filename:  filter_string_crew.h
 *        Version:  1.0
 *        Created:  2014年03月19日 18时47分09秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef FILTER_STRING_CREW_H
#define FILTER_STRING_CREW_H

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ptrhead.h>
#include <sys/types.h>
#include <dirent.h>

#define work_crew_size 4

extern int errno;
size_t path_str_max;
size_t name_str_max;

/*the work_issue defined*/
typedef struct work_tag{
	char *path;
	char *string;
	struct work_tag *next;
}work_t,*work_p;

/*worker thread defined*/
typedef struct worker_tag{
	pthread_t trhead_id;
	int thread_index;
	struct crew_tag *crew;
}worker_t,*worker_p;

/*work_crew defined*/
typedef struct crew_tag{
	int count_crew_size;
	worker_t crew_member[work_crew_size];
	pthead_mutex_t mutex;
	pthread_cond_t start;
	pthread_cond_t done;
	int work_count;
}crew_t,*crew_p;

void *thread_routine(void *arg);

int init_worker_crew(crew_t *crew,int crew_size);

int crew_start(crew_p crew,char *filepath,char *search_string);

#endif
