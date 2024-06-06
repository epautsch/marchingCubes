#ifndef MARCHING_CUBES_HPP
#define MARCHING_CUBES_HPP

// #include <CL/sycl.hpp>

#include "grid.hpp"
#include "types.hpp"

class MarchingCubes {
   public:
    MarchingCubes();
    ~MarchingCubes();

    void computeIsosurface(const Grid&, float isovalue,
                           std::vector<Triangle>& triangles);

   private:
    void runKernel(const Grid& grid, float isovalue,
                   std::vector<Triangle>& triangles);
};

#endif