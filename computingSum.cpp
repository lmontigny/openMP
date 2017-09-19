// First solution
sum = 0;
#pragma omp parallel shared(n,a,sum) private(sum_local){
 sum_local = 0;
 #pragma omp for
 for (i=0; i<n; i++)
 sum_local += a[i]; // form per-thread local sum

 #pragma omp critical {
 sum += sum_local; // form global sum
 }
}


// Cleaner solution
sum = 0;
#pragma omp parallel for \
shared(...) private(...) \
reduction(+:sum)
 {
 for (i=0; i<n; i++)
 sum += a[i];
}
