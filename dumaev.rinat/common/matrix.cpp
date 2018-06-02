#include "matrix.hpp"
#include <memory>
#include <stdexcept>

using namespace dumaev;

Matrix::Matrix(const std::shared_ptr<Shape> shape):
  shapes_(nullptr),
  layersNumber_(0),
  layerSize_(0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid shape");
  }
  addShape(shape);
}

Matrix::Matrix(const Matrix &matrix):
  shapes_(new std::shared_ptr< Shape > [matrix.layerSize_ * matrix.layersNumber_]),
  layersNumber_(matrix.layersNumber_),
  layerSize_(matrix.layerSize_)
{
  for (int i = 0; i < layersNumber_ * layerSize_; ++i)
  {
    shapes_[i] = matrix.shapes_[i];
  }
}

Matrix::Matrix(Matrix &&matrix):
  shapes_(nullptr),
  layersNumber_(matrix.layersNumber_),
  layerSize_(matrix.layerSize_)
{
  shapes_.swap(matrix.shapes_);
  matrix.layerSize_ = 0;
  matrix.layersNumber_ = 0;
}

Matrix& Matrix::operator=(const Matrix &matrix)
{
  if (this != &matrix)
  {
    layersNumber_ = matrix.layersNumber_;
    layerSize_ = matrix.layerSize_;
    std::unique_ptr< std::shared_ptr< Shape >[] > newShapes(new std::shared_ptr< Shape >[layerSize_ * layersNumber_]);
    for (int i = 0; i < layersNumber_ * layerSize_; ++i)
    {
      newShapes[i] = matrix.shapes_[i];
    }
    shapes_.swap(newShapes);
  }
  return *this;
}

Matrix& Matrix::operator=(Matrix &&matrix)
{
  if (this != &matrix)
  {
    layersNumber_ = matrix.layersNumber_;
    layerSize_ = matrix.layerSize_;
    shapes_.reset();
    shapes_.swap(matrix.shapes_);
    matrix.layersNumber_ = 0;
    matrix.layerSize_ = 0;
  }
  return *this;
}

bool Matrix::operator==(const Matrix &rhs) const
{
  if ((this->layersNumber_ == rhs.layersNumber_) && (this->layerSize_ == rhs.layerSize_))
  {
    bool equality = true;
    for (int i = 0; i < layerSize_ * layersNumber_; ++i)
    {
      if (!(this->shapes_[i] == rhs.shapes_[i]))
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

bool Matrix::operator!=(const Matrix &rhs) const
{
  if ((this->layersNumber_ != rhs.layersNumber_) || (this->layerSize_ != rhs.layerSize_))
  {
    return true;
  }
  else
  {
    bool nonequality = false;
    for (int i = 0; i < layerSize_ * layersNumber_; ++i)
    {
      if (this->shapes_[i] != rhs.shapes_[i])
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

std::unique_ptr< std::shared_ptr< Shape >[] > Matrix::operator[](const int layerIndex) const
{
  if ((layerIndex < 0) || (layerIndex >= layersNumber_))
  {
    throw std::out_of_range("Invalid layer index");
  }
  std::unique_ptr< std::shared_ptr< Shape >[] > layer(new std::shared_ptr< Shape >[layerSize_]);
  for (int i = 0; i < layerSize_; ++i)
  {
    layer[i] = shapes_[layerIndex * layerSize_ + i];
  }
  return layer;
}

void Matrix::addShape(const std::shared_ptr<Shape> shape) noexcept
{
  if (layersNumber_ == 0)
  {
    ++layerSize_;
    ++layersNumber_;
    std::unique_ptr< std::shared_ptr< Shape >[] > newShapes(new std::shared_ptr< Shape >[layersNumber_ * layerSize_]);
    shapes_.swap(newShapes);
    shapes_[0] = shape;
  }
  else
  {
    bool addedShape = false;
    for (int i = 0; !addedShape; ++i)
    {
      for (int j = 0; j < layerSize_; ++j)
      {
        if (!shapes_[i * layerSize_ + j])
        {
          shapes_[i * layerSize_ + j] = shape;
          addedShape = true;
          break;
        }
        else
        {
          if (checkOverlapping(i * layerSize_ + j, shape))
          {
            break;
          }
        }

        if (j == (layerSize_ - 1))
        {
          layerSize_++;
          std::unique_ptr< std::shared_ptr< Shape >[] > newShapes(new std::shared_ptr< Shape >[layersNumber_ * layerSize_]);
          for (int n = 0; n < layersNumber_; ++n)
          {
            for (int m = 0; m < layerSize_ - 1; ++m)
            {
              newShapes[n * layerSize_ + m] = shapes_[n * (layerSize_ - 1) + m];
            }
            newShapes[(n + 1) * layerSize_ - 1] = nullptr;
          }
          newShapes[(i + 1) * layerSize_ - 1] = shape;
          shapes_.swap(newShapes);
          addedShape = true;
          break;
        }
      }
      if ((i == (layersNumber_ - 1)) && !addedShape)
      {
        layersNumber_++;
        std::unique_ptr< std::shared_ptr< Shape >[] > newShapes(
                new std::shared_ptr< Shape >[layersNumber_ * layerSize_]);
        for (int n = 0; n < ((layersNumber_ - 1) * layerSize_); ++n)
        {
          newShapes[n] = shapes_[n];
        }
        for (int n = ((layersNumber_  - 1) * layerSize_) ; n < (layersNumber_ * layerSize_); ++n)
        {
          newShapes[n] = nullptr;
        }
        newShapes[(layersNumber_ - 1 ) * layerSize_ ] = shape;
        shapes_.swap(newShapes);
        addedShape = true;
      }
    }
  }
}

bool Matrix::checkOverlapping(const int index, std::shared_ptr< Shape > shape) const noexcept
{
  rectangle_t nShapeFrameRect = shape->getFrameRect();
  rectangle_t mShapeFrameRect = shapes_[index]->getFrameRect();
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
