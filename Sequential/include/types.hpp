#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>

struct Point {
    float x, y, z;
};

struct Vertex {
    Point position;
    float value;
};

// Struct to represent a triangle
struct Triangle {
    Vertex vertices[3];  // Array of three vertices
};

#endif