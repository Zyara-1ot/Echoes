#include "../../include/output/csv_writer.h"
#include <fstream>
#include <iostream>

void write_heatmap_csv(
    const std::string& filename,
    const std::vector<size_t>& sizes,
    const std::vector<size_t>& strides,
    const std::vector<std::vector<uint64_t>>& data
){
    std::ofstream file(filename);
    if(!file.is_open()){
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    file << "size";
    for(int j = 0; j < strides.size(); j++)
        file << "," << strides[j];
    file << "\n";
    for(int i = 0; i < sizes.size(); i++){
        file << sizes[i]/1024 << "KB";
        for(int j = 0; j < strides.size(); j++)
            file << "," << data[i][j];
        file << "\n";
    }

    file.close();
    std::cout << "Heatmap data written to " << filename << std::endl;
}