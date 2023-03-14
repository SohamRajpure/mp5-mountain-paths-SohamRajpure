#ifndef PATH_H
#define PATH_H

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

class Path {
public:
  // write behavior declarations here; define in path.cc.
  Path(size_t length, size_t starting_row);
  Path() = default;
  size_t Length() const;
  size_t StartingRow() const;
  unsigned int EleChange() const;
  void AddStep(size_t row);
  const std::vector<size_t>& GetPath() const;
  void IncEleChange(unsigned int ele_change);
  void SetLoc( size_t col, size_t row);
private:
  size_t length_ = 0;
  size_t starting_row_ = 0;
  std::vector<size_t> path_;
  unsigned int ele_change_ = 0;
};

#endif