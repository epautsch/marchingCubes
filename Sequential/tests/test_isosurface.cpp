#include <gtest/gtest.h>

#include <array>

#include "isosurface.hpp"

class IsosurfaceTest : public ::testing::Test {
   protected:
    void SetUp() override {
        grid = new Grid(3, 3, 3);

        // Random grid
        for (size_t x = 0; x < 3; x++) {
            for (size_t y = 0; y < 3; y++) {
                for (size_t z = 0; z < 3; z++) {
                    grid->setValue(x, y, z, static_cast<float>(x + y + z));
                }
            }
        }

        isosurface = new Isosurface();
    }

    void TearDown() override {
        delete grid;
        delete isosurface;
    }

    Grid *grid;
    Isosurface *isosurface;
};

// Test generating the isosurface
TEST_F(IsosurfaceTest, GenerateIsosurface) {
    std::vector<Triangle> triangles;
    float isovalue = 3.0f;
    isosurface->generateIsosurface(*grid, isovalue, triangles);

    // Verify the number of triangles generated
    ASSERT_FALSE(triangles.empty());

    for (const auto &triangle : triangles) {
        for (const auto &vertex : triangle.vertices) {
            std::cout << "Vertex position: (" << vertex.position.x << ", "
                      << vertex.position.y << ", " << vertex.position.z
                      << "), value = " << vertex.value << std::endl;
        }
    }
}

// Test interpolation
TEST_F(IsosurfaceTest, Interpolate) {
    Vertex v1 = {Point{0.0f, 0.0f, 0.0f}, 1.0f};
    Vertex v2 = {Point{1.0f, 1.0f, 1.0f}, 5.0f};
    float isovalue = 3.0f;

    Vertex result = isosurface->interpolate(v1, v2, isovalue);

    EXPECT_NEAR(result.position.x, 0.5f, 0.0001f);
    EXPECT_NEAR(result.position.y, 0.5f, 0.0001f);
    EXPECT_NEAR(result.position.z, 0.5f, 0.0001f);
    EXPECT_NEAR(result.value, isovalue, 0.0001f);
}

// Test edge index calculation
TEST_F(IsosurfaceTest, CalculateEdgeIndex) {
    std::array<Vertex, 8> cubeVertices = {
        Vertex{Point{0.0f, 0.0f, 0.0f}, 1.0f},
        Vertex{Point{1.0f, 1.0f, 1.0f}, 2.0f},
        Vertex{Point{1.0f, 1.0f, 0.0f}, 3.0f},
        Vertex{Point{0.0f, 1.0f, 0.0f}, 4.0f},
        Vertex{Point{0.0f, 0.0f, 1.0f}, 5.0f},
        Vertex{Point{1.0f, 0.0f, 1.0f}, 6.0f},
        Vertex{Point{1.0f, 1.0f, 1.0f}, 7.0f},
        Vertex{Point{0.0f, 1.0f, 1.0f}, 8.0f}};

    float isovalue = 4.5f;

    int edgeIndex = isosurface->calculateEdgeIndex(cubeVertices, isovalue);

    for (int i = 0; i < 8; i++) {
        std::cout << "Vertex " << i << "; value = " << cubeVertices[i].value
                  << std::endl;
    }
    std::cout << "Calculation edge index: " << edgeIndex << std::endl;

    EXPECT_EQ(edgeIndex, 0b00001111);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}