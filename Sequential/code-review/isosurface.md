# Isosurfacce 

Review and explanation of the isosurface program.

## What is an isosurface?  
An $\text{isosurface}$ is like a $3D$ version of a contour line on a map. It forms a surface that connects all points within a three-dimensional space that share the same value (such as temperature, pressure, velocity, or density). Essentially, it is a surface that highlights where a specific value exists within a $3D$ volume.

We begin by going through the process of generating a isosurface in our isosurface class: 

```cpp
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
```