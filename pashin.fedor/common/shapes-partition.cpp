#include "shapes-partition.hpp"

#include <cmath>
#include <stdexcept>

using namespace std;
using namespace pashin;

pashin::ShapesPartition::ShapesPartition():
  num_rows_(0),
  num_columns_(0)
{}

pashin::ShapesPartition& pashin::ShapesPartition::operator=(const pashin::ShapesPartition& rhs)
{
  if (this != &rhs) {
    int length = rhs.num_rows_ * rhs.num_columns_;
    unique_ptr<Shape*[]> new_matrix(new Shape*[length]());
    num_rows_ = rhs.num_rows_;
    num_columns_ = rhs.num_columns_;
    for (int i = 0; i < length; ++i) {
      new_matrix[i] = rhs.matrix_[i];
    }
    swap(matrix_, new_matrix);
  }
  return *this;
}

pashin::ShapesPartition& pashin::ShapesPartition::operator=(pashin::ShapesPartition&& rhs)
{
  if (this != &rhs) {
    num_rows_ = rhs.num_rows_;
    num_columns_ = rhs.num_columns_;
    matrix_.reset();
    swap(matrix_, rhs.matrix_);
  }
  return *this;
}

unique_ptr<pashin::Shape*[]> pashin::ShapesPartition::operator[](int pos) const
{
  if (!((pos >= 0) && (pos < num_rows_))) {
    throw invalid_argument("Index out of range");
  }
  
  unique_ptr<Shape*[]> layer(new Shape*[num_columns_]);
  for (int i = 0; i < num_columns_; ++i) {
    layer[i] = matrix_[pos * num_columns_ + i];
  }
  return layer;
}

pashin::Shape* pashin::ShapesPartition::getShape(int row, int column) const
{
  if (!((row >= 0) && (row < num_rows_) && (column >= 0) && (column < num_columns_))) {
    throw invalid_argument("Index out of range");
  }
  return matrix_[row * num_columns_ + column];
}

int pashin::ShapesPartition::num_rows() const
{
  return num_rows_;
}

int pashin::ShapesPartition::num_columns() const
{
  return num_columns_;
}

void pashin::ShapesPartition::addShape(pashin::Shape& shape)
{
  for (int i = 0; i < num_rows_ * num_columns_; ++i) {
    if (&shape == matrix_[i]) {
      throw invalid_argument("The shape is already added");
    }
  }
  
  bool is_added = false;
  if (num_columns_ == 0) {
    addColumn();
  } else {
    for (int i = 0; (i < num_rows_) && (cell(i, 0) != nullptr); ++i) {
      bool are_intersecting = false;
      for (int j = 0; (j < num_columns_) && (cell(i, j) != nullptr); ++j) {
        if (areIntersecting(&shape, *cell(i, j))) {
          are_intersecting = true;
          break;
        }
      }
      if (are_intersecting == false) {
        int k = 0;
        if (cell(i, num_columns_ - 1) == nullptr) {
          while (cell(i, k) != nullptr) {
            ++k;
          }
        } else {
          addColumn();
          k = num_columns_ - 1;
        }
        *cell(i, k) = &shape;
        is_added = true;
        break;
      }
    }
  }
  
  if (is_added == false) {
    addRow();
    *cell(num_rows_ - 1, 0) = &shape;
  }
}

void pashin::ShapesPartition::removeShape(pashin::Shape* shape)
{
  if (shape == nullptr) {
    throw invalid_argument("Nullptr");
  }
  
  bool is_found = false;
  for (int i = 0; (i < num_rows_) && (is_found == false); ++i) {
    for (int j = 0; (j < num_columns_) && (is_found == false); ++j) {
      if (*cell(i, j) == shape) {
        is_found = true;
        *cell(i, j) = nullptr;
        for (int k = j; k < num_columns_ - 1; ++k) {
          *cell(i, k) = *cell(i, k + 1);
        }
      }
    }
  }
  
  if (is_found == false) {
    throw invalid_argument("The shape not found");
  }
}

bool pashin::ShapesPartition::areIntersecting(const pashin::Shape* shape_1, const pashin::Shape* shape_2) const
{
  const rectangle_t& frame_rect_1 = shape_1->getFrameRect();
  const rectangle_t& frame_rect_2 = shape_2->getFrameRect();
  if ((abs(frame_rect_2.pos.x - frame_rect_1.pos.x)
        <= frame_rect_1.width / 2 + frame_rect_2.width / 2)
      && (abs(frame_rect_2.pos.y - frame_rect_1.pos.y)
        <= frame_rect_1.height / 2 + frame_rect_2.height / 2)) {
    return true;
  } else {
    return false;
  }
}

pashin::Shape** pashin::ShapesPartition::cell(int row, int column) const
{
  if (!((row >= 0) && (row < num_rows_) && (column >= 0) && (column < num_columns_))) {
    throw invalid_argument("Index out of range");
  }
  return &matrix_[row * num_columns_ + column];
}

void pashin::ShapesPartition::addRow()
{
  int old_length = num_rows_ * num_columns_;
  ++num_rows_;
  int new_length = num_rows_ * num_columns_;
  
  unique_ptr<Shape*[]> new_matrix(new Shape*[new_length]);
  for (int i = 0; i < old_length; ++i) {
    new_matrix[i] = matrix_[i];
  }
  for (int j = 0; j < num_columns_; ++j) {
    new_matrix[old_length + j] = nullptr;
  }
  
  swap(matrix_, new_matrix);
}

void pashin::ShapesPartition::addColumn()
{
  ++num_columns_;
  int new_length = num_rows_ * num_columns_;
  
  unique_ptr<Shape*[]> new_matrix(new Shape*[new_length]);
  for (int i = 0; i < num_rows_; ++i) {
    for (int j = 0; j < num_columns_ - 1; ++j) {
      new_matrix[i * num_columns_ + j] = *cell(i, j);
    }
    new_matrix[i * num_columns_ + num_columns_ - 1] = nullptr;
  }
  
  swap(matrix_, new_matrix);
}
