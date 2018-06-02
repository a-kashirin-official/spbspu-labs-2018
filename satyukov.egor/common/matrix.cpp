#include "matrix.hpp"

#include <memory>
#include <stdexcept>
#include <iostream>

satyukov::Matrix::Matrix(const std::shared_ptr < satyukov::Shape > newShape):
  list_(nullptr),
  layersNumber_(0),
  layerSize_(0)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Null pointer");
  }
  addShape(newShape);
}

satyukov::Matrix::Matrix(const satyukov::Matrix & matrix):
  list_(new std::shared_ptr < satyukov::Shape >[matrix.layersNumber_ * matrix.layerSize_]),
  layersNumber_(matrix.layersNumber_),
  layerSize_(matrix.layerSize_)
{
  for (int i = 0; i < matrix.layersNumber_ * matrix.layerSize_; ++i)
  {
    list_[i] = matrix.list_[i];
  }
}

satyukov::Matrix::Matrix(satyukov::Matrix && matrix):
  list_(nullptr),
  layersNumber_(matrix.layersNumber_),
  layerSize_(matrix.layerSize_)
{
  list_.swap(matrix.list_);
  matrix.layersNumber_ = 0;
  matrix.layerSize_ = 0;
}

satyukov::Matrix::~Matrix()
{
  list_.reset();
  list_ = nullptr;
  layersNumber_ = 0;
  layerSize_ = 0;
}

satyukov::Matrix & satyukov::Matrix::operator =(const satyukov::Matrix & matrix)
{
  if (this != & matrix)
  {
    layersNumber_ = matrix.layersNumber_;
    layerSize_ = matrix.layerSize_;
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > 
        newList (new std::shared_ptr < satyukov::Shape >[matrix.layersNumber_ * matrix.layerSize_]);
    for (int i = 0; i < matrix.layersNumber_ * matrix.layerSize_; ++i)
    {
      newList[i] = matrix.list_[i];
    }
    list_.swap(newList);
  }
  return *this;
}

satyukov::Matrix & satyukov::Matrix::operator =(satyukov::Matrix && matrix)
{
  if (this != & matrix)
  {
    layersNumber_ = matrix.layersNumber_;
    layerSize_ = matrix.layerSize_;
    list_.reset();
    list_.swap(matrix.list_);
    matrix.layersNumber_ = 0;
    matrix.layerSize_ = 0;
  }
  return *this;
}

bool satyukov::Matrix::operator ==(const satyukov::Matrix & matrix) const
{
  if ((this->layersNumber_ != matrix.layersNumber_) || (this->layerSize_ != matrix.layerSize_))
  {
    return false;
  }
  for (int i = 0; i < layersNumber_ * layerSize_; ++i)
    {
      if (this->list_[i] != matrix.list_[i])
      {
        return false;
      }
    }
  return true;
}

bool satyukov::Matrix::operator !=(const satyukov::Matrix & matrix) const
{
  if ((this->layersNumber_ != matrix.layersNumber_) || (this->layerSize_ != matrix.layerSize_))
  {
    return true;
  }
  for (int i = 0; i < layersNumber_ * layerSize_; ++i)
    {
      if (this->list_[i] != matrix.list_[i])
      {
        return true;
      }
    }
  return false;
}

std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > satyukov::Matrix::operator [](const int layerIndex) const
{
  if (layersNumber_ == 0)
  {
    throw std::out_of_range("Matrix is empty");
  }
  if ((layerIndex < 0) || (layerIndex > layersNumber_ - 1))
  {
    throw std::invalid_argument("Invalid layer index");
  }
  std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > 
      layer (new std::shared_ptr < satyukov::Shape >[layerSize_]);
  for (int i = 0; i < layerSize_; ++i)
  {
    layer[i] = list_[layerIndex * layerSize_ + i];
  }
  return layer;
}

int satyukov::Matrix::getLayersNumber() const noexcept
{
  return layersNumber_;
}
int satyukov::Matrix::getLayerSize() const noexcept
{
  return layerSize_;
}

void satyukov::Matrix::addShape(const std::shared_ptr < satyukov::Shape > newShape)
{
  if (layersNumber_ == 0)
  {
    ++layersNumber_;
    ++layerSize_;
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > 
        newList (new std::shared_ptr < satyukov::Shape >[layersNumber_ * layerSize_]);
    list_.swap(newList);
    list_[0] = newShape;
  }
  else
  {
    bool addedShape = false;
    for (int i = 0; !addedShape; ++i)
    {
      for (int j = 0; j < layerSize_; ++j)
      {
        if (list_[i * layerSize_ + j] == nullptr)
        {
          list_[i * layerSize_ + j] = newShape;
          addedShape = true;
          break;
        }
        else
        {
          if (checkOverlapping(i * layerSize_ + j, newShape))
          {
            break;
          }
        }
        if (j == (layerSize_ - 1))
        {
          ++layerSize_;
          std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > 
              newList (new std::shared_ptr < satyukov::Shape >[layersNumber_ * layerSize_]);
          for (int n = 0; n < layersNumber_; ++n)
          {
            for (int m = 0; m < layerSize_ - 1; ++m)
            {
              newList[n * layerSize_ + m] = list_[n * (layerSize_ - 1) + m];
            }
            newList[(n + 1) * layerSize_ - 1] = nullptr;
          }
          newList[(i + 1) * layerSize_ - 1] = newShape;
          list_.swap(newList);
          addedShape = true;
          break;
        }
      }
      if ((i == (layersNumber_ - 1)) && !(addedShape))
      {
        ++layersNumber_;
        std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > 
            newList (new std::shared_ptr < satyukov::Shape >[layersNumber_ * layerSize_]);
        for (int n = 0; n < (layersNumber_ - 1) * layerSize_; ++n)
        {
          newList[n] = list_[n];
        }
        for (int n = (layersNumber_ - 1) * layerSize_; n < layersNumber_ * layerSize_; ++n)
        {
          newList[n] = nullptr;
        }
        newList[(layersNumber_ - 1) * layerSize_] = newShape;
        list_.swap(newList);
        addedShape = true;
      }
    }
  }
}

bool satyukov::Matrix::checkOverlapping(const int index, 
    std::shared_ptr < satyukov::Shape > newShape) const noexcept
{
  satyukov::rectangle_t newShapeFrameRect = newShape->getFrameRect();
  satyukov::rectangle_t matrixShapeFrameRect = list_[index]->getFrameRect();

  satyukov::point_t newShapePoints[4] = 
  {
    { newShapeFrameRect.pos.x - newShapeFrameRect.width / 2.0, 
        newShapeFrameRect.pos.y + newShapeFrameRect.height / 2.0 },
    { newShapeFrameRect.pos.x + newShapeFrameRect.width / 2.0, 
        newShapeFrameRect.pos.y + newShapeFrameRect.height / 2.0 },
    { newShapeFrameRect.pos.x + newShapeFrameRect.width / 2.0, 
        newShapeFrameRect.pos.y - newShapeFrameRect.height / 2.0 },
    { newShapeFrameRect.pos.x - newShapeFrameRect.width / 2.0, 
        newShapeFrameRect.pos.y - newShapeFrameRect.height / 2.0 },
  };

  satyukov::point_t matrixShapePoints[4] = 
  {
    { matrixShapeFrameRect.pos.x - matrixShapeFrameRect.width / 2.0, 
        matrixShapeFrameRect.pos.y + matrixShapeFrameRect.height / 2.0 },
    { matrixShapeFrameRect.pos.x + matrixShapeFrameRect.width / 2.0, 
        matrixShapeFrameRect.pos.y + matrixShapeFrameRect.height / 2.0 },
    { matrixShapeFrameRect.pos.x + matrixShapeFrameRect.width / 2.0, 
        matrixShapeFrameRect.pos.y - matrixShapeFrameRect.height / 2.0 },
    { matrixShapeFrameRect.pos.x - matrixShapeFrameRect.width / 2.0, 
        matrixShapeFrameRect.pos.y - matrixShapeFrameRect.height / 2.0 },
  };

  for (int i = 0; i < 4; ++i)
  {
    if (((newShapePoints[i].x >= matrixShapePoints[0].x) && (newShapePoints[i].x <= matrixShapePoints[2].x)
        && (newShapePoints[i].y >= matrixShapePoints[3].y) && (newShapePoints[i].y <= newShapePoints[1].y))
          || ((matrixShapePoints[i].x >= newShapePoints[0].x) && (matrixShapePoints[i].x <= newShapePoints[2].x)
            && (matrixShapePoints[i].y >= newShapePoints[3].y) && (matrixShapePoints[i].y <= newShapePoints[1].y)))
    {
      return true;
    }
  }
  return false;
}
