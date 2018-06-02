#include "matrix.hpp"

#include <memory>
#include <stdexcept>

suslov::Matrix::Matrix(const std::shared_ptr< suslov::Shape > shape):
  matrixShapes_(nullptr),
  layersNumber_(0),
  layerSize_(0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Null pointer");
  }
  addShape(shape);
}

suslov::Matrix::Matrix(const suslov::Matrix & matrix):
  matrixShapes_(new std::shared_ptr< suslov::Shape >[matrix.layersNumber_ * matrix.layerSize_]),
  layersNumber_(matrix.layersNumber_),
  layerSize_(matrix.layerSize_)
{
  for (int i = 0; i < layersNumber_ * layerSize_; ++i)
  {
    matrixShapes_[i] = matrix.matrixShapes_[i];
  }
}

suslov::Matrix::Matrix(suslov::Matrix && matrix):
  matrixShapes_(nullptr),
  layersNumber_(matrix.layersNumber_),
  layerSize_(matrix.layerSize_)
{
  matrixShapes_.swap(matrix.matrixShapes_);
  matrix.layersNumber_ = 0;
  matrix.layerSize_ = 0;
}

suslov::Matrix::~Matrix()
{
  matrixShapes_.reset();
  matrixShapes_ = nullptr;
  layersNumber_ = 0;
  layerSize_ = 0;
}

suslov::Matrix & suslov::Matrix::operator=(const suslov::Matrix & matrix)
{
  if (this != & matrix)
  {
    layersNumber_ = matrix.layersNumber_;
    layerSize_ = matrix.layerSize_;
    std::unique_ptr < std::shared_ptr < suslov::Shape > [] > 
      newMatrixShapes(new std::shared_ptr < suslov::Shape > [layersNumber_ * layerSize_]);
    for (int i = 0; i < layersNumber_ * layerSize_; ++i)
    {
      newMatrixShapes[i] = matrix.matrixShapes_[i];
    }
    matrixShapes_.swap(newMatrixShapes);
  }
  return *this;
}

suslov::Matrix & suslov::Matrix::operator=(suslov::Matrix && matrix)
{
  if (this != & matrix)
  {
    layersNumber_ = matrix.layersNumber_;
    layerSize_ = matrix.layerSize_;
    matrixShapes_.reset();
    matrixShapes_.swap(matrix.matrixShapes_);
    matrix.layersNumber_ = 0;
    matrix.layerSize_ = 0;
  }
  return *this;
}

bool suslov::Matrix::operator==(const suslov::Matrix & matrix) const
{
  if ((this->layersNumber_ != matrix.layersNumber_) || (this->layerSize_ != matrix.layerSize_))
  {
    return false;
  }
  for (int i = 0; i < layersNumber_ * layerSize_; ++i)
    {
      if (this->matrixShapes_[i] != matrix.matrixShapes_[i])
      {
        return false;
      }
    }
  return true;
}

bool suslov::Matrix::operator!=(const Matrix & matrix) const
{
  if ((this->layersNumber_ != matrix.layersNumber_) || (this->layerSize_ != matrix.layerSize_))
  {
    return true;
  }
    for (int i = 0; i < layersNumber_ * layerSize_; ++i)
    {
      if (this->matrixShapes_[i] != matrix.matrixShapes_[i])
      {
        return true;
      }
    }
  return false;
}

std::unique_ptr < std::shared_ptr < suslov::Shape > [] > suslov::Matrix::operator[](const int layerNumber) const
{
  if ((layerNumber < 0) || (layerNumber >= layersNumber_))
  {
    throw std::out_of_range("invalid layer index");
  }
  std::unique_ptr < std::shared_ptr < suslov::Shape > [] > 
    layer(new std::shared_ptr < suslov::Shape > [layerSize_]);
  for (int i = 0; i < layerSize_; ++i)
  {
    layer[i] = matrixShapes_[layerNumber * layerSize_ + i];
  }
  return layer;
}

void suslov::Matrix::addShape(const std::shared_ptr< suslov::Shape > shape) noexcept
{
  if (layersNumber_ == 0)
  {
    ++layersNumber_;
    ++layerSize_;
    std::unique_ptr < std::shared_ptr < suslov::Shape >[] > 
      newMatrixShapes(new std::shared_ptr < suslov::Shape > [layersNumber_ * layerSize_]);
    matrixShapes_.swap(newMatrixShapes);
    matrixShapes_[0] = shape;
  }
  else
  {
    bool addedShape = false;
    for (int i = 0; !addedShape ; ++i)
    {
      for (int j = 0; j < layerSize_; ++j)
      {
        if (!matrixShapes_[i * layerSize_ + j])
        {
          matrixShapes_[i * layerSize_ + j] = shape;
          addedShape = true;
          break;
        }
        else
        {
          if (checkForOvelap(i * layerSize_ + j, shape))
          {
            break;
          }
        }

        if (j == (layerSize_ - 1))
        {
          layerSize_++;
          std::unique_ptr < std::shared_ptr < suslov::Shape > [] > 
            newMatrixShapes(new std::shared_ptr < suslov::Shape > [layersNumber_ * layerSize_]);
          for (int n = 0; n < layersNumber_; ++n)
          {
            for (int m = 0; m < layerSize_ - 1; ++m)
            {
              newMatrixShapes[n * layerSize_ + m] = matrixShapes_[n * (layerSize_ - 1) + m];
            }
            newMatrixShapes[(n + 1) * layerSize_ - 1] = nullptr;
          }
          newMatrixShapes[(i + 1) * layerSize_ - 1] = shape;
          matrixShapes_.swap(newMatrixShapes);
          addedShape = true;
          break;
        }
      }
      if ((i == (layersNumber_ - 1)) && !addedShape)
      {
        layersNumber_++;
        std::unique_ptr < std::shared_ptr < suslov::Shape > [] > 
          newMatrixShapes(new std::shared_ptr< suslov::Shape >[layersNumber_ * layerSize_]);
        for (int n = 0; n < ((layersNumber_ - 1) * layerSize_); ++n)
        {
          newMatrixShapes[n] = matrixShapes_[n];
        }
        for (int n = ((layersNumber_  - 1) * layerSize_) ; n < (layersNumber_ * layerSize_); ++n)
        {
          newMatrixShapes[n] = nullptr;
        }
        newMatrixShapes[(layersNumber_ - 1 ) * layerSize_] = shape;
        matrixShapes_.swap(newMatrixShapes);
        addedShape = true;
      }
    }
  }
}

bool suslov::Matrix::checkForOvelap(const int index, std::shared_ptr < suslov::Shape > shape) const noexcept
{
  suslov::rectangle_t nShapeFrameRect = shape->getFrameRect();
  suslov::rectangle_t mShapeFrameRect = matrixShapes_[index]->getFrameRect();
  suslov::point_t newShapePoints[4] = {
    {nShapeFrameRect.pos.x - nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y + nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x + nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y + nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x + nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y - nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x - nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y - nShapeFrameRect.height / 2.0}
  };

  suslov::point_t matrixShapePoints[4] = {
    {mShapeFrameRect.pos.x - mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y + mShapeFrameRect.height / 2.0},
    {mShapeFrameRect.pos.x + mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y + mShapeFrameRect.height / 2.0},
    {mShapeFrameRect.pos.x + mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y - mShapeFrameRect.height / 2.0},
    {mShapeFrameRect.pos.x - mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y - mShapeFrameRect.height / 2.0}
  };

  for (int i = 0; i < 4; ++i)
  {
    if (((newShapePoints[i].x >= matrixShapePoints[0].x) && (newShapePoints[i].x <= matrixShapePoints[2].x)
      && (newShapePoints[i].y >= matrixShapePoints[3].y) && (newShapePoints[i].y <= matrixShapePoints[1].y)) 
        || ((matrixShapePoints[i].x >= newShapePoints[0].x) && (matrixShapePoints[i].x <= newShapePoints[2].x)
          && (matrixShapePoints[i].y >= newShapePoints[3].y) && (matrixShapePoints[i].y <= newShapePoints[1].y)))
    {
      return true;
    }
  }
  return false;
}
