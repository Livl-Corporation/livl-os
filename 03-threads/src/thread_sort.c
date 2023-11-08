#include "thread_sort.h"

void *find_min_max(void *arg) {
   struct thread_data *data;
   data = (struct thread_data *) arg;

   data->min = tab[data->start];
   data->max = tab[data->start];

   for(int i=data->start; i<data->end; i++) {
      if(tab[i] < data->min) {
         data->min = tab[i];
      }

      if(tab[i] > data->max) {
         data->max = tab[i];
      }
   }

   pthread_exit(NULL);
}

int main() {
   srand(time(0));

   for(int i=0; i<SIZE; i++) {
      tab[i] = rand();
   }

   pthread_t threads[NUM_THREADS];
   struct thread_data data[NUM_THREADS];
   int status_pthread_create;


   long t;
   for(t=0; t<NUM_THREADS; t++){
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
         printf("ERROR; return code from pthread_create() is %d\n", status_pthread_create);
         perror("pthread_create");
         exit(EXIT_FAILURE);
      }
   }

   for(t=0; t<NUM_THREADS; t++){
      /**
       * wait for the thread identified by threads[t] to terminate (similar as wait)
       * tid: a unique identifier for the thread
       * retval: the return value of the thread (NULL because we don't need to return anything)
       **/
      pthread_join(threads[t], NULL);
   }

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

   printf("Minimum: %d\n", min_val);
   printf("Maximum: %d\n", max_val);

   pthread_exit(NULL); // NULL because we don't need to return anything (otherwise, we would return a pointer to the return value)
}
