#include "matrix.hpp"

#include <memory>
#include <stdexcept>

shapoval::Matrix::Matrix(const std::shared_ptr<shapoval::Shape> new_shape):
  parts_(nullptr),
  layersNumber_(0),
  layerSize_(0)
  {
    if (new_shape == nullptr)
    {
      throw std::invalid_argument("Null pointer!!");
    }
    addShape(new_shape);
  }

shapoval::Matrix::Matrix(const shapoval::Matrix & new_matrix):
  parts_(new std::shared_ptr<shapoval::Shape>[new_matrix.layersNumber_ * new_matrix.layerSize_]),
  layersNumber_(new_matrix.layersNumber_),
  layerSize_(new_matrix.layerSize_)
  {
    for (int i = 0; i< layersNumber_ * layerSize_; ++i)
    {
      parts_[i] = new_matrix.parts_[i];
    }
  }

shapoval::Matrix::Matrix(shapoval::Matrix && new_matrix):
  parts_(nullptr),
  layersNumber_(new_matrix.layersNumber_),
  layerSize_(new_matrix.layerSize_)
{
  parts_.swap(new_matrix.parts_);
  new_matrix.layersNumber_ = 0;
  new_matrix.layerSize_ = 0;
}

shapoval::Matrix & shapoval::Matrix::operator=(const shapoval::Matrix & new_matrix)
{
  if (this != &new_matrix)
  {
    layersNumber_ = new_matrix.layersNumber_;
    layerSize_ = new_matrix.layerSize_;
    std::unique_ptr<std::shared_ptr<shapoval::Shape>[]> new_parts_(
                new std::shared_ptr<shapoval::Shape>[layersNumber_ * layerSize_]);
    for (int i = 0; i< layersNumber_ * layerSize_; ++i)
    {
        new_parts_[i] = new_matrix.parts_[i];
    }
    parts_.swap(new_parts_);
  }
  return *this;
}

shapoval::Matrix & shapoval::Matrix::operator=(shapoval::Matrix && new_matrix)
{
  if (this != &new_matrix)
  {
    layersNumber_ = new_matrix.layersNumber_;
    layerSize_ = new_matrix.layerSize_;
    parts_.reset();
    parts_.swap(new_matrix.parts_);
    new_matrix.layersNumber_ = 0;
    new_matrix.layerSize_ = 0;
  }
  return *this;
}

bool shapoval::Matrix::operator==(const shapoval::Matrix & new_matrix) const
{
  if ((this->layersNumber_ == new_matrix.layersNumber_) && (this->layerSize_ == new_matrix.layerSize_))
  {
    bool equal = true;
    for (int i = 0; i < layersNumber_ * layerSize_; ++i)
    {
      if (!(this->parts_[i] == new_matrix.parts_[i]))
      {
        equal = false;
      }
    }
    if (equal)
    {
      return true;
    }
  }
  return false;
}

bool shapoval::Matrix::operator!=(const shapoval::Matrix & new_matrix) const
{
  if ((this->layersNumber_ != new_matrix.layersNumber_) || (this->layerSize_ != new_matrix.layerSize_))
  {
    return true;
  }
  for (int i = 0; i < layersNumber_ * layerSize_; ++i)
  {
    if (this->parts_[i] != new_matrix.parts_[i])
    {
      return true;
    }
  }
  return false;
}

std::unique_ptr<std::shared_ptr<shapoval::Shape>[]> shapoval::Matrix::operator[] (const int layerNumber) const
{
  if ((layerNumber < 0) || (layerNumber >= layersNumber_))
  {
    throw std::out_of_range("Invalid layer number!!");
  }
  std::unique_ptr<std::shared_ptr<shapoval::Shape>[] > new_layer(
        new std::shared_ptr<shapoval::Shape>[layerSize_]);
  for (int i = 0; i < layerSize_; ++i)
  {
    new_layer[i] = parts_[layerNumber * layerSize_ + i];
  }
  return new_layer;
}

void shapoval::Matrix::addShape(const std::shared_ptr<shapoval::Shape> new_shape) noexcept
{
  if (layersNumber_ == 0)
  {
    ++layerSize_;
    ++layersNumber_;
    std::unique_ptr<std::shared_ptr<shapoval::Shape>[]> new_parts_(
          new std::shared_ptr<shapoval::Shape>[layersNumber_ * layerSize_]);
    parts_.swap(new_parts_);
    parts_[0] = new_shape;
  }
  else
  {
    bool addedShape = false;
    for (int i = 0; !addedShape; ++i)
    {
      for (int j =0; j <layerSize_; ++j)
      {
        if (!parts_[i * layerSize_ + j])
        {
          parts_[i * layerSize_ + j] = new_shape;
          addedShape = true;
          break;
        }
        else
        {
          if (overLappingCheck(i * layerSize_ +j, new_shape))
          {
            break;
          }
        }
        if (j == (layerSize_ - 1))
        {
          layerSize_++;
          std::unique_ptr<std::shared_ptr<shapoval::Shape>[]> new_parts_(
                new std::shared_ptr<shapoval::Shape>[layersNumber_ * layerSize_]);
          for (int n = 0; n < layersNumber_; ++n)
          {
            for (int m = 0; m < layerSize_ - 1; ++m)
            {
              new_parts_[n * layerSize_ + m] = parts_[n * (layerSize_ - 1) + m];
            }
            new_parts_[(n + 1) * layerSize_ - 1] = nullptr;
          }
          new_parts_[(i +1) * layerSize_ - 1] = new_shape;
          parts_.swap(new_parts_);
          addedShape = true;
          break;
        }
      }
      if ((i == (layersNumber_ - 1)) && !addedShape)
      {
        layersNumber_++;
        std::unique_ptr<std::shared_ptr<shapoval::Shape>[]> new_parts_(
              new std::shared_ptr<shapoval::Shape>[layersNumber_ * layerSize_]);
        for (int n = 0; n < ((layersNumber_ - 1) * layerSize_); ++n)
        {
          new_parts_[n] = parts_[n];
        }
        for (int n = ((layersNumber_ - 1) * layerSize_); n < (layersNumber_ * layerSize_); ++n)
        {
          new_parts_[n] = nullptr;
        }
        new_parts_[(layersNumber_ - 1) * layerSize_] = new_shape;
        parts_.swap(new_parts_);
        addedShape = true;
      }
    }
  }
}

shapoval::Matrix::Matrix(const shapoval::CompositeShape new_compositeshape):
  parts_(nullptr),
  layersNumber_(0),
  layerSize_(0)
  {
    if (new_compositeshape.getSize() == 0)
    {
      throw std::invalid_argument("Empty CompositeShape!!");
    }
    for (int i = 0; i < new_compositeshape.getSize(); ++i)
    {
      addShape(new_compositeshape.getShape(i));
    }
  }

bool shapoval::Matrix::overLappingCheck(const int number, std::shared_ptr<shapoval::Shape> new_shape) const noexcept
{
  shapoval::rectangle_t shapeFrameRect1 = new_shape->getFrameRect();
  shapoval::rectangle_t shapeFrameRect2 = parts_[number]->getFrameRect();
  point_t newShapePoints[4] = {
    {shapeFrameRect1.pos.x - shapeFrameRect1.width / 2, shapeFrameRect1.pos.y + shapeFrameRect1.height / 2},
    {shapeFrameRect1.pos.x + shapeFrameRect1.width / 2, shapeFrameRect1.pos.y + shapeFrameRect1.height / 2},
    {shapeFrameRect1.pos.x + shapeFrameRect1.width / 2, shapeFrameRect1.pos.y - shapeFrameRect1.height / 2},
    {shapeFrameRect1.pos.x - shapeFrameRect1.width / 2, shapeFrameRect1.pos.y - shapeFrameRect1.height / 2}
  };
  point_t newMatrixPoints[4] = {
    {shapeFrameRect2.pos.x - shapeFrameRect2.width / 2, shapeFrameRect2.pos.y + shapeFrameRect2.height / 2},
    {shapeFrameRect2.pos.x + shapeFrameRect2.width / 2, shapeFrameRect2.pos.y + shapeFrameRect2.height / 2},
    {shapeFrameRect2.pos.x + shapeFrameRect2.width / 2, shapeFrameRect2.pos.y - shapeFrameRect2.height / 2},
    {shapeFrameRect2.pos.x - shapeFrameRect2.width / 2, shapeFrameRect2.pos.y - shapeFrameRect2.height / 2}
  };
  for (int i = 0; i < 4; ++i)
  {
    if (((newShapePoints[i].x >= newMatrixPoints[0].x) && (newShapePoints[i].x <= newMatrixPoints[2].x)
      && (newShapePoints[i].y >= newMatrixPoints[3].y) && (newShapePoints[i].y <= newMatrixPoints[1].y))
        || ((newShapePoints[i].x <= newMatrixPoints[0].x) && (newShapePoints[i].x >= newMatrixPoints[2].x)
          && (newShapePoints[i].y <= newMatrixPoints[0].y) && (newShapePoints[i].y >= newMatrixPoints[2].y)))
    {
      return true;
    }
  }
  return false;
}

int shapoval::Matrix::getLayersNumber() const noexcept
{
  return layersNumber_;
}

int shapoval::Matrix::getLayerSize(const int layerNumber) const noexcept
{
  int b = 0;
  for (int i=layerNumber; i < layerNumber * layerSize_; ++i)
    if (parts_ != nullptr)
    {
      ++b;
    }
  return b;
}

int shapoval::Matrix::getMaxLayerSize() const noexcept
{
  return layerSize_;
}

