#include <cassert>
#include <vector>
#include "processing.hpp"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  int h = Image_height(img);
  int w = Image_width(img);
  Matrix_init(energy, w, h);
  int max_energy = 0;
  for(int i = 1; i<h-1; i++){
    for(int j = 1; j<w-1; j++){
      Pixel N = Image_get_pixel(img, i-1, j);
      Pixel S = Image_get_pixel(img, i+1, j);
      Pixel W = Image_get_pixel(img, i, j-1);
      Pixel E = Image_get_pixel(img, i, j+1);
      int e = squared_difference(N, S) + squared_difference(W, E);
      *Matrix_at(energy, i, j) = e;
      if(e > max_energy){
        max_energy = e;
      }
    }
  }
  for(int i=0; i<w; i++){
    *Matrix_at(energy, 0, i) = max_energy;
    *Matrix_at(energy, h-1, i) = max_energy;
  }
  for(int j=0; j<h; j++){
    *Matrix_at(energy, j, 0) = max_energy;
    *Matrix_at(energy, j, w-1) = max_energy;
  }
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  int w = Matrix_width(energy);
  int h = Matrix_height(energy);
  Matrix_init(cost, w, h);
  for(int i = 0; i<w; i++){
    *Matrix_at(cost, 0, i) = *Matrix_at(energy, 0, i);
  }
  for(int i = 1; i<h; i++){
    for(int j = 0; j<w; j++){
      int start_index;
      int end_index;
      if(j==0){
        start_index = 0;
      }else{
        start_index = j-1;
      }
      if(j==(w-1)){
        end_index = w;
      }else{
        end_index = j+2;
      }
      int cost_above = Matrix_min_value_in_row(cost, i-1, start_index, end_index);
      *Matrix_at(cost, i, j) = *Matrix_at(energy, i, j)+cost_above;
    }
  }
}


// REQUIRES: cost points to a valid Matrix
// EFFECTS:  Returns the vertical seam with the minimal cost according to the given
//           cost matrix, represented as a vector filled with the column numbers for
//           each pixel along the seam, with index 0 representing the lowest numbered
//           row (top of image). The length of the returned vector is equal to
//           Matrix_height(cost).
//           While determining the seam, if any pixels tie for lowest cost, the
//           leftmost one (i.e. with the lowest column number) is used.
//           See the project spec for details on computing the minimal seam.
//           Note: When implementing the algorithm, compute the seam starting at the
//           bottom row and work your way up.
vector<int> find_minimal_vertical_seam(const Matrix* cost) {
  int w = Matrix_width(cost);
  int h = Matrix_height(cost);
  vector<int> seam(h);
  int col1 = Matrix_column_of_min_value_in_row(cost, h-1, 0, w);
  seam[h-1]=col1;
  for(int i = h-2; i>=0; i--){
    int start_index;
      int end_index;
      if(col1==0){
        start_index = 0;
      }else{
        start_index = col1-1;
      }
      if(col1==(w-1)){
        end_index = w;
      }else{
        end_index = col1+2;
      }
      col1 = Matrix_column_of_min_value_in_row(cost, i, start_index, end_index);
      seam[i]=col1;
  }
  return seam;
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam.size() == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Declare a new variable to hold the smaller Image, and
//           then do an assignment at the end to copy it back into the
//           original image.
void remove_vertical_seam(Image *img, const vector<int> &seam) {
  int w = Image_width(img);
  int h = Image_height(img);
  Image result;
  Image_init(&result, w-1, h);
  for(int i = 0; i<h; i++){
    int index = seam[i];
    for(int j = 0; j < index; j++){
      Pixel p = Image_get_pixel(img, i, j);
      Image_set_pixel(&result, i, j, p);
    }
    for(int k = index+1; k < w; k++){
      Pixel m = Image_get_pixel(img, i, k);
      Image_set_pixel(&result, i, k-1, m);
    }
  }
  *img = result;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use a vector to hold the seam, and make sure that it has
//           the right size. You can use .data() on a vector to get
//           the underlying array.
void seam_carve_width(Image *img, int newWidth) {
  while(Image_width(img) > newWidth){
    Matrix energy;
    Matrix cost;
    compute_energy_matrix(img, &energy);
    compute_vertical_cost_matrix(&energy, &cost);
    vector<int> seam = find_minimal_vertical_seam(&cost);
    remove_vertical_seam(img, seam);
  }
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
    rotate_left(img);
    seam_carve_width(img, newHeight);
    rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  seam_carve_width(img, newWidth);
  seam_carve_height(img, newHeight);
}
