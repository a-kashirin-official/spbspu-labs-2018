//
//  matrix.cpp
//  A4 
//
//  Created by Георгий Тимошенский on 27.05.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//

#include "matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <memory>

timoshenskiy::Matrix::Matrix(const std::shared_ptr < timoshenskiy::Shape > shape):
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

timoshenskiy::Matrix::Matrix(const timoshenskiy::Matrix &matrix):
  matrixShapes_(new std::shared_ptr < timoshenskiy::Shape > [matrix.layersNumber_ * matrix.layerSize_]),
  layersNumber_(matrix.layersNumber_),
  layerSize_(matrix.layerSize_)
{
  for (int i = 0; i < layersNumber_ * layerSize_; ++i)
  {
    matrixShapes_[i] = matrix.matrixShapes_[i];
  }
}

timoshenskiy::Matrix::Matrix(timoshenskiy::Matrix &&matrix):
  matrixShapes_(nullptr),
  layersNumber_(matrix.layersNumber_),
  layerSize_(matrix.layerSize_)
{
  matrixShapes_.swap(matrix.matrixShapes_);
  matrix.layersNumber_ = 0;
  matrix.layerSize_ = 0;
}

timoshenskiy::Matrix &timoshenskiy::Matrix::operator = (const timoshenskiy::Matrix &matrix)
{
  if (this != &matrix)
  {
    layersNumber_ = matrix.layersNumber_;
    layerSize_ = matrix.layerSize_;
    std::unique_ptr < std::shared_ptr < timoshenskiy::Shape > [] >
      newMatrixShapes(new std::shared_ptr < timoshenskiy::Shape > [layersNumber_ * layerSize_]);
    for (int i = 0; i < layersNumber_ * layerSize_; ++i)
    {
      newMatrixShapes[i] = matrix.matrixShapes_[i];
    }
    matrixShapes_.swap(newMatrixShapes);
  }
  return *this;
}

bool timoshenskiy::Matrix::operator == (const timoshenskiy::Matrix &matrix) const
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

bool timoshenskiy::Matrix::operator != (const Matrix &matrix) const
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

std::unique_ptr < std::shared_ptr < timoshenskiy::Shape > [] > timoshenskiy::Matrix::operator [] (const int layerNumber) const
{
  if ((layerNumber < 0) || (layerNumber >= layersNumber_))
  {
    throw std::out_of_range("invalid layer index");
  }
  std::unique_ptr < std::shared_ptr < timoshenskiy::Shape > [] >
    layer(new std::shared_ptr < timoshenskiy::Shape > [layerSize_]);
  for (int i = 0; i < layerSize_; ++i)
  {
    layer[i] = matrixShapes_[layerNumber * layerSize_ + i];
  }
  return layer;
}

void timoshenskiy::Matrix::addShape(const std::shared_ptr < timoshenskiy::Shape > shape)
{
  if (layersNumber_ == 0)
  {
    std::unique_ptr < std::shared_ptr < timoshenskiy::Shape >[] >
      newMatrixShapes(new std::shared_ptr < timoshenskiy::Shape > [(layersNumber_ + 1) * (layerSize_ + 1)]);
    ++layersNumber_;
    ++layerSize_;
    matrixShapes_.swap(newMatrixShapes);
    matrixShapes_[0] = shape;
  }
  else
  {
    bool addedShape = false;
    for (int i = 0; !addedShape; ++i)
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
          if (areIntersected(i * layerSize_ + j, shape))
          {
            break;
          }
        }

        if (j == (layerSize_ - 1))
        {
          std::unique_ptr < std::shared_ptr < timoshenskiy::Shape > [] >
            newMatrixShapes(new std::shared_ptr < timoshenskiy::Shape > [(layersNumber_ ) * (layerSize_ + 1)]);
          layerSize_++;
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
        std::unique_ptr < std::shared_ptr < timoshenskiy::Shape > [] >
          newMatrixShapes(new std::shared_ptr< timoshenskiy::Shape >[(layersNumber_ + 1) * (layerSize_)]);
        layersNumber_++;
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

bool timoshenskiy::Matrix::areIntersected(const int index, std::shared_ptr < timoshenskiy::Shape > shape) const
{
  timoshenskiy::rectangle_t nShapeFrameRect = shape->getFrameRect();
  timoshenskiy::rectangle_t mShapeFrameRect = matrixShapes_[index]->getFrameRect();
  timoshenskiy::point_t newShapePeaks[4] = {
    {nShapeFrameRect.pos.x - nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y + nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x + nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y + nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x + nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y - nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x - nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y - nShapeFrameRect.height / 2.0}
  };

  timoshenskiy::point_t matrixShapePeaks[4] = {
    {mShapeFrameRect.pos.x - mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y + mShapeFrameRect.height / 2.0},
    {mShapeFrameRect.pos.x + mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y + mShapeFrameRect.height / 2.0},
    {mShapeFrameRect.pos.x + mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y - mShapeFrameRect.height / 2.0},
    {mShapeFrameRect.pos.x - mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y - mShapeFrameRect.height / 2.0}
  };

  for (int i = 0; i < 4; ++i)
  {
    if (((newShapePeaks[i].x >= matrixShapePeaks[0].x) && (newShapePeaks[i].x <= matrixShapePeaks[2].x)
         && (newShapePeaks[i].y >= matrixShapePeaks[3].y) && (newShapePeaks[i].y <= matrixShapePeaks[1].y))
        || ((matrixShapePeaks[i].x >= newShapePeaks[0].x) && (matrixShapePeaks[i].x <= newShapePeaks[2].x)
            && (matrixShapePeaks[i].y >= newShapePeaks[3].y) && (matrixShapePeaks[i].y <= newShapePeaks[1].y)))
    {
      return true;
    }
  }
  return false;
}

std::string timoshenskiy::Matrix::printInformation(const timoshenskiy::Shape &shape) const
{
  std::stringstream info;

  info << "\t Width of the frame: " << shape.getFrameRect().width << "\n"
       << "\t Height of the frame: " << shape.getFrameRect().height << "\n"
       << "\t Center of the frame (" << shape.getFrameRect().pos.x << ", " 
                                  << shape.getFrameRect().pos.y << ")" << "\n"
       << "\t Area: " << shape.getArea() << "\n"
       << "________________________" << std::endl;
  return info.str();
}

