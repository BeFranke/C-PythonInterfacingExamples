#include "libmatmult.h"
#include <iostream>

double* mat_mult(double* mat1, double* mat2, int m1_dim1, int shared_dim, int m2_dim2) {
    double* result = new double[m1_dim1 * m2_dim2];
    for(auto i = 0; i < m1_dim1; ++i) {
        for(auto j = 0; j < m2_dim2; ++j) {
            result[i * m2_dim2 + j] = 0.0;
            for(int k = 0; k < shared_dim; ++k) {
                result[i * m2_dim2 + j] += mat1[i * shared_dim + k] * mat2[k * m2_dim2 + j];
            }
        }
    }
    return result;
}