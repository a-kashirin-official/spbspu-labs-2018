#include "matrix.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace gessen;

Matrix::Matrix():
  matrixList_(new Shape*[0]),
  shapeCounter_(0)
{

}

Matrix::Matrix(Shape *shp):
  matrixList_(new Shape *[1]),
  shapeCounter_(1)
{
  if (shp == nullptr)
  {
    throw std::invalid_argument("Invalid_figures");
  }
  matrixList_[0] = shp;
}

Matrix::Matrix(const Matrix &mtrx):
  matrixList_(new Shape *[mtrx.shapeCounter_]),
  shapeCounter_(mtrx.getNum())
{
  for (int i = 0; i < shapeCounter_;i++)
  {
    matrixList_[i] = mtrx.matrixList_[i];
  }
}

Matrix::Matrix(Matrix &&mtrx):
  matrixList_(nullptr),
  shapeCounter_(0)
{
  *this = std::move(mtrx);
}

Matrix::~Matrix()
{
  for (int i = 0; i < shapeCounter_; i++)
  {
    delete matrixList_[i];
  }
}

int Matrix::getNum() const
{
  return shapeCounter_;
}

void Matrix::addShape(Shape *shp)
{
  if (shp == nullptr)
  {
    throw std::invalid_argument("Invalid figures");
  }
  shapeCounter_++;
  std::unique_ptr<Shape *[]> tmp (new Shape *[shapeCounter_]);
  for (int i = 0; i < shapeCounter_-1; i++)
  {
    tmp[i] = matrixList_[i];
  }
  tmp[shapeCounter_-1] = shp;
  matrixList_.swap(tmp);
}

bool Matrix::overlapping(const Shape *shp1, const Shape *shp2)
{
  if ((shp1 == nullptr) || (shp2 == nullptr))
  {
    return false;
  }
  double dx = shp1->getFrameRect().pos.x - shp2->getFrameRect().pos.x;
  double dy = shp1->getFrameRect().pos.y - shp2->getFrameRect().pos.y;
  double dWidth = shp1->getFrameRect().width/2 + shp2->getFrameRect().width/2;
  double dHeigth = shp1->getFrameRect().height/2 + shp2->getFrameRect().height/2;
  return ((fabs(dx) < dWidth) && (fabs(dy) < dHeigth));
}

Matrix &Matrix::operator=(Matrix &mtrx)
{
  if (this!=&mtrx)
  {
    shapeCounter_ = mtrx.shapeCounter_;
    for (int i = 0; i < mtrx.shapeCounter_; i++)
    {
      matrixList_[i] = mtrx.matrixList_[i];
    }
  }
  return *this;
}

Matrix &Matrix::operator=(Matrix &&mtrx)
{
  if (this!=&mtrx)
  {
    shapeCounter_ = mtrx.shapeCounter_;
    matrixList_.swap(mtrx.matrixList_);
    mtrx.matrixList_ = nullptr;
    mtrx.shapeCounter_ = 0;
  }
  return *this;
}
Shape *Matrix::operator[](int num) const
{
  if (num>shapeCounter_)
  {
    throw std::invalid_argument("Invalid_value");
  }
  return matrixList_[num];
}

void Matrix::printShapes()
{
  int layer[shapeCounter_];
  layer[0] = 0;
  for (int i = 1; i < shapeCounter_; i++)
  {
    if (overlapping(matrixList_[i],matrixList_[i-1]))
    {
      layer[i] = layer[i-1] + 1;
    }
    else
    {
      layer[i] = layer[i-1];
    }
  }
  for (int i = 0; i <= layer[shapeCounter_-1]; i++)
  {
    std::cout << std::endl << "Layer " << i << ": |";
    for (int j = 0; j < shapeCounter_; j++)
    {
      if (i == layer[j])
      {
        std::cout << " * |";
      }
      else
      {
        std::cout << "   |";
      }
    }
  }
  std::cout << std::endl;
}

