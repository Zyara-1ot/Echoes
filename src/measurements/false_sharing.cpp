#include "../include/measurements/false_sharing.h"
#include "../include/utils/timer.h"
#include<iostream>
#include<thread>
#include <utility>

std::pair<uint64_t, uint64_t> measure_false_sharing(){
    struct shareddata{
    uint64_t a;
    uint64_t b;
};

struct paddeddata{
    uint64_t a;
    char padding[56];
    uint64_t b;
};

shareddata shared;
paddeddata padded;

uint64_t start = rdtsc();
std::thread t1([&](){
    for(int i = 0; i < 10000000; i++){
        shared.a++;
    }
});

std::thread t2([&](){
    for(int i = 0; i < 10000000; i++){
        shared.b++;
    }
});

t1.join();
t2.join();
uint64_t with_false_shr = rdtsc() - start;


uint64_t start2 = rdtsc();
std::thread t3([&](){
    for(int i = 0; i < 10000000; i++){
        padded.a++;
    }
});

std::thread t4([&](){
    for(int i = 0; i < 10000000; i++){
        padded.b++;
    }
});

t3.join();
t4.join();
uint64_t with_padded_shr = rdtsc() - start2;
return {with_false_shr, with_padded_shr};

}
