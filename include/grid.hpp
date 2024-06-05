#ifndef GRID_HPP
#define GRID_HPP

// #include <CL/sycl.hpp>
#include <vector>

#include "types.hpp"

class Grid {
   public:
    Grid(size_t width, size_t height, size_t depth);
    ~Grid();

    // Method to set the value at a specific point
    void setValue(size_t x, size_t y, size_t z, float value);

    float getValue(size_t x, size_t y, size_t z) const;

    // Method to get the dimensions of the grid
    void getDimension(size_t &width, size_t &height, size_t &depth) const;

    size_t calculateIndex(size_t x, size_t y, size_t z) const;

    // Method to get a pointer to the raw data (for SYCL operations)
    float *getRawData();              // read-write access
    const float *getRawData() const;  // read-only access

   private:
    size_t width_;
    size_t height_;
    size_t depth_;
    std::vector<float> data_;  // 3D grid data stored in a 1D vector
};

#endif