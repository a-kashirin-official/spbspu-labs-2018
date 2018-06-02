//
// Created by matvey on 28.05.18.
//
#include "matrix.hpp"

#include <iostream>
#include <stdexcept>
#include <iostream>

russkov::Matrix::Matrix(const std::shared_ptr<russkov::Shape> shape_ptr):
  matrix_(nullptr),
  layersNumber_(0),
  layersSize_(0)
{
  if (shape_ptr == nullptr)
  {
    throw std::invalid_argument("Error. Null pointer.");
  }
  addShape(shape_ptr);
}

russkov::Matrix::Matrix(const russkov::Matrix &obj):
  matrix_(new std::shared_ptr<russkov::Shape>[obj.layersNumber_ * obj.layersSize_]),
  layersNumber_(obj.layersNumber_),
  layersSize_(obj.layersSize_)
{
  for(size_t i = 0; i < obj.layersNumber_ * obj.layersSize_; i++)
  {
    matrix_[i] = obj.matrix_[i];
  }
}

russkov::Matrix::Matrix(russkov::Matrix &&obj):
  matrix_(nullptr),
  layersNumber_(obj.layersNumber_),
  layersSize_(obj.layersSize_)
{
  matrix_.swap(obj.matrix_);
  obj.layersNumber_ = 0;
  obj.layersSize_ = 0;
}

russkov::Matrix::~Matrix()
{
  matrix_.reset();
  matrix_ = nullptr;
  layersNumber_ = 0;
  layersSize_ = 0;
}

russkov::Matrix &russkov::Matrix::operator =(const russkov::Matrix & obj)
{
  if(this != &obj)
  {
    layersNumber_ = obj.layersNumber_;
    layersSize_ = obj.layersSize_;
    std::unique_ptr<std::shared_ptr<russkov::Shape>[]>
      newArray(new std::shared_ptr<russkov::Shape>[obj.layersNumber_*obj.layersSize_]);
    for (size_t i = 0; i < obj.layersNumber_*obj.layersSize_; i++)
    {
      newArray[i] = obj.matrix_[i];
    }
    matrix_.swap(newArray);
  }
  return *this;
}

russkov::Matrix &russkov::Matrix::operator =(russkov::Matrix && obj)
{
  if(this == &obj)
  {
    return *this;
  }

  layersNumber_ = obj.layersNumber_;
  layersSize_ = obj.layersSize_;
  matrix_.reset();
  matrix_.swap(obj.matrix_);
  obj.layersNumber_ = 0;
  obj.layersSize_ = 0;

  return *this;
}

std::unique_ptr<std::shared_ptr<russkov::Shape>[]> russkov::Matrix::operator [](size_t index)
{
  if(layersNumber_ == 0)
  {
    throw std::out_of_range("Matrix is empty");
  }
  if (index > layersNumber_ - 1)
  {
    throw std::invalid_argument("Error.Invalid index");
  }
  std::unique_ptr<std::shared_ptr<russkov::Shape>[]>
    newArray(new std::shared_ptr<russkov::Shape>[layersSize_]);
  for(size_t i = 0; i < layersSize_; i++)
  {
    newArray[i] = matrix_[index * layersSize_ + i];
  }

  return newArray;
}

void russkov::Matrix::addShape(const std::shared_ptr <russkov::Shape> shape_ptr)
{
  if(layersNumber_ == 0)
  {
    ++layersNumber_;
    ++layersSize_;
    std::unique_ptr<std::shared_ptr<russkov::Shape>[]>
      newArray(new std::shared_ptr<russkov::Shape>[layersNumber_*layersSize_]);
    matrix_.swap(newArray);
    matrix_[0] = shape_ptr;
  }
  else
  {
    bool addedShape = false;
    for (size_t i = 0; !addedShape; ++i)
    {
      for (size_t j = 0; j < layersSize_; ++j)
      {
        if (!matrix_[i * layersSize_ + j])
        {
          matrix_[i * layersSize_ + j] = shape_ptr;
          addedShape = true;
          break;
        }
        else
        {
          if (checkOverlapping(i * layersSize_ + j, shape_ptr))
          {
            break;
          }
        }

        if (j == (layersSize_ - 1))
        {
          layersSize_++;
          std::unique_ptr< std::shared_ptr< russkov::Shape >[] > newElements(
            new std::shared_ptr< russkov::Shape >[layersNumber_ * layersSize_]);
          for (size_t n = 0; n < layersNumber_; ++n)
          {
            for (size_t m = 0; m < layersSize_ - 1; ++m)
            {
              newElements[n * layersSize_ + m] = matrix_[n * (layersSize_ - 1) + m];
            }
            newElements[(n + 1) * layersSize_ - 1] = nullptr;
          }
          newElements[(i + 1) * layersSize_ - 1] = shape_ptr;
          matrix_.swap(newElements);
          addedShape = true;
          break;
        }
      }

      if ((i == (layersNumber_ - 1)) && !addedShape)
      {
        layersNumber_++;
        std::unique_ptr< std::shared_ptr< russkov::Shape >[] > newElements(
          new std::shared_ptr< russkov::Shape >[layersNumber_ * layersSize_]);
        for (size_t n = 0; n < ((layersNumber_ - 1) * layersSize_); ++n)
        {
          newElements[n] = matrix_[n];
        }
        for (size_t n = ((layersNumber_  - 1) * layersSize_) ; n < (layersNumber_ * layersSize_); ++n)
        {
          newElements[n] = nullptr;
        }
        newElements[(layersNumber_ - 1 ) * layersSize_ ] = shape_ptr;
        matrix_.swap(newElements);
        addedShape = true;
      }
    }
  }
}


bool russkov::Matrix::checkOverlapping(const int index, std::shared_ptr< russkov::Shape > obj) const
{
  russkov::rectangle_t nShapeFrameRect = obj->getFrameRect();
  russkov::rectangle_t mShapeFrameRect = matrix_[index]->getFrameRect();
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

