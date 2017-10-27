// From http://www.drdobbs.com/parallel/programming-intels-xeon-phi-a-jumpstart/240144160?pgno=2

/* firstMatrix.c (Rob Farber) */
#ifndef MIC_DEV
#define MIC_DEV 0
#endif
 
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <mkl.h>
#include <math.h>
 
// An OpenMP simple matrix multiply
void doMult(int size, float (* restrict A)[size],
        float (* restrict B)[size], float (* restrict C)[size]) 
{
#pragma offload target(mic:MIC_DEV) \
                in(A:length(size*size)) in( B:length(size*size))    \
                out(C:length(size*size))
  {
    // Zero the C matrix
#pragma omp parallel for default(none) shared(C,size)
    for (int i = 0; i < size; ++i)
      for (int j = 0; j < size; ++j)
        C[i][j] =0.f;
     
    // Compute matrix multiplication.
#pragma omp parallel for default(none) shared(A,B,C,size)
    for (int i = 0; i < size; ++i)
      for (int k = 0; k < size; ++k)
        for (int j = 0; j < size; ++j)
          C[i][j] += A[i][k] * B[k][j];
  }
}
 
int main(int argc, char *argv[])
{
 
  if(argc != 4) {
    fprintf(stderr,"Use: %s size nThreads nIter\n",argv[0]);
    return -1;
  }
 
  int i,j,k;
  int size=atoi(argv[1]);
  int nThreads=atoi(argv[2]);
  int nIter=atoi(argv[3]);
   
  omp_set_num_threads(nThreads);
 
  float (*restrict A)[size] = malloc(sizeof(float)*size*size);
  float (*restrict B)[size] = malloc(sizeof(float)*size*size);
  float (*restrict C)[size] = malloc(sizeof(float)*size*size);
 
  // Fill the A and B arrays
#pragma omp parallel for default(none) shared(A,B,size) private(i,j,k)
  for (i = 0; i < size; ++i) {
    for (j = 0; j < size; ++j) {
      A[i][j] = (float)i + j;
      B[i][j] = (float)i - j;
    }
  }
   
  // warm up
  doMult(size, A,B,C);
 
  double aveTime,minTime=1e6,maxTime=0.;
  for(int i=0; i < nIter; i++) {
    double startTime = dsecnd();
    doMult(size, A,B,C);
    double endTime = dsecnd();
    double runtime = endTime-startTime;
    maxTime=(maxTime > runtime)?maxTime:runtime;
    minTime=(minTime < runtime)?minTime:runtime;
    aveTime += runtime;
  }
  aveTime /= nIter;
   
  printf("%s nThrds %d matrix %d maxRT %g minRT %g aveRT %g ave_GFlop/s %g\n",
     argv[0], omp_get_num_threads(), size,
     maxTime,minTime,aveTime, 2e-9*size*size*size/aveTime);
 
  free(A); free(B); free(C);
  return 0;
}
