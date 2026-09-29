#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

// Checks that Image_init sets width/height and initializes all channels to 0.
TEST(test_init) {
  Image img;
  Image_init(&img, 3, 2);

  ASSERT_EQUAL(img.width, 3);
  ASSERT_EQUAL(img.height, 2);

  for (int row = 0; row < img.height; row++) {
    for (int col = 0; col < img.width; col++) {
      ASSERT_EQUAL(*Matrix_at(&img.red_channel, row, col), 0);
      ASSERT_EQUAL(*Matrix_at(&img.green_channel, row, col), 0);
      ASSERT_EQUAL(*Matrix_at(&img.blue_channel, row, col), 0);
    }
  }
}

// Checks that Image_set_pixel writes each channel correctly at the correct location.
TEST(test_set_pixel) {
  Image img;
  Image_init(&img, 4, 3);

  const Pixel p = {10, 20, 30};
  Image_set_pixel(&img, 1, 2, p);

  ASSERT_EQUAL(*Matrix_at(&img.red_channel, 1, 2), 10);
  ASSERT_EQUAL(*Matrix_at(&img.green_channel, 1, 2), 20);
  ASSERT_EQUAL(*Matrix_at(&img.blue_channel, 1, 2), 30);
}

// Checks that Image_get_pixel returns the correct RGB triples.
TEST(test_get_pixel) {
  Image img;
  Image_init(&img, 2, 2);

  const Pixel p1 = {1, 2, 3};
  Image_set_pixel(&img, 0, 1, p1);

  Pixel p2 = Image_get_pixel(&img, 0, 1);
  ASSERT_EQUAL(p2.r, 1);
  ASSERT_EQUAL(p2.g, 2);
  ASSERT_EQUAL(p2.b, 3);
}

// Checks that Image_fill sets every pixel to the same color.
TEST(test_fill) {
  Image img;
  Image_init(&img, 3, 3);

  const Pixel p = {5, 6, 7};
  Image_fill(&img, p);

  for (int row = 0; row < img.height; row++) {
    for (int col = 0; col < img.width; col++) {
      ASSERT_EQUAL(*Matrix_at(&img.red_channel, row, col), 5);
      ASSERT_EQUAL(*Matrix_at(&img.green_channel, row, col), 6);
      ASSERT_EQUAL(*Matrix_at(&img.blue_channel, row, col), 7);
    }
  }
}



TEST_MAIN() // Do NOT put a semicolon here
