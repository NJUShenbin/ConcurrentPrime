# 质数的串行和并行算法

本项目是《基于多核的并行编程》的作业。题目为计算1到10^7内所有的质数。本文档比较了质数的串行和并行算法，并对性能做出一些分析。
在Windows和Linux下分别使用了WindowsAPI和pthread库。两平台下均可以使用openmp。

## 质数检测
质数检测是用非常简单的算法，即对于数n，检测从1到sqrt(n)之间是否有整数可以整除n，若没有则判断为质数。

## 串行与并行
串行时由单条线程依次对1到10^7中所有的数做质数检测，并记录结果。并行化时，采用数据并行的思路，将10^7个数分给不同的线程完成。

这里主要有两个考虑点，一是数据横切还是纵切，二是线程数应为多少。

对于一，数据纵切更合适。因为检测1到1000之中质数的计算量，远小于检测100000+1到100000+1000之间质数的计算量。
因此，纵切数据使得各线程都分到大数和小数，从而使各线程的计算量差不多。

对于二，线程数应为一个比处理器核心数大的质数。这里要求线程数为质数，是因为合数会导致各线程的质数分布不均。
假设线程数为6，那么3号线程处理的数据为3,9,15,21,27等等，这些数全为3的倍数。每个数在检测到3能整除它时，质数检测就结束，因此3号线程的计算很快就结束了。
而使用质数作为线程数时，各线程的质数分布很均匀。

## 性能分析

计算1到10^7内所有的质数。

串行消耗时间8s，并行消耗时间3s，处理器核心数为4。加速比为2.67。
从算法角度来讲，程序中同步和通信的开销很小，理论上应该能达到3到4的加速比。实际上没有达到,可能是进程无法完全利用4核资源。

对于Linux和Window平台，结果几乎一致。

## 关键代码
判定一个数是否为质数
```c++
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
```

串行计算
```c++
for(int i=2; i<=N; i++) {
    if(isPrime(i)) {
        primes.push_back(i);
    }
}
```

线程库并行
```c++
//创建线程
{
  thread_handle threads[THREAD_NUM];
  ThreadArg threadArgs[THREAD_NUM];

  for(int i=0;i<THREAD_NUM;i++){

      threadArgs[i].N=N;
      threadArgs[i].threadId=i;
      threadArgs[i].threadNumber=THREAD_NUM;

      createThread(threadArgs[i],threads[i]);
  }
}

//线程内方法
{
  ThreadArg* arg = (ThreadArg*)threadArg;
  for(int i = arg-> threadId ; i<= arg->N ; i += arg->threadNumber){
      if( isPrime(i) ){
          arg->primes.push_back(i);
      }
  }
}
```

openmp并行
```c++
#pragma omp parallel for reduction(+:count)
for( int i=2; i<=N; i++) {
    if(isPrime(i)) {
        count++;
    }
}
```
