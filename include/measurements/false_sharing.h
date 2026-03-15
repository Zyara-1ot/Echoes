#ifndef FALSE_SHARING_H
#define FALSE_SHARING_H

#include <cstdint>
#include <utility>

std::pair<uint64_t, uint64_t> measure_false_sharing();

#endif
