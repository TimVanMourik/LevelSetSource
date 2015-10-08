#ifndef CURVATUREKERNEL_HPP
#define CURVATUREKERNEL_HPP

#include "Matrix.hpp"

class CurvatureKernel : public Matrix
{
public:
    CurvatureKernel(
            ) : Matrix(26, 9)
    {
        (*this)(0, 0)  = 1; (*this)(0, 1)  = 1; (*this)(0, 2)  = 1; (*this)(0, 3)  = 2;  (*this)(0, 4)  = 2;  (*this)(0, 5)  = 2;  (*this)(0, 6)  = -1; (*this)(0, 7)  = -1; (*this)(0, 8)  = -1;
        (*this)(1, 0)  = 1; (*this)(1, 1)  = 1; (*this)(1, 2)  = 0; (*this)(1, 3)  = 2;  (*this)(1, 4)  = 0;  (*this)(1, 5)  = 0;  (*this)(1, 6)  = -1; (*this)(1, 7)  = -1; (*this)(1, 8)  = 0;
        (*this)(2, 0)  = 1; (*this)(2, 1)  = 1; (*this)(2, 2)  = 1; (*this)(2, 3)  = 2;  (*this)(2, 4)  = -2; (*this)(2, 5)  = -2; (*this)(2, 6)  = -1; (*this)(2, 7)  = -1; (*this)(2, 8)  = 1;
        (*this)(3, 0)  = 1; (*this)(3, 1)  = 0; (*this)(3, 2)  = 1; (*this)(3, 3)  = 0;  (*this)(3, 4)  = 0;  (*this)(3, 5)  = 2;  (*this)(3, 6)  = -1; (*this)(3, 7)  = 0;  (*this)(3, 8)  = -1;
        (*this)(4, 0)  = 1; (*this)(4, 1)  = 0; (*this)(4, 2)  = 0; (*this)(4, 3)  = 0;  (*this)(4, 4)  = 0;  (*this)(4, 5)  = 0;  (*this)(4, 6)  = -1; (*this)(4, 7)  = 0;  (*this)(4, 8)  = 0;
        (*this)(5, 0)  = 1; (*this)(5, 1)  = 0; (*this)(5, 2)  = 1; (*this)(5, 3)  = 0;  (*this)(5, 4)  = 0;  (*this)(5, 5)  = -2; (*this)(5, 6)  = -1; (*this)(5, 7)  = 0;  (*this)(5, 8)  = 1;
        (*this)(6, 0)  = 1; (*this)(6, 1)  = 1; (*this)(6, 2)  = 1; (*this)(6, 3)  = -2; (*this)(6, 4)  = -2; (*this)(6, 5)  = 2;  (*this)(6, 6)  = -1; (*this)(6, 7)  = 1;  (*this)(6, 8)  = -1;
        (*this)(7, 0)  = 1; (*this)(7, 1)  = 1; (*this)(7, 2)  = 0; (*this)(7, 3)  = -2; (*this)(7, 4)  = 0;  (*this)(7, 5)  = 0;  (*this)(7, 6)  = -1; (*this)(7, 7)  = 1;  (*this)(7, 8)  = 0;
        (*this)(8, 0)  = 1; (*this)(8, 1)  = 1; (*this)(8, 2)  = 1; (*this)(8, 3)  = -2; (*this)(8, 4)  = 2;  (*this)(8, 5)  = -2; (*this)(8, 6)  = -1; (*this)(8, 7)  = 1;  (*this)(8, 8)  = 1;
        (*this)(9, 0)  = 0; (*this)(9, 1)  = 1; (*this)(9, 2)  = 1; (*this)(9, 3)  = 0;  (*this)(9, 4)  = 2;  (*this)(9, 5)  = 0;  (*this)(9, 6)  = 0;  (*this)(9, 7)  = -1; (*this)(9, 8)  = -1;
        (*this)(10, 0) = 0; (*this)(10, 1) = 1; (*this)(10, 2) = 0; (*this)(10, 3) = 0;  (*this)(10, 4) = 0;  (*this)(10, 5) = 0;  (*this)(10, 6) = 0;  (*this)(10, 7) = -1; (*this)(10, 8) = 0;
        (*this)(11, 0) = 0; (*this)(11, 1) = 1; (*this)(11, 2) = 1; (*this)(11, 3) = 0;  (*this)(11, 4) = -2; (*this)(11, 5) = 0;  (*this)(11, 6) = 0;  (*this)(11, 7) = -1; (*this)(11, 8) = 1;
        (*this)(12, 0) = 0; (*this)(12, 1) = 0; (*this)(12, 2) = 1; (*this)(12, 3) = 0;  (*this)(12, 4) = 0;  (*this)(12, 5) = 0;  (*this)(12, 6) = 0;  (*this)(12, 7) = 0;  (*this)(12, 8) = -1;
        (*this)(13, 0) = 0; (*this)(13, 1) = 0; (*this)(13, 2) = 1; (*this)(13, 3) = 0;  (*this)(13, 4) = 0;  (*this)(13, 5) = 0;  (*this)(13, 6) = 0;  (*this)(13, 7) = 0;  (*this)(13, 8) = 1;
        (*this)(14, 0) = 0; (*this)(14, 1) = 1; (*this)(14, 2) = 1; (*this)(14, 3) = 0;  (*this)(14, 4) = -2; (*this)(14, 5) = 0;  (*this)(14, 6) = 0;  (*this)(14, 7) = 1;  (*this)(14, 8) = -1;
        (*this)(15, 0) = 0; (*this)(15, 1) = 1; (*this)(15, 2) = 0; (*this)(15, 3) = 0;  (*this)(15, 4) = 0;  (*this)(15, 5) = 0;  (*this)(15, 6) = 0;  (*this)(15, 7) = 1;  (*this)(15, 8) = 0;
        (*this)(16, 0) = 0; (*this)(16, 1) = 1; (*this)(16, 2) = 1; (*this)(16, 3) = 0;  (*this)(16, 4) = 2;  (*this)(16, 5) = 0;  (*this)(16, 6) = 0;  (*this)(16, 7) = 1;  (*this)(16, 8) = 1;
        (*this)(17, 0) = 1; (*this)(17, 1) = 1; (*this)(17, 2) = 1; (*this)(17, 3) = -2; (*this)(17, 4) = 2;  (*this)(17, 5) = -2; (*this)(17, 6) = 1;  (*this)(17, 7) = -1; (*this)(17, 8) = -1;
        (*this)(18, 0) = 1; (*this)(18, 1) = 1; (*this)(18, 2) = 0; (*this)(18, 3) = -2; (*this)(18, 4) = 0;  (*this)(18, 5) = 0;  (*this)(18, 6) = 1;  (*this)(18, 7) = -1; (*this)(18, 8) = 0;
        (*this)(19, 0) = 1; (*this)(19, 1) = 1; (*this)(19, 2) = 1; (*this)(19, 3) = -2; (*this)(19, 4) = -2; (*this)(19, 5) = 2;  (*this)(19, 6) = 1;  (*this)(19, 7) = -1; (*this)(19, 8) = 1;
        (*this)(20, 0) = 1; (*this)(20, 1) = 0; (*this)(20, 2) = 1; (*this)(20, 3) = 0;  (*this)(20, 4) = 0;  (*this)(20, 5) = -2; (*this)(20, 6) = 1;  (*this)(20, 7) = 0;  (*this)(20, 8) = -1;
        (*this)(21, 0) = 1; (*this)(21, 1) = 0; (*this)(21, 2) = 0; (*this)(21, 3) = 0;  (*this)(21, 4) = 0;  (*this)(21, 5) = 0;  (*this)(21, 6) = 1;  (*this)(21, 7) = 0;  (*this)(21, 8) = 0;
        (*this)(22, 0) = 1; (*this)(22, 1) = 0; (*this)(22, 2) = 1; (*this)(22, 3) = 0;  (*this)(22, 4) = 0;  (*this)(22, 5) = 2;  (*this)(22, 6) = 1;  (*this)(22, 7) = 0;  (*this)(22, 8) = 1;
        (*this)(23, 0) = 1; (*this)(23, 1) = 1; (*this)(23, 2) = 1; (*this)(23, 3) = 2;  (*this)(23, 4) = -2; (*this)(23, 5) = -2; (*this)(23, 6) = 1;  (*this)(23, 7) = 1;  (*this)(23, 8) = -1;
        (*this)(24, 0) = 1; (*this)(24, 1) = 1; (*this)(24, 2) = 0; (*this)(24, 3) = 2;  (*this)(24, 4) = 0;  (*this)(24, 5) = 0;  (*this)(24, 6) = 1;  (*this)(24, 7) = 1;  (*this)(24, 8) = 0;
        (*this)(25, 0) = 1; (*this)(25, 1) = 1; (*this)(25, 2) = 1; (*this)(25, 3) = 2;  (*this)(25, 4) = 2;  (*this)(25, 5) = 2;  (*this)(25, 6) = 1;  (*this)(25, 7) = 1;  (*this)(25, 8) = 1;
    }
};

// 1  1  1    2   2   2
// 1  1  0    2   0   0
// 1  1  1    2  -2  -2
// 1  0  1    0   0   2
// 1  0  0    0   0   0
// 1  0  1    0   0  -2
// 1  1  1   -2  -2   2
// 1  1  0   -2   0   0
// 1  1  1   -2   2  -2
// 0  1  1    0   2   0
// 0  1  0    0   0   0
// 0  1  1    0  -2   0
// 0  0  1    0   0   0
// 0  0  1    0   0   0
// 0  1  1    0  -2   0
// 0  1  0    0   0   0
// 0  1  1    0   2   0
// 1  1  1   -2   2  -2
// 1  1  0   -2   0   0
// 1  1  1   -2  -2   2
// 1  0  1    0   0  -2
// 1  0  0    0   0   0
// 1  0  1    0   0   2
// 1  1  1    2  -2  -2
// 1  1  0    2   0   0
// 1  1  1    2   2   2

#endif // CURVATUREKERNEL_HPP