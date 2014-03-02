#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

pthread_key_t key;

typedef
struct tsd_tag{
	pthread_t thread_tg;
	char *string;
}tsd_t;

void destructor (tsd_t *value_pointer) {
    printf ("thread %lu ends, param = %s\n", value_pointer->thread_tg,value_pointer->string);
    free (value_pointer);
    value_pointer = NULL;
}
void * thread_routine(void *arg) {
    tsd_t *value_pointer = (tsd_t *)malloc(sizeof(tsd_t));
    value_pointer->string=(char *)arg;
    value_pointer->thread_tg=pthread_self();
    printf ("thread %lu is running\n", value_pointer->thread_tg);
    pthread_setspecific (key, (void *) value_pointer);
    sleep (3);
    printf ("thread %lu returns %s\n", value_pointer->thread_tg,((tsd_t *)pthread_getspecific(key))->string);
    sleep (4);
}
int main(int argc , char *argv[]) {
    pthread_t thid1, thid2;

    printf ("Main Thread begins running\n");
    pthread_key_create (&key, (void *)destructor);
    pthread_create (&thid1, NULL, thread_routine, "Thread 1");
    pthread_create (&thid2, NULL, thread_routine, "Thread 2");
    sleep (8);
    pthread_key_delete (key);
    printf ("Main Thread exit\n");
    return 0;
}
