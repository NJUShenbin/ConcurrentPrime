//
// Created by sbin on 6/13/17.
//

#ifndef PTHREADTEST_PRIMECOMPUTER_H
#define PTHREADTEST_PRIMECOMPUTER_H

#include <vector>

#if PTHREAD
#include <pthread.h>
#else
#include <windows.h>
#endif

using namespace std;

class PrimeComputer {

public:
    static vector<int> computeSerial(int N);
    static vector<int> computeParallel(int N);

private:

    struct ThreadArg{
        int N;
        int threadNumber;
        int threadId;
        vector<int> primes;
    };

#if PTHREAD
    typedef void* return_t;
    typedef pthread_t thread_handle;
    static void createThread(ThreadArg& arg, thread_handle& thread){
        pthread_create(&thread, NULL, computePartPrime, (void *) &arg );
    }
    static void join(thread_handle thread){
        pthread_join(thread,NULL);
    }

    static return_t computePartPrime(void* threadArg);

#else
    typedef DWORD return_t;
    typedef HANDLE thread_handle;
    static void createThread(ThreadArg& arg, thread_handle& thread){
        thread = CreateThread(NULL, 0,
                                  computePartPrime,
                                  (void *) &arg,
                                  0, NULL);
    }
    static void join(thread_handle thread){
        WaitForSingleObject(thread,INFINITE);
    }

    static return_t WINAPI computePartPrime(void* threadArg);

#endif


};


#endif //PTHREADTEST_PRIMECOMPUTER_H
