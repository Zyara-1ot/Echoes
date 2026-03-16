#include <iostream>
#include <cstdint>   
#include <cstdlib>  
#include <cstring>   
#include <vector>    
#include <algorithm> 
#include "../include/utils/timer.h"
#include "../include/measurements/cache_size.h"
#include "../include/measurements/false_sharing.h"

int main(){
    std::size_t size = 10000000;
    std::vector<char> l_arr(size);
    uint64_t t1 = rdtsc();
    volatile char val = l_arr[0];
    uint64_t t2 = rdtsc();
    //std::cout << t2 - t1 << std::endl;
    int n = 100;
    std::vector<uint64_t> t;
    std::vector<uint64_t> tim;
    for(int i = 0; i < n; i++){
        t1 = rdtsc();
        volatile char val = l_arr[i];
        t2 = rdtsc();
        uint64_t d = t2 - t1;
        tim.push_back(d);
    }
    std::sort(tim.begin(), tim.end());
    //std::cout << tim[tim.size() / 2] << std::endl;
    std::vector<uint64_t> res = cache_line_size();
    std::vector<size_t> sizes = {4*1024,8*1024, 16*1024, 32*1024, 64*1024, 128*1024, 256*1024, 512*1024,768*1024,
        1*1024*1024,2*1024*1024, 3*1024*1024, 4*1024*1024,8*1024*1024, 16*1024*1024, 32*1024*1024, 64*1024*1024};
    for(int i = 0; i < res.size(); i++){
        std::cout << "size: " << sizes[i]/1024 << "KB cycles: " << res[i] << std::endl;
    }

    auto result = measure_false_sharing();
    std::cout << "with false sharing:    " << result.first << " cycles" << std::endl;
    std::cout << "without false sharing: " << result.second << " cycles" << std::endl;
    std::cout << "penalty: " << (double)result.first / result.second << "x slower" << std::endl;


    
}
