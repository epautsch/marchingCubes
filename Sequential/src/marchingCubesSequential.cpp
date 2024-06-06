#include <cmath>
#include <iostream>
#include <vector>

#include "define.h"

// Define Vec3f class
struct Vec3f {
    float x, y, z;
    Vec3f operator+(const Vec3f& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }
    Vec3f operator-(const Vec3f& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
    Vec3f operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }
};

// Define GRIDCELL and TriMeshFace structures
struct GRIDCELL {
    Vec3f p[8];
    float val[8];
};

struct TriMeshFace {
    int I[3];
};

// Define interpolation function
Vec3f VertexInterp(const Vec3f& p1, const Vec3f& p2, float valp1, float valp2) {
    return p1 + (-valp1 / (valp2 - valp1)) * (p2 - p1);
}

int Polygonise(GRIDCELL& Grid, TriMeshFace* Triangles, int& NewVertexCount,
               Vec3f* Vertices) {
    int TriangleCount;
    int CubeIndex;

    Vec3f VertexList[12];
    Vec3f NewVertexList[12];
    char LocalRemap[12];

    // Determine the index into the edge table which tells us which vertices are
    // inside of the surface
    CubeIndex = 0;
    if (Grid.val[0] < 0.0f) CubeIndex |= 1;
    if (Grid.val[1] < 0.0f) CubeIndex |= 2;
    if (Grid.val[2] < 0.0f) CubeIndex |= 4;
    if (Grid.val[3] < 0.0f) CubeIndex |= 8;
    if (Grid.val[4] < 0.0f) CubeIndex |= 16;
    if (Grid.val[5] < 0.0f) CubeIndex |= 32;
    if (Grid.val[6] < 0.0f) CubeIndex |= 64;
    if (Grid.val[7] < 0.0f) CubeIndex |= 128;

    // Cube is entirely in/out of the surface
    if (edgeTable[CubeIndex] == 0) return (0);

    // Find the vertices where the surface intersects the cube
    if (edgeTable[CubeIndex] & 1)
        VertexList[0] =
            VertexInterp(Grid.p[0], Grid.p[1], Grid.val[0], Grid.val[1]);
    if (edgeTable[CubeIndex] & 2)
        VertexList[1] =
            VertexInterp(Grid.p[1], Grid.p[2], Grid.val[1], Grid.val[2]);
    if (edgeTable[CubeIndex] & 4)
        VertexList[2] =
            VertexInterp(Grid.p[2], Grid.p[3], Grid.val[2], Grid.val[3]);
    if (edgeTable[CubeIndex] & 8)
        VertexList[3] =
            VertexInterp(Grid.p[3], Grid.p[0], Grid.val[3], Grid.val[0]);
    if (edgeTable[CubeIndex] & 16)
        VertexList[4] =
            VertexInterp(Grid.p[4], Grid.p[5], Grid.val[4], Grid.val[5]);
    if (edgeTable[CubeIndex] & 32)
        VertexList[5] =
            VertexInterp(Grid.p[5], Grid.p[6], Grid.val[5], Grid.val[6]);
    if (edgeTable[CubeIndex] & 64)
        VertexList[6] =
            VertexInterp(Grid.p[6], Grid.p[7], Grid.val[6], Grid.val[7]);
    if (edgeTable[CubeIndex] & 128)
        VertexList[7] =
            VertexInterp(Grid.p[7], Grid.p[4], Grid.val[7], Grid.val[4]);
    if (edgeTable[CubeIndex] & 256)
        VertexList[8] =
            VertexInterp(Grid.p[0], Grid.p[4], Grid.val[0], Grid.val[4]);
    if (edgeTable[CubeIndex] & 512)
        VertexList[9] =
            VertexInterp(Grid.p[1], Grid.p[5], Grid.val[1], Grid.val[5]);
    if (edgeTable[CubeIndex] & 1024)
        VertexList[10] =
            VertexInterp(Grid.p[2], Grid.p[6], Grid.val[2], Grid.val[6]);
    if (edgeTable[CubeIndex] & 2048)
        VertexList[11] =
            VertexInterp(Grid.p[3], Grid.p[7], Grid.val[3], Grid.val[7]);

    NewVertexCount = 0;
    for (int i = 0; i < 12; i++) LocalRemap[i] = -1;

    for (int i = 0; triTable[CubeIndex][i] != -1; i++) {
        if (LocalRemap[triTable[CubeIndex][i]] == -1) {
            NewVertexList[NewVertexCount] = VertexList[triTable[CubeIndex][i]];
            LocalRemap[triTable[CubeIndex][i]] = NewVertexCount;
            NewVertexCount++;
        }
    }

    for (int i = 0; i < NewVertexCount; i++) {
        Vertices[i] = NewVertexList[i];
    }

    TriangleCount = 0;
    for (int i = 0; triTable[CubeIndex][i] != -1; i += 3) {
        Triangles[TriangleCount].I[0] = LocalRemap[triTable[CubeIndex][i + 0]];
        Triangles[TriangleCount].I[1] = LocalRemap[triTable[CubeIndex][i + 1]];
        Triangles[TriangleCount].I[2] = LocalRemap[triTable[CubeIndex][i + 2]];
        TriangleCount++;
    }

    return (TriangleCount);
}

void marchingCubes(Point* points, int gridSize, std::vector<int>& outputIndices,
                   std::vector<Vec3f>& outputVertices) {
    int numCubes = (gridSize - 1) * (gridSize - 1);
    outputIndices.clear();
    outputVertices.clear();

    for (int z = 0; z < gridSize - 1; z++) {
        for (int y = 0; y < gridSize - 1; y++) {
            for (int x = 0; x < gridSize - 1; x++) {
                GRIDCELL gridCell;
                int index = 0;

                for (int i = 0; i < 8; i++) {
                    int xi = x + (i & 1);
                    int yi = y + ((i & 2) >> 1);
                    int zi = z + ((i & 4) >> 2);
                    Point& p = points[(zi * gridSize * gridSize) +
                                      (yi * gridSize) + xi];
                    gridCell.p[i] = {p.x, p.y, p.z};
                    gridCell.val[i] = p.value;
                }

                TriMeshFace triangles[5];
                Vec3f vertices[12];
                int newVertexCount = 0;
                int numTriangles =
                    Polygonise(gridCell, triangles, newVertexCount, vertices);

                for (int i = 0; i < newVertexCount; i++) {
                    outputVertices.push_back(vertices[i]);
                }

                for (int i = 0; i < numTriangles; i++) {
                    outputIndices.push_back(triangles[i].I[0]);
                    outputIndices.push_back(triangles[i].I[1]);
                    outputIndices.push_back(triangles[i].I[2]);
                }
            }
        }
    }
}

void createSphere(Point* points, int gridSize, float radius, Point center) {
    int index = 0;
    for (int z = 0; z < gridSize; z++) {
        for (int y = 0; y < gridSize; y++) {
            for (int x = 0; x < gridSize; x++) {
                float dx = (x - center.x);
                float dy = (y - center.y);
                float dz = (z - center.z);
                float distance = sqrt(dx * dx + dy * dy + dz * dz);
                points[index] = {static_cast<float>(x), static_cast<float>(y),
                                 static_cast<float>(z), distance - radius};
                index++;
            }
        }
    }
}

int main() {
    const int gridSize = 200;
    const float radius = 80.0f;
    Point center = {gridSize / 2.0f, gridSize / 2.0f, gridSize / 2.0f};

    int numPoints = gridSize * gridSize * gridSize;
    Point* points = new Point[numPoints];
    createSphere(points, gridSize, radius, center);

    std::vector<int> outputIndices;
    std::vector<Vec3f> outputVertices;
    marchingCubes(points, gridSize, outputIndices, outputVertices);

    delete[] points;
    return 0;
}
