#include "matrix.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace khodyreva;

Matrix::Matrix(const std::shared_ptr<Shape> & shape):
data_(new std::shared_ptr<Shape>[1]),
rows_(1),
columns_(1)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("invalid pointer");
  }
  data_[0] = shape;
}

Matrix::Matrix(const Matrix & matrix):
rows_(matrix.rows_),
columns_(matrix.columns_)
{
  std::unique_ptr <std::shared_ptr<Shape>[]> mtxCopy(new std::shared_ptr<Shape>[rows_ * columns_]);
  for (size_t i = 0; i < (rows_ * columns_); i ++)
  {
    mtxCopy[i] = matrix.data_[i];
  }
  data_.swap(mtxCopy);
}

Matrix::Matrix(Matrix && matrix):
rows_(matrix.rows_),
columns_(matrix.columns_)
{
  data_=std::move(matrix.data_);
  matrix.data_=(nullptr);
  matrix.rows_=0;
  matrix.columns_=0;
}

Matrix & Matrix::operator=(const Matrix & matrix)
{
  if (this != &matrix)
  {
    rows_ = matrix.rows_;
    columns_ = matrix.columns_;
    std::unique_ptr <std::shared_ptr<Shape>[]> mtxCopy(new std::shared_ptr<Shape>[rows_ * columns_]);

    for (size_t i = 0; i < (rows_ * columns_); i ++)
    {
      mtxCopy[i] = matrix.data_[i];
    }
    data_.swap(mtxCopy);
  }
  return *this;
}

Matrix & Matrix::operator=(Matrix && matrix)
{
  if (this != &matrix)
  {
    rows_ = matrix.rows_;
    columns_ = matrix.columns_;
    data_=std::move(matrix.data_);
    matrix.data_ = (nullptr);
    matrix.rows_ = 0;
    matrix.columns_ = 0;
  }
  return *this;
}


std::unique_ptr <std::shared_ptr<Shape>[]>::pointer Matrix::operator[](const size_t index) const
{
  if (index > rows_)
  {
    throw std::invalid_argument("index out of range");
  }
  return data_.get() + index * columns_;
}


void Matrix::addShape(const std::shared_ptr<Shape> & shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("invalid pointer");
  }
  size_t i = rows_ * columns_;
  size_t desired_row = 1;

  while (i > 0)
  {
    i --;
    if (checkOverlap(data_[i], shape))
    {
      desired_row = i / columns_ + 2;
    }
  }

  size_t rows_temp = rows_;
  size_t columns_temp = columns_;
  size_t free_columns = 0;

  if (desired_row > rows_)
  {
    rows_temp ++;
    free_columns = columns_;
  }
  else
  {
    size_t j = (desired_row - 1) * columns_;
    while (j < (desired_row * columns_))
    {
      if (data_[j] == nullptr)
      {
        free_columns ++;
      }
      j ++;
    }

    if (free_columns == 0)
    {
      columns_temp ++;
      free_columns = 1;
    }
  }

  std::unique_ptr <std::shared_ptr<Shape>[]> matrix_temp(new std::shared_ptr<Shape>[rows_temp * columns_temp]);

  for (size_t i = 0; i < rows_temp; i ++)
  {
    for (size_t j = 0; j < columns_temp; j ++)
    {
      if (i >= rows_ || j >= columns_)
      {
        matrix_temp[i * columns_temp + j] = nullptr;
        continue;
      }
      matrix_temp[i * columns_temp + j] = data_[i * columns_ + j];
    }
  }

  matrix_temp[desired_row * columns_temp - free_columns] = shape;

  data_.swap(matrix_temp);
  rows_ = rows_temp;
  columns_ = columns_temp;
}


size_t Matrix::getColumns() const
{
  return columns_;
}

size_t Matrix::getRows() const
{
  return rows_;
}

size_t Matrix::getLayerSize(const size_t row) const
{
  int count = 0;
  for (size_t i = rows_; i < row * columns_; ++i)
  {
    if (data_[i] != (nullptr))
    {
      ++count;
    }
  }
  return count;
}

void Matrix::addFromCShape(const CompositeShape &composite)
{
  for (size_t i = 0; i < composite.getSize(); i++)
  {
    addShape(composite[i]);
  }
}

bool Matrix::checkOverlap(const std::shared_ptr<Shape> &shape_1, const std::shared_ptr<Shape> &shape_2) const
{
  if (shape_1 == nullptr || shape_2 == nullptr)
  {
    return false;
  }

  rectangle_t shape_1_frame_rect = shape_1 -> getFrameRect();
  rectangle_t shape_2_frame_rect = shape_2 -> getFrameRect();

  return ((fabs(shape_1_frame_rect.pos.x - shape_2_frame_rect.pos.x)
           < ((shape_1_frame_rect.width / 2) + (shape_2_frame_rect.width / 2)))
             && ((fabs(shape_1_frame_rect.pos.y - shape_2_frame_rect.pos.y)
               < ((shape_1_frame_rect.height / 2) + (shape_2_frame_rect.height / 2)))));
}


void Matrix::printInfo()
{
  if (rows_ == 0 && columns_ == 0)
  {
    std::cout << "Matrix is empty" << std::endl;
  }
  else
  {
    for (size_t i = 0; i < rows_; i++)
    {
      for (size_t j = 0; j < columns_; j++)
      {
        if (data_[i * columns_ + j])
        {
          std::cout << std::setw(10) << data_[i * columns_ + j] -> getName();
        }
      }
      std::cout << std::endl;
    }
  }
}
