#include <iostream>
#include "matrix.hpp"

using std::cout;
using std::endl;
using namespace averin;

Matrix::Matrix(const std::shared_ptr<Shape>& shape) :
  matrix_(new std::shared_ptr<Shape>[1]),
  columns_(1),
  rows_(1)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  matrix_[0] = shape;
}

Matrix::Matrix() :
  matrix_(new std::shared_ptr<Shape>[1]),
  columns_(0),
  rows_(0)
{

}

Matrix & Matrix::operator = (const Matrix& mtrx)
{
  if (this != &mtrx)
  {
    this->columns_ = mtrx.columns_;
    this->rows_ = mtrx.rows_;
    std::unique_ptr<std::shared_ptr<Shape>[]> tempMatrix (new std::shared_ptr<Shape>[rows_ * columns_]);
    for (int i = 0; i < rows_*columns_; i++)
    {
      tempMatrix[i] = mtrx.matrix_[i];
    }
    this->matrix_.swap(tempMatrix);
  }
  return *this;
}

void Matrix::addShape(const std::shared_ptr<Shape>& shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  if ((rows_ == 0) && (columns_ == 0))
  {
    columns_ = 1;
    rows_ = 1;
    matrix_[0] = shape;
    return;
  }
  int newRow = 1; 
  for (int i = 0; i < rows_ * columns_; i++)  
  {
    if (checkIntersection(matrix_[i], shape) == true)
    {
      newRow = i / columns_ + 2;
    }
  }
  int tempRows = rows_;
  int tempColumns = columns_;
  int freeColumns = 0; 
  if (newRow > rows_)
  {
    tempRows++;
    freeColumns = columns_;
  }
  else
  {
    for (int j = (newRow - 1) * columns_; j < newRow * columns_; j++)
    {
      if (matrix_[j] == nullptr)
      {
        freeColumns++;
      }
    }  
    if (freeColumns == 0)
    {
      tempColumns++;
      freeColumns = 1;
    }
  }

  std::unique_ptr <std::shared_ptr<Shape>[]> matrix_temp(new std::shared_ptr<Shape>[tempRows * tempColumns]);
  
  for (int i = 0; i < tempRows; i++)
  {
    for (int j = 0; j < tempColumns; j++)
    {
      if (i >= rows_ || j >= columns_)
      {
        matrix_temp[i * tempColumns + j] = nullptr;
        continue;
      }
      matrix_temp[i * tempColumns + j] = matrix_[i * columns_ + j];
    }
  }
  matrix_temp[newRow * tempColumns - freeColumns] = shape; 
  matrix_.swap(matrix_temp);
  rows_ = tempRows;
  columns_ = tempColumns;
}

int Matrix::getRows() const
{
  return rows_;
}

int Matrix::getColumns() const
{
  return columns_;
}

bool Matrix::checkIntersection(const std::shared_ptr<Shape>& shape1, const std::shared_ptr<Shape>& shape2)
{
  if (shape1 == nullptr)
  {
    return false;
  }
  bool checkX = false;
  double x1 = shape1->getFrameRect().pos.x;
  double x2 = shape2->getFrameRect().pos.x;
  double width1 = shape1->getFrameRect().width;
  double width2 = shape2->getFrameRect().width;
  if (abs(x1-x2) < (width1/2 + width2/2))  
  {
    checkX = true;
  }
  bool checkY = false;
  double y1 = shape1->getFrameRect().pos.y;
  double y2 = shape2->getFrameRect().pos.y;
  double height1 = shape1->getFrameRect().height;
  double height2 = shape2->getFrameRect().height;  
  if (abs(y1-y2) < (height1/2 + height2/2))  
  {
    checkY = true;
  }
  return checkX && checkY;
}

void Matrix::printInfo() const
{
  cout << endl;
  cout << "Rows: " << rows_ << " Columns: " << columns_ << endl;
  for (int i = 0; i < rows_; i++)
  {
    for (int j = 0; j < columns_; j++)
    {
      if (matrix_[i * columns_ + j] != nullptr)
      {
        matrix_[i * columns_ + j]->printName();
        cout << " ";
      }
    }
    cout << endl;
  }
}
