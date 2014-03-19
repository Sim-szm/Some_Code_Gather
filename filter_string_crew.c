/*
 * =====================================================================================
 *
 *       Filename:  filter_string_crew.c
 *        Version:  1.0
 *        Created:  2014年03月19日 18时47分09秒
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


