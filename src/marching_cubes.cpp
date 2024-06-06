#include "marching_cubes.hpp"

MarchingCubes::MarchingCubes() {}

MarchingCubes::~MarchingCubes() {}

void MarchingCubes::computeIsosurface(const Grid& grid, float isovalue,
                                      std::vector<Triangle>& triangles) {
    runKernel(grid, isovalue, triangles);
}

void MarchingCubes::runKernel(const Grid& grid, float isovalue,
                              std::vector<Triangle>& triangles) {}