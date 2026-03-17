#include "../../include/measurements/heatmap_sweep.h"
#include "../../include/utils/timer.h"
#include <vector>
#include <cstdint>
#include <algorithm>

std::vector<std::vector<uint64_t>> heatmap_sweep(){
    std::vector<size_t> sizes = {4*1024, 8*1024, 16*1024, 32*1024, 64*1024, 128*1024, 256*1024, 512*1024,
        1*1024*1024, 2*1024*1024, 4*1024*1024, 8*1024*1024, 16*1024*1024};
    std::vector<size_t> strides = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    
    std::vector<std::vector<uint64_t>> result(sizes.size(), std::vector<uint64_t>(strides.size()));
    
    for(int i = 0; i < sizes.size(); i++){
        size_t cur_size = sizes[i];
        std::vector<char> buffer(cur_size);
        
        for(int j = 0; j < strides.size(); j++){
            size_t stride = strides[j];
            std::vector<uint64_t> timing;
            
            for(int rep = 0; rep < 100; rep++){
                uint64_t t1 = rdtsc();
                for(size_t k = 0; k < cur_size; k += stride){
                    volatile char val = buffer[k];
                }
                uint64_t t2 = rdtsc();
                timing.push_back((t2 - t1) / (cur_size / stride));
            }
            
            std::sort(timing.begin(), timing.end());
            result[i][j] = timing[timing.size() / 2];
        }
    }
    return result;
}