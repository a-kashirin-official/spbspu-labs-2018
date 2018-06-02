#include "matrix.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

spodeneyko::MatrixShape::MatrixShape(const std::shared_ptr<Shape> & shapeElement):
  matrix_(new std::shared_ptr<Shape>[1]),
  rows_(0),
  columns_(0)
{
  if (!shapeElement)
  {
    throw std::invalid_argument("Error. Object does not exist.");
  }
  matrix_[0] = shapeElement;
  ++rows_;
  ++columns_;
}

spodeneyko::MatrixShape::MatrixShape(const MatrixShape & object):
  matrix_(new std::shared_ptr<Shape>[object.rows_ * object.columns_]),
  rows_(object.rows_),
  columns_(object.columns_)
{  
  for (size_t i = 0; i < (rows_ * columns_); ++i)
  {
    matrix_[i] = object.matrix_[i];
  }
}

spodeneyko::MatrixShape::MatrixShape(MatrixShape && object):
  matrix_(std::move(object.matrix_)),
  rows_(std::move(object.rows_)),
  columns_(std::move(object.columns_))
{
  object.matrix_.reset();
  object.rows_ = 0;
  object.columns_ = 0;
}

spodeneyko::MatrixShape & spodeneyko::MatrixShape::operator =(const MatrixShape & object)
{
  if (this != &object)
  {
    rows_ = object.rows_;
    columns_ = object.columns_;
    matrix_type new_arr(new std::shared_ptr<Shape>[rows_ * columns_]);
    for (size_t i = 0; i < (rows_ * columns_); ++i)
    {
      new_arr[i] = object.matrix_[i];
    }
    matrix_.swap(new_arr);
  }
  return *this;
}

spodeneyko::MatrixShape & spodeneyko::MatrixShape::operator =(MatrixShape && object)
{
  if (this != &object)
  {
    matrix_ = std::move(object.matrix_);
    rows_ = std::move(object.rows_);
    columns_ = std::move(object.columns_);
    object.matrix_.reset();
    object.rows_ = 0;
    object.columns_ = 0;
  }
  return *this;
}

std::unique_ptr<std::shared_ptr<spodeneyko::Shape>[]>::pointer spodeneyko::MatrixShape::operator [](const size_t index)
{
  if (index > rows_)
  {
    throw std::out_of_range("Error. Index is out of range.");
  }
  return (matrix_.get() + index * columns_);
}

void spodeneyko::MatrixShape::addShape(const std::shared_ptr<Shape> & shapeElement)
{
  if (!shapeElement)
  {
    throw std::invalid_argument("Error. Object does not exist.");
  }
  size_t i = rows_ * columns_;
  size_t desired_row = 1; // Номер строки, на которую будет помещена фигура.
  while (i > 0)
  {
    --i;
    if (checkOverlap(matrix_[i], shapeElement))
    {
      desired_row = i / columns_ + 2;
    }
  }
  size_t rows_temp = rows_;
  size_t columns_temp = columns_;
  size_t free_columns = 0; // Число свободных ячеек на выбранной строке.
  if (desired_row > rows_)
  {
    ++rows_temp;
    free_columns = columns_;
  }
  else
  {
    size_t j = (desired_row - 1) * columns_;
    while (j < (desired_row * columns_))
    {
      if (!matrix_[j])
      {
        ++free_columns;
      }
      ++j;
    }
    if (free_columns == 0)
    {
      ++columns_temp;
      free_columns = 1;
    }
  }
  matrix_type new_arr(new std::shared_ptr<Shape>[rows_temp * columns_temp]);
  for (size_t i = 0; i < rows_temp; ++i)
  {
    for (size_t j = 0; j < columns_temp; ++j)
    {
      if ((i >= rows_) || (j >= columns_))
      {
        new_arr[i * columns_temp + j].reset();
        continue;
      }
      new_arr[i * columns_temp + j] = matrix_[i * columns_ + j];
    }
  }
  new_arr[desired_row * columns_temp - free_columns] = shapeElement;
  matrix_.swap(new_arr);
  rows_ = rows_temp;
  columns_ = columns_temp;
}

void spodeneyko::MatrixShape::print() const
{
  for (size_t i = 0; i < rows_; ++i)
  {
    for (size_t j = 0; j < columns_; ++j)
    {
      if (matrix_[i * columns_ + j])
      {
        std::cout << std::setw(15) << std::right << matrix_[i * columns_ + j] -> getName();
      }
    }
    std::cout << std::endl;
  }
}

bool spodeneyko::MatrixShape::checkOverlap(const std::shared_ptr<Shape> & shape1, const std::shared_ptr<Shape> & shape2) const
{
  if ((!shape1) || (!shape2))
  {
    return false;
  }
  rectangle_t shapeFrameRect1 = shape1 -> getFrameRect();
  rectangle_t shapeFrameRect2 = shape2 -> getFrameRect();
  return ((abs(shapeFrameRect1.pos.x - shapeFrameRect2.pos.x)
    < ((shapeFrameRect1.width / 2) + (shapeFrameRect2.width / 2)))
      && ((abs(shapeFrameRect1.pos.y - shapeFrameRect2.pos.y)
        < ((shapeFrameRect1.height / 2) + (shapeFrameRect2.height / 2)))));
}
