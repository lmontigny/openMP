#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

// Suppose we wanted one portion of our threaded code to execute in thread order.

#define THREADS 16

/* the function called for each thread */
void worker( ) {
  /* get our thread id */
  int id = omp_get_thread_num( );

  #pragma omp ordered
  printf("Thread %d says hello!\n", id);
}

int main ( ) {
  int i;

  #pragma omp parallel for num_threads(THREADS) ordered
  for (i = 0; i < THREADS; i++) {
    worker( );
  }
  return 0;
}
