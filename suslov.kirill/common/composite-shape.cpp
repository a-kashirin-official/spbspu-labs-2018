#include "composite-shape.hpp"

#include <stdexcept>
#include <memory>
#include <math.h>

suslov::CompositeShape::CompositeShape(std::shared_ptr < suslov::Shape > shape):
  shapes_(nullptr),
  size_(0),
  angle_(0.0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Nullptr");
  }
  addShape(shape);
}

suslov::CompositeShape::CompositeShape(const CompositeShape & compositeShape):
  shapes_(new std::shared_ptr < suslov::Shape > [compositeShape.size_]),
  size_(compositeShape.size_),
  angle_(compositeShape.angle_)
{
  for (int i =0; i < size_; ++i)
  {
    shapes_[i] = compositeShape.shapes_[i];
  }
}

suslov::CompositeShape::CompositeShape(CompositeShape && compositeShape):
  shapes_(nullptr),
  size_(compositeShape.size_),
  angle_(compositeShape.angle_)
{
  shapes_.swap(compositeShape.shapes_);
  compositeShape.deleteAllShapes();
}


suslov::CompositeShape::~CompositeShape()
{
  deleteAllShapes();
}

suslov::CompositeShape & suslov::CompositeShape::operator = (const suslov::CompositeShape & compositeShape) 
{
  if (this != & compositeShape)
  {
    size_ = compositeShape.size_;
    angle_ = compositeShape.angle_;
    std::unique_ptr< std::shared_ptr< suslov::Shape >[] > newShapes(new std::shared_ptr < suslov::Shape > [compositeShape.size_]);
    for (int i = 0; i < size_; ++i)
    {
      newShapes[i] = compositeShape.shapes_[i];
    }
    shapes_.swap(newShapes);
  }
  return *this;
}

suslov::CompositeShape & suslov::CompositeShape::operator = (CompositeShape && compositeShape)
{
  if (this != & compositeShape)
  {
    size_ = compositeShape.size_;
    angle_ = compositeShape.angle_;
    shapes_.swap(compositeShape.shapes_);
    compositeShape.deleteAllShapes();
  }
  return *this;
}

bool suslov::CompositeShape::operator==(const suslov::CompositeShape & compositeShape) const
{
  if ((this->size_ != compositeShape.size_) || (this->angle_ != compositeShape.angle_))
  {
    return false;
  }
  for (int i = 0; i < size_; ++i)
    {
      if (this->shapes_[i] != compositeShape.shapes_[i])
      {
        return false;
      }
    }
  return true;
}

bool suslov::CompositeShape::operator!=(const suslov::CompositeShape & compositeShape) const
{
  if ((this->size_ != compositeShape.size_) || (this->angle_ != compositeShape.angle_))
  {
    return true;
  }
  for (int i = 0; i < size_; ++i)
    {
      if (this->shapes_[i] != compositeShape.shapes_[i])
      {
        return true;
      }
    }
  return false;
}

suslov::rectangle_t suslov::CompositeShape::getFrameRect() const noexcept
{
  if (size_ == 0)
  {
    return{{0, 0}, 0, 0};
  }
  else
  {
    suslov::rectangle_t frameRect = shapes_[0]->getFrameRect();
    double left = frameRect.pos.x - frameRect.width / 2.0;
    double right = frameRect.pos.x + frameRect.width / 2.0;
    double bottom = frameRect.pos.y - frameRect.height / 2.0;
    double top = frameRect.pos.y + frameRect.height / 2.0;

    for (int i = 1; i < size_; ++i)
    {
      frameRect = shapes_[i]->getFrameRect();
      double left_ = frameRect.pos.x - frameRect.width / 2.0;
      double right_ = frameRect.pos.x + frameRect.width / 2.0;
      double bottom_ = frameRect.pos.y - frameRect.height / 2.0;
      double top_ = frameRect.pos.y + frameRect.height / 2.0;

      if (left_ < left)
      {
        left = left_;
      }
      if (right_ > right)
      {
        right = right_;
      }
      if (bottom_ < bottom)
      {
        bottom = bottom_;
      }
      if (top_ > top)
      {
        top = top_;
      }
    }
    return{{((left + right) / 2.0), ((top + bottom) / 2.0)}, (right - left), (top - bottom)};
  }
}

double suslov::CompositeShape::getArea() const noexcept
{
  double area = 0;
  for (int i = 0; i < size_; ++i)
  {
    area += shapes_[i]->getArea();
  }
  return area;
}

double suslov::CompositeShape::getAngle() const
{
  return angle_;
}

void suslov::CompositeShape::move(const double dx, const double dy) noexcept
{
  for (int i = 0; i < size_; ++i)
  {
    shapes_[i]->move(dx, dy);
  }
}

void suslov::CompositeShape::move(const suslov::point_t & newPoint) noexcept
{
  move(newPoint.x - getFrameRect().pos.x, newPoint.y - getFrameRect().pos.y);
}

void suslov::CompositeShape::scale(const double coef)
{
  if (coef < 0.0)
  {
    throw std::invalid_argument("Invalide scale coefficient");
  }
  const suslov::point_t FRAME_CENTER = getFrameRect().pos;
  for(int i = 0; i < size_; ++i)
  {
    shapes_[i]->move((coef - 1.0) * (shapes_[i]->getFrameRect().pos.x - FRAME_CENTER.x), 
      (coef - 1.0) * (shapes_[i]->getFrameRect().pos.y - FRAME_CENTER.y));
    shapes_[i]->scale(coef);
  }
}

void suslov::CompositeShape::rotate(const double angle) noexcept
{
  angle_ += angle;
  const double SINE = sin(angle * M_PI / 180);
  const double COSINE = cos(angle * M_PI / 180);
  const suslov::point_t compositeCenter = getFrameRect().pos;
  for (int i = 0; i < size_; ++i)
  {
    const suslov::point_t shapeCenter = shapes_[i]->getFrameRect().pos;
    shapes_[i]->move({compositeCenter.x + (shapeCenter.x - compositeCenter.x) * COSINE - (shapeCenter.y - compositeCenter.y) * SINE,
      compositeCenter.y + (shapeCenter.y - compositeCenter.y) * COSINE + (shapeCenter.x - compositeCenter.x) * SINE});
    shapes_[i]->rotate(angle);
  }
}

void suslov::CompositeShape::addShape(const std::shared_ptr < suslov::Shape > shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Nullptr"); 
  }
  for (int i = 0; i < size_; ++i)
  {
    if (shape == shapes_[i])
    {
      throw std::invalid_argument("Shape is already added");
    }
  }
  std::unique_ptr < std::shared_ptr < suslov::Shape > [] > newShapes(new std::shared_ptr < suslov::Shape > [size_ +1]);
  for (int i = 0; i < size_; ++i)
  {
    newShapes[i] = shapes_[i];
  }
  newShapes[size_++] = shape;
  shapes_.swap(newShapes);
}

void suslov::CompositeShape::deleteShape(const int shapeNumber)
{
  if ((shapeNumber <= 0) || (shapeNumber >= size_))
  {
    throw std::invalid_argument("Invalide shape number");
  }
  if (size_ == 0)
  {
    throw std::invalid_argument("Empty composite shape");
  }
  else
  {
    std::unique_ptr < std::shared_ptr < suslov::Shape > [] > newShapes(new std::shared_ptr <suslov::Shape> [size_ - 1]);
    for (int i = 0; i < (shapeNumber - 1); ++i)
    {
      newShapes[i] = shapes_[i];
    }
    for (int i = shapeNumber; i < size_; ++i)
    {
      newShapes[i-1] = shapes_[i];
    }
    shapes_.swap(newShapes);
    --size_;
  }
}

void suslov::CompositeShape::deleteAllShapes() noexcept
{
  shapes_.reset();
  shapes_ = nullptr;
  size_ = 0;
  angle_ = 0.0;
}
