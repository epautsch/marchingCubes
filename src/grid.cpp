#include "grid.hpp"

Grid::Grid(size_t width, size_t height, size_t depth)
    : width_(width),
      height_(height),
      depth_(depth),
      data_(width * height * depth) {}

Grid::~Grid() {}

void Grid::setValue(size_t x, size_t y, size_t z, float value) {
    size_t index = calculateIndex(x, y, z);
    data_[index] = value;
}

float Grid::getValue(size_t x, size_t y, size_t z) const {
    size_t index = calculateIndex(x, y, z);
    return data_[index];
}

void Grid::getDimension(size_t &width, size_t &height, size_t &depth) const {
    width = width_;
    height = height_;
    depth = depth_;
}

float *Grid::getRawData() { return data_.data(); }

const float *Grid::getRawData() const { return data_.data(); }

size_t Grid::calculateIndex(size_t x, size_t y, size_t z) const {
    return x + width_ * (y + height_ * z);
}

