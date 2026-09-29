#include <cassert>
#include "Matrix.hpp"

// REQUIRES: mat points to a Matrix
//           0 < width && 0 < height
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height,
//           with all elements initialized to 0.
void Matrix_init(Matrix* mat, int width, int height) {
  mat->width = width;
  mat->height = height;
  mat->data.assign(width*height, 0);
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  os << Matrix_width(mat) << " " << Matrix_height(mat) << "\n";
  for(int i = 0; i<Matrix_height(mat);i++){
    for(int j = 0; j<Matrix_width(mat); j++){
      os << mat->data[i*(Matrix_width(mat))+j] << " ";
    }
    os << "\n";
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  int w = Matrix_width(mat);
  int index = row*w+column;
  return &mat->data[index];
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  int w = Matrix_width(mat);
  int index = row*w+column;
  return &mat->data[index];
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  int h = Matrix_height(mat);
  int w = Matrix_width(mat);
  for(int i = 0; i<h; i++){
    for(int j = 0; j<w; j++){
      *Matrix_at(mat, i, j) = value;
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  int h = Matrix_height(mat);
  int w = Matrix_width(mat);
  if(h == 0||w == 0){
    return;
  }
  for(int i=0; i<h; i++){
    *Matrix_at(mat, i, 0) = value;
    *Matrix_at(mat, i, w-1) = value;
  }
  for(int j = 1; j<w-1; j++){
    *Matrix_at(mat, 0, j) = value;
    *Matrix_at(mat, h-1, j) = value;
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  int max = *Matrix_at(mat, 0, 0);
  int h = Matrix_height(mat);
  int w = Matrix_width(mat);
  for(int i = 0; i<h;i++){
    for(int j = 0; j<w; j++){
      int value = *Matrix_at(mat, i, j);
      if(value>max){
        max = value;
      }
    }
  }
  return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  int min = *Matrix_at(mat, row, column_start);
  int index = column_start;
  for(int i = column_start+1; i<column_end; i++){
    int value = *Matrix_at(mat, row, i);
    if(value<min){
      min = value;
      index = i;
    }
  }
  return index;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
  int min = *Matrix_at(mat, row, column_start);
  for(int i = column_start+1; i<column_end; i++){
    int value = *Matrix_at(mat, row, i);
    if(value<min){
      min = value;
    }
  }
  return min;
}
