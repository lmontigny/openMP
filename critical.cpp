#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

#define THREADS 32
#define START 0
#define END 100000

/* a global variable */
unsigned long sum = 0;

/* the function called for each thread */
void sum_part( ) {
    /* get our thread id */
    int id = omp_get_thread_num( );

    /* calculate the start and end points by evenly dividing the range */
    unsigned long start = ((END - START) / THREADS) * id;
    unsigned long end = start + ((END - START) / THREADS) - 1;

    /* the last thread needs to do all remaining ones */
    if (id == (THREADS - 1)) {
        end = END;
    }
    
  /* do the calculation */
  unsigned long i;
  for (i = start; i <= end; i++) {
#pragma omp critical //access one thread at a time
    sum += i;
  }
}

int main ( ) {
#pragma omp parallel num_threads(THREADS)
    sum_part( );

    /* now all results are in */
    printf("Final answer = %lu.\n", sum);
    return 0;
}
