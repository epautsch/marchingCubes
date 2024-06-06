#include "isosurface.hpp"

#include <array>
#include <cmath>

#include "define.h"
#include "types.hpp"

#define EPISOLN 0.00001

// Constructor
Isosurface::Isosurface() {}

// Destructor
Isosurface::~Isosurface() {}

// Isosurface from a 3D grid
void Isosurface::generateIsosurface(const Grid& grid, float isovalue,
                                    std::vector<Triangle>& triangles) {
    size_t width, height, depth;
    grid.getDimension(width, height, depth);

    // for each cube in the grid
    for (size_t x = 0; x < width - 1; x++) {
        for (size_t y = 0; y < width - 1; y++) {
            for (size_t z = 0; z < depth - 1; z++) {
                processCube(grid, x, y, z, isovalue, triangles);
            }
        }
    }
}

// Interpolate between two vertices base on the isovalue
Vertex Isosurface::interpolate(const Vertex& v1, const Vertex& v2,
                               float isovalue) const {
    // If v1 is very close to the isovalue then
    // v1 is on the isosurface
    if (std::abs(isovalue - v1.value) < EPISOLN) {
        return v1;
    }
    // If v2 is very close to the isovalue then
    // v2 is on the isosurface
    if (std::abs(isovalue - v2.value) < EPISOLN) {
        return v2;
    }
    // If v1 and v2 are very close to each other
    // then the two verices are the same scalar
    // value (no need for interpolation)
    // WLOG return v1
    if (std::abs(v1.value - v2.value) < EPISOLN) {
        return v1;
    }

    float t = (isovalue - v1.value) / (v2.value - v1.value);
    Vertex v;
    v.position.x = v1.position.x + t * (v2.position.x - v1.position.x);
    v.position.y = v1.position.y + t * (v2.position.y - v1.position.y);
    v.position.z = v1.position.z + t * (v2.position.z - v.position.z);
    v.value = isovalue;
    return v;
}

// Process a single cube in the grid
void Isosurface::processCube(const Grid& grid, size_t x, size_t y, size_t z,
                             float isovalue,
                             std::vector<Triangle>& triangles) const {
    ////////////////////////////////////////////
    // LOOk FOR A BETTER WAY. IT WORKS FOR NOW
    float x_float = static_cast<float>(x);
    float y_float = static_cast<float>(y);
    float z_float = static_cast<float>(z);
    ////////////////////////////////////////////
    // Get the values at the 8 corners of the cube
    std::array<Vertex, 8> cubeVertices = {
        Vertex{Point{x_float, y_float, z_float}, grid.getValue(x, y, z)},
        Vertex{Point{x_float + 1, y_float, z_float},
               grid.getValue(x + 1, y, z)},
        Vertex{Point{x_float + 1, y_float + 1, z_float},
               grid.getValue(x + 1, y + 1, z)},
        Vertex{Point{x_float, y_float + 1, z_float},
               grid.getValue(x, y + 1, z)},
        Vertex{Point{x_float, y_float, z_float + 1},
               grid.getValue(x, y, z + 1)},
        Vertex{Point{x_float + 1, y_float, z_float + 1},
               grid.getValue(x + 1, y, z + 1)},
        Vertex{Point{x_float + 1, y_float + 1, z_float + 1},
               grid.getValue(x + 1, y + 1, z + 1)},
        Vertex{Point{x_float, y_float + 1, z_float + 1},
               grid.getValue(x, y + 1, z + 1)},
    };

    //////////////////////////////////////////////////////////
    int edgeIndex = calculateEdgeIndex(cubeVertices, isovalue);
    //////////////////////////////////////////////////////////

    // check if the cube is entirely inside or outside the isosurface
    if (edgeIndex == 0 || edgeIndex == 255) {
        return;
    }

    //////////////////////////////////////////////////////////
    // A list of interpolated vertices on the edges of the cube
    std::array<Vertex, 12> edgeVertices;
    if (edgeTable[edgeIndex] & 1) {
        edgeVertices[0] =
            interpolate(cubeVertices[0], cubeVertices[1], isovalue);
    }
    if (edgeTable[edgeIndex] & 2) {
        edgeVertices[1] =
            interpolate(cubeVertices[1], cubeVertices[2], isovalue);
    }
    if (edgeTable[edgeIndex] & 4) {
        edgeVertices[2] =
            interpolate(cubeVertices[2], cubeVertices[3], isovalue);
    }
    if (edgeTable[edgeIndex] & 8) {
        edgeVertices[3] =
            interpolate(cubeVertices[3], cubeVertices[0], isovalue);
    }
    if (edgeTable[edgeIndex] & 16) {
        edgeVertices[4] =
            interpolate(cubeVertices[4], cubeVertices[5], isovalue);
    }
    if (edgeTable[edgeIndex] & 32) {
        edgeVertices[5] =
            interpolate(cubeVertices[5], cubeVertices[6], isovalue);
    }
    if (edgeTable[edgeIndex] & 64) {
        edgeVertices[6] =
            interpolate(cubeVertices[6], cubeVertices[7], isovalue);
    }
    if (edgeTable[edgeIndex] & 128) {
        edgeVertices[7] =
            interpolate(cubeVertices[7], cubeVertices[4], isovalue);
    }
    if (edgeTable[edgeIndex] & 256) {
        edgeVertices[8] =
            interpolate(cubeVertices[0], cubeVertices[4], isovalue);
    }
    if (edgeTable[edgeIndex] & 512) {
        edgeVertices[9] =
            interpolate(cubeVertices[1], cubeVertices[5], isovalue);
    }
    if (edgeTable[edgeIndex] & 1024) {
        edgeVertices[10] =
            interpolate(cubeVertices[2], cubeVertices[6], isovalue);
    }
    if (edgeTable[edgeIndex] & 2048) {
        edgeVertices[11] =
            interpolate(cubeVertices[3], cubeVertices[7], isovalue);
    }

    //////////////////////////////////////////////////////////

    // Generate triangles based on the edge table
    for (int i = 0; triTable[edgeIndex][i] != -1; i += 3) {
        Triangle triangle;
        triangle.vertices[0] = edgeVertices[triTable[edgeIndex][i]];
        triangle.vertices[1] = edgeVertices[triTable[edgeIndex][i + 1]];
        triangle.vertices[2] = edgeVertices[triTable[edgeIndex][i + 2]];
        triangles.push_back(triangle);
    }
}

// Method to calculate the index in the edge table for cube configuration
int Isosurface::calculateEdgeIndex(const std::array<Vertex, 8>& cubeVertices,
                                   float isovalue) const {
    int edgeIndex = 0;
    for (int i = 0; i < 8; ++i) {
        if (cubeVertices[i].value < isovalue) {
            edgeIndex |= (1 << i);
        }
    }
    return edgeIndex;
}