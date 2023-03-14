#include "path.hpp"
#include <stdexcept>
Path::Path(size_t length, size_t starting_row) : length_(length), starting_row_(starting_row) {
  for (size_t i = 0; i < length; i++) {
    path_.push_back(starting_row);
  }
}

size_t Path::StartingRow() const {
  return starting_row_;
}

size_t Path::Length() const {
  return length_;
}

const std::vector<size_t>& Path::GetPath() const {
  return path_;
}

unsigned int Path::EleChange() const {
  return ele_change_;
}

void Path::AddStep(size_t row) {
  path_.push_back(row);
  ++length_;
}

void Path::IncEleChange(unsigned int ele_change) {
  ele_change_ += ele_change;
}

void Path::SetLoc(size_t col, size_t row) {
  path_.at(col) = row;
}