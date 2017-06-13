#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include "PrimeComputer.h"

using namespace std;

const int N = 1000*10000;


int main(void) {

    time_t begin,end;
    time(&begin);
    cout << PrimeComputer::computeSerial(N).size() <<endl;
    time(&end);
    cout<<"serial delta time:"<< end-begin <<endl;

    time(&begin);
    cout << PrimeComputer::computeParallel(N).size() <<endl;
    time(&end);
    cout<<"parallel delta time:"<< end-begin <<endl;

    return 0;

}