/*
Compare to critical:
locks are more flexible since they lock a data element, not a code fragment

*/

// omp_init_lock.cpp  
// compile with: /openmp  
#include <stdio.h>  
#include <omp.h>  
  
omp_lock_t my_lock;  
  
int main() {  
   omp_init_lock(&my_lock);  
  
   #pragma omp parallel num_threads(4)  
   {  
      int tid = omp_get_thread_num( );  
      int i, j;  
  
      for (i = 0; i < 5; ++i) {  
         omp_set_lock(&my_lock);  
         printf_s("Thread %d - starting locked region\n", tid);  
         printf_s("Thread %d - ending locked region\n", tid);  
         omp_unset_lock(&my_lock);  
      }  
   }  
  
   omp_destroy_lock(&my_lock);  
}  


/*
Thread 0 - starting locked region  
Thread 0 - ending locked region  
Thread 0 - starting locked region  
Thread 0 - ending locked region  
Thread 0 - starting locked region  
Thread 0 - ending locked region  
Thread 0 - starting locked region  
Thread 0 - ending locked region  
Thread 0 - starting locked region  
Thread 0 - ending locked region  
Thread 1 - starting locked region  
Thread 1 - ending locked region  
Thread 1 - starting locked region  
Thread 1 - ending locked region  
Thread 1 - starting locked region  
Thread 1 - ending locked region  
Thread 1 - starting locked region  
Thread 1 - ending locked region  
Thread 1 - starting locked region  
Thread 1 - ending locked region  
Thread 2 - starting locked region  
Thread 2 - ending locked region  
Thread 2 - starting locked region  
Thread 2 - ending locked region  
Thread 2 - starting locked region  
Thread 2 - ending locked region  
Thread 2 - starting locked region  
Thread 2 - ending locked region  
Thread 2 - starting locked region  
Thread 2 - ending locked region  
Thread 3 - starting locked region  
Thread 3 - ending locked region  
Thread 3 - starting locked region  
Thread 3 - ending locked region  
Thread 3 - starting locked region  
Thread 3 - ending locked region  
Thread 3 - starting locked region  
Thread 3 - ending locked region  
Thread 3 - starting locked region  
Thread 3 - ending locked region  
*/
