// iliyacod@gmail.com
#pragma once
#include <iostream>
#include <cmath>

#define eps 0.0001 // since we are using double values for the matrix 

// this is the header file for the SquareMat class.
// this header contains the class definition as well as the function declarations.
// i have implemented 2 constuctors -
// 1 is a default constructor which takes a size N and allocates the memory for the matrix.
// 2 is a constructor which takes a size N and a pointer to a double array.
// both of these constructors are explicit because I want to avoid
// any unintentional conversions. i don't want to be able to create a matrix
// using an input that was not intended for that.

// using explicit i can always asure the matrix
// will be created using the intended input.
// for example - SquareMat mat(6); which will be a 6x6 matrix


namespace SquareMat
{
    class SquareMat
    {
    private:
        // private members:
        // N, the size of the matrix
        // **arr, the pointer to the matrix
        int N;
        double **arr;

    public:

        explicit SquareMat(int size) : N(size)
        {
            if (size <= 0)
            {
                throw std::invalid_argument("Size must be positive");
            }

            int allocated = 0;
            try
            {
                arr = new double *[N];
                while (allocated < N)
                {
                    arr[allocated] = new double[N]{};
                    allocated++;
                }
            }
            catch (const std::exception &ex)
            {
                for (int i = 0; i < allocated; ++i)
                {
                    delete[] arr[i];
                }
                delete[] arr;
                throw std::runtime_error(ex.what());
            }
        }
        // a 2nd constructor which takes a size N and a pointer to
        // a double array. this function is explicit because we want to
        explicit SquareMat(int size, const double *values, int values_size) : N(size)
        {
            // size validation check
            if (size <= 0)
            {
                throw std::invalid_argument("Size must be positive");
            }
            // array values validation
            if (!values)
            {
                throw std::invalid_argument("Values array cannot be null");
            }

            // values size needs to be N*N - meaning it has to be square
            if (values_size != N * N)
            {
                throw std::invalid_argument("Values array size does not match matrix size");
            }

            // we have to check inside the array if any of the values are null
            const double *ptr_value = values;

            for (int i = 0; i < N * N; ++i)
            {
                double val_Arr = *ptr_value;
                // check if the value is null using cmath library
                if (std::isnan(val_Arr))
                {
                    throw std::invalid_argument("value is null!");
                }
                // do that for the whole array
                ++ptr_value;
            }
            // values array are valid therfore we keep going. allocating memory for the matrix
            arr = new double *[N];
            int allocated = 0;
            try
            {
                int k = 0;

                while (allocated < N)

                {
                    arr[allocated] = new double[N];
                    for (int j = 0; j < N; ++j)
                    {
                        // insert the values to the matrix
                        // incrementing k each iteration
                        arr[allocated][j] = values[k++];
                    }
                    allocated++;
                }
            }
            catch (const std::exception &ex)
            {
                for (int i = 0; i < allocated; ++i)
                {
                    delete[] arr[i];
                }
                delete[] arr;
                throw std::runtime_error(ex.what());
            }
        }

        // destructor
        ~SquareMat();

        // copy constructor, deep copy of a matrix
        SquareMat(const SquareMat &other_mat);

        // copy assignment operator, used in the copy assignment
        SquareMat &operator=(const SquareMat &other);

        // getter function. size of the matrix(N is reffered to N*N matrix, since all the matrices are squares)
        int get_size() const
        {
            return N;
        }

        // matrix sum function
        double sum() const
        {
            double sum = 0;
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; ++j)
                {
                    sum += arr[i][j];
                }
            }
            return sum;
        }

        // this function will be used for the row reductions
        // as learned in algebra 1
        void swap_rows(int i, int j)
        {
            // index validation check
            if (i < 0 || i >= N || j < 0 || j >= N)
            {
                throw std::out_of_range("Index out of bounds");
            }

            double *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }

        // the formula is as follows:
        // (A|I) ---> (I|A^-1)
        // we have learned this in linear algebra 2

        SquareMat inverse() const
        {
            // matrix size validation
            if (N <= 0)
            {
                throw std::invalid_argument("Matrix size must be positive");
            }

            // a matrix that has a determinant of 0 is not invertible
            // i check if its less than epsilon because we
            // are dealing with double values.
            if (std::abs(!*this) < eps)
            {
                throw std::invalid_argument("matrix cannot be inversed");
            }

            // create a working copy of the current matrix
            SquareMat A(*this);

            // create an identity matrix of the same size
            SquareMat I(N); // I for identity

            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < N; ++j)
                {
                    if (i == j)
                    {
                        I[i][j] = 1;
                    }
                    else
                    {
                        I[i][j] = 0;
                    }
                }
            }

            // row reductions
            for (int pivot = 0; pivot < N; ++pivot)
            {

                // the pivot element is the diagonal element of the current row
                double pivot_val = A[pivot][pivot];

                // if the pivot is zero (or very close to it), we have to fix it
                // and find a better pivot in a different row and work with it
                if (std::abs(pivot_val) < eps)
                {
                    // we have to find the pivot which we can work with
                    // and
                    bool foundValidPivot = false;

                    // search the rows below for a better pivot
                    for (int potential_pivot = pivot + 1; potential_pivot < N; ++potential_pivot)
                    {
                        // if we find a row with a that isnt withn the eps threshold
                        // we can work with it

                        if (std::abs(A[potential_pivot][pivot]) > eps)
                        {

                            // swap the pivot row with the row we found
                            A.swap_rows(pivot, potential_pivot);
                            I.swap_rows(pivot, potential_pivot);

                            // we get the new pivot val
                            pivot_val = A[pivot][pivot];

                            foundValidPivot = true;
                            // we can now perform the "row reduction"
                            break;
                        }
                    }

                    // if the loop ends and we didnt find a pivot then the matrix
                    // cannot be inversed
                    if (!foundValidPivot)
                    {
                        throw std::runtime_error("matrix cannot be inversed");
                    }
                }

                // divide the entire pivot row by the pivot value
                // so that the pivot becomes 1

                // we can use our implemented matrix operators for this
                for (int col = 0; col < N; ++col)
                {
                    // divide the pvt row in order to make it 1
                    A[pivot][col] /= pivot_val;

                    // we do it in the iden mat as well
                    // this is a method we used in linear algebra 2
                    I[pivot][col] /= pivot_val;
                }

                // now eliminate the pivot column values in all other rows
                for (int row = 0; row < N; ++row)
                {
                    // skip the pivot row itself
                    if (row == pivot)
                    {
                        continue;
                    }

                    // the pivot multiplier to eliminate the value in the current row
                    double pvt_mult = A[row][pivot];

                    // substraction of 
                    for (int col = 0; col < N; ++col)
                    {
                        // perform the row reduction on both the given matrix and the identity matrix
                        A[row][col] = (A[row][col]) -(pvt_mult * A[pivot][col]);
                        I[row][col] = (I[row][col])- (pvt_mult * I[pivot][col]);
                    }
                }
            }
            // I is now the inverse of a
            return I;
        }

        // plus/minus between 2 matrices.
        SquareMat operator+(const SquareMat &mat) const;
        SquareMat operator-(const SquareMat &mat) const;

        // unary operator on a matrix.
        SquareMat operator-() const;

        // multiplication between 2 matrices.
        SquareMat operator*(const SquareMat &mat) const;

        // scalar multiplication on a matrix.
        SquareMat operator*(double scalar) const;

        // scalar modulo on a matrix.
        SquareMat operator%(const SquareMat &mat) const;

        // scalar modulo on a matrix.
        SquareMat operator%(int scalar) const;

        //  matrix division using a scalar.
        SquareMat operator/(double scalar) const;

        // matrix power operator with an integer
        SquareMat operator^(int power) const;

        // prefix increment operator
        SquareMat &operator++();

        // postfix increment operator
        SquareMat operator++(int);

        // prefix decrement operator
        SquareMat &operator--();

        // postfix decrement operator
        SquareMat operator--(int);

        // transpose operator
        SquareMat operator~() const;

        // access operator for the matrix to modify an element
        double *operator[](int index);

        // constant operator[] to
        // access an element without the need to change it.
        const double *operator[](int index) const;

        // comparison operators
        bool operator==(const SquareMat &mat) const;
        bool operator!=(const SquareMat &mat) const;
        bool operator<(const SquareMat &mat) const;
        bool operator>(const SquareMat &mat) const;
        bool operator<=(const SquareMat &mat) const;
        bool operator>=(const SquareMat &mat) const;

        // determinant operator
        double operator!() const;

        // assignment operators between 2 matrices and scalar
        // all of these operators are used to modify the current matrix
        // and therfore they return a reference to the current matrix.
        // for these operator we are changing the current matrix meaning that we return the result by reference
        SquareMat &operator+=(const SquareMat &mat);
        SquareMat &operator-=(const SquareMat &mat);
        SquareMat &operator*=(const SquareMat &mat);

        SquareMat &operator*=(double scalar);
        SquareMat &operator/=(double scalar);

        SquareMat &operator%=(const SquareMat &mat);
        SquareMat &operator%=(int scalar);

        // 2 friend operators -
        // 1. multiplication operation between a scalar and a matrix
        // 2. printing operator for the matrix
        friend SquareMat operator*(double scalar, const SquareMat &mat);
        friend std::ostream &operator<<(std::ostream &os, const SquareMat &mat);
    };

}