#ifndef _MARCHING_CUBES_KERNEL_SYCL_HPP_
#define _MARCHING_CUBES_KERNEL_SYCL_HPP_

#include <CL/sycl.hpp>
#include <cstring>
#include <dpct/dpct.hpp>
#include <iostream>

#include "define.h"
#include "tables.h"

sycl::buffer<unit32_t, 1> edgeBuffer(edgeTable, sycl::range<1>(256));
sycl::buffer<unit32_t, 1> triBuffer(triTable, sycl::range<1>(4096));
sycl::buffer<unit32_t, 1> numVertsBuffer(numVertsTable, sycl::range<1>(256));

extern "C" void allocateBuffers(sycl::queue &q, uint32_t **d_edgeTable,
                                uint32_t **d_triTable,
                                uint32_t **d_numVertsTable) {
    *d_edgeTable = sycl::malloc_device<uint32_t>(256, q);
    q.memcpy(*d_edgeTable, edgeTable, 256 * sizeof(uint32_t)).wait();

    *d_triTable = sycl::malloc_device<uint32_t>(256, q);
    q.memcpy(*d_triTable, triTable, 256 * 16 * sizeof(uint32_t)).wait();

    *d_numVertsTable = sycl::malloc_device<uint32_t>(256, q);
    q.memcpy(*d_numVertsTable, numVertsTable, 256 * sizeof(uint32_t)).wait();
}

// Test kernel to verify data
void testKernel(sycl::queue &q, uint32_t *d_edgeTable, uint32_t *d_triTable,
                uint32_t *d_numVertsTable) {
    q.submit([&](sycl::handler &h) {
         // Accessors for the buffers
         auto edgeAcc = edgeBuffer.get_access<sycl::access::mode::read>(h);
         auto triAcc = triBuffer.get_access<sycl::access::mode::read>(h);
         auto numVertsAcc =
             numVertsBuffer.get_access<sycl::access::mode::read>(h);

         h.parallel_for<class TestKernel>(
             sycl::range<1>(256), [=](sycl::id<1> idx) {
                 uint32_t edgeVal = edgeAcc[idx];
                 uint32_t vertVal = numVertsAcc[idx];

                 if (edgeVal != d_edgeTable[idx] ||
                     vertVal != d_numVertsTable[idx]) {
                     printf("Mismatch at idx %d: edgeVal = %d, vertVal = %d\n",
                            idx[0], edgeVal, vertVal);
                 }
             });
     }).wait();
}

int main() {
    sycl::queue q;

    uint32_t *d_edgeTable;
    uint32_t *d_triTable;
    uint32_t *d_numVertsTable;

    // Allocate and copy buffers
    allocateBuffers(q, &d_edgeTable, &d_triTable, &d_numVertsTable);

    // Run test kernel
    testKernel(q, d_edgeTable, d_triTable, d_numVertsTable);

    // Free device memory
    sycl::free(d_edgeTable, q);
    sycl::free(d_triTable, q);
    sycl::free(d_numVertsTable, q);

    std::cout << "Test completed." << std::endl;

    return 0;
}