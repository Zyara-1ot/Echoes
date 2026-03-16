#include "../../include/measurements/cache_line.h"
#include "../../include/utils/timer.h"
#include <vector>
#include <cstdint>
#include <algorithm>

std::vector<uint64_t> detect_cache_line(){
    std::vector<char> buffer(64*1024*1024);
    std::vector<uint64_t> stride = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    std::vector<uint64_t> result;
    for(int i = 0; i < stride.size(); i++){
        std::vector<uint64_t>timing;
        for(int j = 0; j < buffer.size(); j += stride[i]){
            uint64_t t1 = rdtsc();
            volatile char val = buffer[j];
            uint64_t t2 = rdtsc();
            uint64_t dif = t2 - t1;
            timing.push_back(dif);
        }
        std::sort(timing.begin(), timing.end());
        result.push_back(timing[timing.size()/2]);
        
    }
    return result;

}