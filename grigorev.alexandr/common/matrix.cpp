#include "matrix.hpp"
#include <memory>
#include <stdexcept>

grigorev::Matrix::Matrix(const std::shared_ptr< grigorev::Shape > shape):
  list_(nullptr),
  layersCount_(0),
  layerSize_(0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid pointeer");
  }
  addShape(shape);
}

grigorev::Matrix::Matrix(const grigorev::Matrix & matrix):
  list_(new std::shared_ptr< grigorev::Shape >[matrix.layersCount_ * matrix.layerSize_]),
  layersCount_(matrix.layersCount_),
  layerSize_(matrix.layerSize_)
{
  for (int i = 0; i < layersCount_ * layerSize_; ++i)
  {
    list_[i] = matrix.list_[i];
  }
}

grigorev::Matrix::Matrix(grigorev::Matrix && matrix):
  list_(nullptr),
  layersCount_(matrix.layersCount_),
  layerSize_(matrix.layerSize_)
{
  list_.swap(matrix.list_);
  matrix.layersCount_ = 0;
  matrix.layerSize_ = 0;
}

grigorev::Matrix & grigorev::Matrix::operator = (const grigorev::Matrix & matrix)
{
  if (this != & matrix)
  {
  layersCount_ = matrix.layersCount_;
    layerSize_ = matrix.layerSize_;
    std::unique_ptr< std::shared_ptr< grigorev::Shape >[] > newList(
      new std::shared_ptr< grigorev::Shape >[layersCount_ * layerSize_]);
    for (int i = 0; i < layersCount_ * layerSize_; ++i)
    {
      newList[i] = matrix.list_[i];
    }
    list_.swap(newList);
  }
  return *this;
}

grigorev::Matrix & grigorev::Matrix::operator = (grigorev::Matrix && matrix)
{
  if (this != & matrix)
  {
    layerSize_ = matrix.layerSize_;
    layersCount_ = matrix.layersCount_;
    list_.swap(matrix.list_);
    matrix.list_ = nullptr;
    matrix.layersCount_ = 0;
    matrix.layerSize_ = 0;
  }
  return *this;
}

std::unique_ptr< std::shared_ptr< grigorev::Shape >[] > grigorev::Matrix::operator[](const int layerIndex) const
{
  if ((layerIndex >= layersCount_) || (layerIndex < 0))
  {
    throw std::invalid_argument("Invalid index");
  }
  std::unique_ptr< std::shared_ptr< grigorev::Shape >[] > layer(
    new std::shared_ptr< grigorev::Shape >[layerSize_]);
  for (int i = 0; i < layerSize_; ++i)
  {
    layer[i] = list_[layerIndex * layerSize_ + i];
  }
  return layer;
}

void grigorev::Matrix::addShape(const std::shared_ptr< grigorev::Shape > shape)
{
  if (layersCount_ == 0)
  {
    ++layerSize_;
    ++layersCount_;
    std::unique_ptr< std::shared_ptr<grigorev::Shape >[] > newList(
      new std::shared_ptr< grigorev::Shape >[layersCount_ * layerSize_]);
    list_.swap(newList);
    list_[0] = shape;
  }
  else
  {
    bool addedShape = false;
    for (int i = 0; !addedShape ; ++i)
    {
      for (int j = 0; j < layerSize_; ++j)
      {
        if (list_[i * layerSize_ + j] == nullptr)
        {
          list_[i * layerSize_ + j] = shape;
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
          std::unique_ptr< std::shared_ptr< grigorev::Shape >[] > newList(
            new std::shared_ptr< grigorev::Shape >[layersCount_ * layerSize_]);
          for (int n = 0; n < layersCount_; ++n)
          {
            for (int m = 0; m < layerSize_ - 1; ++m)
            {
              newList[n * layerSize_ + m] = list_[n * (layerSize_ - 1) + m];
            }
            newList[(n + 1) * layerSize_ - 1] = nullptr;
          }
          newList[(i + 1) * layerSize_ - 1] = shape;
          list_.swap(newList);
          addedShape = true;
          break;
        }
      }
      if ((i == (layersCount_ - 1)) && !addedShape)
      {
        layersCount_++;
        std::unique_ptr< std::shared_ptr< grigorev::Shape >[] > newList(
          new std::shared_ptr< grigorev::Shape >[layersCount_ * layerSize_]);
        for (int n = 0; n < ((layersCount_ - 1) * layerSize_); ++n)
        {
          newList[n] = list_[n];
        }
        for (int n = ((layersCount_  - 1) * layerSize_) ; n < (layersCount_ * layerSize_); ++n)
        {
          newList[n] = nullptr;
        }
        newList[(layersCount_ - 1 ) * layerSize_ ] = shape;
        list_.swap(newList);
        addedShape = true;
      }
    }
  }
}

bool grigorev::Matrix::checkOverlapping(const int index, std::shared_ptr<Shape> shape) const
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

