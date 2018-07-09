 THis is what  your code should look like:
 double  dif;
 double start = omp_get_wtime( ); //start the timer
 //beginning of computation
 ..
 ...
//end of computation
    double end = omp_get_wtime();// end the timer
   dif = end - start // stores the difference in dif
  printf("the time of dif is %f", dif);
 //this should point you in the way
