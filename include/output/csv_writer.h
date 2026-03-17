#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <vector>
#include <string>
#include <cstdint>

void write_heatmap_csv(
    const std::string& filename,
    const std::vector<size_t>& sizes,
    const std::vector<size_t>& strides,
    const std::vector<std::vector<uint64_t>>& data
);

#endif