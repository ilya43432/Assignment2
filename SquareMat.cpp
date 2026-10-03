#include "SquareMat.hpp"
#include <exception>
#include <stdexcept>
/*

I have used lots of try catches in this assignment. this of course is a good practice (for me at least)
to ensure that we dont have any memory leaks in a case of an exception.

Rule of three is imeplemted here as well. we have a copy constructor, a copy assignment operator
and a destructor. 

2 friend functions are implemented in this assignment, these are the following functions - 
- 1. friend function for the multiplication operator with a scalar.
Explanation - since a scalar isnt an object of the matrix class
it is not possilbe to call a member function but yet we have to access the
matrix elements and therefore we have to use a friend function.

example - 4 * (matrix), 4 cannot call the member function of the matrix class.
this on the other hand is good - (matrix) * 4, since the matrix is an object of the 
class and can call the member function.


- 2. friend function for the output operator <<
Explanation - ostream isnt a member function of the class and therefore we have
 to use a friend function for it. as explained earlier it needs 
 access to the private members of the class, which more precisely 
 will be the elements inside the matrix.
*/
namespace SquareMat
{
    // copy constructor
    // this constructor will create a new matrix and copy the values from the other matrix.
    // this is of course a deep copy, so we have to allocate the memory for the new matrix.
    SquareMat::SquareMat(const SquareMat& other) : N(other.N)
    {
        // allocate memory for the new matrix
        arr = new double *[N];

        // keep track of the already allocated rows.
        int allocated_rows = 0; 

        // a try/catch function block to ensure we safely deallocate
        // the memory in case of an exception.
        try
        {
            while (allocated_rows < N)
            {
                // memory allocation
                arr[allocated_rows] = new double[N];
                allocated_rows++;
            }

            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < N; ++j)
                {
                    // values copy
                    arr[i][j] = other.arr[i][j];
                }
            }
        }
        // if we catch an exception
        // we have to deallocate the memory that was already allocated
        // in order to avoid memory leaks.
        catch (const std::exception& ex)
        {
            for (int i = 0; i < allocated_rows; ++i) 
            {
            delete[] arr[i];
            }
            delete[] arr;
            throw std::runtime_error(ex.what());
        }
    }

    // this is the copy assignment operator 
    SquareMat& SquareMat::operator=(const SquareMat& other) {
        // if the current matrix is the same as the other matrix then we can just return our current matrix.
        if (this == &other)
            return *this;

        // a pointer to the new array
        double** new_arr = nullptr;
        try
        {
            // allocate memory with the size of the other matrix
            new_arr = new double*[other.N];

            // i have to keep track of the allocated rows in a case
            // where there is an exception and i need to free them to avoid leaks
            int allocated_rows = 0;
            
            while(allocated_rows < other.N)
            {
                // memory allocation
                new_arr[allocated_rows] = new double[other.N];
                for (int j = 0; j < other.N; ++j)
                {
                    // after allocation we can assign the values from the other mat
                    new_arr[allocated_rows][j] = other.arr[allocated_rows][j];
                }
                allocated_rows++;
            }

            // we remove the memory from the old array
            for (int i = 0; i < N; ++i)
            {
                delete[] arr[i];
            }
            delete[] arr;

            // assign the size
            N = other.N;
            // assign the arr to the new array
            arr = new_arr;
            
        }
        catch (const std::exception& exp)
        {
                // a check to see if the new arr was actually allocated
                // because i dont want to free nothing
            if (new_arr != nullptr)
            {
                for (int i = 0; i < other.N; ++i)
                {
                    delete[] new_arr[i];
                }
                delete[] new_arr;
            }
            throw std::runtime_error(exp.what());
        }

        return *this;
    }

    // destructor. a part of the RULE OF THREE.
    // this destructor is responsible for deallocating the memory
    // that was allocated for the matrix. we have to delete each row
    // and then delete the array of pointers.
    SquareMat::~SquareMat() {
        for (int i = 0; i < N; ++i)
        {
            delete[] arr[i];
        }
        delete[] arr;
    }

    // matrix addition with another matrix.
    SquareMat SquareMat::operator+(const SquareMat &mat) const
    {
        if (N != mat.N)
        {
            throw std::invalid_argument("both matrices's size have to be equal!");
        }
        
        SquareMat result_mat(N);

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                result_mat.arr[i][j] = arr[i][j] + mat.arr[i][j];
            }
        }

        return result_mat;
    }

    // matrix subtraction operator with another matrix.
    SquareMat SquareMat::operator-(const SquareMat &mat) const
    {
        if (N != mat.N)
        {
            throw std::invalid_argument("both matrices's size have to be equal!");
        }

        SquareMat result_mat(N);

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                result_mat.arr[i][j] = arr[i][j] - mat.arr[i][j];
            }
        }

        return result_mat;
    }


    // transpose operator. we create a result matrix.
    // and instead of allocating the result matrix the current index i,j
    // we switch it to Aji. we repeat that for the whole matrix
    // with 2 for loops.
    SquareMat SquareMat::operator~() const
    {
        SquareMat result_mat(N);

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                // result matrix Aij value is the current matrix Aji
                // because A(i,j) transpose is A^t(j,i)
                result_mat.arr[i][j] = arr[j][i];
            }
        }
        // this function is of course a by value function so we return 
        // a new matrix. 
        return result_mat;
    }

    // matrix multiplication with another matrix
    // formally it will be c(ij) = a(ik) * b(kj) in a sigma sum from k = 0 to N - 1
    // and well do that for each C (ij)
    SquareMat SquareMat::operator*(const SquareMat &mat) const
    {
        if (N != mat.N)
        {
            throw std::invalid_argument("both matrices's size have to be equal!");
        }

        SquareMat result_mat(N);

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                double sum_indxs = 0;
                for (int a = 0; a < N; ++a)
                {
                    sum_indxs += arr[i][a] * mat.arr[a][j];
                }
                result_mat.arr[i][j] = sum_indxs;
            }
        }

        return result_mat;
    }

    // unary operator implementation
    SquareMat SquareMat::operator-() const
    {
        SquareMat result_mat(N);

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                result_mat.arr[i][j] = -arr[i][j];
            }
        }

        return result_mat;
    }

    // matrix mutiplication with a scalar.
    SquareMat SquareMat::operator*(double scalar) const
    {
        SquareMat result_mat(N);

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                result_mat.arr[i][j] = arr[i][j] * scalar;
            }
        }

        return result_mat;
    }

    // the % operator is defined as multliplication between 2 matrices.
    // but not the usual multiplication we know but for each index i,j
    // we multiply bo
    SquareMat SquareMat::operator%(const SquareMat &mat) const
    {
        if (N != mat.N)
        {
            // can't multiply 2 matrices with different sizes
            throw std::invalid_argument("both matrices's size have to be equal!");
        }

       SquareMat result_mat(N);

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                // each index i j is multiplied with the other matrix in the same index
                // formally it will be Aij * Bij
                result_mat.arr[i][j] = arr[i][j] * mat.arr[i][j];
            }
        }

        return result_mat;
    }

    // modulu operator with a scalar using the cmath library
    SquareMat SquareMat::operator%(int scalar) const
    {
        if (scalar == 0)
        {
            // rookie mistake
            throw std::runtime_error("Can't divide by zero!");
        }

        SquareMat result_mat(N);

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                // we use fmod, since we are using double values
                // and we want to get the modulo of the double value
               result_mat.arr[i][j] = std::fmod(arr[i][j], scalar);
            }
        }

        return result_mat;
    }
    // matrix division with a scalar.
    SquareMat SquareMat::operator/(double scalar) const
    {
        if (scalar == 0)
        {
            // (: 
            throw std::runtime_error("Can't divide by zero!");
        }

        SquareMat result_mat(N);

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                // each index i j is divided by the scalar
                result_mat.arr[i][j] = arr[i][j] / scalar;
            }
        }

        return result_mat;
    }

    // matrix power with an integer.
    SquareMat SquareMat::operator^(int power) const
    {
    if (power == 0)
    {
        // power == 0 is identity matrix
        SquareMat result_mat(N);
        
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if (i == j) {

                    result_mat.arr[i][j] = 1; 
                } else {
                    result_mat.arr[i][j] = 0; 
                }
            }
        }
        return result_mat;
    }

    if (power < 0 ) 
    {
        // we can calculate the inverse of the matrix. 
        // we can see the negative power as the inverse of the matrix multiplied by the power.
        // for example - (B^-2) would be = (B^-1) * (B^2)
        // so formally it will be (b^<negative power>) = (B^-1) * (B^<positive power>)
        SquareMat inverse_matrix = this->inverse();


        SquareMat result = inverse_matrix;

        // we know power is negative so we make it positive for the for loop to work properly
        for (int i = 0 ; i < -(power) ; ++i) 
        {
            // inverse multiplication by itself - power times
            result = result * inverse_matrix;
         }

        return result;
    }

    // if the power is positive then we can just multiply the matrix by itself power times..
    SquareMat result(*this);

    for (int i = 1; i < power; ++i)
    {
        result = result * (*this);
    }
    return result;
}

    // matrix comparison operator. in this assignment, matrix equality is defined
    // as the sum of the elements in the matrix.
    // so if the sum of both matrices is equal, we return true.
    // otherwise they're not equal.
    bool SquareMat::operator==(const SquareMat &mat) const
    {
        if (N != mat.N)
        {
            return false;
        }

        double sum_mat1 = 0;
        double sum_mat2 = 0;

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                sum_mat1 += arr[i][j];
                sum_mat2 += mat.arr[i][j];
            }
        }

        return sum_mat1 == sum_mat2;
    }


    // inequality operator. we can make a shortcut and just call the equality operator 
    // and check whether the equality is false.
    bool SquareMat::operator!=(const SquareMat &mat) const
    {
        return !(*this == mat);
    }

    // comparison operator < 
    // sum of the current matrix is less than the sum of the matrix passed as a parameter.
    bool SquareMat::operator<(const SquareMat &mat) const
    {
        if (N != mat.N)
        {
            throw std::invalid_argument("both matrices's size have to be equal!");
        }

        double sum1 = 0, sum2 = 0;

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                sum1 += arr[i][j];
                sum2 += mat.arr[i][j];
            }

        return sum1 < sum2;
    }

    // comparison operator >
    // sum of the current matrix is greater than the sum of the matrix passed as a parameter.
    bool SquareMat::operator>(const SquareMat &mat) const
    {
        if (N != mat.N)
        {
            throw std::invalid_argument("both matrices's size have to be equal!");
        }

        double sum1 = 0, sum2 = 0;

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                sum1 += arr[i][j];
                sum2 += mat.arr[i][j];
            }

        return sum1 > sum2;
    }

    // comparison operator <= 
    // shortcut in here, we just use the < operator and the == operator
    bool SquareMat::operator<=(const SquareMat &mat) const
    {
        return (*this < mat) || (*this == mat);
    }

    // comparison operator >=
    // this one is also a shortcut, we just use the > operator and the == operator
    bool SquareMat::operator>=(const SquareMat &mat) const
    {
        return (*this > mat) || (*this == mat);
    }

    // access operator [] for the matrix to modify an element
    double *SquareMat::operator[](int i)
    {
        if (i < 0 || i >= N)
        {
            throw std::out_of_range("Index out of bounds");
        }
        return arr[i];
    }

    // a constant operator [] to access an element without the need to change it.
    const double *SquareMat::operator[](int i) const
    {
        if (i < 0 || i >= N)
        {
            throw std::out_of_range("Index out of bounds");
        }
        return arr[i];
    }

    // prefix increment operator
    SquareMat &SquareMat::operator++()
    {
        for (int i = 0; i < N; ++i ) 
        {
            for (int j = 0; j < N; ++j) 
            {
                arr[i][j] += 1;
            }
        }
        return *this;
    }

    // postfix increment operator
    SquareMat SquareMat::operator++(int)
    {
        // we create a copy of the current matrix
        // increment the current matrix
        // and return the old matrix.
        SquareMat old_matrix(*this);
        ++(*this);
        return old_matrix;
    }

    // prefix decrement operator
    SquareMat &SquareMat::operator--()
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j) {
                arr[i][j] -= 1;
            }
        }
        return *this;
    }

    // postfix decrement operator
    SquareMat SquareMat::operator--(int)
    {   
        /* copy the current matrix
         decrement the current matrix
         and return the old matrix.
        */
        SquareMat old_matrix(*this);
        --(*this);
        return old_matrix;
    }

    double SquareMat::operator!() const
    {
        // 2 base cases - 1 for a 1x1 matrix and the 2'nd is for a 2x2 which is trivial
        // from linear algebra 2

        // det for 1x1
        if (N == 1)
        {
            return arr[0][0];
        }

        // det for 2x2
        // a(00) * a(11) - a(01) * a(10)
        if (N == 2)
        {
            return arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
        }

        
        //det for N > 2
        double det = 0;
        double *minor_vec = nullptr;

        // try/catch because i allocate a minor vector
        // to calculate the determinant of the minor matrix
        try
        {
            // for N >= 3 we need to allocate a new vector for the minor matrix
            // the size of the minor matrix is (N-1)*(N-1)
            /*
            The follwing formula for the determinant of the matrix as we learned in 
            linear algebra 2 is the following -
            det(A) = (sigma sum that runs from i=0 to N-1) of (-1)^i * a(0,i) * det(A(0,i))

            */
            minor_vec = new double[(N - 1) * (N - 1)];

            for (int col = 0; col < N; ++col)
            {
                int idx = 0;

                for (int i = 1; i < N; ++i)
                {
                    for (int j = 0; j < N; ++j)
                    {
                        if (j != col)
                        {
                            minor_vec[idx++] = arr[i][j];
                        }
                    }
                }

                SquareMat minor(N - 1, minor_vec, (N - 1) * (N - 1));
                // 1 for even | -1 for odd
                double sign;
                if (col % 2 == 0) {
                    sign = 1;
                }
                else
                {
                    sign = -1;
                }
                // we calculate according to the formula
                det += sign * arr[0][col] * !minor;
            }
        }
        catch (const std::exception &exp)
        {
            delete[] minor_vec;
            throw std::runtime_error(exp.what());
        }

        delete[] minor_vec;
        return det;
    }

    // matrice addition operator
    SquareMat &SquareMat::operator+=(const SquareMat &mat)
    {
        if (N != mat.N)
        {
            // we cant add 2 matrices with different sizes
            throw std::invalid_argument("Matrices sizes do not MATCH!");
        }
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                // each index i,j is added to the other matrix in the same index
                arr[i][j] += mat.arr[i][j];
            }
         }       
         // returned by reference
        return *this;
    }

    // matrices subtraction operator
    SquareMat &SquareMat::operator-=(const SquareMat &mat)
    {
        if (N != mat.N)
        {
            // not allowed to subtract 2 matrices with different sizes
            throw std::invalid_argument("Matrices sizes do not MATCH!");
        }
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j){
                arr[i][j] -= mat.arr[i][j];
            }
        }
        // returned by reference
        return *this;
    }


    // matrix division with a scalar
    SquareMat &SquareMat::operator/=(double scalar)
    {
        if (scalar == 0)
        {
            throw std::invalid_argument("Can't divide by zero!");
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                arr[i][j] /= scalar;
            }
        }
        return *this;
    }

    // matrix multiplication with a scalar
    SquareMat &SquareMat::operator*=(double scalar)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                arr[i][j] *= scalar;
            }
        }
        return *this;
    }

    // multiplication between 2 matrices
    SquareMat &SquareMat::operator*=(const SquareMat &mat)
    {
        if (N != mat.N)
        {
            throw std::invalid_argument("Matrices sizes do not MATCH!");
        }
        // we can use the multi operator that is already implemented
        *this = (*this) * mat;


        return *this;
    }


    // the % operator is defined as multiplication between 2 matrices.
    // each index i,j is multiplied with the other matrix in the same index
    SquareMat &SquareMat::operator%=(const SquareMat &mat)
    {
        if (N != mat.N)
        {
            throw std::invalid_argument("Matrices sizes do not MATCH!");
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) 
            {
                arr[i][j] *= mat.arr[i][j];
            }
        }
        return *this;
    }

    // modulo operator with a scalar
    SquareMat &SquareMat::operator%=(int scalar)
    {
        if (scalar == 0)
        {
            // division by zero is not allowed
            throw std::invalid_argument("Modulo by zero!");
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
            // since we are using a double values for the matrix
            // we can use the fmod mod from the cmath library.
                arr[i][j] = std::fmod(arr[i][j], scalar);
        }
    }
        return *this;
    }

    // friend function - multiplication operator with a scalar.
    SquareMat operator*(double scalar, const SquareMat &mat)
    {
        return mat * scalar;
    }

    // friend function - the printing operator for this matrix.
    std::ostream &operator<<(std::ostream &os, const SquareMat &mat)
    {
        for (int i = 0; i < mat.N; ++i) {
            os << "(";
            for (int j = 0; j < mat.N; ++j) {
                os << mat.arr[i][j];
                // , until we reach the last index
                if (j < mat.N - 1) {
                    os << ", "; }
            }
            // and finally finish forming the mat with )
            os << ")" << '\n';
        }
        return os;
    }
}