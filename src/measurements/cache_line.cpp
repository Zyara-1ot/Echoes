#include "../include/cache_line.h"
#include "../include/timer.h"
#include <iostream>
#include <cstdint>   
#include <cstdlib>  
#include <cstring>   
#include <vector>    
#include <algorithm>

std::vector<uint64_t> cache_line_size(){
    std::vector<size_t> sizes = {4*1024,8*1024, 16*1024, 32*1024, 64*1024, 128*1024, 256*1024, 512*1024,768*1024,
        1*1024*1024,2*1024*1024, 3*1024*1024, 4*1024*1024,8*1024*1024, 16*1024*1024, 32*1024*1024, 64*1024*1024};
    std::vector<uint64_t> latency;
    for(int i = 0; i < sizes.size(); i++){
    size_t cur_size = sizes[i];
    std::vector<char> arr(cur_size);
    std::vector<uint64_t> timing;
   size_t num_acc = cur_size / 64;
   for(int repeat = 0; repeat < 3; repeat++){
    for(size_t j = 0; j < num_acc; j++){
        uint64_t t1 = rdtsc();
        volatile char val = arr[(j * 64) % cur_size];
        uint64_t t2 = rdtsc();
        timing.push_back(t2-t1);
    }
}
    std::sort(timing.begin(), timing.end());
    latency.push_back(timing[timing.size() / 2]);

}
return latency;

}