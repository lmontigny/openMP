#include <stdio.h>
#include <omp.h>
#include <iostream>
using namespace std;

int threads = 100;
int id = 100;
int array[]{1,2,3,4,5};
int sum;

int main()
{
    #pragma omp parallel for reduction(+:sum)
    for(int i=0; i<5; i++){
         threads = omp_get_num_threads();
         id = omp_get_thread_num();

         sum += array[i];
    }
    cout << sum << endl;

    int result = 0;
    #pragma omp parallel shared(sum)
    {
        int local;
        #pragma omp for
        for (int i = 0; i < 5; i++) {
            local = array[i];
            #pragma omp critical
            result += local;
        }

    }
    cout << result << endl;



    int a=0, b=0, c=0;
    #pragma omp parallel num_threads(4)
    {
            #pragma omp single
            a++;
            #pragma omp critical
            b++;
            #pragma omp atomic
            c++;
    }
    printf("single: %d, critical: %d, atomic: %d\n", a, b, c);


    return 0;
}
