#include "matrix.hpp"

#include <stdexcept>
#include <memory>

korichev::Matrix::Matrix() noexcept:
  items_(),
  layers_(0),
  layerSize_(0)
{}

korichev::Matrix::Matrix(const korichev::Matrix & rhs):
  layers_(0),
  layerSize_(0)
{
  items_ = std::make_unique< std::shared_ptr < korichev::Shape > []>(rhs.layers_ * rhs.layerSize_);
  layers_ = rhs.layers_;
  layerSize_ = rhs.layerSize_;
  for (size_t i = 0; i < (layers_ * layerSize_) ; i++) {
    items_[i] = rhs.items_[i];
  }
}

korichev::Matrix::Matrix(Matrix && rhs) noexcept:
  layers_(0),
  layerSize_(0)
{
  items_ = std::make_unique< std::shared_ptr < korichev::Shape > []>(rhs.layers_ * rhs.layerSize_);
  layers_ = rhs.layers_;
  layerSize_ = rhs.layerSize_;
  for (size_t i = 0; i < (layers_ * layerSize_) ; i++) {
    items_[i] = rhs.items_[i];
  }
}

korichev::Matrix & korichev::Matrix::operator= (const korichev::Matrix & rhs)
{
  if (this == &rhs) {
    return *this;
  }

  items_ = std::make_unique< std::shared_ptr < korichev::Shape > []>(rhs.layers_ * rhs.layerSize_);
  layers_ = rhs.layers_;
  layerSize_ = rhs.layerSize_;
  for (size_t i = 0; i < (layers_ * layerSize_) ; i++) {
    items_[i] = rhs.items_[i];
  }
  return *this;
}

korichev::Matrix & korichev::Matrix::operator= (korichev::Matrix && rhs) noexcept
{

  items_ = std::make_unique< std::shared_ptr < korichev::Shape > []>(rhs.layers_ * rhs.layerSize_);
  layers_ = rhs.layers_;
  layerSize_ = rhs.layerSize_;
  for (size_t i = 0; i < (layers_ * layerSize_) ; i++) {
    items_[i] = rhs.items_[i];
  }
  return *this;
}

std::shared_ptr < korichev::Shape > * korichev::Matrix::operator[] (size_t index) const
{
  if (index >= layers_) {
    throw std::invalid_argument("Wrong index!");
  }

  return items_.get() + layerSize_*index;
}

void korichev::Matrix::add(const std::shared_ptr < korichev::Shape > & shape)
{
  if (!shape) {
    throw std::invalid_argument("Shape cannot be nullptr");
  }
  if ((layers_ == 0) && (layerSize_ == 0)) {
    items_ = std::make_unique< std::shared_ptr < korichev::Shape > [] >(1);
    layers_ = 1;
    layerSize_ = 1;
    items_[0] = shape;
    return;
  }
  size_t i = 0;
  for (i = 0; i < layers_; i++) {
    size_t j = 0;
    for( j = 0; j < layerSize_; j++) {
      if (!items_[i * layerSize_ + j]) {
        items_[i * layerSize_ + j] = shape;
        return;
      }
      if (items_[i * layerSize_ + j]->getFrameRect().cross(shape->getFrameRect())) {
        break;
      }
    }
    if (j == layerSize_) {
      std::unique_ptr< std::shared_ptr < korichev::Shape > [] > temp_matrix =
        std::make_unique< std::shared_ptr < korichev::Shape > []>(layers_ * (layerSize_ + 1));
      for (size_t v = 0; v < layers_; v++) {
        for (j = 0; j < layerSize_; j++) {
          temp_matrix[v * layerSize_ + j + v] = items_[v * layerSize_ + j];
        }
      }
      layerSize_++;
      temp_matrix[(i + 1) * layerSize_ - 1] = shape;
      items_.swap(temp_matrix);
      return;
    }
  }
  if (i == layers_) {
    std::unique_ptr< std::shared_ptr < korichev::Shape > [] > temp_matrix =
      std::make_unique< std::shared_ptr < korichev::Shape > []>((layers_ + 1) * layerSize_);
    for (size_t v = 0; v < layers_ * layerSize_; v++) {
      temp_matrix[v] = items_[v];
    }
    temp_matrix[layers_ * layerSize_] = shape;
    layers_++;
    items_.swap(temp_matrix);
  }
}

void korichev::Matrix::clear() noexcept
{
  items_.reset();
  layers_ = 0;
  layerSize_ = 0;
}

size_t korichev::Matrix::getLayers() const noexcept
{
  return layers_;
}

size_t korichev::Matrix::getLayerSize() const noexcept
{
  return layerSize_;
}
