static double a[1000], b[1000], k, m;
void update_a(void){ 
  int i;
  #pragma omp parallel for firstprivate(k) \
  lastprivate(m)
  for (i=0;i<1000;i++) {
    m = k * (double)i/2.0;
    a[i]= b[i] + m ; 
  }
}
