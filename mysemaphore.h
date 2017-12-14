#ifndef MYSEMAPHORE_H_
#define MYSEMAPHORE_H_

#include <iostream>
#include <semaphore.h>

typedef struct mysemaphore{

 sem_t rw_mutex;
 sem_t mutex ;
 int read_count ;
	

} mysem_t;

#endif