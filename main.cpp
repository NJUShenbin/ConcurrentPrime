#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include "PrimeComputer.h"
#include <omp.h>

using namespace std;

const int N = 1000*10000*1;
//const int N = 10*1;

int main(void) {

    double begin,end;
//    begin = omp_get_wtime();
//    cout << PrimeComputer::computeSerial(N).size() <<endl;
//    end = omp_get_wtime();
//    cout<<"serial delta time:"<< end-begin <<endl;
//
//    begin = omp_get_wtime();
//    cout << PrimeComputer::computeParallel(N).size() <<endl;
//    end = omp_get_wtime();
//    cout<<"parallel delta time:"<< end-begin <<endl;

    begin = omp_get_wtime();
    PrimeComputer::computeOpenmp(N);
    end = omp_get_wtime();
    cout<<"parallel delta time:"<< end-begin <<endl;
    return 0;

}