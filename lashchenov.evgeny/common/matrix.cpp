
#include "matrix.hpp"
#include <cmath>
#include <iostream>

using namespace lashchenov;

Matrix::Layer::Layer(const size_t size, const std::unique_ptr<std::shared_ptr<Shape>[]>::pointer & list) :
  size_(size),
  list_(new std::shared_ptr<Shape>[size_])
{
  for (size_t i = 0; i < size_; ++i) {
    list_[i] = list[i];
  }
}

Shape & Matrix::Layer::operator[](const size_t j)
{
  if (j >= size_) {
    throw std::out_of_range("Index \"j\" out of range");
  }
  return *list_[j];
}

Matrix::Matrix() :
  LayerCount_(0),
  MaxLayerSize_(0),
  LayerSize_(nullptr),
  list_(nullptr)
{
}

Matrix::Matrix(const Matrix & matrix) :
  LayerCount_(matrix.LayerCount_),
  MaxLayerSize_(matrix.MaxLayerSize_)
{
  std::unique_ptr<size_t[]> NumberOfShape_tmp(new size_t[LayerCount_]);
  for (size_t i = 0; i < LayerCount_; ++i) {
    NumberOfShape_tmp[i] = matrix.LayerSize_[i];
  }
  LayerSize_.swap(NumberOfShape_tmp);

  std::unique_ptr<std::shared_ptr<Shape>[]> list_tmp(new std::shared_ptr<Shape>[MaxLayerSize_ * LayerCount_]);
  for (size_t i = 0; i < LayerCount_; ++i) {
    for (size_t j = 0; j < LayerSize_[i]; ++j) {
      list_tmp[i * MaxLayerSize_ + j] = matrix.list_[i * MaxLayerSize_ + j]->getCopy();
    }
  }
  list_.swap(list_tmp);
}

Matrix::Matrix(Matrix && matrix) noexcept :
  LayerCount_(matrix.LayerCount_),
  MaxLayerSize_(matrix.MaxLayerSize_),
  LayerSize_(std::move(matrix.LayerSize_)),
  list_(std::move(matrix.list_))
{
  matrix.LayerCount_ = 0;
  matrix.MaxLayerSize_ = 0;
  matrix.LayerSize_.reset();
  matrix.list_.reset();
}

Matrix & Matrix::operator=(const Matrix & matrix)
{
  if (this != &matrix) {
    LayerCount_ = matrix.LayerCount_;
    MaxLayerSize_ = matrix.MaxLayerSize_;
    std::unique_ptr<size_t[]> NumberOfShape_tmp(new size_t[LayerCount_]);
    for (size_t i = 0; i < LayerCount_; ++i) {
      NumberOfShape_tmp[i] = matrix.LayerSize_[i];
    }
    LayerSize_.swap(NumberOfShape_tmp);

    std::unique_ptr<std::shared_ptr<Shape>[]> list_tmp(new std::shared_ptr<Shape>[MaxLayerSize_ * LayerCount_]);
    for (size_t i = 0; i < LayerCount_; ++i) {
      for (size_t j = 0; j < LayerSize_[i]; ++j) {
        list_tmp[i * MaxLayerSize_ + j] = matrix.list_[i * MaxLayerSize_ + j]->getCopy();
      }
    }
    list_.swap(list_tmp);
  }
  return *this;
}

Matrix & Matrix::operator=(Matrix && matrix) noexcept
{
  if (this != &matrix) {
    LayerCount_ = matrix.LayerCount_;
    MaxLayerSize_ = matrix.MaxLayerSize_;
    LayerSize_ = std::move(matrix.LayerSize_);
    list_ = std::move(matrix.list_);

    matrix.LayerCount_ = 0;
    matrix.MaxLayerSize_ = 0;
    matrix.LayerSize_.reset();
    matrix.list_.reset();
  }
  return *this;
}

Matrix::Layer Matrix::operator[](const size_t i) const
{
  if (i >= LayerCount_) {
    throw std::out_of_range("Index \"i\" out of range");
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> tmpList(new std::shared_ptr<Shape>[LayerSize_[i]]);
  for (size_t j = 0; j < LayerSize_[i]; ++j) {
    tmpList[j] = list_[i * MaxLayerSize_ + j];

  }
  return std::move(Layer(LayerSize_[i], tmpList.get()));
}

void Matrix::remove(const size_t i, const size_t j)
{
  if (i >= LayerCount_) {
    throw std::out_of_range("Index \"i\" out of range");
  }
  if (j >= LayerSize_[i]) {
    throw std::out_of_range("Index \"j\" out of range");
  }
  Matrix tmpMatrix;
  for (size_t k = 0; k < LayerCount_; ++k) {
    for (size_t l = 0; l < LayerSize_[k]; ++l) {
      if ((k != i) || (l != j)) {
        tmpMatrix.add(*list_[k * MaxLayerSize_ + l]);
      }
    }
  }
  *this = std::move(tmpMatrix);
}

void Matrix::addElementsFromCShape(const CompositeShape & cShape)
{
  for (size_t i = 0; i < cShape.size(); ++i) {
    this->add(cShape[i]);
  }

}

void Matrix::add(const Shape & shape)
{
  size_t SuitableLayer = LayerCount_;
  for (size_t i = 0; i < LayerCount_; ++i) {
    if (IsSuitableLayer(i, shape)) {
      SuitableLayer = i;
      break;
    }
  }

  if (SuitableLayer == LayerCount_) {
    addLayer();
  }

  if (LayerSize_[SuitableLayer] == MaxLayerSize_) {
    resizeLayer(MaxLayerSize_ + 1);
  }

  const size_t PlaceForNewShape = SuitableLayer * MaxLayerSize_ + LayerSize_[SuitableLayer];
  list_[PlaceForNewShape] = shape.getCopy();
  LayerSize_[SuitableLayer]++;
}

size_t Matrix::getLayerCount() const
{
  return LayerCount_;
}

size_t Matrix::getLayerSize(const size_t i) const
{
  if (i >= LayerCount_) {
    throw std::out_of_range("Index out of range");
  }
  return LayerSize_[i];
}

void Matrix::printInfo() const
{
  std::cout << "____________Matrix____________" << std::endl;
  for (size_t i = 0; i < LayerCount_; ++i) {
    std::cout << "Layer " << i << ":" << std::endl;
    for (size_t j = 0; j < LayerSize_[i]; ++j) {
      list_[i * MaxLayerSize_ + j]->printInfo();
    }

    if (i == LayerCount_ - 1) {
      std::cout << "______________________________" << std::endl;
    } else {
      std::cout << std::endl;
    }

  }
}

bool Matrix::IsSuitableLayer(const size_t LayerNumber, const Shape & shape) const
{
  const rectangle_t rect1 = shape.getFrameRect();
  for (size_t i = 0; i < LayerSize_[LayerNumber]; ++i) {
    rectangle_t rect2 = list_[LayerNumber * MaxLayerSize_ + i]->getFrameRect();
    if ((rect1.pos.x - rect1.width / 2) < (rect2.pos.x + rect2.width / 2)
        && (rect1.pos.x + rect1.width / 2) > (rect2.pos.x - rect2.width / 2)
        && (rect1.pos.y + rect1.height / 2) > (rect2.pos.y - rect2.height / 2)
        && (rect1.pos.y - rect1.height / 2) < (rect2.pos.y + rect2.height / 2)) {
      return false;
    }
  }
  return true;
}

void Matrix::resizeLayer(const size_t NewLayerSize)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> tmpList(new std::shared_ptr<Shape>[NewLayerSize * LayerCount_]);
  for (size_t i = 0; i < LayerCount_; ++i) {
    for (size_t j = 0; j < LayerSize_[i]; ++j) {
      tmpList[i * NewLayerSize + j] = list_[i * MaxLayerSize_ + j];
    }
  }
  list_.swap(tmpList);
  MaxLayerSize_ = NewLayerSize;
}

void Matrix::addLayer()
{
  std::unique_ptr<size_t[]> tmp(new size_t[LayerCount_ + 1]);
  for (size_t i = 0; i < LayerCount_; ++i) {
    tmp[i] = LayerSize_[i];
  }
  tmp[LayerCount_++] = 0;
  LayerSize_.swap(tmp);

  std::unique_ptr<std::shared_ptr<Shape>[]> tmpList(new std::shared_ptr<Shape>[MaxLayerSize_ * LayerCount_]);
  for (size_t i = 0; i < LayerCount_; ++i) {
    for (size_t j = 0; j < LayerSize_[i]; ++j) {
      tmpList[i * MaxLayerSize_ + j] = list_[i * MaxLayerSize_ + j];
    }
  }
  list_.swap(tmpList);
}
