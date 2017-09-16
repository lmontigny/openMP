#include <stdio.h>
#include <omp.h>

int main()
{
	 omp_set_num_threads (16); // OPTIONAL — Can also use // OMP_NUM_THREADS environment variable

	 #pragma omp parallel num_threads(8) // Restrict team size locally
	 {
	 printf ("hello, world! \n"); // Execute in parallel
	 } // Implicit barrier/join

	 return 0;
}
