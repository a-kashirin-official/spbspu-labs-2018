#include "matrix.hpp"

#include <algorithm>
#include <stdexcept>

styagov::Matrix::Matrix() noexcept:
  shapes_(),
  layersCount_(0),
  layerLength_(0)
{

}

styagov::Matrix::Matrix(const std::shared_ptr <styagov::Shape> shape):
  shapes_(nullptr),
  layersCount_(0),
  layerLength_(0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Matrix: Null Pointer exception");
  }

  this->add(shape);
}

styagov::Matrix::Matrix(const styagov::CompositeShape & compositeShape):
  shapes_(nullptr),
  layersCount_(0),
  layerLength_(0)
{
  std::unique_ptr <std::shared_ptr <styagov::Shape>[]> shapes = compositeShape.getShapes();
  for (size_t i = 0; i < compositeShape.getSize(); i++)
  {
    this->add(shapes[i]);
  }
}

styagov::Matrix::Matrix(const styagov::Matrix & object):
  shapes_(new std::shared_ptr <styagov::Shape>[object.layersCount_ * object.layerLength_]),
  layersCount_(object.layersCount_),
  layerLength_(object.layerLength_)
{
  std::copy(object.shapes_.get(), object.shapes_.get() + layersCount_ * layerLength_, shapes_.get());
}

styagov::Matrix::Matrix(styagov::Matrix && object) noexcept:
  shapes_(std::move(object.shapes_)),
  layersCount_(object.layersCount_),
  layerLength_(object.layerLength_)
{
  object.layersCount_ = 0;
  object.layerLength_ = 0;
}

styagov::Matrix::~Matrix()
{
  shapes_.reset();
  shapes_ = nullptr;
  layerLength_ = 0;
  layersCount_ = 0;
}

styagov::Matrix & styagov::Matrix::operator=(const styagov::Matrix & object) noexcept
{
  if (this == &object) 
  {
    return * this;
  }

  layersCount_ = object.layersCount_;
  layerLength_ = object.layerLength_;

  std::unique_ptr <std::shared_ptr< styagov::Shape>[]> newShapes(new std::shared_ptr <styagov::Shape>[layersCount_ * layerLength_]);
  for (size_t i = 0; i < layersCount_ * layerLength_; i++)
  {
    newShapes[i] = object.shapes_[i];
  }
  shapes_.swap(newShapes);
  
  return * this;
}

styagov::Matrix & styagov::Matrix::operator=(styagov::Matrix && object) noexcept
{
  shapes_ = std::move(object.shapes_);
  layersCount_ = object.layersCount_;
  layerLength_ = object.layerLength_;
  object.layersCount_ = 0;
  object.layerLength_ = 0;

  return * this;
}

bool styagov::Matrix::operator==(const styagov::Matrix & object) const
{
  if ((layersCount_ != object.layersCount_) && (layerLength_ != object.layerLength_))
  {
    return false;
  }

  for (size_t i = 0; i < layersCount_ * layerLength_; i++)
  {
    if (shapes_[i] != object.shapes_[i])
    {
      return false;
    }
  }

  return true;
}

bool styagov::Matrix::operator!=(const styagov::Matrix & object) const
{
  if ((layersCount_ != object.layersCount_) || (layerLength_ != object.layerLength_))
  {
    return true;
  }

  for (size_t i = 0; i < layersCount_ * layerLength_; i++)
  {
    if (shapes_[i] != object.shapes_[i])
    {
      return true;
    }
  }

  return false;
}

std::unique_ptr <std::shared_ptr <styagov::Shape>[]> styagov::Matrix::operator[] (size_t index) const
{
  if (index >= layersCount_) 
  {
    throw std::out_of_range("Matrix: Index is out of range");
  }

  std::unique_ptr <std::shared_ptr <styagov::Shape>[]> layer(new std::shared_ptr <styagov::Shape>[layerLength_]);
  for (size_t i = 0; i < layerLength_; i++)
  {
    layer[i] = shapes_[index * layerLength_ + i];
  }

  return layer;
}

void styagov::Matrix::add(const std::shared_ptr <styagov::Shape> shape)
{
  if (layersCount_ == 0)
  {
    try
    {
      std::unique_ptr <std::shared_ptr <styagov::Shape>[]> tmp(new std::shared_ptr <styagov::Shape>[1]);
      layerLength_++;
      layersCount_++;
      shapes_.swap(tmp);
      shapes_[0] = shape;
    }
    catch(const std::bad_alloc & e)
    {
      throw;
    }
  }
  else
  {
    bool finish = false;
    for (size_t i = 0; !finish ; i++) // while not finish
    {
      for (size_t j = 0; j < layerLength_; j++)
      {
        if (!shapes_[i * layerLength_ + j])
        {
          shapes_[i * layerLength_ + j] = shape;
          finish = true;

          break;
        }
        else
        {
          if (this->doesOverlap(i * layerLength_ + j, shape))
          {
            break;
          }
        }

        if (j == (layerLength_ - 1))
        {
          try
          {
            std::unique_ptr <std::shared_ptr <styagov::Shape>[]> modified(new std::shared_ptr <styagov::Shape>[layersCount_ * (layerLength_ + 1)]);
            layerLength_++;
            
            for (size_t k = 0; k < layersCount_; k++)
            {
              for (size_t l = 0; l < layerLength_ - 1; l++)
              {
                modified[k * layerLength_ + l] = shapes_[k * (layerLength_ - 1) + l];
              }
              modified[(k + 1) * layerLength_ - 1] = nullptr;
            }
            modified[(i + 1) * layerLength_ - 1] = shape;
            shapes_.swap(modified);
            finish = true;

            break;
          }
          catch(const std::bad_alloc & e)
          {
            throw;
          }
        }
      }

      if ((i == (layersCount_ - 1)) && !finish)
      {
        try
        {
          std::unique_ptr <std::shared_ptr <styagov::Shape>[]> modified(new std::shared_ptr <styagov::Shape>[(layersCount_ + 1) * layerLength_]);
          layersCount_++;

          for (size_t j = 0; j < ((layersCount_ - 1) * layerLength_); j++)
          {
            modified[j] = shapes_[j];
          }

          for (size_t k = ((layersCount_  - 1) * layerLength_) ; k < (layersCount_ * layerLength_); k++)
          {
            modified[k] = nullptr;
          }

          modified[(layersCount_ - 1 ) * layerLength_ ] = shape;
          shapes_.swap(modified);

          finish = true;
        }
        catch(const std::bad_alloc & e)
        {
          throw;
        }
      }
    }
  }
}

void styagov::Matrix::clear() noexcept
{
  shapes_.reset();
  layersCount_ = 0;
  layerLength_ = 0;
}

size_t styagov::Matrix::getLayers() const noexcept
{
  return layersCount_;
}

size_t styagov::Matrix::getLayerSize() const noexcept
{
  return layerLength_;
}

size_t styagov::Matrix::getElementsInLayer(size_t index) const
{
  if (index >= layersCount_) 
  {
    throw std::out_of_range("Matrix: Index is out of range");
  }

  size_t count = 0;

  for (size_t i = 0; i < layerLength_; i++)
  {
    if (shapes_[index + i])
    {
      count++;
    }
  }

  return count;
}

bool styagov::Matrix::doesOverlap(const size_t index, std::shared_ptr <styagov::Shape> shape) const noexcept
{
  styagov::rectangle_t shapeFrameRect = shape->getFrameRect();
  styagov::rectangle_t elementFrameRect = shapes_[index]->getFrameRect();

  point_t shapeCorners[4] = {
    { /* upper left */
      shapeFrameRect.pos.x - shapeFrameRect.width / 2.0,
      shapeFrameRect.pos.y + shapeFrameRect.height / 2.0
    },
    { /* upper right */
      shapeFrameRect.pos.x + shapeFrameRect.width / 2.0,
      shapeFrameRect.pos.y + shapeFrameRect.height / 2.0
    },
    { /* bottom right */
      shapeFrameRect.pos.x + shapeFrameRect.width / 2.0,
      shapeFrameRect.pos.y - shapeFrameRect.height / 2.0
    },
    { /* bottom left */
      shapeFrameRect.pos.x - shapeFrameRect.width / 2.0,
      shapeFrameRect.pos.y - shapeFrameRect.height / 2.0
    }
  };

  point_t elementCorners[4] = {
    { /* upper left */
      elementFrameRect.pos.x - elementFrameRect.width / 2.0,
      elementFrameRect.pos.y + elementFrameRect.height / 2.0
    },
    { /* upper right */
      elementFrameRect.pos.x + elementFrameRect.width / 2.0,
      elementFrameRect.pos.y + elementFrameRect.height / 2.0
    },
    { /* bottom right */
      elementFrameRect.pos.x + elementFrameRect.width / 2.0,
      elementFrameRect.pos.y - elementFrameRect.height / 2.0
    },
    { /* bottom left */
      elementFrameRect.pos.x - elementFrameRect.width / 2.0,
      elementFrameRect.pos.y - elementFrameRect.height / 2.0
    }
  };

  for (size_t i = 0; i < 4; i++)
  {
    if (
        ((shapeCorners[i].x >= elementCorners[0].x) && (shapeCorners[i].x <= elementCorners[2].x) &&
          (shapeCorners[i].y >= elementCorners[3].y) && (shapeCorners[i].y <= elementCorners[1].y)) || 
        ((elementCorners[i].x >= shapeCorners[0].x) && (elementCorners[i].x <= shapeCorners[2].x) && 
          (elementCorners[i].y >= shapeCorners[3].y) && (elementCorners[i].y <= shapeCorners[1].y))
      )
    {
      return true;
    }
  }
  
  return false;
}
