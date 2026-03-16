#include "../../include/utils/timer.h"

uint64_t rdtsc(){
    uint32_t lo;
    uint32_t hi;
    __asm__ __volatile__(
        "mfence\n\t"
        "rdtsc"
        : "=a"(lo), "=d"(hi)
        :
    );
    return (uint64_t)hi << 32 | lo;
}