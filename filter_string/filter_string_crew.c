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
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "filter_string_crew.h"

int init_worker_crew(crew_t *crew,int crew_size){
	/*this is bug wait to fix !*/
	int status;
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
		status=pthread_create(&crew->crew_member[index].trhead_id,   \
					NULL,thread_routine,(void*)&crew->crew_member[index]);
		assert(status==0);
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
		pthread_mutex_lock(&crew->mutex);
		while(crew->first==NULL){
			status=pthread_cond_wait(&crew->start,&crew->mutex);
			assert(status==0);
		}
		work=crew->first;
		crew->first=work->next;
		if(crew->first==NULL){
			crew->end=NULL;
		}
		pthread_mutex_unlock(&crew->mutex);

		/*have a work ,process it*/
		status=lstat(work->path,&filestat);
		/*part one : if it was a link */
		if(S_ISLNK(filestat.st_mode)){
			printf("thread %d:%s is a link,skipping.\n",\
						tran->thread_index,work->path);
		}
		/*part two: if it was a directory */
		else if(S_ISDIR(filestat.st_mode)){
			DIR *directory;
			struct dirent *as;
			directory=opendir(work->path);
			if(directory==NULL){
				errno=EINVAL;
				continue;
			}
			while(1){
				status=readdir_r(directory,entry,&as);
				if(status!=0){
					printf("unable to read directory %s\n",\
								work->path);
					errno=status;
					break;
				}
				if(as==NULL)
				      break;
				/*skipping ./ ../ */
				if(strcmp(entry->d_name,".")==0)
				      continue;
				if(strcmp(entry->d_name,"..")==0)
				      continue;
				new_work=(work_t*)malloc(sizeof(work_t));
				assert(new_work!=NULL);
				new_work->path=(char*)malloc(sizeof(path_str_max));
				assert((new_work->path)!=NULL);
				strcpy(new_work->path,work->path);
				strcat(new_work->path,"/");
				strcat(new_work->path,entry->d_name);
				new_work->string=work->string;
				new_work->next=NULL;

				pthread_mutex_lock(&crew->mutex);
				if(crew->first==NULL){
					crew->first=new_work;
					crew->end=new_work;
				}else{
					crew->end->next=new_work;
					crew->end=new_work;
				}
				crew->work_count++;
				pthread_cond_signal(&crew->start);
				status=pthread_mutex_unlock(&crew->mutex);
				assert(status==0);
			}
			closedir(directory);
		/* part three: if it was a file !*/
		}else if(S_ISREG(filestat.st_mode)){
			FILE *search;
			char buffer[256],*bufptr,*searchptr;
			search=fopen(work->path,"r");
			if(search==NULL){
			      printf("unable to open %s\n",\
						      work->path);
			      errno=EINVAL;
			}else{
				while(1){
					bufptr=fgets(buffer,sizeof(buffer),search);
					if(bufptr==NULL){
						if(feof(search)) break;
						if(ferror(search)){
						      printf("unable to read %s\n",\
									      work->path);
						      break;
						}
					}
					if((searchptr=strstr(buffer,work->string))!=NULL){
						printf("thread %d found *|%s|*\
									in %s \n",\
									tran->thread_index,work->string,work->path);
						break;
					}
				}
				fclose(search);
			}
		/*part four: if it was other type */
		}else{
			printf("other type ... ( never process it !)\n");
		}

		free(work->path);
		free(work);

		pthread_mutex_lock(&crew->mutex);
		crew->work_count--;
		if(crew->work_count<=0){
			printf("crew thread %d done\n",tran->thread_index);
			status=pthread_mutex_unlock(&crew->mutex);
			assert(status==0);
			break;
		}
		pthread_mutex_unlock(&crew->mutex);
	}

	free(entry);
	return NULL;
}

int crew_start(crew_p crew,char *filepath,char *search_string){
	work_p request;

	pthread_mutex_lock(&crew->mutex);
	while(crew->work_count>0){
		if(pthread_cond_wait(&crew->done,&crew->mutex)!=0){
			pthread_mutex_unlock(&crew->mutex);
			return 1;
		}
	}
	errno=0;
	path_str_max=pathconf(filepath,_PC_PATH_MAX);
	if(path_str_max==-1){
		if(errno==0)
		      path_str_max=1024;
		else
		      printf("unable to get path_max");
	}
	errno=0;
	name_str_max=pathconf(filepath,_PC_NAME_MAX);
	if(name_str_max==-1){
		if(errno==0)
		      name_str_max=256;
		else
		      printf("unbale to get name_max");
	}
	path_str_max++;
	name_str_max++;
	request=(work_p)malloc(sizeof(work_t));
	if(request==NULL){
		errno=EINVAL;
	}
	request->path=(char*)malloc(sizeof(path_str_max));
	strcpy(request->path,filepath);
	request->string=search_string;
	request->next=NULL;
	if(crew->first==NULL){
		crew->first=request;
		crew->end=request;
	}else{
		crew->end->next=request;
		crew->end=request;
	}

	crew->work_count++;
	pthread_cond_signal(&crew->start);

	while(crew->work_count>0){
		pthread_cond_wait(&crew->done,&crew->mutex);
	}
	pthread_mutex_unlock(&crew->mutex);
	return 0;
}
