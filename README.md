# ECHOES

A tool that experimentally maps your CPU's cache hierarchy by stressing memory with different access patterns and visualizing latency and cache behavior.

## What it measures
- Cache size sweep  detects L1/L2/L3 boundaries empirically
- False sharing  measures penalty of cache line contention between threads

## Sample Output

### Cache Hierarchy Detection
```
size: 4KB    cycles: 16    ← L1 cache
size: 8KB    cycles: 16    ← L1 cache
size: 64KB   cycles: 20    ← L2 cache
size: 512KB  cycles: 32    ← L2 cache
size: 1MB    cycles: 45    ← L3 cache
size: 4MB    cycles: 100   ← L3 cache
size: 8MB    cycles: 265   ← RAM (L3 boundary hit)
size: 16MB   cycles: 352   ← RAM
```
*Tested on AMD Ryzen 5 5500U (L1: 32KB, L2: 512KB, L3: 8MB)*

### False Sharing Detection
```
with false sharing:    228,665,031 cycles
without false sharing:  60,197,424 cycles
penalty: 3.79x slower
```
*Two threads writing to adjacent variables on the same cache line vs padded variables on separate cache lines.*

## Build
```bash
g++ -O0 -o echoes src/main.cpp src/measurements/cache_line.cpp src/measurements/false_sharing.cpp src/utils/timer.cpp -lpthread
./echoes
```
