#include "matrix.hpp"
#include <iostream>
#include <memory>
#include <cmath>

shapovalova::Matrix::Matrix(const std::shared_ptr<Shape> & element):
  matrix_(new std::shared_ptr<Shape>[1]),
  rows_(0),
  columns_(0)
{
  if (element == nullptr)
  {
    matrix_.reset();
    throw std::invalid_argument ("Error! Detected nullptr");
  }
  matrix_[0] = element;
  rows_++;
  columns_++;
}

shapovalova::Matrix::Matrix(const Matrix & elem):
  matrix_(new std::shared_ptr<Shape>[(elem.rows_ * elem.columns_)]),
  rows_(elem.rows_),
  columns_(elem.columns_)
{
  for (int i = 0; i < (rows_ * columns_); ++i)
  {
    matrix_[i] = elem.matrix_[i];
  }
}

shapovalova::Matrix::Matrix(Matrix && elem):
  matrix_(std::move(elem.matrix_)),
  rows_(elem.rows_),
  columns_(elem.columns_)
{
  elem.matrix_.reset();
  elem.rows_ = 0;
  elem.columns_ = 0;
}

shapovalova::Matrix & shapovalova::Matrix::operator= (const Matrix & elem)
{
  if (this == &elem)
  {
    return *this;
  }
  matrix_.reset(new std::shared_ptr<Shape>[(elem.rows_ * elem.columns_)]);
  rows_ = elem.rows_;
  columns_ = elem.columns_;
  for (int i = 0; i < (rows_ * columns_); ++i)
  {
    matrix_[i] = elem.matrix_[i];
  }
  return *this;
}

shapovalova::Matrix & shapovalova::Matrix::operator= (Matrix && elem)
{
  matrix_ = std::move(elem.matrix_);
  rows_ = elem.rows_;
  columns_ = elem.columns_;
  elem.rows_ = 0;
  elem.columns_ = 0;
  return *this;
}

std::unique_ptr<std::shared_ptr<shapovalova::Shape>[]> shapovalova::Matrix::operator [](const int index) const
{
  if ((index < 0) || (index >= rows_))
  {
    throw std::out_of_range ("Invalid index!");
  }
  std::unique_ptr<std::shared_ptr<shapovalova::Shape>[]>
      layer(new std::shared_ptr<shapovalova::Shape>[columns_]);
  for (int i = 0; i < columns_; ++i)
  {
    layer[i] = matrix_[index * columns_ + i];
  }
  return layer;
}

void shapovalova::Matrix::addShape(const std::shared_ptr<Shape> & element)
{
  if (element == nullptr)
  {
    throw std::invalid_argument ("The object must exist!");
  }
  bool checkingAdd = false;
  for (int i = 0; !checkingAdd; ++i)
  {
    for (int j = 0; j < columns_; ++j)
    {
      if (!matrix_[i * columns_ + j])
      {
        matrix_[i * columns_ + j] = element;
        checkingAdd = true;
        break;
      }
      else
      {
        if (checkInsertion(matrix_[i * columns_ + j], element))
        {
          break;
        }
      }

      if (j == (columns_ - 1) && (!checkingAdd))
      {
        std::unique_ptr<std::shared_ptr<shapovalova::Shape>[]> newMatrix (
              new std::shared_ptr<shapovalova::Shape>[rows_ * (columns_ + 1)]);
        columns_++;
        for (int n = 0; n < rows_; ++n)
        {
          for (int m = 0; m < columns_ - 1; ++m)
          {
            newMatrix[n * columns_ + m] = matrix_[n * (columns_ - 1) + m];
          }
          newMatrix[(n + 1) * columns_ - 1] = nullptr;
        }
        newMatrix[(i + 1) * columns_ - 1] = element;
        matrix_.swap(newMatrix);
        checkingAdd = true;
        break;
      }
    }
    if ((i == (rows_ - 1)) && (!checkingAdd))
    {
      std::unique_ptr<std::shared_ptr<shapovalova::Shape>[]> newMatrix (
            new std::shared_ptr<shapovalova::Shape>[(rows_ + 1) * columns_]);
      rows_++;
      for (int n = 0; n < ((rows_ - 1) * columns_); ++n)
      {
        newMatrix[n] = matrix_[n];
      }
      for (int n = ((rows_ - 1) * columns_); n < (rows_ * columns_); ++n)
      {
        newMatrix[n] = nullptr;
      }
      newMatrix[(rows_ - 1) * columns_] = element;
      matrix_.swap(newMatrix);
      checkingAdd = true;
    }
  }
}

void shapovalova::Matrix::print() const noexcept
{
  std::cout << "Matrix:" << std::endl;
  std::cout << "Number of rows: " << rows_ << std::endl;
  std::cout << "Number of columns: " << columns_ << std::endl;
}

int shapovalova::Matrix::getRows() const noexcept
{
  return rows_;
}

int shapovalova::Matrix::getColumns() const noexcept
{
  return columns_;
}

bool shapovalova::Matrix::checkInsertion(const std::shared_ptr<Shape> & shape1, const std::shared_ptr<Shape> & shape2)
{
  if ((shape1 == nullptr) || (shape2 == nullptr))
  {
    return false;
  }
  shapovalova::rectangle_t shapeFrameRect1 = shape1 -> getFrameRect();
  shapovalova::rectangle_t shapeFrameRect2 = shape2 -> getFrameRect();
  bool checkX = (abs(shapeFrameRect1.pos.x - shapeFrameRect2.pos.x)
                 < (shapeFrameRect1.width / 2 + shapeFrameRect2.width / 2));
  bool checkY = (abs(shapeFrameRect1.pos.y - shapeFrameRect2.pos.y)
                 < (shapeFrameRect1.height / 2 + shapeFrameRect2.height / 2));
  return ((checkX) && (checkY));
}
