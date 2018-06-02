#include "matrix.hpp"

#include <memory>
#include <stdexcept>

using namespace krasilnikov;

Matrix::Matrix(const std::shared_ptr<Shape> shape):
  list_(nullptr),
  layersNumber_(0),
  layerCount_(0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  addShape(shape);
}

Matrix::Matrix(const Matrix & matrix):
  list_(new std::shared_ptr<Shape>[matrix.layersNumber_ * matrix.layerCount_]),
  layersNumber_(matrix.layersNumber_),
  layerCount_(matrix.layerCount_)
{
  for (int i = 0; i < layersNumber_ * layerCount_; ++i)
  {
    list_[i] = matrix.list_[i];
  }
}

Matrix::Matrix(Matrix && matrix):
  list_(nullptr),
  layersNumber_(matrix.layersNumber_),
  layerCount_(matrix.layerCount_)
{
  list_.swap(matrix.list_);
  matrix.layerCount_ = 0;
  matrix.layersNumber_ = 0;
}

Matrix::~Matrix()
{
  list_.reset();
  list_ = nullptr;
  layerCount_ = 0;
  layersNumber_ = 0;
}

Matrix & Matrix::operator=(const Matrix & matrix)
{
  if (this != & matrix)
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> temp(
      new std::shared_ptr<Shape>[matrix.layersNumber_ * matrix.layerCount_]);
    layersNumber_ = matrix.layersNumber_;
    layerCount_ = matrix.layerCount_;
    for (int i = 0; i < layersNumber_ * layerCount_; ++i)
    {
      temp[i] = matrix.list_[i];
    }
    list_.swap(temp);
  }
  return *this;
}

Matrix & Matrix::operator=(Matrix && matrix)
{
  if (this != & matrix)
  {
    layersNumber_ = matrix.layersNumber_;
    layerCount_ = matrix.layerCount_;
    list_.reset();
    list_.swap(matrix.list_);
    matrix.layersNumber_ = 0;
    matrix.layerCount_ = 0;
  }
  return *this;
}

bool Matrix::operator==(const Matrix & rhs) const
{
  if ((layersNumber_ == rhs.layersNumber_) && (layerCount_ == rhs.layerCount_))
  {
    bool equality = true;
    for (int i = 0; i < layersNumber_ * layerCount_; ++i)
    {
      if (!(list_[i] == rhs.list_[i]))
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

bool Matrix::operator!=(const Matrix & rhs) const
{
  if ((layersNumber_ != rhs.layersNumber_) || (layerCount_ != rhs.layerCount_))
  {
    return true;
  }
  else
  {
    bool nonequality = false;
    for (int i = 0; i < layersNumber_ * layerCount_; ++i)
    {
      if (list_[i] != rhs.list_[i])
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


std::unique_ptr<std::shared_ptr<Shape>[]> Matrix::operator[](const int index) const
{
  if ((index < 0) || (index >= layersNumber_))
  {
    throw std::out_of_range("Invalid index");
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> layer(new std::shared_ptr<Shape>[layerCount_]);
  for (int i = 0; i < layerCount_; ++i)
  {
    layer[i] = list_[index * layerCount_ + i];
  }
  return layer;
}

void Matrix::addShape(const std::shared_ptr<Shape> shape)
{
  if (layersNumber_ == 0)
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> temp(new std::shared_ptr<Shape>[(layersNumber_ + 1) * (layerCount_ + 1)]);
    layerCount_++;
    layersNumber_++;
    list_.swap(temp);
    list_[0] = shape;
  }
  else
  {
    bool addedShape = false;
    for (int i = 0; !addedShape ; ++i)
    {
      for (int j = 0; j < layerCount_; ++j)
      {
        if (!list_[i * layerCount_ + j])
        {
          list_[i * layerCount_ + j] = shape;
          addedShape = true;
          break;
        }
        else
        {
          if (checkOverLapping(i * layerCount_ + j, shape))
          {
            break;
          }
        }

        if (j == (layerCount_ - 1))
        {
          std::unique_ptr<std::shared_ptr<Shape>[]> temp(
            new std::shared_ptr<Shape>[layersNumber_ * (layerCount_ + 1)]);
          layerCount_++;
          for (int n = 0; n < layersNumber_; ++n)
          {
            for (int m = 0; m < layerCount_ - 1; ++m)
            {
              temp[n * layerCount_ + m] = list_[n * (layerCount_ - 1) + m];
            }
            temp[(n + 1) * layerCount_ - 1] = nullptr;
          }
          temp[(i + 1) * layerCount_ - 1] = shape;
          list_.swap(temp);
          addedShape = true;
          break;
        }
      }
      if ((i == (layersNumber_ - 1)) && !addedShape)
      {
        std::unique_ptr<std::shared_ptr<Shape>[]> temp(
          new std::shared_ptr<Shape>[(layersNumber_ + 1) * layerCount_]);
        layersNumber_++;
        for (int n = 0; n < ((layersNumber_ - 1) * layerCount_); ++n)
        {
          temp[n] = list_[n];
        }
        for (int n = ((layersNumber_ - 1) * layerCount_) ; n < (layersNumber_ * layerCount_); ++n)
        {
          temp[n] = nullptr;
        }
        temp[(layersNumber_ - 1) * layerCount_ ] = shape;
        list_.swap(temp);
        addedShape = true;
      }
    }
  }
}

bool Matrix::checkOverLapping(const int index, std::shared_ptr<Shape> shape) const
{
  rectangle_t nShapeFrameRect = shape->getFrameRect();
  rectangle_t mShapeFrameRect = list_[index]->getFrameRect();
  point_t newPoints[4] = {
    {nShapeFrameRect.pos.x - nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y + nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x + nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y + nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x + nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y - nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x - nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y - nShapeFrameRect.height / 2.0}
  };

  point_t matrixPoints[4] = {
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
