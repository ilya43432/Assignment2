#include <iostream>
#include "SquareMat.hpp"


int main() 
{
    double values[] = {1, 2, 3, 4, 5, 6 , 7 , 8, 9};
    double values2[] = {5, 6, 7, 8, 9, 10 , 11 , 12, 13};

    // 2 matrices of size 3x3, created using "new"
    // well have to free it later.
    SquareMat::SquareMat* mat1 = new SquareMat::SquareMat(3, values, 9);
    SquareMat::SquareMat* mat2 = new SquareMat::SquareMat(3, values2, 9);

    std::cout << "printing both matrices" << std::endl;

    std::cout << "mat1: " << std::endl;
    std::cout << *mat1 << std::endl;

    std::cout << "mat2: " << std::endl;
    std::cout << *mat2 << std::endl;

    // destructor usage
    delete mat1;
    delete mat2;

    SquareMat::SquareMat mat3(3, values, 9);
    SquareMat::SquareMat mat4(3, values2, 9);
    SquareMat::SquareMat mat5 = mat3 + mat4;

    std::cout << "mat3 + mat4: " << std::endl;
    std::cout << "matrix addition" << std::endl;
    std::cout << mat5 << std::endl;


    SquareMat::SquareMat mat6 = mat3 - mat4;
    std::cout << "matrix subtraction" << std::endl;
    std::cout << "mat3 - mat4: " << std::endl;

    std::cout << mat6 << std::endl;


    SquareMat::SquareMat mat7 = mat3 * mat4;
    std::cout << "matrix multiplication" << std::endl;
    std::cout << "mat3 * mat4: " << std::endl;

    std::cout << mat7 << std::endl;


    SquareMat::SquareMat mat8 = mat3 * 2;
    std::cout << "matrix multiplication by a scalar" << std::endl;
    std::cout << "mat3 * 2: " << std::endl;
    std::cout << mat8 << std::endl;

    SquareMat::SquareMat mat9 = mat3 / 2;
    std::cout << "matrix division by a scalar" << std::endl;
    std::cout << "mat3 / 2: " << std::endl;

    std::cout << mat9 << std::endl;

    SquareMat::SquareMat mat10 = mat3 % mat4;
    std::cout << "Matrix Multiplication - using the defined % operator for this assignment" << std::endl;
    std::cout << "mat3 % mat4: " << std::endl;

    SquareMat::SquareMat mat11 = mat3 % 2;
    std::cout << "Matrix modulo division by a scalar" << std::endl;
    std::cout << "mat3 % 2: " << std::endl;
    std::cout << mat11 << std::endl;

    SquareMat::SquareMat mat12 = mat3 ^ 2;
    std::cout << "Matrix power" << std::endl;
    std::cout << "mat3 ^ 2: " << std::endl;
    std::cout << mat12 << std::endl;

    SquareMat::SquareMat mat13 = ~mat3;
    std::cout << "Matrix transpose" << std::endl;
    std::cout << "mat3 ~: " << std::endl;
    std::cout << mat13 << std::endl;

    SquareMat::SquareMat mat14 = -mat3;
    std::cout << "Matrix negation" << std::endl;
    std::cout << "mat3 -: " << std::endl;
    std::cout << mat14 << std::endl;

    SquareMat::SquareMat mat15 = mat3++;
    std::cout << "Matrix postfix increment" << std::endl;
    std::cout << "mat3++: " << std::endl;
    std::cout << mat15 << std::endl;

    SquareMat::SquareMat mat16 = ++mat3;
    std::cout << "Matrix prefix increment" << std::endl;
    std::cout << "++mat3: " << std::endl;
    std::cout << mat16 << std::endl;

    SquareMat::SquareMat mat17 = mat3--;
    std::cout << "Matrix postfix decrement" << std::endl;
    std::cout << "mat3--: " << std::endl;
    std::cout << mat17 << std::endl;

    SquareMat::SquareMat mat18 = --mat3;
    std::cout << "Matrix prefix decrement" << std::endl;
    std::cout << "--mat3: " << std::endl;
    std::cout << mat18 << std::endl;

    return 0;
}