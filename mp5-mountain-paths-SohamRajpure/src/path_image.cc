#include "path_image.hpp"
#include "path.hpp"
#include "grayscale_image.hpp"
#include <cmath>
#include "utility"
#include "color.hpp"
#include <elevation_dataset.hpp>

PathImage::PathImage(const GrayscaleImage& image, const ElevationDataset& data) : path_image_(image.GetImage()){
    height_ = data.Height();
    width_ = data.Width();
    paths_ = std::vector<Path>(height_);
    //Compute the paths for each starting point in the left column
    Path shorty {};
    shorty.IncEleChange(std::numeric_limits<unsigned int>::max());
    for (size_t row = 0; row < height_; ++row) {
        Path path = ComputePath(row, data);
        paths_.at(row) = path;
        for (size_t col = 0; col < width_; ++col) {
            //path.GetPath().at(col) pulls the row index from the path's row vector
            path_image_.at(path.GetPath().at(col)).at(col) = kRed;
        }
        if (path.EleChange() < shorty.EleChange()) {
            shorty = path;
        }
    }

    //Coloring in the shortest path ("shorty") as green   
    for (size_t col = 0; col < width_; ++col) { 
        //accessing row information from path vector containing row indeces
        size_t row = shorty.GetPath().at(col);
        path_image_.at(row).at(col) = kGreen; 
    } 
} 

Path PathImage::ComputePath(size_t start_row, const ElevationDataset& dataset) const {
    // Create a Path object to represent the current path being computed
    Path current_path(width_, start_row);
    size_t current_row = start_row;
    size_t current_col = 0;
    current_path.SetLoc(current_col, current_row);

    while (current_col < width_ - 1) {
        // Determine the row indices of the three adjacent cells in the next column over (must go '-' for north and '+' for south because top left is 0,0)
        size_t north_row = std::max(static_cast<int>(current_row - 1), 0);
        size_t south_row = std::min(static_cast<int>(current_row + 1), static_cast<int>(dataset.Height() - 1));

        // Calculate the change in elevation for each of the three possible next steps
        unsigned int straight_change = std::abs(dataset.DatumAt(current_row, current_col) - dataset.DatumAt(current_row, current_col + 1));
        unsigned int north_change = std::abs(dataset.DatumAt(current_row, current_col) - dataset.DatumAt(north_row, current_col + 1));
        unsigned int south_change = std::abs(dataset.DatumAt(current_row, current_col) - dataset.DatumAt(south_row, current_col + 1));

        // Determine the direction with the least elevation change, with ties broken
        if (south_change < straight_change && south_change <= north_change) {
            current_path.IncEleChange(south_change);
            current_row = south_row;
        } else if (straight_change <= north_change) {
            current_path.IncEleChange(straight_change);
        } else {
            current_path.IncEleChange(north_change);
            current_row = north_row;
        }
        
        current_path.SetLoc(current_col + 1, current_row);
        ++current_col;
    }
    return current_path;
}

void PathImage::ToPpm(const std::string& name) const {
    //Writes out path_image_ in plain PPM format; filename is name.
    // Open the output file
  std::ofstream ofs{name};

  // Write the PPM header
  ofs << "P3" << "\n" << width_ << " " << height_ << "\n" << "255" << std::endl;

  // Write the pixel data
  for (size_t row = 0; row < height_; ++row) {
    std::string line;
    for (size_t col = 0; col < width_; ++col) {
        const Color& color = path_image_[row][col];
        line += std::to_string(color.Red()) + " " + std::to_string(color.Green()) + " " + std::to_string(color.Blue()) + " ";
    }
    line = line.substr(0, line.length() - 1);
    ofs << line << std::endl;
  }
}

// Getters
size_t PathImage::Width() const { return width_; }

size_t PathImage::Height() const { return height_; }

const std::vector<std::vector<Color>>& PathImage::GetPathImage() const { return path_image_; }

unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }