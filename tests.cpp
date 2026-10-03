// iliyacod@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.hpp"

/*
Here I will go through every function one by one, the order will be based on the github assignment order..
*/

TEST_CASE("memory check test cases") 
{
    double arr[] = { 1 , 2, 3,
                    4 , 5, 6,
                    7 , 8, 9 };

   
    double arr2[] = { 1 , 12313312312, 324.42332423,
                    4 , 5, 321312321,
                    7 , 8, 634643 };

    double arr3[] = { 1 , 3242, 0.12312312,
                    4.3432 , 5, 4234242,
                    7/234 , 8, 9 };

    SquareMat::SquareMat* mat1 = new SquareMat::SquareMat(3, arr, 9);
    SquareMat::SquareMat* mat2 = new SquareMat::SquareMat(3, arr2, 9);
    SquareMat::SquareMat* mat3 = new SquareMat::SquareMat(3, arr3, 9);


    CHECK(mat1->get_size() == 3);
    CHECK(mat2->get_size() == 3);
    CHECK(mat3->get_size() == 3);

    CHECK((*mat1)[0][0] == 1);
    CHECK((*mat1)[0][1] == 2);
    CHECK((*mat2)[1][2] == 321312321);
    CHECK((*mat3)[2][2] == 9);

    delete mat1;
    delete mat2;
    delete mat3;
}

TEST_CASE("matrix copy") {

    double arr1[] = {
                    1 , 2, 3,
                    4 , 5, 6,
                    7 , 8, 9 };
    
    double arr2[] = {
                     5, 6, 7,
                    8 , 9, 10,
                    11 , 12, 13 };

    SquareMat::SquareMat mat1(3, arr1, 9);
    SquareMat::SquareMat mat2(3, arr2, 9);
    
    CHECK_FALSE(mat1 == mat2);
    CHECK(mat2.get_size() == 3);
    
    mat2 = mat1;

    CHECK(mat1 == mat2);

}


TEST_CASE("matrices addition and subtraction") 
{
    double arr[] = { 1 , 2, 3,
                    4 , 5, 6,
                    7 , 8, 9 };

    SquareMat::SquareMat mat1(3, arr, 9);
    SquareMat::SquareMat mat2(3, arr, 9);
    // addition
    SquareMat::SquareMat mat_result = mat1 + mat2;

    CHECK(mat_result.get_size() == 3);

    CHECK(mat_result[0][0] == 2);
    CHECK(mat_result[0][1] == 4);
    CHECK(mat_result[0][2] == 6);
    CHECK(mat_result[1][0] == 8);
    CHECK(mat_result[1][1] == 10);
    CHECK(mat_result[1][2] == 12);
    CHECK(mat_result[2][0] == 14);
    CHECK(mat_result[2][1] == 16);
    CHECK(mat_result[2][2] == 18);

    // subtraction
    SquareMat::SquareMat mat_result2 = mat1 - mat2;
    CHECK(mat_result2[0][0] == 0);
    CHECK(mat_result2[0][1] == 0);
    CHECK(mat_result2[0][2] == 0);
    CHECK(mat_result2[1][0] == 0);

}

TEST_CASE("unary matrix test function") 
{
    double arr[] = { 1 , 2, 3,
                    4 , 5, 6,
                    7 , 8, 9 };

    SquareMat::SquareMat mat(3, arr, 9);
    SquareMat::SquareMat unr_mat = -mat;

    CHECK(unr_mat[0][0] == -1);
    CHECK(unr_mat[2][2] == -9);
     
}

TEST_CASE("multiplication operator between 2 matrices") 
{
    double arr[] = { 1 , 1, 1,
                    1 , 1, 1,
                    1 , 1, 1 };

    SquareMat::SquareMat mat1(3, arr, 9);
    SquareMat::SquareMat mat2(3, arr, 9);
    SquareMat::SquareMat mat_result = mat1 * mat2;

    CHECK(mat_result[0][0] == 3);
    CHECK(mat_result[1][1] == 3);
    CHECK(mat_result[2][2] == 3);


}


TEST_CASE("matrix multiplication with a scalar") 
{
    double arr[] = { 1 , 2, 3,
                     4 , 5, 6,
                     7 , 8, 9 };

    double arr2[] = { 3 , -6, 34,
                     -2 , 5, 10,
                      7 , 8, 9  };

    SquareMat::SquareMat mat1(3, arr, 9);
    SquareMat::SquareMat mat2(3, arr2, 9);

    SquareMat::SquareMat mat_result = mat1 * 3.5;
    CHECK(mat_result[0][0] == 3.5);
    CHECK(mat_result[1][1] == 17.5);
    CHECK(mat_result[2][2] == 31.5);

    SquareMat::SquareMat mat_result2 = mat2 * 4.5;

    CHECK(mat_result2[0][0] == 13.5);
    CHECK(mat_result2[1][1] == 22.5);
    CHECK(mat_result2[2][2] == 40.5);
                
}

TEST_CASE("matrix modulo division with a scalar") 
{
    double arr1[] = { 1 , 2, 3,
                     4 , 5, 6,
                     7 , 8, 9 };

    double arr2[] = { 3 , -6, 34,
                      -2 , 5, 10,
                      7 , 8, 9 };   

    SquareMat::SquareMat mat1(3, arr1, 9);
    SquareMat::SquareMat mat2(3, arr2, 9);                
                    

    CHECK_THROWS_AS(mat1 / 0, std::runtime_error);
    CHECK_THROWS_AS(mat2 / 0, std::runtime_error);

}

TEST_CASE("matrix division with a scalar") 
{
 // test edge case with a 0 scalar
 double arr[] = {1 , 2, 3,
                 4 , 5, 6,
                 7 , 8, 9};

 // matrix will be 3x3, the array has 9 elements which will translate into a 3x3 matrix.
SquareMat::SquareMat mat(3, arr, 9);
// try to / with a 0 scalar
CHECK_THROWS_AS(mat / 0, std::runtime_error);



}

TEST_CASE("the power operation on a matrix") 
{
    double arr[] = { 
                        1, 2,
                        3, 4
                                };

    SquareMat::SquareMat mat(2, arr, 4);

    SquareMat::SquareMat pow0 = mat ^ 0;
    CHECK(pow0[0][0] == 1);
    CHECK(pow0[0][1] == 0);
    CHECK(pow0[1][0] == 0);
    CHECK(pow0[1][1] == 1);

    SquareMat::SquareMat pow1 = mat ^ 1;
    CHECK(pow1[0][0] == 1);
    CHECK(pow1[0][1] == 2);
    CHECK(pow1[1][0] == 3);
    CHECK(pow1[1][1] == 4);

    SquareMat::SquareMat pow2 = mat ^ 2;
    CHECK(pow2[0][0] == 7);
    CHECK(pow2[0][1] == 10);
    CHECK(pow2[1][0] == 15);
    CHECK(pow2[1][1] == 22);
}

TEST_CASE("the increment operator on a matrix (postfix and prefix)") 
{
    double arr[] = { 1, 2, 3,
                     4, 5, 6,
                     7, 8, 9 };

    SquareMat::SquareMat mat(3, arr, 9);  
    
    SquareMat::SquareMat mat2 = ++mat;
    CHECK(mat2[0][0] == 2);
    CHECK(mat2[0][1] == 3);
    CHECK(mat2[0][2] == 4);
    CHECK(mat2[1][0] == 5);
    
    CHECK(mat[0][0] == 2);
    CHECK(mat[0][1] == 3);
    CHECK(mat[0][2] == 4);

    SquareMat::SquareMat mat3 = mat++;

    CHECK(mat3[0][0] == 2);
    CHECK(mat3[0][1] == 3);
    CHECK(mat3[0][2] == 4);

    CHECK(mat[0][0] == 3);
    CHECK(mat[0][1] == 4);
    CHECK(mat[0][2] == 5);
    

    
}

TEST_CASE("the decrement operator on a matrix (postfix and prefix)") 
{
    double arr[] = { 1, 2, 3,
                     4, 5, 6,
                     7, 8, 9 };

    SquareMat::SquareMat mat(3, arr, 9);  
    
    SquareMat::SquareMat mat2 = --mat;
    CHECK(mat2[0][0] == 0);
    CHECK(mat2[0][1] == 1);
    CHECK(mat2[0][2] == 2);
    CHECK(mat2[1][0] == 3);
    
    CHECK(mat[0][0] == 0);
    CHECK(mat[0][1] == 1);
    CHECK(mat[0][2] == 2);

    SquareMat::SquareMat mat3 = mat--;

    CHECK(mat3[0][0] == 0);
    CHECK(mat3[0][1] == 1);
    CHECK(mat3[0][2] == 2);
    CHECK(mat[0][0] == -1);

    
}

TEST_CASE("the transpose operator on a matrix") 
{
    double arr[] = { 1, 2, 3,
                    4, 5, 6,
                    7, 8, 9 };

    SquareMat::SquareMat mat(3, arr, 9);
    SquareMat::SquareMat trans_mat = ~mat;

    CHECK(trans_mat[0][0] == 1);
    CHECK(trans_mat[0][1] == 4);
    CHECK(trans_mat[0][2] == 7);
    CHECK(trans_mat[1][0] == 2);
    CHECK(trans_mat[1][1] == 5);
    CHECK(trans_mat[1][2] == 8);
    CHECK(trans_mat[2][0] == 3);
    CHECK(trans_mat[2][1] == 6);
    CHECK(trans_mat[2][2] == 9);
    
}

TEST_CASE("the [] operator to access an element within the matrix") 
{
    double arr1[] = { 1 , 2, 3,
                      4 , 5, 6,
                      7 , 8, 9 };

    double arr2[] = {  3 , -6, 34, 3.1235 , 7,
                      -2 , 5.23232, 10, 56, 435.324,
                       7 , 8, 9.3657, 1.2121, 0.221,
                    -1.2332, -323, 4, 6, 1,
                    0 , 1.2234324, 543, 99999, 1 };

    double arr3[] = { 7 , 8, 
                     3 , 2, };


     SquareMat::SquareMat mat1(3, arr1, 9);
     SquareMat::SquareMat mat2(5, arr2, 25);
     SquareMat::SquareMat mat3(2, arr3, 4);

    CHECK(mat1[1][2] == 6);
    CHECK(mat1[2][2] == 9);

    CHECK(mat2[1][2] == 10);
    CHECK(mat2[3][2] == 4);

  

    CHECK(mat3[1][0] == 3);
    CHECK(mat3[1][1] == 2);


    
}

TEST_CASE("equality and inequality between matrices") 
{

    // equality is defined in equal sums.. somehow
    // so it doesnt matter if the matrix is different than 
    // the other one, as long as their sums are equal then
    // we have 2 equal matrices

    double arr1[] = { 1 , 2, 3,
                    4 , 5, 6,
                    7 , 8, 9 };

    double arr2[] = { 3 , -6, 34,
                     -2 , 5, 10,
                     7 , 8, 9 };  
   
    double arr3[] = { 7 , 8, 9,
                     3 , 2, 1,
                     4 , 5, 6 };
                     
    // arr2 and arr1 shouldnt be equal but arr1 and arr3 should be equal 
    // because they have equal sums.

    SquareMat::SquareMat m1(3,arr1, 9);
    SquareMat::SquareMat m2(3,arr2, 9);
    SquareMat::SquareMat m3(3,arr3, 9);

    CHECK_EQ(m1 == m2 , false);
    CHECK_EQ(m1 != m3, false);
    CHECK_FALSE(m2 == m3);
}

TEST_CASE("comparison operators between matrices") 
{

    double arr1[] = { 1 , 2, 3,
                      4 , 5, 6,
                      7 , 8, 9  };

    double arr2[] = { 3 , -6, 34,
                     -2 , 5, 10,
                      7 , 8, 9  };  

    double arr3[] = { 7 , 8, 9,
                      3 , 2, 1,
                      4 , 5, 6  };


    SquareMat::SquareMat mat1(3, arr1, 9);
    SquareMat::SquareMat mat2(3, arr2, 9);
    SquareMat::SquareMat mat3(3, arr3, 9);

    CHECK(mat1 == mat3);  // equal sums
    CHECK(mat1 != mat2);  // different sums
    
}

TEST_CASE("the determinant operator for a matrix") 
{
    double arr1[] = {2};

    double arr2[] = { 1 , 2,
                      3 , 4 };

    double arr3[] = { 3 , -6, 34,
                     -2 , 5, 10,
                      7 , 8, 9  };

    SquareMat::SquareMat mat1(1, arr1, 1);
    SquareMat::SquareMat mat2(2, arr2, 4);
    SquareMat::SquareMat mat3(3, arr3, 9);
    
    // det calculation 
    CHECK(!mat1 == 2);
    CHECK(!mat2 == -2);
    CHECK(!mat3 == -2367);


    
}

TEST_CASE("assignment operators for a matrix") 
{
    double arr1[] = 
    {   7 , 8, 9,
        3 , 2, 1,
        4 , 5, 6  };
    
    double arr2[] = 
    {   3 , -6, 34,
        -2 , 5, 10,
        7 , 8, 9  }; 


    SquareMat::SquareMat mat1(3, arr1, 9);
    SquareMat::SquareMat mat2(3, arr2, 9);

    mat1 += mat2;

    CHECK(mat1[0][0] == 10);
    CHECK(mat1[0][1] == 2);
    CHECK(mat1[0][2] == 43);
    CHECK(mat1[1][0] == 1);
    CHECK(mat1[1][1] == 7);
    CHECK(mat1[1][2] == 11);
    CHECK(mat1[2][0] == 11);
    CHECK(mat1[2][1] == 13);
    CHECK(mat1[2][2] == 15);

    mat1 -= mat2;

    CHECK(mat1[0][0] == 7);
    CHECK(mat1[0][1] == 8);
    CHECK(mat1[0][2] == 9);
    CHECK(mat1[1][0] == 3);
    CHECK(mat1[1][1] == 2);
    CHECK(mat1[1][2] == 1);
    CHECK(mat1[2][0] == 4);
    CHECK(mat1[2][1] == 5);
    CHECK(mat1[2][2] == 6);

    mat1 *= mat2;
    // only first row
    CHECK(mat1[0][0] == 68);
    CHECK(mat1[0][1] == 70);
    CHECK(mat1[0][2] == 399);

    // reset
   mat1 = SquareMat::SquareMat(3, arr1, 9);
   mat2 = SquareMat::SquareMat(3, arr2, 9);

    

    // again i reset 
    mat1 = SquareMat::SquareMat(3, arr1, 9);
    mat2 = SquareMat::SquareMat(3, arr2, 9);

    mat1 %= mat2;

    CHECK(mat1[0][0] == 21);
    CHECK(mat1[0][1] == -48);
    CHECK(mat1[0][2] == 9 * 34);
    CHECK(mat1[1][0] == -6);
    CHECK(mat1[1][1] == 10);
    CHECK(mat1[1][2] == 10);
    CHECK(mat1[2][0] == 28);
    CHECK(mat1[2][1] == 40);
    CHECK(mat1[2][2] == 54);
}

TEST_CASE("printing operator for the matrix") 
{
    double arr1[] = 
        { 7,8,9,
          3,2,1,
          4,5,6
                 };

    SquareMat::SquareMat mat(3, arr1, 9);

    std::ostringstream please_work;

    please_work << mat;
    std::string mat_print =
        "(7, 8, 9)\n"
        "(3, 2, 1)\n"
        "(4, 5, 6)\n";

    CHECK(please_work.str() == mat_print);


}