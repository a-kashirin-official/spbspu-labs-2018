#include <iostream>
#include "matrix.hpp"

using namespace starikov;

Matrix::Matrix(const std::shared_ptr<Shape> shape):
  sizeLayer_(0),
  sizeShape_(0),
  arrayShape_(nullptr)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Can't be nullptr!");
  }
  if ((shape->getFrameRect().height < 0.0) || (shape->getFrameRect().width < 0.0))
  {
    throw std::invalid_argument("Warning! Incorrect values...");
  }
  addShape(shape);
}

Matrix::Matrix() noexcept:
  sizeLayer_(0),
  sizeShape_(0),
  arrayShape_(nullptr)
{
}

Matrix::~Matrix()
{
}

Matrix::Matrix(const Matrix & matrix):
  sizeLayer_(matrix.sizeLayer_),
  sizeShape_(matrix.sizeShape_),
  arrayShape_(new std::shared_ptr<Shape>[matrix.sizeLayer_ * matrix.sizeShape_])
{
  for (int i = 0; i < sizeLayer_ * sizeShape_; ++i)
  {
    arrayShape_[i] = matrix.arrayShape_[i];
  }
}

Matrix::Matrix(Matrix && matrix):
  sizeLayer_(matrix.sizeLayer_),
  sizeShape_(matrix.sizeShape_),
  arrayShape_(nullptr)
{
  arrayShape_.swap(matrix.arrayShape_);
  matrix.sizeShape_ = 0;
  matrix.sizeLayer_ = 0;
}

const Shape & Matrix::operator [](int index) const
{
  if ((index < 0) || (index >= (sizeShape_ * sizeLayer_)))
  {
    throw std::out_of_range("Matrix's index is out of range!");
  }
  return *arrayShape_[index];
}

void Matrix::addShape(const std::shared_ptr<starikov::Shape> newShape)
{
  if (newShape == nullptr) {
    throw std::invalid_argument("Can't be nullptr!");
  }
  if ((newShape->getFrameRect().height < 0.0) || (newShape->getFrameRect().width < 0.0)) {
    throw std::invalid_argument("Warning! Incorrect values...");
  }
  if ((sizeLayer_ == 0) && (sizeShape_ == 0))
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> tempArray(new std::shared_ptr<Shape>[1]);
    tempArray[0] = newShape;
    arrayShape_.swap(tempArray);
    sizeLayer_ = 1;
    sizeShape_ = 1;
    return;
  }
  int i = 0;
  for (; i < sizeLayer_; ++i)
  {
    int j = 0;
    for(; j < sizeShape_; ++j)
    {
      if (!arrayShape_[i * sizeShape_ + j])
      {
        arrayShape_[i * sizeShape_ + j] = newShape;
        return;
      }
      if (crossChecking(arrayShape_[i * sizeShape_ + j], newShape))
      {
        break;
      }
    }
    if (j == sizeShape_)
    {
      std::unique_ptr<std::shared_ptr<Shape>[]> tempArray(new std::shared_ptr<Shape>[sizeLayer_ * (sizeShape_ + 1)]);
      for (int k = 0; k < sizeLayer_; ++k)
      {
        for (j = 0; j < sizeShape_; ++j)
        {
          tempArray[k * sizeShape_ + j + k] = arrayShape_[k * sizeShape_ + j];
        }
      }
      ++sizeShape_;
      tempArray[(i + 1) * sizeShape_ - 1] = newShape;
      arrayShape_ = std::move(tempArray);
      return;
    }
  }
  if (i == sizeLayer_) {
    std::unique_ptr<std::shared_ptr<Shape>[]> tempArray(new std::shared_ptr<Shape>[(sizeLayer_ + 1) * sizeShape_]);
    for (int k = 0; k < sizeLayer_ * sizeShape_; ++k) {
      tempArray[k] = arrayShape_[k];
    }
    tempArray[sizeLayer_ * sizeShape_] = newShape;
    ++sizeLayer_;
    ++sizeShape_;
    arrayShape_ = std::move(tempArray);
  }
}

bool Matrix::crossChecking(const std::shared_ptr<starikov::Shape> &shapeCurr, const std::shared_ptr<starikov::Shape> &shapeNew) const
{
  if ((shapeNew == nullptr) && (shapeCurr == nullptr))
  {
    std::invalid_argument("Shape is nullptr!");
  }
  rectangle_t newShape = shapeNew->getFrameRect();
  rectangle_t currShape = shapeCurr->getFrameRect();
  point_t newPoints[4] =
    {
      {newShape.pos.x - newShape.width / 2.0, newShape.pos.y + newShape.height / 2.0},
      {newShape.pos.x + newShape.width / 2.0, newShape.pos.y + newShape.height / 2.0},
      {newShape.pos.x - newShape.width / 2.0, newShape.pos.y - newShape.height / 2.0},
      {newShape.pos.x + newShape.width / 2.0, newShape.pos.y - newShape.height / 2.0}
    };
  point_t currPoints[4] = 
    {
      {currShape.pos.x - currShape.width / 2.0, currShape.pos.y + currShape.height / 2.0},
      {currShape.pos.x + currShape.width / 2.0, currShape.pos.y + currShape.height / 2.0},
      {currShape.pos.x - currShape.width / 2.0, currShape.pos.y - currShape.height / 2.0},
      {currShape.pos.x + currShape.width / 2.0, currShape.pos.y - currShape.height / 2.0}
    };
  for (int i = 0; i < 4; ++i)
  {
    if (((newPoints[i].x >= currPoints[0].x) && (newPoints[i].x <= currPoints[2].x)
         && (newPoints[i].y >= currPoints[3].y) && (newPoints[i].y <= currPoints[1].y))
        || ((currPoints[i].x >= newPoints[0].x) && (currPoints[i].x <= newPoints[2].x)
            && (currPoints[i].y >= newPoints[3].y) && (currPoints[i].y <= newPoints[1].y)))
    {
      return true;
    }
  }
  return false;
}

int Matrix::getLayerSize() noexcept
{
  return sizeLayer_;
}

int Matrix::getShapeSize() noexcept
{
  return sizeShape_;
}
