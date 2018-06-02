#include "matrix.hpp"
#include <algorithm>
#include <stdexcept>

using namespace sergeev;

Matrix::Matrix():
  items_(0),
  layers_(0),
  layerSize_(0)
{}

Matrix::Matrix(Matrix & rhs):
  items_(std::make_unique< element_type[] >(rhs.layers_ * rhs.layerSize_)),
  layers_(rhs.layers_),
  layerSize_(rhs.layerSize_)
{
  std::copy(rhs.items_.get(), rhs.items_.get() + layers_ * layerSize_, items_.get());
}

Matrix::Matrix(Matrix && rhs):
  items_(std::move(rhs.items_)),
  layers_(rhs.layers_),
  layerSize_(rhs.layerSize_)
{
  rhs.layerSize_ = 0;
  rhs.layers_ = 0;
}

Matrix & Matrix::operator=(const Matrix & rhs)
{
  if(this == &rhs)
  {
    return *this;
  }

  items_ = std::make_unique< element_type[] >(rhs.layers_ * rhs.layerSize_);
  layers_ = rhs.layers_;
  layerSize_ = rhs.layerSize_;
  std::copy(rhs.items_.get(), rhs.items_.get() + layers_ * layerSize_, items_.get());
  return *this;
}

Matrix & Matrix::operator=(Matrix && rhs)
{
  items_ = std::move(rhs.items_);
  layers_ = rhs.layers_;
  layerSize_ = rhs.layerSize_;
  
  rhs.layerSize_ = 0;
  rhs.layers_ = 0;
  
  return *this;
}

Matrix::layer_type Matrix::operator[](size_t index) const
{
  if (index >= layers_) {
    throw std::out_of_range("Out of range Index!!!");
  }
  layer_type layer = std::make_unique< element_type[] >(layerSize_);
  std::copy(items_.get() + index * layerSize_, items_.get() + (index + 1) * layerSize_, layer.get());
  return layer;
}

void Matrix::add(const element_type & shape)
{
  if (!shape) 
  {
    throw std::invalid_argument("Invalid shape!!");
  }

  if ((layers_ == 0) && (layerSize_ == 0)) 
  {
    items_ = std::make_unique< element_type[] >(1);
    layers_ = layerSize_ = 1;
    items_[0] = shape;
    return;
  }

  size_t i = 0;
  for (; i < layers_; ++i) 
  {

    size_t j = 0;
    for(; j < layerSize_; ++j) 
    {

      if (!items_[i * layerSize_ + j]) 
      {
        items_[i * layerSize_ + j] = shape;
        return;
      }

      if (intersection(items_[i * layerSize_ + j], shape)) 
      {
        break;
      }

    }

    if (j == layerSize_) 
    {
      layer_type newShapes = std::make_unique< element_type[] >(layers_ * (layerSize_ + 1));
      
      for (size_t k = 0; k < layers_; ++k) 
      {
        
        for (j = 0; j < layerSize_; ++j) 
        {
          newShapes[k * layerSize_ + j + k] = items_[k * layerSize_ + j];
        }
      }

      ++layerSize_;
      newShapes[(i + 1) * layerSize_ - 1] = shape;
      items_ = std::move(newShapes);
      return;
    }
  }

  if (i == layers_) 
  {
    layer_type newShapes = std::make_unique< element_type[] >((layers_ + 1) * layerSize_);
   
    for (size_t k = 0; k < layers_ * layerSize_; ++k) {
      newShapes[k] = items_[k];
    }
    newShapes[layers_ * layerSize_] = shape;
    ++layers_;
    items_ = std::move(newShapes);
  }
}

void Matrix::clean()
{
  items_.reset();
  layers_ = 0;
  layerSize_ = 0;
}

size_t Matrix::getLayers() const
{
  return layers_;
}

size_t Matrix::getLayerSize() const
{
  return layerSize_;
}

bool Matrix::intersection(const element_type & lhs, const element_type & rhs)
{
  return lhs->getFrameRect().intersection(rhs->getFrameRect());
}
