#ifndef THREAD_SORT_H
#define THREAD_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

// This size equal to 1x10^8 = 100,000,000
#define SIZE (int)1e8

#define NUM_THREADS 2

// The array that contains the random values
int tab[SIZE];

/**
 * pthread_mutex_t - mutex type
 * Used to protect shared data from being simultaneously accessed by multiple threads
*/
pthread_mutex_t lock;

/*
 * Each thread will have its own struct to be able to store the min and max values 
 * and each thread will have its own range to search for the min and max values 
 * with the start and end values to know where to start and end in the array
 * (Useful when the array is too big and we want to split the work between multiple threads)
 */ 
struct thread_data {
   int  start;
   int  end;
   int  min;
   int  max;
};

#endif //THREAD_SORT_H
