#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

//Basic case with a 3x5 Matrix
TEST(test_Matrix_Init_Basic){
  Matrix mat;
  Matrix expected;
  const int w = 3;
  const int h = 5;
  Matrix_init(&mat, w, h);
  Matrix_init(&expected, w, h);
  ASSERT_TRUE(Matrix_equal(&mat, &expected));
}

//Test a 1x1 Matrix
TEST(test_Matrix_Init_One){
  Matrix mat;
  Matrix expected;
  const int w = 1;
  const int h = 1;
  Matrix_init(&mat, w, h);
  Matrix_init(&expected, w, h);
  ASSERT_TRUE(Matrix_equal(&mat, &expected));
}

//Test a 1x5 Matrix
TEST(test_Matrix_Init_One_Row){
  Matrix mat;
  Matrix expected;
  const int w = 5;
  const int h = 1;
  Matrix_init(&mat, w, h);
  Matrix_init(&expected, w, h);
  ASSERT_TRUE(Matrix_equal(&mat, &expected));
}

//Test a 5x1 Matrix
TEST(test_Matrix_Init_One_Col){
  Matrix mat;
  Matrix expected;
  const int w = 1;
  const int h = 5;
  Matrix_init(&mat, w, h);
  Matrix_init(&expected, w, h);
  ASSERT_TRUE(Matrix_equal(&mat, &expected));
}

// Test Reset
TEST(test_Matrix_Init_Reset){
  Matrix mat;
  Matrix expected;
  const int w = 2;
  const int h = 2;
  Matrix_init(&mat, w, h);
  Matrix_fill(&mat,5);
  Matrix_init(&mat, 3, 3);
  Matrix_init(&expected, 3, 3);
  ASSERT_TRUE(Matrix_equal(&mat, &expected));
}

//Test Basic Print
TEST(test_Matrix_Print_Basic){
  Matrix mat;
  Matrix_init(&mat, 2, 2);
  *Matrix_at(&mat, 0, 0) = 1;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 1, 0) = 3;
  *Matrix_at(&mat, 1, 1) = 4;
  ostringstream expected;
  expected << "2 2\n"
           << "1 2 \n"
           << "3 4 \n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}

//Test 1x1 Print
TEST(test_Matrix_Print_One){
  Matrix mat;
  Matrix_init(&mat, 1, 1);
  *Matrix_at(&mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}

//Test 1x5 Matrix
TEST(test_Matrix_Print_One_Row){
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 0;
  *Matrix_at(&mat, 0, 1) = 1;
  *Matrix_at(&mat, 0, 2) = 2;
  *Matrix_at(&mat, 0, 3) = 3;
  *Matrix_at(&mat, 0, 4) = 4;
  ostringstream expected;
  expected << "5 1\n"
           << "0 1 2 3 4 \n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}

//Test 5x1 Matrix
TEST(test_Matrix_Print_One_Col){
  Matrix mat;
  Matrix_init(&mat, 1, 5);
  *Matrix_at(&mat, 0, 0) = 0;
  *Matrix_at(&mat, 1, 0) = 1;
  *Matrix_at(&mat, 2, 0) = 2;
  *Matrix_at(&mat, 3, 0) = 3;
  *Matrix_at(&mat, 4, 0) = 4;
  ostringstream expected;
  expected << "1 5\n"
           << "0 \n"
           << "1 \n"
           << "2 \n"
           << "3 \n"
           << "4 \n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}

//Test Negative Number
TEST(test_Matrix_Print_Negative){
  Matrix mat;
  Matrix_init(&mat, 2, 2);
  *Matrix_at(&mat, 0, 0) = -1;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 1, 0) = -3;
  *Matrix_at(&mat, 1, 1) = -4;
  ostringstream expected;
  expected << "2 2\n"
           << "-1 2 \n"
           << "-3 -4 \n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}

// test basic Matrix w&h
TEST(test_width_height_Basic){
  Matrix mat;
  Matrix_init(&mat, 4, 5);
  ASSERT_EQUAL(Matrix_width(&mat), 4);
  ASSERT_EQUAL(Matrix_height(&mat), 5);
}

// test reinitialized h&w
TEST(test_width_height_reinit){
  Matrix mat;
  Matrix_init(&mat, 4, 5);
  Matrix_init(&mat, 2, 7);
  ASSERT_EQUAL(Matrix_width(&mat), 2);
  ASSERT_EQUAL(Matrix_height(&mat), 7);
}

//test basic example
TEST(test_Matrix_at_basic){
  Matrix mat;
  Matrix_init(&mat, 3, 2);
  int * value1 = Matrix_at(&mat, 0, 0);
  * value1 = 5;
  int * value2 = Matrix_at(&mat, 1, 0);
  * value2 = 55;
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 0), 55);
}

//test corner values
TEST(test_Matrix_at_corners){
  Matrix mat;
  Matrix_init(&mat, 4, 4);
  *Matrix_at(&mat, 0, 0) = 2;
  *Matrix_at(&mat, 0, 3) = 4;
  *Matrix_at(&mat, 3, 0) = 6;
  *Matrix_at(&mat, 3, 3) = 8;
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 2);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 3), 4);
  ASSERT_EQUAL(*Matrix_at(&mat, 3, 0), 6);
  ASSERT_EQUAL(*Matrix_at(&mat, 3, 3), 8);
}

//test same index
TEST(test_Matrix_at_Index){
  Matrix mat;
  Matrix_init(&mat, 4, 2);
  int* value1 = Matrix_at(&mat, 1, 1);
  int* value2 = Matrix_at(&mat, 1, 1);
  *value1 = 5;
  ASSERT_EQUAL(*value2, 5);
}

//test const Matrix_at function
TEST(test_const_Matrix_at){
  Matrix mat;
  Matrix_init(&mat, 4, 2);
  *Matrix_at(&mat, 1, 1) = 5;
  const Matrix* m = &mat;
  const int* value = Matrix_at(m, 1, 1);
  ASSERT_EQUAL(*value, 5);
}

//test basic Matrix_fill
TEST(test_Matrix_fill_basic){
  Matrix mat;
  Matrix_init(&mat, 3, 2);
  Matrix_fill(&mat, 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 2), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 2), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 1), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 1), 5);
}

//test negative Matrix_fill
TEST(test_Matrix_fill_negative){
  Matrix mat;
  Matrix_init(&mat, 3, 2);
  Matrix_fill(&mat, -5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), -5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 2), -5);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 0), -5);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 2), -5);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 1), -5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 1), -5);
}

//test zero Matrix_fill
TEST(test_Matrix_fill_zero){
  Matrix mat;
  Matrix_init(&mat, 1, 1);
  Matrix_fill(&mat, 0);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 0);
}

//test basic fill_border
TEST(test_Matrix_fill_border_basic){
  Matrix mat;
  Matrix_init(&mat, 4, 3);
  Matrix_fill_border(&mat, 5);
  //test corners
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 3), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 3), 5);
  //test top row
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 2), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 1), 5);
  //test bottom row
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 1), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 2), 5);
  //Left and right column
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 3), 5);
  //Interior
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 1), 0);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 2), 0);
}

//test 1x1 Matrix
TEST(test_Matrix_fill_border_one){
  Matrix mat;
  Matrix_init(&mat, 1, 1);
  Matrix_fill_border(&mat, 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 5);
}

//test 1x5 Matrix
TEST(test_Matrix_fill_border_one_row){
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  Matrix_fill_border(&mat, 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 1), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 2), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 3), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 4), 5);
}

//test 5x1 Matrix
TEST(test_Matrix_fill_border_one_col){
  Matrix mat;
  Matrix_init(&mat, 1, 5);
  Matrix_fill_border(&mat, 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 3, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 4, 0), 5);
}

//test interior specifically
TEST(test_Matrix_fill_border_interior){
  Matrix mat;
  Matrix_init(&mat, 5, 5);
  *Matrix_at(&mat, 1, 1) = 99;
  Matrix_fill_border(&mat, 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 1), 99);
}

//test all zeros Matrix_max
TEST(test_Matrix_max_all_zero){
  Matrix mat;
  Matrix_init(&mat, 3, 3);
  ASSERT_EQUAL(Matrix_max(&mat), 0);
}

//test negative Matrix_max
TEST(test_Matrix_max_negative){
  Matrix mat;
  Matrix_init(&mat, 3, 3);
  *Matrix_at(&mat, 0, 0)=-1;
  *Matrix_at(&mat, 0, 2)=-2;
  *Matrix_at(&mat, 1, 0)=-3;
  *Matrix_at(&mat, 1, 1)=-4;
  *Matrix_at(&mat, 0, 1)=-3;
  *Matrix_at(&mat, 1, 2)=-4;
  *Matrix_at(&mat, 2, 0)=-3;
  *Matrix_at(&mat, 2, 1)=-6;
  *Matrix_at(&mat, 2, 2)=-5;
  ASSERT_EQUAL(Matrix_max(&mat), -1);
}

//test multiple max values Matrix_max
TEST(test_Matrix_max_multiple){
  Matrix mat;
  Matrix_init(&mat, 3, 3);
  *Matrix_at(&mat, 1, 1)= 5;
  *Matrix_at(&mat, 0, 2)= 5;
  ASSERT_EQUAL(Matrix_max(&mat), 5);
}

//test corner max
TEST(test_Matrix_max_corner){
  Matrix mat;
  Matrix_init(&mat, 3, 3);
  *Matrix_at(&mat, 0, 2) = 3;
  ASSERT_EQUAL(Matrix_max(&mat), 3);
}

//test 1x5 Matrix
TEST(test_Matrix_max_one_row){
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = -1;
  *Matrix_at(&mat, 0, 1) = 3;
  *Matrix_at(&mat, 0, 2) = 3;
  *Matrix_at(&mat, 0, 3) = 5;
  *Matrix_at(&mat, 0, 4) = 5;
  ASSERT_EQUAL(Matrix_max(&mat), 5);
}

//test 5x1 Matrix
TEST(test_Matrix_max_one_col){
  Matrix mat;
  Matrix_init(&mat, 1, 5);
  *Matrix_at(&mat, 0, 0) = -1;
  *Matrix_at(&mat, 1, 0) = -3;
  *Matrix_at(&mat, 2, 0) = 0;
  *Matrix_at(&mat, 3, 0) = 5;
  *Matrix_at(&mat, 4, 0) = 2;
  ASSERT_EQUAL(Matrix_max(&mat), 5);
}

//test one col
TEST(test_Matrix_col_min_One_col){
  Matrix mat;
  Matrix_init(&mat, 5, 3);
  *Matrix_at(&mat, 1, 2) = 3;
  *Matrix_at(&mat, 1, 3) = 7;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 1, 2, 3), 2);
}

//test start col
TEST(test_Matrix_col_min_start_col){
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 3;
  *Matrix_at(&mat, 0, 1) = -2;
  *Matrix_at(&mat, 0, 2) = 5;
  *Matrix_at(&mat, 0, 3) = 6;
  *Matrix_at(&mat, 0, 4) = 7;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 1, 4), 1);
}

//test end col
TEST(test_Matrix_col_min_end_col){
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 3;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 0, 2) = 5;
  *Matrix_at(&mat, 0, 3) = 0;
  *Matrix_at(&mat, 0, 4) = -2;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 1, 4), 3);
}

//test middle col
TEST(test_Matrix_col_min_middle_col){
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 3;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 0, 2) = -10;
  *Matrix_at(&mat, 0, 3) = 0;
  *Matrix_at(&mat, 0, 4) = -2;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 1, 5), 2);
}

//test multiple mins
TEST(test_Matrix_col_min_multiple){
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 3;
  *Matrix_at(&mat, 0, 1) = -10;
  *Matrix_at(&mat, 0, 2) = -10;
  *Matrix_at(&mat, 0, 3) = 0;
  *Matrix_at(&mat, 0, 4) = -100;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 1, 4), 1);
}

//test one col min value
TEST(test_Matrix_min_value_in_row_basic){
  Matrix mat;
  Matrix_init(&mat, 5, 3);
  *Matrix_at(&mat, 1, 2) = 3;
  *Matrix_at(&mat, 1, 3) = 7;
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 2, 3), 3);
}

//test start min
TEST(test_Matrix_min_value_start_col){
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 3;
  *Matrix_at(&mat, 0, 1) = -2;
  *Matrix_at(&mat, 0, 2) = 5;
  *Matrix_at(&mat, 0, 3) = 6;
  *Matrix_at(&mat, 0, 4) = 7;
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 1, 4), -2);
}

//test end min
TEST(test_Matrix_min_value_end_col){
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 3;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 0, 2) = 5;
  *Matrix_at(&mat, 0, 3) = 0;
  *Matrix_at(&mat, 0, 4) = -2;
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 1, 5), -2);
}

//test middle min
TEST(test_Matrix_min_value_middle_col){
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 3;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 0, 2) = -10;
  *Matrix_at(&mat, 0, 3) = 0;
  *Matrix_at(&mat, 0, 4) = -2;
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 1, 5), -10);
}

//test multiple min values
TEST(test_Matrix_min_value_multiple){
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = -3;
  *Matrix_at(&mat, 0, 1) = -2;
  *Matrix_at(&mat, 0, 2) = -10;
  *Matrix_at(&mat, 0, 3) = -10;
  *Matrix_at(&mat, 0, 4) = -100;
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 0, 4), -10);
}



























// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST_MAIN() // Do NOT put a semicolon here
