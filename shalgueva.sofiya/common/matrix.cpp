#include "matrix.hpp"

#include <memory>
#include <stdexcept>

shalgueva::Matrix::Matrix(const std::shared_ptr<shalgueva::Shape> object):
  matrix_(nullptr),
  numberOfLayers_(0),
  numberOfShapes_(0)
{
  if (object == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  addShape(object);
}

shalgueva::Matrix::Matrix(const shalgueva::Matrix & object):
  matrix_(new std::shared_ptr<Shape>[object.numberOfLayers_ * object.numberOfShapes_]),
  numberOfLayers_(object.numberOfLayers_),
  numberOfShapes_(object.numberOfShapes_)
{
  for (int i = 0; i < numberOfLayers_ * numberOfShapes_; ++i)
  {
    matrix_[i] = object.matrix_[i];
  }
}

shalgueva::Matrix::Matrix(shalgueva::Matrix && object):
  matrix_(nullptr),
  numberOfLayers_(object.numberOfLayers_),
  numberOfShapes_(object.numberOfShapes_)
{
  matrix_.swap(object.matrix_);
  object.numberOfShapes_ = 0;
  object.numberOfLayers_ = 0;
}

shalgueva::Matrix::~Matrix()
{
  matrix_.reset();
  matrix_ = nullptr;
  numberOfShapes_ = 0;
  numberOfLayers_ = 0;
}

shalgueva::Matrix & shalgueva::Matrix::operator=(const shalgueva::Matrix & object)
{
  if (this != & object)
  {
    std::unique_ptr<std::shared_ptr<shalgueva::Shape>[]> newMatrix(
      new std::shared_ptr<shalgueva::Shape>[object.numberOfLayers_ * object.numberOfShapes_]);
    numberOfLayers_ = object.numberOfLayers_;
    numberOfShapes_ = object.numberOfShapes_;
    for (int i = 0; i < numberOfLayers_ * numberOfShapes_; ++i)
    {
      newMatrix[i] = object.matrix_[i];
    }
    matrix_.swap(newMatrix);
  }
  return *this;
}

bool shalgueva::Matrix::operator== (const Matrix & object) const
{
  if ((numberOfLayers_ == object.numberOfLayers_) && (numberOfShapes_ == object.numberOfShapes_))
  {
    bool equality = true;
    for (int i = 0; i < numberOfLayers_ * numberOfShapes_; ++i)
    {
      if (!(matrix_[i] == object.matrix_[i]))
      {
        equality = false;
      }
    }
    if (equality)
    {
      return true;
    }
  }
  return false;
}

bool shalgueva::Matrix::operator!= (const Matrix & object) const
{
  if ((numberOfLayers_ != object.numberOfLayers_) || (numberOfShapes_ != object.numberOfShapes_))
  {
    return true;
  }
  else
  {
    bool nonequality = false;
    for (int i = 0; i < numberOfLayers_ * numberOfShapes_; ++i)
    {
      if (matrix_[i] != object.matrix_[i])
      {
        nonequality = true;
        break;
      }
    }
    if (nonequality)
    {
      return true;
    }
  }
  return false;
}

shalgueva::Matrix & shalgueva::Matrix::operator=(shalgueva::Matrix && object)
{
  if (this != & object)
  {
    numberOfLayers_ = object.numberOfLayers_;
    numberOfShapes_ = object.numberOfShapes_;
    matrix_.reset();
    matrix_.swap(object.matrix_);
    object.numberOfLayers_ = 0;
    object.numberOfShapes_ = 0;
  }
  return *this;
}

std::unique_ptr<std::shared_ptr<shalgueva::Shape>[]> shalgueva::Matrix::operator[](const int index) const
{
  if ((index < 0) || (index >= numberOfLayers_))
  {
    throw std::out_of_range("Invalid index");
  }
  std::unique_ptr<std::shared_ptr<shalgueva::Shape>[]> layer(
    new std::shared_ptr<shalgueva::Shape>[numberOfShapes_]);
  for (int i = 0; i < numberOfShapes_; ++i)
  {
    layer[i] = matrix_[index * numberOfShapes_ + i];
  }
  return layer;
}

size_t shalgueva::Matrix::getLayersNumber() const noexcept
{
  return numberOfLayers_;
}

void shalgueva::Matrix::addShape(const std::shared_ptr<shalgueva::Shape> object) noexcept
{
  if (numberOfLayers_ == 0)
  {
    std::unique_ptr<std::shared_ptr<shalgueva::Shape>[]> newMatrix(
      new std::shared_ptr<shalgueva::Shape>[(numberOfLayers_ + 1) * (numberOfShapes_ + 1)]);
    numberOfShapes_++;
    numberOfLayers_++;
    matrix_.swap(newMatrix);
    matrix_[0] = object;
  }
  else
  {
    bool addedShape = false;
    for (int i = 0; !addedShape ; ++i)
    {
      for (int j = 0; j < numberOfShapes_; ++j)
      {
        if (!matrix_[i * numberOfShapes_ + j])
        {
          matrix_[i * numberOfShapes_ + j] = object;
          addedShape = true;
          break;
        }
        else
        {
          if (checkIntersection(i * numberOfShapes_ + j, object))
          {
            break;
          }
        }

        if (j == (numberOfShapes_ - 1))
        {
          std::unique_ptr<std::shared_ptr<shalgueva::Shape>[]> newMatrix(
            new std::shared_ptr<shalgueva::Shape>[numberOfLayers_ * (numberOfShapes_ + 1)]);
          numberOfShapes_++;
          for (int n = 0; n < numberOfLayers_; ++n)
          {
            for (int m = 0; m < numberOfShapes_ - 1; ++m)
            {
              newMatrix[n * numberOfShapes_ + m] = matrix_[n * (numberOfShapes_ - 1) + m];
            }
            newMatrix[(n + 1) * numberOfShapes_ - 1] = nullptr;
          }
          newMatrix[(i + 1) * numberOfShapes_ - 1] = object;
          matrix_.swap(newMatrix);
          addedShape = true;
          break;
        }
      }
      if ((i == (numberOfLayers_ - 1)) && !addedShape)
      {
        std::unique_ptr<std::shared_ptr<shalgueva::Shape>[]> newMatrix(
          new std::shared_ptr<shalgueva::Shape>[(numberOfLayers_ + 1) * numberOfShapes_]);
        numberOfLayers_++;
        for (int n = 0; n < ((numberOfLayers_ - 1) * numberOfShapes_); ++n)
        {
          newMatrix[n] = matrix_[n];
        }
        for (int n = ((numberOfLayers_ - 1) * numberOfShapes_) ; n < (numberOfLayers_ * numberOfShapes_); ++n)
        {
          newMatrix[n] = nullptr;
        }
        newMatrix[(numberOfLayers_ - 1) * numberOfShapes_ ] = object;
        matrix_.swap(newMatrix);
        addedShape = true;
      }
    }
  }
}

bool shalgueva::Matrix::checkIntersection(const int index,
  std::shared_ptr<shalgueva::Shape> object) const noexcept
{
  shalgueva::rectangle_t nShapeFrameRect = object->getFrameRect();
  shalgueva::rectangle_t mShapeFrameRect = matrix_[index]->getFrameRect();
  shalgueva::point_t newPoints[4] = 
  {
    {nShapeFrameRect.pos.x - nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y + nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x + nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y + nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x + nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y - nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x - nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y - nShapeFrameRect.height / 2.0}
  };

  shalgueva::point_t matrixPoints[4] = 
  {
    {mShapeFrameRect.pos.x - mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y + mShapeFrameRect.height / 2.0},
    {mShapeFrameRect.pos.x + mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y + mShapeFrameRect.height / 2.0},
    {mShapeFrameRect.pos.x + mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y - mShapeFrameRect.height / 2.0},
    {mShapeFrameRect.pos.x - mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y - mShapeFrameRect.height / 2.0}
  };

  for (int i = 0; i < 4; ++i)
  {
    if (((newPoints[i].x >= matrixPoints[0].x) && (newPoints[i].x <= matrixPoints[2].x)
        && (newPoints[i].y >= matrixPoints[3].y) && (newPoints[i].y <= matrixPoints[1].y))
            || ((matrixPoints[i].x >= newPoints[0].x) && (matrixPoints[i].x <= newPoints[2].x)
                && (matrixPoints[i].y >= newPoints[3].y) && (matrixPoints[i].y <= newPoints[1].y)))
    {
      return true;
    }
  }
  return false;
}
