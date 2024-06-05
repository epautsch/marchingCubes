#ifndef ISOSURFACE_HPP
#define ISOSURFACE_HPP

#include <vector>

#include "grid.hpp"
#include "types.hpp"

class Isosurface {
   public:
    Isosurface();
    ~Isosurface();

    // Method to generate the isosurface from a 3D grid
    void generateIsosurface(const Grid&, float isovalue,
                            std::vector<Triangle>& triangles);

    // Method to interpolate between two vertices based on the isovalue
    Vertex interpolate(const Vertex& v1, const Vertex& v2,
                       float isovalue) const;

    // Method to process a single cube in the grid
    void processCube(const Grid& grid, size_t x, size_t y, size_t z,
                     float isovalue, std::vector<Triangle>& triangles) const;

    // Method to caluculate the index in the edge table for a cube configuration
    int calculateEdgeIndex(const std::array<Vertex, 8>& cubeVertices,
                           float isovalue) const;
};

#endif