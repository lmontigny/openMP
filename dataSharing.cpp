/*
shared—Shared variables within a parallel region share a single storage location.
private—Private variables within a parallel region have multiple storage locations, one location for each thread in the team.

In a parallel region, any data declared outside it will be shared: any thread using a variable  x will access 
the same memory location associated with that variable.

Shared variables introduce an overhead, because one instance of a variable is shared between multiple threads.
Therefore, it is often best to minimize the number of shared variables when a good performance is desired.

On several occasions, we can avoid listing private variables in the OpenMP constructs by declaring them inside a parallel region. 
*/

// Example 1
# pragma omp parallel shared ( a, b, c, n, pi, s ) private ( angle, i, j, k )
{
  # pragma omp for
  for ( i = 0; i < n; i++ )
  {
    for ( j = 0; j < n; j++ )
    {
      angle = 2.0 * pi * i * j / ( double ) n;
      a[i][j] = s * ( sin ( angle ) + cos ( angle ) );
    }
  }
  
  
// Example 2
  #pragma omp parallel for private (j)
 for(i = 0; i < M; i++)
 for(j=0; j < N; j++)
 a[i][j] = min(a[i][j], a[i][k]+tmp[j]); 
