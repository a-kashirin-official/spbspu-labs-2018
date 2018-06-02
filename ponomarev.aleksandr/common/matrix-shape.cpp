#include "matrix-shape.hpp"

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <memory>


using namespace ponomarev;

MatrixShape::MatrixShape():
  matrix_(new std::shared_ptr<Shape>[0]),
  numberOfColumns_(0),
  numberOfRows_(0)
{
}

MatrixShape::MatrixShape(const MatrixShape &matrixShape):
  matrix_(new std::shared_ptr<Shape>[matrixShape.numberOfRows_ * matrixShape.numberOfColumns_]),
  numberOfColumns_(matrixShape.numberOfColumns_),
  numberOfRows_(matrixShape.numberOfRows_)
{
  for (unsigned int i = 0; i < numberOfColumns_ * numberOfRows_; i++)
  {
    matrix_[i] = matrixShape.matrix_[i];
  }
}

MatrixShape::MatrixShape(MatrixShape &&matrixShape) noexcept:
  matrix_(nullptr),
  numberOfColumns_(matrixShape.numberOfColumns_),
  numberOfRows_(matrixShape.numberOfRows_)
{
  matrix_.swap(matrixShape.matrix_);
  matrixShape.numberOfRows_ = 0;
  matrixShape.numberOfColumns_ = 0;
}

MatrixShape::~MatrixShape()
{
}

const std::shared_ptr<Shape> MatrixShape::operator()(unsigned int row, unsigned int column) const
{
  size_t index = row * numberOfColumns_ + column;
  if ((index >= numberOfRows_ * numberOfColumns_) || (row >= numberOfRows_) || (column >= numberOfColumns_))
  {
    throw std::out_of_range("MatrixShape operator () : out of size range");
  }
  return matrix_[index];
}

MatrixShape &MatrixShape::operator=(const MatrixShape &rhs)
{
  if (this != &rhs)
  {
    numberOfColumns_ = rhs.getNumberOfColumns();
    numberOfRows_ = rhs.getNumberOfRows();
    std::unique_ptr<std::shared_ptr<Shape>[]> copyObj
      (new std::shared_ptr<Shape>[rhs.getNumberOfColumns()]);
    for(size_t i = 0; i < rhs.getNumberOfColumns(); i++)
    {
      copyObj[i] = rhs.matrix_[i];
    }
    matrix_.swap(copyObj);
  }
  return *this;
}

MatrixShape &MatrixShape::operator=(MatrixShape &&rhs) noexcept
{
  if (this != &rhs)
  {
    numberOfColumns_ = rhs.numberOfColumns_;
    numberOfRows_ = rhs.numberOfRows_;
    matrix_.swap(rhs.matrix_);
    rhs.matrix_ = nullptr;
    rhs.numberOfColumns_ = 0;
    rhs.numberOfRows_ = 0;
  }
  return *this;
}

std::ostream &ponomarev::operator<<(std::ostream &out, const MatrixShape &matrix)
{
  for (size_t i = 0; i < matrix.getNumberOfRows(); i++)
  {
    out << "Layer number" << i + 1 << ":\n";
    for (size_t j = 0; j < matrix.numberOfColumns_; j++)
    {
      if (matrix.matrix_[i * matrix.getNumberOfColumns() + j] != nullptr)
      {
        matrix.matrix_[i * matrix.getNumberOfColumns() + j]->printShape();
        out << "\n";
      }
    }
  }
  return out;
}

void MatrixShape::addShape(const std::shared_ptr<Shape> &shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("invalid pointer");
  }

  if ((numberOfRows_ == 0) && (numberOfColumns_ == 0))
  {
    numberOfRows_ = 1;
    numberOfColumns_ = 1;
    std::unique_ptr<std::shared_ptr<Shape>[]> copyMatrix (new std::shared_ptr<Shape>[numberOfRows_ * numberOfColumns_]);
    matrix_.swap(copyMatrix);
    matrix_[0] = shape;
    return;
  }

  size_t i = numberOfRows_ * numberOfColumns_;
  size_t desired_row = 1;

  while (i > 0)
  {
    i --;
    if (checkForIntersection(matrix_[i], shape))
    {
      desired_row = i / numberOfColumns_ + 2;
    }
  }

  size_t rows_temp = numberOfRows_;
  size_t columns_temp = numberOfColumns_;
  size_t free_columns = 0;

  if (desired_row > numberOfRows_)
  {
    rows_temp ++;
    free_columns = numberOfColumns_;
  }
  else
  {
    size_t j = (desired_row - 1) * numberOfColumns_;
    while (j < (desired_row * numberOfColumns_))
    {
      if (matrix_[j] == nullptr)
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
      if (i >= numberOfRows_ || j >= numberOfColumns_)
      {
        matrix_temp[i * columns_temp + j] = nullptr;
        continue;
      }

      matrix_temp[i * columns_temp + j] = matrix_[i * numberOfColumns_ + j];
    }
  }

  matrix_temp[desired_row * columns_temp - free_columns] = shape;
  
  matrix_.swap(matrix_temp);
  numberOfRows_ = rows_temp;
  numberOfColumns_ = columns_temp;
}

size_t MatrixShape::getNumberOfColumns() const
{
  return numberOfColumns_;
}

size_t MatrixShape::getNumberOfRows() const
{
  return numberOfRows_;
}

bool MatrixShape::checkForIntersection(const std::shared_ptr<Shape> &firstShape,
  const std::shared_ptr<Shape> &secondShape) const
{
  rectangle_t getFrameF = firstShape->getFrameRect();
  rectangle_t getFrameS = secondShape->getFrameRect();

  double firstRectangleLeft = getFrameF.pos.x - getFrameF.width / 2.0;
  double firstRectangleRight = getFrameF.pos.x + getFrameF.width / 2.0;
  double firstRectangleTop = getFrameF.pos.y + getFrameF.height / 2.0;
  double firstRectangleBottom = getFrameF.pos.y - getFrameF.height / 2.0;

  double secondRectangleLeft = getFrameS.pos.x - getFrameS.width / 2.0;
  double secondRectangleRight = getFrameS.pos.x + getFrameS.width / 2.0;
  double secondRectangleTop = getFrameS.pos.y + getFrameS.height / 2.0;
  double secondRectangleBottom = getFrameS.pos.y - getFrameS.height / 2.0;

  bool Expression1 = firstRectangleLeft > secondRectangleRight;
  bool Expression2 = firstRectangleRight < secondRectangleLeft;
  bool Expression3 = firstRectangleTop < secondRectangleBottom;
  bool Expression4 = firstRectangleBottom > secondRectangleTop;

  if (Expression1 || Expression2 || Expression3 || Expression4)
  {
    return false;
  }
  else
  {
    return true;
  }
}

