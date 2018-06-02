#include <memory>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include "matrix.hpp"

revtova::Matrix::Matrix(const ptr_type rhs):
  figures_(nullptr),
  layersNumber_(0),
  layerSize_(0)
{
  if (rhs == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  addShape(rhs);
}
revtova::Matrix::Matrix(const revtova::Matrix &rhs):
  figures_(new ptr_type[rhs.layersNumber_ * rhs.layerSize_]),
  layersNumber_(rhs.layersNumber_),
  layerSize_(rhs.layerSize_)
{
  for (size_t i = 0; i < layersNumber_ * layerSize_; ++i)
  {
    figures_[i] = rhs.figures_[i];
  }
}
revtova::Matrix::Matrix(revtova::Matrix && rhs):
  figures_(nullptr),
  layersNumber_(rhs.layersNumber_),
  layerSize_(rhs.layerSize_)
{
  figures_.swap(rhs.figures_);
  rhs.layerSize_ = 0;
  rhs.layersNumber_ = 0;
}
revtova::Matrix::~Matrix()
{
  figures_.reset();
  figures_ = nullptr;
  layerSize_ = 0;
  layersNumber_ = 0;
}
revtova::Matrix &revtova::Matrix::operator= (const revtova::Matrix & rhs)
{
  if (this != & rhs)
  {
    layer_type newShapes(new ptr_type[rhs.layersNumber_ * rhs.layerSize_]);
    layersNumber_ = rhs.layersNumber_;
    layerSize_ = rhs.layerSize_;
    for (size_t i = 0; i < layersNumber_ * layerSize_; ++i)
    {
      newShapes[i] = rhs.figures_[i];
    }
    figures_.swap(newShapes);
  }
  return *this;
}
revtova::Matrix &revtova::Matrix::operator= (revtova::Matrix && rhs)
{
  if (this != & rhs)
  {
    layersNumber_ = rhs.layersNumber_;
    layerSize_ = rhs.layerSize_;
    figures_.reset();
    figures_.swap(rhs.figures_);
    rhs.layersNumber_ = 0;
    rhs.layerSize_ = 0;
  }
  return *this;
}
revtova::Matrix::layer_type revtova::Matrix::operator[](size_t index) const
{
  if (index >= layersNumber_)
  {
    throw std::out_of_range("Invalid index");
  }
  layer_type layer(new ptr_type[layerSize_]);
  for (size_t i = 0; i < layerSize_; ++i)
  {
    layer[i] = figures_[index * layerSize_ + i];
  }
  return layer;
}
void revtova::Matrix::addShape(const ptr_type shp)
{
  if (layersNumber_ == 0)
  {
    layer_type newShapes(new ptr_type[(layersNumber_ + 1) * (layerSize_ + 1)]);
    layerSize_++;
    layersNumber_++;
    figures_.swap(newShapes);
    figures_[0] = shp;
  }
  else
  {
    bool addedShape = false;
    for (size_t i = 0; !addedShape ; ++i)
    {
      for (size_t j = 0; j < layerSize_; ++j)
      {
        if (!figures_[i * layerSize_ + j])
        {
          figures_[i * layerSize_ + j] = shp;
          addedShape = true;
          break;
        }
        else
        {
          if (Intersection(figures_[i * layerSize_ + j], shp))
          {
            break;
          }
        }

        if (j == (layerSize_ - 1))
        {
          layer_type newShapes(new ptr_type[layersNumber_ * (layerSize_ + 1)]);
          layerSize_++;
          for (size_t n = 0; n < layersNumber_; ++n)
          {
            for (size_t m = 0; m < layerSize_ - 1; ++m)
            {
              newShapes[n * layerSize_ + m] = figures_[n * (layerSize_ - 1) + m];
            }
            newShapes[(n + 1) * layerSize_ - 1] = nullptr;
          }
          newShapes[(i + 1) * layerSize_ - 1] = shp;
          figures_.swap(newShapes);
          addedShape = true;
          break;
        }
      }
      if ((i == (layersNumber_ - 1)) && !addedShape)
      {
        layer_type newShapes(new ptr_type[(layersNumber_ + 1) * layerSize_]);
        layersNumber_++;
        for (size_t n = 0; n < ((layersNumber_ - 1) * layerSize_); ++n)
        {
          newShapes[n] = figures_[n];
        }
        for (size_t n = ((layersNumber_ - 1) * layerSize_) ; n < (layersNumber_ * layerSize_); ++n)
        {
          newShapes[n] = nullptr;
        }
        newShapes[(layersNumber_ - 1) * layerSize_ ] = shp;
        figures_.swap(newShapes);
        addedShape = true;
      }
    }
  }
}
bool revtova::Matrix::Intersection(const ptr_type &shp, const ptr_type &rhs) const noexcept
{
  rectangle_t getFrameF = shp->getFrameRect();
  rectangle_t getFrameS = rhs->getFrameRect();

  double shpLeft = getFrameF.pos.x - getFrameF.width / 2.0;
  double shpRight = getFrameF.pos.x + getFrameF.width / 2.0;
  double shpDown = getFrameF.pos.y - getFrameF.height / 2.0;
  double shpUp = getFrameF.pos.y + getFrameF.height / 2.0;

  double rhsLeft = getFrameS.pos.x - getFrameS.width / 2.0;
  double rhsRight = getFrameS.pos.x + getFrameS.width / 2.0;
  double rhsDown = getFrameS.pos.y - getFrameS.height / 2.0;
  double rhsUp = getFrameS.pos.y + getFrameS.height / 2.0;

  if ((shpLeft > rhsRight) || (shpRight < rhsLeft) || (shpDown > rhsUp) || (shpUp < rhsDown))
  {
    return false;
  }
  else
  {
    return true;
  }
}
void revtova::Matrix::print()
{
  size_t layerNum[layersNumber_];
  layerNum[0] = 0;
  for (size_t i = 1; i < layersNumber_; i++)
  {
    if (Intersection(figures_[i],figures_[i-1]))
    {
      layerNum[i] = layerNum[i-1] + 1;
    }
    else
    {
      layerNum[i] = layerNum[i-1];
    }
  }
  for (size_t i = 0; i <= layerNum[layersNumber_-1]; i++)
  {
    std::cout << std::endl << "Layer " << i << ": |";
    for (size_t j = 0; j < layersNumber_; j++)
    {
      if (i == layerNum[j])
      {
        std::cout << " * |";
      }
      else
      {
        std::cout << "   |";
      }
    }
  }
  std::cout << std::endl;
}
