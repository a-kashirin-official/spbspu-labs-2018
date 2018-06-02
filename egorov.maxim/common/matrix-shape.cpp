#include "matrix-shape.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip>

using namespace egorov;

MatrixShape::MatrixShape():
  rows_(0),
  columns_(0),
  groups_(nullptr)
{
}

MatrixShape::MatrixShape(const MatrixShape &object):
  rows_(object.rows_),
  columns_(object.columns_),
  groups_(new std::shared_ptr<Shape> [object.rows_ * object.columns_])
{
  for (size_t i = 0; i < (rows_ * columns_); i++)
  {
    groups_[i] = object.groups_[i];
  }
}

MatrixShape::MatrixShape(MatrixShape &&object) noexcept:
  rows_(object.rows_),
  columns_(object.columns_),
  groups_(nullptr)
{
  groups_.swap(object.groups_);
  object.rows_ = 0;
  object.columns_ = 0;
}

MatrixShape &MatrixShape::operator=(const MatrixShape &rhs)
{
  if (this != &rhs)
  {
    rows_ = rhs.rows_;
    columns_ = rhs.columns_;
    std::unique_ptr <std::shared_ptr <Shape>[]> copyObject (new std::shared_ptr <Shape>[rows_ * columns_]);
    for (size_t i = 0; i < (rows_ * columns_); i++)
    {
      copyObject[i] = rhs.groups_[i];
    }
    groups_.swap(copyObject);
  }
  return *this;
}

MatrixShape &MatrixShape::operator=(MatrixShape &&rhs) noexcept
{
  if (this != &rhs)
  {
    rows_ = rhs.rows_;
    columns_ = rhs.columns_;
    groups_.reset();
    groups_.swap(rhs.groups_);
    rhs.rows_ = 0;
    rhs.columns_ = 0;
  }
  return *this;
}

std::unique_ptr<std::shared_ptr<Shape>[]>::pointer MatrixShape::operator[](size_t index) const
{
  if (index > rows_)
  {
    throw std::invalid_argument("Invalid index");
  }

  return groups_.get() + index * columns_;
}

void MatrixShape::addShape(const std::shared_ptr<Shape> &shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Invalid pointer");
  }

  if ((rows_ == 0) && (columns_ == 0))
  {
    rows_ = 1;
    columns_ = 1;
    std::unique_ptr<std::shared_ptr<Shape>[]> copyMatrix (new std::shared_ptr<Shape>[rows_ * columns_]);
    groups_.swap(copyMatrix);
    groups_[0] = shape;
    return;
  }

  size_t i = rows_ * columns_;
  size_t desired_row = 1;

  while (i > 0)
  {
    i --;
    if (crossing(groups_[i], shape))
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
      if (groups_[j] == nullptr)
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

  std::unique_ptr <std::shared_ptr<Shape>[]> temp(new std::shared_ptr<Shape>[rows_temp * columns_temp]);

  for (size_t i = 0; i < rows_temp; i ++)
  {
    for (size_t j = 0; j < columns_temp; j ++)
    {
      if (i >= rows_ || j >= columns_)
      {
        temp[i * columns_temp + j] = nullptr;
        continue;
      }

      temp[i * columns_temp + j] = groups_[i * columns_ + j];
    }
  }

  temp[desired_row * columns_temp - free_columns] = shape;

  groups_.swap(temp);
  rows_ = rows_temp;
  columns_ = columns_temp;
}

bool MatrixShape::crossing(const std::shared_ptr<Shape> &shape1, const std::shared_ptr<Shape> &shape2) noexcept
{
  if (!shape1 || !shape2)
  {
    return false;
  }

  return (abs(shape1->getFrameRect().pos.x - shape2->getFrameRect().pos.x) < ((shape1->getFrameRect().width +
  shape2->getFrameRect().width) / 2) && (abs(shape1->getFrameRect().pos.y - shape2->getFrameRect().pos.y) <
  (shape1->getFrameRect().height + shape2->getFrameRect().height) / 2));
}

void MatrixShape::printInfo() noexcept
{
  if (rows_ == 0 && columns_ == 0)
  {
    std::cout << "Matrix is empty" << '\n';
  }
  else
  {
  for (size_t i = 0; i < rows_; i++)
  {
    for (size_t j = 0; j < columns_; j++)
    {
      if (groups_[i * columns_ + j])
      {
        std::cout << std::setw(10) << groups_[i * columns_ + j] -> getName();
      }
    }
    std::cout << '\n';
  }
  }
}
