#include "../../include/measurements/tlb.h"
#include "../../include/utils/timer.h"
#include <vector>
#include <cstdint>
#include <algorithm>
#include <random>

std::vector<uint64_t> detect_tlb(){
    std::vector<size_t> sizes = {4*1024,8*1024, 16*1024, 32*1024, 64*1024, 128*1024, 256*1024, 512*1024,768*1024,
        1*1024*1024,2*1024*1024, 3*1024*1024, 4*1024*1024,8*1024*1024, 16*1024*1024, 32*1024*1024, 64*1024*1024};

    std::vector<uint64_t> res;
    for(int i = 0; i < sizes.size(); i++){
        size_t cur_size = sizes[i];
        std::vector<char> buffer(cur_size);
        size_t num_pages = cur_size / 4096;
        std::vector<size_t> ind(num_pages);
        for(int k = 0; k < num_pages; k++){
            ind[k] = k * 4096;
        }
        std::shuffle(ind.begin(), ind.end(),
    std::default_random_engine(42));

    for(size_t k = 0; k < num_pages; k++){
        volatile char val = buffer[ind[k]];
    }
    std::vector<uint64_t> timing;
    for(int j = 0; j < 1000; j++){
    uint64_t t1 = rdtsc();
    for(size_t b = 0; b < num_pages; b++){
        volatile char val = buffer[ind[b]];
    }
    uint64_t t2 = rdtsc();
    timing.push_back((t2 - t1) / num_pages);
}
    std::sort(timing.begin(), timing.end());
    res.push_back(timing[timing.size() / 2]);

    }
    return res;

}

