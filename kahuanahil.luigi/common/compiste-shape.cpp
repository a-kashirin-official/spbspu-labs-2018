#include "composite-shape.hpp"
#include <stdexcept>
#include <math.h>

kahuanahil::CompositeShape::CompositeShape(std::shared_ptr < kahuanahil::Shape > nshape) : 
  list_(nullptr),
  size_(0),
  angle_(0.0)
{
  if (nshape == nullptr)
  {
    throw std::invalid_argument("Error");
  }
  addShape(nshape);
}

kahuanahil::CompositeShape::CompositeShape(const CompositeShape & compositeShape):
  list_(new std::shared_ptr < kahuanahil::Shape > [compositeShape.size_]),
  size_(compositeShape.size_),
  angle_(compositeShape.angle_)
{
  for (int i = 0; i < size_; ++i)
  {
    list_[i] = compositeShape.list_[i];
  }
}

kahuanahil::CompositeShape::CompositeShape(CompositeShape && compositeShape):
  list_(nullptr),
  size_(compositeShape.size_),
  angle_(compositeShape.angle_)
{
  list_.swap(compositeShape.list_);
  compositeShape.deleteAllShape();
}

kahuanahil::CompositeShape::~CompositeShape()
{
  deleteAllShape();
}

kahuanahil::CompositeShape & kahuanahil::CompositeShape::operator = (const kahuanahil::CompositeShape & compositeShape)
{
  if(this != &compositeShape)
  {
    size_ = compositeShape.size_;
    angle_ = compositeShape.angle_;
    std::unique_ptr < std::shared_ptr < kahuanahil::Shape >[] > newShapes(new std::shared_ptr < kahuanahil::Shape > [compositeShape.size_]);
    for (int i = 0; i < size_; ++i)
    {
      newShapes[i] = compositeShape.list_[i];
    }
    list_.swap(newShapes);
  }
  return *this;
}

kahuanahil::CompositeShape & kahuanahil::CompositeShape::operator = (CompositeShape && compositeShape)
{
  if (this != & compositeShape)
  {
    size_ = compositeShape.size_;
    angle_ = compositeShape.angle_;
    list_.swap(compositeShape.list_);
    compositeShape.deleteAllShape();
  }
  return *this;
}

bool kahuanahil::CompositeShape::operator==(const kahuanahil::CompositeShape & compositeShape) const
{
  if ((this->size_ != compositeShape.size_) || (this->angle_ != compositeShape.angle_))
  {
    return false;
  }
  for (int i = 0; i < size_; ++i)
    {
      if (this->list_[i] != compositeShape.list_[i])
      {
        return false;
      }
    }
  return true;
}

bool kahuanahil::CompositeShape::operator!=(const kahuanahil::CompositeShape & compositeShape) const
{
  if ((this->size_ != compositeShape.size_) || (this->angle_ != compositeShape.angle_))
  {
    return true;
  }
  for (int i = 0; i < size_; ++i)
    {
      if (this->list_[i] != compositeShape.list_[i])
      {
        return true;
      }
    }
  return false;
}

void kahuanahil::CompositeShape::addShape(const std::shared_ptr < kahuanahil::Shape > nshape)
{
  if (nshape == nullptr)
  {
    throw std::invalid_argument("Error");
  }
  for (int i = 0; i < size_; i++)
  {
    if (nshape == list_[i])
    {
      throw std::invalid_argument("Is already added");
    }
  }
  std::unique_ptr< std::shared_ptr < kahuanahil::Shape > [] > new_array(new std::shared_ptr < kahuanahil::Shape > [size_+1]);
  for (int i = 0; i < size_; i++)
  {
    new_array[i] = list_[i];
  }
  new_array[size_++] = nshape;
  list_.swap(new_array);
}

void kahuanahil::CompositeShape::deleteShape(const int index)
{
  if (size_ <= 0)
  {
    throw std::invalid_argument("Error. List is empty.");
  }
  if (index >= size_)
  {
    throw std::invalid_argument("Index out of range.");
  }
  if (size_ == 1)
  {
    list_.reset();
    list_ = nullptr;
    size_ = 0;
    return;
  }
  else
  {
  std::unique_ptr<std::shared_ptr < kahuanahil::Shape > [] > new_array(new std::shared_ptr < kahuanahil::Shape > [size_ -1]);
  for (int i = 0; i < (index - 1); ++i)
  {
    new_array[i] = list_[i];
  }
  for (int i = index; 1 < size_; ++i)
  {
    new_array[i-1] = list_[i];
  }
  list_.swap(new_array);
  --size_;
  }
}

kahuanahil::rectangle_t kahuanahil::CompositeShape::getFrameRect() const noexcept
{
  if (size_ == 0)
  {
    return { 0.0, 0.0, { 0.0, 0.0 }};
  }
  else
  {
    kahuanahil::rectangle_t frameRect = list_[0]->getFrameRect();
    double left = frameRect.pos.x - frameRect.width / 2.0;
    double right = frameRect.pos.x + frameRect.width / 2.0;
    double bottom = frameRect.pos.y - frameRect.height / 2.0;
    double top = frameRect.pos.y + frameRect.height / 2.0;
    for (int i = 1; i < size_; ++i)
    {
      frameRect = list_[i]->getFrameRect();
      double newLeft = frameRect.pos.x - frameRect.width / 2.0;
      double newRight = frameRect.pos.x + frameRect.width / 2.0;
      double newBottom = frameRect.pos.y - frameRect.height / 2.0;
      double newTop = frameRect.pos.y + frameRect.height / 2.0;
      if (newLeft < left)
      {
        left = newLeft;
      }
      if (newRight > right)
      {
        right = newRight;
      }
      if (newBottom < bottom)
      {
        bottom = newBottom;
      }
      if (newTop > top)
      {
        top = newTop;
      }
    }
    return {(right - left), (top - bottom), { (left + right) / 2.0, (bottom + top) / 2.0 }};
  }
}

void kahuanahil::CompositeShape::move(const point_t &pos) noexcept
{
  move(pos.x - getFrameRect().pos.x, pos.y - getFrameRect().pos.y);
}

void kahuanahil::CompositeShape::move(const double dx, const double dy) noexcept
{
  for (int i = 0; i < size_; i++)
  {
    list_[i]->move(dx, dy);
  }
}

double kahuanahil::CompositeShape::getArea() const noexcept
{
  double Area = 0.0;
  for (int i = 0; i < size_; i++)
  {
    Area += list_[i] -> getArea();
  }
  return Area;
}

kahuanahil::point_t kahuanahil::CompositeShape::getCenter() const noexcept
{
  return getFrameRect().pos;
}

void kahuanahil::CompositeShape::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Error. Invalid Scale");
  }
  point_t composite_shape_pos = getFrameRect().pos;
  for (int i = 0; i < size_; i++)
  {
    point_t shape_pos = list_[i] -> getFrameRect().pos;
    list_[i] -> move((factor - 1) * (shape_pos.x - composite_shape_pos.x), (factor - 1) * (shape_pos.y - composite_shape_pos.y));
    list_[i] -> scale(factor);
  }
}

void kahuanahil::CompositeShape::rotate(const double angle) noexcept
{
  angle_ += angle;
  const double SIN = sin(angle * M_PI / 180);
  const double COS = cos(angle * M_PI / 180);
  const kahuanahil::point_t compositeCenter = getFrameRect().pos;
  for (int i = 0; i < size_; ++i)
  {
    const kahuanahil::point_t shapeCenter = list_[i]->getFrameRect().pos;
    list_[i]->move({compositeCenter.x + (shapeCenter.x - compositeCenter.x) * COS - (shapeCenter.y - compositeCenter.y) * SIN,
      compositeCenter.y + (shapeCenter.y - compositeCenter.y) * COS + (shapeCenter.x - compositeCenter.x) * SIN});
    list_[i]->rotate(angle);
  }
}

double kahuanahil::CompositeShape::getAngle() const
{
  return angle_;
}

void kahuanahil::CompositeShape::deleteAllShape() noexcept
{
  list_.reset();
  list_ = nullptr;
  size_ = 0;
  angle_ = 0.0;
}
