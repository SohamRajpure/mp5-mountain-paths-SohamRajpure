#include "grayscale_image.hpp"
#include "color.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
    // Get the minimum and maximum elevation values
    int min_ele = dataset.MinEle();
    int max_ele = dataset.MaxEle();

    // Construct the grayscale image
    height_ = dataset.Height();
    width_ = dataset.Width();
    
    for (size_t i = 0; i < height_; ++i) {
        std::vector<Color> inner;
        for (size_t j = 0; j < width_; ++j) {
            int elevation_point = dataset.DatumAt(i, j);
            int32_t shade_of_gray = 0;
            if (max_ele != min_ele) {
                shade_of_gray = static_cast<int>(std::round((static_cast<double>(elevation_point) - min_ele) / (max_ele - min_ele) * kMaxColorValue));
            }
            Color gray_color(shade_of_gray, shade_of_gray, shade_of_gray);
            inner.push_back(gray_color);
        }
        image_.push_back(inner);
    }
}

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) : width_(width), height_(height) {
    ElevationDataset dataset(filename, width, height);
    int min_ele = dataset.MinEle();
    int max_ele = dataset.MaxEle();

    for (size_t i = 0; i < height_; ++i) {
        std::vector<Color> inner;
        for (size_t j = 0; j < width_; ++j) {
            int elevation_point = dataset.DatumAt(i, j);
            int shade_of_gray = 0;
            if (max_ele != min_ele) {
                shade_of_gray = static_cast<int>(std::round((static_cast<double>(elevation_point) - min_ele) / (max_ele - min_ele) * kMaxColorValue));
            }
            Color gray_color(shade_of_gray, shade_of_gray, shade_of_gray);
            inner.push_back(gray_color);
        }
        image_.push_back(inner);
    }
}

size_t GrayscaleImage::Width() const { return width_; }

size_t GrayscaleImage::Height() const { return height_; }

unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }

const Color& GrayscaleImage::ColorAt(int row, int col) const {
    return image_[row][col];
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
    return image_;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  // Open the output file
  std::ofstream ofs{name};

  // Write the PPM header
  ofs << "P3" << "\n" << width_ << " " << height_ << "\n" << "255" << std::endl;

  // Write the pixel data
  for (size_t row = 0; row < height_; ++row) {
    std::string line;
    for (size_t col = 0; col < width_; ++col) {
        const Color& color = image_[row][col];
        line += std::to_string(color.Red()) + " " + std::to_string(color.Green()) + " " + std::to_string(color.Blue()) + " ";
    }
    line = line.substr(0, line.length() - 1);
    ofs << line << std::endl;
  }
}