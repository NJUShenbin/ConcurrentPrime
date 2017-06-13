//
// Created by sbin on 6/13/17.
//

#include <cmath>
#include "PrimeComputer.h"
#include <iostream>
#include <sstream>

bool isPrime(int number){

    if(number<=1){
        return false;
    }

    bool prime = true;

    double sqrtN = sqrt(number);
    for(int i=2; i<=sqrtN; i++) {
        if(number%i==0) {
            prime = false;
            break;
        }
    }

    return prime;
}


vector<int> PrimeComputer::computeSerial(int N) {

    if(N <= 1){
        return vector<int>();
    }

    vector<int> primes;

    for( int i=2; i<=N; i++) {
        if(isPrime(i)) {
            primes.push_back(i);
        }
    }

    return primes;

}

vector<int> PrimeComputer::computeParallel(int N) {

    const int THREAD_NUM = 11;

    if(N <= THREAD_NUM){
        return computeSerial(N);
    }

    thread_handle threads[THREAD_NUM];
    ThreadArg threadArgs[THREAD_NUM];

    for(int i=0;i<THREAD_NUM;i++){

        threadArgs[i].N=N;
        threadArgs[i].threadId=i;
        threadArgs[i].threadNumber=THREAD_NUM;

        createThread(threadArgs[i],threads[i]);
    }

    vector<int> primes;
    for(int i=0;i<THREAD_NUM;i++){
        join(threads[i]);
        primes.insert(primes.end(),threadArgs[i].primes.begin(),threadArgs[i].primes.end());
    }
    return primes;

}

PrimeComputer::return_t PrimeComputer::computePartPrime(void *threadArg) {
    ThreadArg* arg = (ThreadArg*)threadArg;
    for(int i = arg-> threadId ; i<= arg->N ; i += arg->threadNumber){
        if( isPrime(i) ){
            arg->primes.push_back(i);
        }
    }
    return 0;
}





