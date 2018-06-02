#include "matrix.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

hvetsckovich::Matrix::Matrix(const std::shared_ptr< Shape > shape):
  items_(nullptr),
  layers_(0),
  sizeOfLayer_(0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Matrix: Null Pointer exception");
  }

  this->addShape(shape);
}


hvetsckovich::Matrix::Matrix(const Matrix & matrix):
  items_(new std::shared_ptr< Shape >[matrix.layers_ * matrix.sizeOfLayer_]),
  layers_(matrix.layers_),
  sizeOfLayer_(matrix.sizeOfLayer_)
{
  std::copy(matrix.items_.get(), matrix.items_.get() + layers_ * sizeOfLayer_, items_.get());
}

hvetsckovich::Matrix::Matrix(Matrix && matrix):
  items_(std::move(matrix.items_)),
  layers_(matrix.layers_),
  sizeOfLayer_(matrix.sizeOfLayer_)
{
  matrix.layers_ = 0;
  matrix.sizeOfLayer_ = 0;
}

hvetsckovich::Matrix::~Matrix()
{
  items_.reset();
  items_ = nullptr;
  sizeOfLayer_ = 0;
  layers_ = 0;
}

hvetsckovich::Matrix & hvetsckovich::Matrix::operator=(const Matrix & matrix)
{
  if (this != &matrix)
  {
    layers_ = matrix.layers_;
    sizeOfLayer_ = matrix.sizeOfLayer_;
    std::unique_ptr< std::shared_ptr< Shape >[] > newShapes(new std::shared_ptr< Shape >[layers_ * sizeOfLayer_]);
    for (int i = 0; i < layers_ * sizeOfLayer_; i++)
    {
      newShapes[i] = matrix.items_[i];
    }
    items_.swap(newShapes);
  }
  return * this;
}

hvetsckovich::Matrix & hvetsckovich::Matrix::operator=(Matrix && matrix)
{
  items_ = std::move(matrix.items_);
  layers_ = matrix.layers_;
  sizeOfLayer_ = matrix.sizeOfLayer_;
  matrix.layers_ = 0;
  matrix.sizeOfLayer_ = 0;

  return * this;
}

bool hvetsckovich::Matrix::operator==(const Matrix & matrix) const
{//equal checking
  if ((layers_ != matrix.layers_) && (sizeOfLayer_ != matrix.sizeOfLayer_))
  {
    return false;
  }
  else
  {
    for (int i = 0; i < layers_ * sizeOfLayer_; i++)
    {
      if (items_[i] != matrix.items_[i])
      {
        return false;
      }
    }
    return true;
  }
}

bool hvetsckovich::Matrix::operator!=(const Matrix & matrix) const
{//unequal checking
  if ((layers_ != matrix.layers_) && (sizeOfLayer_ != matrix.sizeOfLayer_))
  {
    return true;
  }
  else
  {
    for (int i = 0; i < layers_ * sizeOfLayer_; i++)
    {
      if (items_[i] != matrix.items_[i])
      {
        return true;
      }
    }
    return false;
  }
}

std::unique_ptr< std::shared_ptr< hvetsckovich::Shape >[] > hvetsckovich::Matrix::operator[] (int index) const
{
  if ((index < 0) || (index >= layers_))
  {
    throw std::out_of_range("Matrix: Index is out of range");
  }

  std::unique_ptr< std::shared_ptr< Shape >[] > layer(new std::shared_ptr <Shape>[sizeOfLayer_]);
  for (int i = 0; i < sizeOfLayer_; i++)
  {
    layer[i] = items_[index * sizeOfLayer_ + i];
  }

  return layer;
}

void hvetsckovich::Matrix::addShape(const std::shared_ptr< Shape > shape)
{
  if (layers_ == 0)
  {
    // adding first shape
    try
    {
      std::unique_ptr <std::shared_ptr <Shape>[]> tmp(new std::shared_ptr <Shape>[1]);
      sizeOfLayer_++;
      layers_++;
      items_.swap(tmp);
      items_[0] = shape;
    }
    catch (const std::bad_alloc & e)
    {
      throw;
    }
  }
  else
  {
    bool finish = false;
    for (int i = 0; !finish ; i++) // trying to add somewhere
    { // looking for a layer
      for (int j = 0; j < sizeOfLayer_; j++)
      { // looking for a place in i-th layer
        if (!items_[i * sizeOfLayer_ + j])
        { // empty => place shape here
          items_[i * sizeOfLayer_ + j] = shape;
          finish = true;
          break;
        }
        else
        {
          if (this->checkOverlaying(i * sizeOfLayer_ + j, shape))
          { // this layer doesn't fit
            break;
          }
        }

        if (j == (sizeOfLayer_ - 1))
        { // layer is applicable, no free space on the way, adding to the end
          try
          {
            std::unique_ptr< std::shared_ptr< Shape >[] > tmp(new std::shared_ptr< Shape >[layers_ * (sizeOfLayer_ + 1)]);
            sizeOfLayer_++;
            for (int k = 0; k < layers_; k++)
            {
              for (int l = 0; l < sizeOfLayer_ - 1; l++)
              {
                tmp[k * sizeOfLayer_ + l] = items_[k * (sizeOfLayer_ - 1) + l];
              }
              tmp[(k + 1) * sizeOfLayer_ - 1] = nullptr;
            }
            tmp[(i + 1) * sizeOfLayer_ - 1] = shape;
            items_.swap(tmp);
            finish = true;
            break;
          }
          catch (const std::bad_alloc & e)
          {
            throw;
          }
        }
      }

      if ((i == (layers_ - 1)) && !finish)
      { // no suitable spaces in all existing layers, creating new empty one
        try
        {
          std::unique_ptr< std::shared_ptr< Shape >[] > tmp(new std::shared_ptr< Shape >[(layers_ + 1) * sizeOfLayer_]);
          layers_++;

          for (int j = 0; j < ((layers_ - 1) * sizeOfLayer_); j++)
          {
            tmp[j] = items_[j];
          }
          for (int k = ((layers_  - 1) * sizeOfLayer_) ; k < (layers_ * sizeOfLayer_); k++)
          {
            tmp[k] = nullptr;
          }
          tmp[(layers_ - 1 ) * sizeOfLayer_ ] = shape;
          items_.swap(tmp);

          finish = true;
        }
        catch (const std::bad_alloc & e)
        {
          throw;
        }
      }
    }
  }
}

void hvetsckovich::Matrix::eraseAll()
{
  items_.reset();
  layers_ = 0;
  sizeOfLayer_ = 0;
}

int hvetsckovich::Matrix::getLayers() const
{
  return layers_;
}

int hvetsckovich::Matrix::getLayerSize() const
{
  return sizeOfLayer_;
}

bool hvetsckovich::Matrix::checkOverlaying(const int index, std::shared_ptr< Shape > shape) const // check whether shape overlaps matrix item at index given
{
  rectangle_t shapeRect = shape->getFrameRect();
  rectangle_t innerShapeRect = items_[index]->getFrameRect();

  point_t shapeCorners[4] = {
    { shapeRect.pos.x - shapeRect.width / 2.0, shapeRect.pos.y + shapeRect.height / 2.0 },
    { shapeRect.pos.x + shapeRect.width / 2.0, shapeRect.pos.y + shapeRect.height / 2.0 },
    { shapeRect.pos.x + shapeRect.width / 2.0, shapeRect.pos.y - shapeRect.height / 2.0 },
    { shapeRect.pos.x - shapeRect.width / 2.0, shapeRect.pos.y - shapeRect.height / 2.0 }
  };

  point_t elementCorners[4] = {
    { innerShapeRect.pos.x - innerShapeRect.width / 2.0, innerShapeRect.pos.y + innerShapeRect.height / 2.0 },
    { innerShapeRect.pos.x + innerShapeRect.width / 2.0, innerShapeRect.pos.y + innerShapeRect.height / 2.0 },
    { innerShapeRect.pos.x + innerShapeRect.width / 2.0, innerShapeRect.pos.y - innerShapeRect.height / 2.0 },
    { innerShapeRect.pos.x - innerShapeRect.width / 2.0, innerShapeRect.pos.y - innerShapeRect.height / 2.0 }
  };

  for (int i = 0; i < 4; i++)
  {
    if (((shapeCorners[i].x >= elementCorners[0].x) && (shapeCorners[i].x <= elementCorners[2].x)
    && (shapeCorners[i].y >= elementCorners[3].y) && (shapeCorners[i].y <= elementCorners[1].y))
    || ((elementCorners[i].x >= shapeCorners[0].x) && (elementCorners[i].x <= shapeCorners[2].x)
    && (elementCorners[i].y >= shapeCorners[3].y) && (elementCorners[i].y <= shapeCorners[1].y))
      )
    {
      return true;
    }
  }

  return false;
}
