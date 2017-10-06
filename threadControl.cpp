/* C/C++ example */

#pragma omp parallel private(myid, istart, iend)
{
  myrange(myid, nthreads, global_start, global_end, &istart, &iend);
  for(i=istart; i<=iend; i++){
     a[i] = b[i];
  }
  #pragma omp barrier
  #pragma omp master
  {
  n = global_end - global_start + 1;
  write_size = fwrite(a, 1, n, file_pointer);
  }
  do_work(istart, iend);
}
