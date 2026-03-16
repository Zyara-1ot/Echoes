#include "../../include/measurements/cache_size.h"
#include "../../include/utils/timer.h"
#include <iostream>
#include <cstdint>   
#include <cstdlib>  
#include <cstring>   
#include <vector>    
#include <algorithm>
#include <random>

std::vector<uint64_t> cache_line_size(){
    std::vector<size_t> sizes = {4*1024,8*1024, 16*1024, 32*1024, 64*1024, 128*1024, 256*1024, 512*1024,768*1024,
        1*1024*1024,2*1024*1024, 3*1024*1024, 4*1024*1024,8*1024*1024, 16*1024*1024, 32*1024*1024, 64*1024*1024};
    std::vector<uint64_t> latency;
    for(int i = 0; i < sizes.size(); i++){
    size_t cur_size = sizes[i];
    size_t num_elem = cur_size / sizeof(size_t);
    std::vector<size_t> arr(num_elem);
    std::vector<uint64_t> timing;
    std::vector<size_t> indices(num_elem);
    for(size_t k = 0; k < num_elem; k++)
        indices[k] = k;
    std::shuffle(indices.begin(), indices.end(),
        std::default_random_engine(42));
    for(size_t k = 0; k < num_elem - 1; k++)
        arr[indices[k]] = indices[k+1];
    arr[indices[num_elem-1]] = indices[0];
    size_t idx = indices[0];
    for(size_t k = 0; k < num_elem; k++)
        idx = arr[idx];
    idx = indices[0];
    for(int j = 0; j < 1000; j++){
        uint64_t t1 = rdtsc();
        for(int b = 0; b < 100; b++){
            idx = arr[idx];
        }
        uint64_t t2 = rdtsc();
        timing.push_back((t2 - t1) / 100);
    }
    std::sort(timing.begin(), timing.end());
    latency.push_back(timing[timing.size() / 2]);
}
return latency;

}