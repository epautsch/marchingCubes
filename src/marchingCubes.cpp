// includes
#include <sycl/sycl.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace sycl;

const int edgeTable[256];
const int triTable[256][16];

struct Point {
  float x, y, z;
  float value;
};

int getIndex(const Point cube[8]) {
  int index = 0;
  for (int i = 0; i < 8; i++) {
    if (cube[i].value < 0) {
      index |= (1 <<i);
    }
  }
  return index;
}

void marchingCubesKernel(Point *points, int numPoints, 
                          std::vector<int>& outputIndices) {

    queue q; 
    buffer<Point, 1> pointsBuffer(points, range<1>(numPoints));
    buffer<int, 1> outputBuffer(outputIndices.data(), range<1>(outputIndices.size()));

    q.submit([&](handler &cgh) {
      auto points =
    }) 
}