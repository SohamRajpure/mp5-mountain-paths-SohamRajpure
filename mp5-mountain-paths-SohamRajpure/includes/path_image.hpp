#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <utility>

#include "color.hpp"
#include "path.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"

class PathImage {
public:
  // write behavior declarations here; define in path_image.cc.
  PathImage(const GrayscaleImage& image, const ElevationDataset& data);
  
  // Getters
  size_t Width() const;
  size_t Height() const;
  const std::vector<std::vector<Color>>& GetPathImage() const;
  const std::vector<Path>& GetPaths() const;
  Path ComputePath(size_t start_row, const ElevationDataset& dataset) const;
  unsigned int MaxColorValue() const;
  void ToPpm(const std::string& name) const;
private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  const Color kGreen = Color(31,253,13);
  const Color kRed = Color(252,25,63);
  const unsigned long kFunny = 4206;
};

#endif