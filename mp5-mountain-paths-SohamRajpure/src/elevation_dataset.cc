#include "elevation_dataset.hpp"

ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height) : width_(width), height_(height) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw std::runtime_error("unable to open file");
    }
    data_.resize(height_);
    for (size_t i = 0; i < height_; i++) {
        data_.at(i).resize(width_);
        for (size_t j = 0; j < width_; j++) {
            int elevation = 0;

            ifs >> elevation;
            
            if (ifs.fail()) {
                throw std::runtime_error("too little data in file or format read error.");
            }

            data_.at(i).at(j) = elevation;
            if (i == 0 && j == 0) {
                min_ele_ = elevation;
                max_ele_ = elevation;
            }
            if (elevation < min_ele_) {
                min_ele_ = elevation;
            }
            if (elevation > max_ele_) {
                max_ele_ = elevation;
            }
        }
    }
    //skip any empty lines
    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //check if there are any more data points meaning that there is too much data in the file
    int more = 0;
    if (ifs >> more) {
        throw std::runtime_error("Too much data in file");
    }
}

size_t ElevationDataset::Height() const { return height_; }

size_t ElevationDataset::Width() const { return width_; }

int ElevationDataset::MinEle() const { return min_ele_; }

int ElevationDataset::MaxEle() const { return max_ele_; }

int ElevationDataset::DatumAt(size_t row, size_t col) const { return data_[row][col]; }

const std::vector<std::vector<int>>& ElevationDataset::GetData() const { 
    return data_; 
}