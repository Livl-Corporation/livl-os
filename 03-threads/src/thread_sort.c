#include "thread_sort.h"

void *find_min_max(void *arg) {
   struct thread_data *data;
   data = (struct thread_data *) arg;

   int local_min = tab[data->start];
   int local_max = tab[data->start];

   for(int i=data->start; i<data->end; i++) {
      if(tab[i] < local_min) {
         local_min = tab[i];
      }

      if(tab[i] > local_max) {
         local_max = tab[i];
      }
   }

   // Lock the mutex before accessing the shared variable
   // This ensures that these shared variables are not being written to by multiple threads
   // at the same time, which could cause data inconsistencies...
   pthread_mutex_lock(&lock);
   data->min = local_min;
   data->max = local_max;
   pthread_mutex_unlock(&lock);

   pthread_exit(NULL);
}


int main() {
   srand(time(0));
   pthread_mutex_init(&lock, NULL);

   pthread_t threads[NUM_THREADS];
   struct thread_data data[NUM_THREADS];
   int status_pthread_create;

   // Calculate time elapsed
   struct timeval start, end;
   gettimeofday(&start, NULL);

   // Initialize array with random values
   for(int i=0; i<SIZE; i++) {
      tab[i] = rand();
   }

   long t;
   for(t=0; t<NUM_THREADS; t++){
      // Initialize struct start and end values depending where the thread will start and end in the array
      data[t].start = t * (SIZE/NUM_THREADS);
      data[t].end = (t+1) * (SIZE/NUM_THREADS);

      /**
       * pthread_create() - create a new thread
       * 
       * tid: a unique identifier for the new thread
       * attr: an opaque attribute object that may be used to set thread attributes (NULL for default attributes)
       * start_routine (function): the C routine that the thread will execute once it is created
       * arg: a single argument that may be passed to start_routine
      */
      status_pthread_create = pthread_create(&threads[t], NULL, find_min_max, (void *)&data[t]);
      if (status_pthread_create){
         printf("ERROR: return code from pthread_create() is %d\n", status_pthread_create);
         perror("pthread_create");
         exit(EXIT_FAILURE);
      }
   }

   for(t=0; t<NUM_THREADS; t++){
      /**
       * pthread_join doesn’t make the worker threads wait, it makes the main thread wait for the worker threads. 
       * The worker threads themselves do not wait --> they run concurrently as soon as they are created
       * So the main thread wait for the thread identified by threads[t] to terminate (similar as wait)
       * tid: a unique identifier for the thread
       * retval: the return value of the thread (NULL because we don't need to return anything)
       **/
      pthread_join(threads[t], NULL);
   }

   // Calculate time elapsed 
   gettimeofday(&end, NULL);
   long seconds = (end.tv_sec - start.tv_sec);
   long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

   // Find min and max values from all threads
   int min_val = data[0].min;
   int max_val = data[0].max;

   for(t=1; t<NUM_THREADS; t++){
      if(min_val > data[t].min) {
         min_val = data[t].min;
      }
      if(max_val < data[t].max) {
         max_val = data[t].max;
      }
   }

   printf("Time elapsed is %ld seconds and %ld micros\n", seconds, micros);
   printf("Minimum: %d\n", min_val);
   printf("Maximum: %d\n", max_val);

   pthread_mutex_destroy(&lock);
   pthread_exit(NULL); // NULL because we don't need to return anything (otherwise, we would return a pointer to the return value)
}
