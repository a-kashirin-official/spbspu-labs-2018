#include "matrix.hpp"

#include <stdexcept>

semakina::Matrix::Matrix(const std::shared_ptr <semakina::Shape> shape):
  line_(0),
  column_(0),
  matrix_(nullptr)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid_pointer");
  }
  addShape(shape);
}

semakina::Matrix::Matrix(const semakina::Matrix & matrix):
  line_(matrix.line_),
  column_(matrix.column_)
{
  matrix_.reset(new std::shared_ptr <semakina::Shape>[column_ * line_]);
  for (int i = 0; i < line_ * column_; ++i)
  {
    matrix_[i] = matrix.matrix_[i];
  }
}

semakina::Matrix::Matrix(const semakina::CompositeShape & compositeshape):
  line_(0),
  column_(0),
  matrix_(nullptr)
{
  for (int i = 0; i < compositeshape.getCounter(); ++i)
  {
    addShape(compositeshape[i]);
  }
}

semakina::Matrix::~Matrix()
{
  line_ = 0;
  column_ = 0;
  matrix_.reset(nullptr);
}

semakina::Matrix & semakina::Matrix::operator = (const semakina::Matrix & matrix)
{
  if (this != & matrix)
  {
    line_ = matrix.line_;
    column_ = matrix.column_;
    matrix_.reset(new std::shared_ptr <semakina::Shape>[column_ * line_]);
    for (int i = 0; i < line_ * column_; ++i)
    {
      matrix_[i] = matrix.matrix_[i];
    }
  }
  return * this;
}

std::shared_ptr <semakina::Shape > * semakina::Matrix::operator[](const int index) const
{
  if ((index < 0) || (index >= line_))
  {
    throw std::out_of_range("Invalid_layer");
  }
  return & matrix_[index * column_];
}

void semakina::Matrix::addShape(const std::shared_ptr <semakina::Shape> shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid_pointer");
  }
  if (line_ == 0)
  {
    ++line_;
    ++column_;
    std::unique_ptr <std::shared_ptr <semakina::Shape>[] > matrix(new std::shared_ptr < semakina::Shape >[1]);
    matrix_.swap(matrix);
    matrix_[0] = shape;
    return;
  }
  else
  {
    for (int i = 0; i < line_; ++i)
    {
      for (int j = 0; j < column_; ++j)
      {
        if (matrix_[i * column_ + j] == nullptr)
        {
          matrix_[i * column_ + j] = shape;
          return;
        }
        else if (checkLayer(i * column_ + j, shape))
        {
          break;
        }
        if (j == (column_ - 1))
        {
          ++column_;
          std::unique_ptr <std::shared_ptr <semakina::Shape>[] > matrix(new std::shared_ptr < semakina::Shape >[line_ * column_]);
          for (int k = 0; k < line_; ++k)
          {
            for (int n = 0; n < (column_ - 1); ++n)
            {
               matrix[k * column_ + n] = matrix_[k * (column_ - 1) + n];
            }
            matrix[(k + 1) * column_ - 1] = nullptr;
          }
          matrix[(i + 1) * column_ - 1] = shape;
          matrix_.swap(matrix);
          return;
        }
      }
      if (i == (line_ - 1))
      {
        ++line_;
        std::unique_ptr <std::shared_ptr <semakina::Shape>[] > matrix(new std::shared_ptr < semakina::Shape >[line_ * column_]);
        for (int k = 0; k < ((line_ - 1) * column_); ++k)
        {
          matrix[k] = matrix_[k];
        }
        for (int k = ((line_ - 1) * column_); k < (line_ * column_); ++k)
        {
          matrix[k] = nullptr;
        }
          matrix[(line_ - 1) * column_] = shape;
          matrix_.swap(matrix);
          return;
      }
    }
  }
}


bool semakina::Matrix::checkLayer(const int index, const std::shared_ptr <semakina::Shape> shape) const noexcept
{
  if ((shape == nullptr) || (matrix_[index] == nullptr))
  {
    return false;
  }
  semakina::rectangle_t newRect = shape -> getFrameRect();
  semakina::rectangle_t rect = matrix_[index] -> getFrameRect();
  return !(((rect.pos.x + rect.width / 2) < (newRect.pos.x - newRect.width / 2))
    || ((newRect.pos.x + newRect.width / 2) < (rect.pos.x - rect.width / 2))
      || ((rect.pos.y + rect.height / 2) < (newRect.pos.y - newRect.height / 2))
        || ((newRect.pos.y + newRect.height / 2) < (rect.pos.y - rect.height / 2)));
}

int semakina::Matrix::getLine() const noexcept
{
  return line_;
}

int semakina::Matrix::getColumn() const noexcept
{
  return column_;
}
