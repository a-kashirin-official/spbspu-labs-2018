#include "matrix.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace petrachenko;

Matrix::Matrix(Shape *shp):
  elements_(new Shape *[1]),
  numOfShapes_(1)
{
  if (shp == nullptr)
  {
    throw std::invalid_argument("Invalid_figures");
  }
  elements_[0] = shp;
}

Matrix::Matrix(const Matrix &mtrx):
  elements_(new Shape *[mtrx.numOfShapes_]),
  numOfShapes_(mtrx.getNum())
{
  for (size_t i = 0; i < numOfShapes_;i++)
  {
    elements_[i] = mtrx.elements_[i];
  }
}

Matrix::Matrix(Matrix &&mtrx):
  elements_(nullptr),
  numOfShapes_(0)
{
  *this = std::move(mtrx);
}

Matrix::~Matrix()
{
  for (size_t i = 0; i < numOfShapes_; i++)
  {
    delete elements_[i];
  }
}

size_t Matrix::getNum() const
{
  return numOfShapes_;
}

void Matrix::addShape(Shape *shp)
{
  if (shp == nullptr)
  {
    throw std::invalid_argument("Invalid_figures");
  }
  numOfShapes_++;
  std::unique_ptr<Shape *[]> tmp (new Shape *[numOfShapes_]);
  for (size_t i = 0; i < numOfShapes_-1; i++)
  {
    tmp[i] = elements_[i];
  }
  tmp[numOfShapes_-1] = shp;
  elements_.swap(tmp);
}

bool Matrix::isOverlapped(const Shape *shp1, const Shape *shp2)
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
    numOfShapes_ = mtrx.numOfShapes_;
    for (size_t i = 0; i < mtrx.numOfShapes_; i++)
    {
      elements_[i] = mtrx.elements_[i];
    }
  }
  return *this;
}

Matrix &Matrix::operator=(Matrix &&mtrx)
{
  if (this!=&mtrx)
  {
    numOfShapes_ = mtrx.numOfShapes_;
    elements_.swap(mtrx.elements_);
    mtrx.elements_ = nullptr;
    mtrx.numOfShapes_ = 0;
  }
  return *this;
}
Shape *Matrix::operator[](size_t num) const
{
  if (num>numOfShapes_)
  {
    throw std::invalid_argument("Invalid_value");
  }
  return elements_[num];
}

void Matrix::print()
{
  size_t layer[numOfShapes_];
  layer[0] = 0;
  for (size_t i = 1; i < numOfShapes_; i++)
  {
    if (isOverlapped(elements_[i],elements_[i-1]))
    {
      layer[i] = layer[i-1] + 1;
    }
    else
    {
      layer[i] = layer[i-1];
    }
  }
  for (size_t i = 0; i <= layer[numOfShapes_-1]; i++)
  {
    std::cout << std::endl << "Layer " << i << ": |";
    for (size_t j = 0; j < numOfShapes_; j++)
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

