/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *        Version:  1.0
 *        Created:  2014年03月19日 20时57分09秒
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
#include "filter_string_crew.h"

int main(int argc, char *argv[]){
	crew_t point;
	char line[128],*next;
	if(argc<3){
		fprintf(stderr,"Usage:%s string path\n",argv[0]);
		return -1;
	}
	int status=init_worker_crew(&point,work_crew_size);
//	assert(status==0);
	crew_start(&point,argv[2],argv[1]);
	return 0;
}

