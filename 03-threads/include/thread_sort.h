#ifndef THREAD_SORT_H
#define THREAD_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define SIZE (int)1e8
#define NUM_THREADS 2

int tab[SIZE];

/**
 * pthread_mutex_t - mutex type
 * Used to protect shared data from being simultaneously accessed by multiple threads
*/
pthread_mutex_t lock;

struct thread_data {
   int  start;
   int  end;
   int  min;
   int  max;
};

#endif //THREAD_SORT_H
