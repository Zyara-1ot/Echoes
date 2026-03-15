# ECHOES

A tool that experimentally maps your CPU's cache hierarchy by stressing memory with different access patterns and visualizing latency and cache behavior.

## What it measures
- Cache size sweep — detects L1/L2/L3 boundaries empirically
- False sharing — measures penalty of cache line contention between threads

## Sample output
```
size: 4KB    cycles: 147   (L1)
size: 512KB  cycles: 147   (L2)
size: 4096KB cycles: 462   (L3 boundary)
size: 8192KB cycles: 441   (RAM)

with false sharing:    156,282,756 cycles
without false sharing:  44,087,736 cycles
penalty: 3.5x slower
```

## Build
```bash
g++ -O0 -o echoes src/main.cpp src/measurements/cache_line.cpp src/measurements/false_sharing.cpp src/utils/timer.cpp -lpthread
./echoes
```
