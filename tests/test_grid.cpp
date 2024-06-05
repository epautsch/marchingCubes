#include <gtest/gtest.h>

#include "grid.hpp"

class GridTest : public ::testing::Test {
   protected:
    void SetUp() override {
        grid = new Grid(10, 10, 10);  // Create a 10x10x10 for testing
    }
    void TearDown() override { delete grid; }

    Grid *grid;
};

// Test grid initialization and dimensions
TEST_F(GridTest, InitializationAndDimensions) {
    size_t width, height, depth;
    grid->getDimension(width, height, depth);

    EXPECT_EQ(width, 10);
    EXPECT_EQ(height, 10);
    EXPECT_EQ(depth, 10);
}

// Test setting and getting values
TEST_F(GridTest, SetValuesAndGetValue) {
    grid->setValue(5, 5, 5, 3.14f);
    EXPECT_FLOAT_EQ(grid->getValue(5, 5, 5), 3.14f);
}

// Test setting and getting values at the boundaries
TEST_F(GridTest, SetValueAndGetValueAtBoundaries) {
    grid->setValue(0, 0, 0, 1.0f);
    grid->setValue(9, 9, 9, 2.0f);

    EXPECT_FLOAT_EQ(grid->getValue(0, 0, 0), 1.0f);
    EXPECT_FLOAT_EQ(grid->getValue(9, 9, 9), 2.0f);
}

// Test raw data access
TEST_F(GridTest, RawDataAccess) {
    float *rawData = grid->getRawData();
    rawData[grid->calculateIndex(5, 5, 5)] = 2.71f;
    EXPECT_FLOAT_EQ(grid->getValue(5, 5, 5), 2.71f);

    const float *constRawData = grid->getRawData();
    EXPECT_FLOAT_EQ(constRawData[grid->calculateIndex(5, 5, 5)], 2.71f);
}

// Test calculate index
TEST_F(GridTest, CalculateIndex) {
    size_t index = grid->calculateIndex(5, 5, 5);
    EXPECT_EQ(index, 5 + 10 * (5 + 10 * 5));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}