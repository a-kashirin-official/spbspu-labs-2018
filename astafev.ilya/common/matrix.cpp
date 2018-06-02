

#include"matrix.hpp"
#include"shape.hpp"

#include <stdexcept>
#include <iostream>
#include <new>
#include <algorithm>

astafev::Matrix::Matrix(const std::shared_ptr<Shape> & shape):
  matrix_(nullptr),
  layerNumber_(0),
  layerSize_(0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Empty shape");
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> newElement(new std::shared_ptr<Shape>[(layerNumber_ + 1) * (layerSize_ + 1)]);
  newElement[0]=shape;
  matrix_=std::move(newElement);
  layerSize_++;
  layerNumber_++;
}

astafev::Matrix::Matrix(const Matrix & other):
  matrix_(new std::shared_ptr<Shape>[other.layerNumber_ * other.layerSize_]),
  layerNumber_(other.layerNumber_),
  layerSize_(other.layerSize_)
{
  for(size_t i=0;i<layerNumber_*layerSize_;++i)
  {
    matrix_[i]=other.matrix_[i];
  }
}

astafev::Matrix::Matrix(Matrix && other):
  matrix_(std::move(other.matrix_)),
  layerNumber_(other.layerNumber_),
  layerSize_(other.layerSize_)
{
  other.matrix_=nullptr;
  other.layerNumber_=0;
  other.layerSize_=0;
}

astafev::Matrix::~Matrix()
{
  matrix_=nullptr;
  layerNumber_=0;
  layerSize_=0;
}

astafev::Matrix & astafev::Matrix::operator= (const astafev::Matrix & other)
{
  if (this == &other)
  {
    return *this;
  }
  matrix_.reset(new std::shared_ptr<astafev::Shape> [other.layerSize_*other.layerNumber_] );
  layerNumber_=other.layerNumber_;
  layerSize_=other.layerSize_;
  for(size_t i=0;i<layerNumber_*layerSize_;++i)
  {
    matrix_[i]=other.matrix_[i];
  }
  return *this;
}

astafev::Matrix & astafev::Matrix::operator= (astafev::Matrix && other)
{
  if (this == &other)
  {
    return *this;
  }
  matrix_.reset(new std::shared_ptr<astafev::Shape>[other.layerNumber_* other.layerSize_]);
  layerSize_=other.layerSize_;
  layerNumber_=other.layerNumber_;
  matrix_=std::move(other.matrix_);
  other.matrix_=nullptr;
  other.layerNumber_=0;
  other.layerSize_=0;
  return *this;
}

std::unique_ptr<std::shared_ptr<astafev::Shape>[]> astafev::Matrix::operator[](const size_t index) const
{
  if (layerNumber_ == 0) 
  {
    throw std::out_of_range("Matrix is empty");
  }
  if (index > layerNumber_ - 1) 
  {
    throw std::invalid_argument("Invalid layerCount index");
  }
  std::unique_ptr<std::shared_ptr<astafev::Shape>[]>
    layer(new std::shared_ptr<astafev::Shape>[layerSize_]);
  for (size_t i = 0; i < layerSize_; ++i) {
    layer[i] = matrix_[index * layerSize_ + i];
  }
  return layer;
}

bool astafev::Matrix::checkOverLapping(size_t index, const std::shared_ptr< astafev::Shape > &shape) const noexcept
{
  astafev::rectangle_t nShapeFrameRect = shape->getFrameRect();
  astafev::rectangle_t mShapeFrameRect = matrix_[index]->getFrameRect();
  astafev::point_t newPoints[4] = {
    { nShapeFrameRect.pos.x - nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y + nShapeFrameRect.height / 2.0 },
  { nShapeFrameRect.pos.x + nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y + nShapeFrameRect.height / 2.0 },
  { nShapeFrameRect.pos.x + nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y - nShapeFrameRect.height / 2.0 },
  { nShapeFrameRect.pos.x - nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y - nShapeFrameRect.height / 2.0 }
  };

  astafev::point_t matrixPoints[4] = {
    { mShapeFrameRect.pos.x - mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y + mShapeFrameRect.height / 2.0 },
  { mShapeFrameRect.pos.x + mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y + mShapeFrameRect.height / 2.0 },
  { mShapeFrameRect.pos.x + mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y - mShapeFrameRect.height / 2.0 },
  { mShapeFrameRect.pos.x - mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y - mShapeFrameRect.height / 2.0 }
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


void astafev::Matrix::addElement(const std::shared_ptr< astafev::Shape > &shape) noexcept
{
  bool addedShape = false;
  for (size_t i = 0; !addedShape; ++i)
  {
    for (size_t j = 0; j < layerSize_; ++j)
    {
      if (!matrix_[i * layerSize_ + j])
      {
        matrix_[i * layerSize_ + j] = shape;
        addedShape = true;
        break;
      }
      else
      {
        if (checkOverLapping(i * layerSize_ + j, shape))
        {
          break;
        }
      }

      if (j == (layerSize_ - 1))
      {
        layerSize_++;
        std::unique_ptr< std::shared_ptr< astafev::Shape >[] > newElements(
          new std::shared_ptr< astafev::Shape >[layerNumber_ * layerSize_]);
        for (size_t n = 0; n < layerNumber_; ++n)
        {
          for (size_t m = 0; m < layerSize_ - 1; ++m)
          {
            newElements[n * layerSize_ + m] = matrix_[n * (layerSize_ - 1) + m];
          }
          newElements[(n + 1) * layerSize_ - 1] = nullptr;
        }
        newElements[(i + 1) * layerSize_ - 1] = shape;
        matrix_.swap(newElements);
        addedShape = true;
        break;
      }
    }
    if ((i == (layerNumber_ - 1)) && !addedShape)
    {
      layerNumber_++;
      std::unique_ptr< std::shared_ptr< astafev::Shape >[] > newElements(
        new std::shared_ptr< astafev::Shape >[layerNumber_ * layerSize_]);
      for (size_t n = 0; n < ((layerNumber_ - 1) * layerSize_); ++n)
      {
        newElements[n] = matrix_[n];
      }
      for (size_t n = ((layerNumber_ - 1) * layerSize_); n < (layerNumber_ * layerSize_); ++n)
      {
        newElements[n] = nullptr;
      }
      newElements[(layerNumber_ - 1) * layerSize_] = shape;
      matrix_.swap(newElements);
      addedShape = true;
    }
  }
}

size_t astafev::Matrix::getLayerNumber() const noexcept
{
  return layerNumber_;
}

size_t astafev::Matrix::getLayerSize() const noexcept
{
  return layerSize_;
}

void astafev::Matrix::printInfo() const noexcept
{
  for(size_t i=0;i<layerNumber_;++i)
  {
    std::cout <<i+1<< "- Layer----------------------------------------" << std::endl;
    for(size_t j=0;j<layerSize_;++j)
    {
      if (matrix_[i*layerSize_ + j])
      {
        matrix_[i*layerSize_ + j]->printInfo();
      }
    }
  }
}

void astafev::Matrix::addElement(const std::shared_ptr<astafev::CompositeShape> &shape, size_t size) noexcept
{
  for (size_t i = 0; i < size; ++i) 
  {
    this->addElement((*shape)[i]);
  }
}



  
