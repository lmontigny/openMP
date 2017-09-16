omp_set_num_threads (16); // OPTIONAL — Can also use // OMP_NUM_THREADS environment variable
#pragma omp parallel // Activates the team of threads
{
	#pragma omp for shared (a,n) private (i) // Declares work sharing loop
	for (i = 0; i < n; ++i) {
	a[i] += foo (i);
	} // Implicit barrier/join
} // Implicit barrier/join
