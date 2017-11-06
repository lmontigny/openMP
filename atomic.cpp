/*
Compare to critical:

Atomic operation:
Is much faster!
Only ensures the serialisation of a particular operation.

 atomic allows the compiler more opportunities for optimisation 
 (using hardware instructions, for example). 

In other cases, there are differences. If incrementing array elements
(e.g. a[i]++ ), atomic allows different threads to update different elements 
of the array concurrently whereas critical does not.
*/

#include <omp.h>  //prevents a load-time problem with a .dll not being found
  int count;
   void Tick() {
   // Replace lock annotations
     #pragma omp atomic
        count = count+1;
  }
