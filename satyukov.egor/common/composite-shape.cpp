#include "composite-shape.hpp"

#include <memory>
#include <stdexcept>
#include <math.h>

satyukov::CompositeShape::CompositeShape(const std::shared_ptr < satyukov::Shape > newShape):
  list_(nullptr),
  size_(0),
  angle_(0.0)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Null pointer");
  }
  addShape(newShape);
}

satyukov::CompositeShape::CompositeShape(const satyukov::CompositeShape & compositeShape):
  list_(new std::shared_ptr < satyukov::Shape >[compositeShape.size_]),
  size_(compositeShape.size_),
  angle_(compositeShape.angle_)
{
  for (int i = 0; i < size_; ++i)
  {
    list_[i] = compositeShape.list_[i];
  }
}

satyukov::CompositeShape::CompositeShape(satyukov::CompositeShape && compositeShape):
  list_(nullptr),
  size_(compositeShape.size_),
  angle_(compositeShape.angle_)
{
  list_.swap(compositeShape.list_);
  compositeShape.clear();
}

satyukov::CompositeShape::~CompositeShape()
{
  clear();
}

satyukov::CompositeShape & satyukov::CompositeShape::operator =(const satyukov::CompositeShape & compositeShape)
{
  if (this != & compositeShape)
  {
    size_ = compositeShape.size_;
    angle_ = compositeShape.angle_;
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > 
        newList (new std::shared_ptr < satyukov::Shape >[compositeShape.size_]);
    for (int i = 0; i < size_; ++i)
    {
      newList[i] = compositeShape.list_[i];
    }
    list_.swap(newList);
  }
  return *this;
}

satyukov::CompositeShape & satyukov::CompositeShape::operator =(satyukov::CompositeShape && compositeShape)
{
  if (this != & compositeShape)
  {
    size_ = compositeShape.size_;
    angle_ = compositeShape.angle_;
    list_.swap(compositeShape.list_);
    compositeShape.clear();
  }
  return *this;
}

bool satyukov::CompositeShape::operator ==(const satyukov::CompositeShape & compositeShape) const
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

bool satyukov::CompositeShape::operator !=(const satyukov::CompositeShape & compositeShape) const
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

double satyukov::CompositeShape::getArea() const noexcept
{
  double area = 0;
  for (int i = 0; i < size_; ++i)
  {
    area += list_[i]->getArea();
  }
  return area;
}

double satyukov::CompositeShape::getAngle() const noexcept
{
  return angle_;
}

satyukov::point_t satyukov::CompositeShape::getCoordinates() const noexcept
{
  return getFrameRect().pos;
}

satyukov::rectangle_t satyukov::CompositeShape::getFrameRect() const noexcept
{
  if (size_ == 0)
  {
    return { { 0.0, 0.0 }, 0.0, 0.0 };
  }
  else
  {
    satyukov::rectangle_t frameRect = list_[0]->getFrameRect();
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
    return { { (left + right) / 2.0, (bottom + top) / 2.0 }, (right - left), (top - bottom) };
  }
}

void satyukov::CompositeShape::move(const satyukov::point_t & newPos) noexcept
{
  const satyukov::point_t curPos = getFrameRect().pos;
  move(newPos.x - curPos.x, newPos.y - curPos.y);
}

void satyukov::CompositeShape::move(const double dx, const double dy) noexcept
{ 
  for (int i = 0; i < size_; ++i)
  {
    list_[i]->move(dx, dy);
  }
}

void satyukov::CompositeShape::scale(const double coefficient)
{
  if (coefficient <= 0.0)
  {
    throw std::invalid_argument("Invalid coefficient");
  }
  const satyukov::point_t curPos = getCoordinates();
  for (int i = 0; i < size_; ++i)
  {
    const satyukov::point_t shapePos = list_[i]->getCoordinates();
    list_[i]->move({ curPos.x + coefficient * (shapePos.x - curPos.x), 
        curPos.y + coefficient * (shapePos.y - curPos.y) });
    list_[i]->scale(coefficient);
  }
}

void satyukov::CompositeShape::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (abs(angle_) >= 360.0)
  {
    angle_ = std::fmod(angle_, 360.0);
  }
  const double sine = sin(angle_ * M_PI / 180.0);
  const double cosine = cos(angle_ * M_PI / 180.0);
  const satyukov::point_t curPos = getCoordinates();
  for (int i = 0; i < size_; ++i)
  {
    const satyukov::point_t shapePos = list_[i]->getCoordinates();
    list_[i]->move({ curPos.x + cosine * (shapePos.x - curPos.x) - sine * (shapePos.y - curPos.y), 
        curPos.y + cosine * (shapePos.y - curPos.y) + sine * (shapePos.x - curPos.x) });
    list_[i]->rotate(angle);
  }
}

void satyukov::CompositeShape::addShape(const std::shared_ptr < satyukov::Shape > newShape)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Null pointer");
  }
  for (int i = 0; i < size_; ++i)
  {
    if (newShape == list_[i])
    {
      throw std::invalid_argument("This shape is already added in Composite Shape");
    }
  }
  std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > 
      newList (new std::shared_ptr < satyukov::Shape >[size_ + 1]);
  for (int i = 0; i < size_; ++i)
  {
    newList[i] = list_[i];
  }
  newList[size_++] = newShape;
  list_.swap(newList);
}

std::shared_ptr < satyukov::Shape > satyukov::CompositeShape::getShape(int const index) const
{
  if (size_ == 0)
  {
    throw std::out_of_range("Composite Shape is empty");
  }
  if ((index < 0) || (index > size_ - 1))
  {
    throw std::invalid_argument("Invalid index");
  }
  return list_[index];
}

void satyukov::CompositeShape::removeShape(const int index)
{
  if (size_ == 0)
  {
    throw std::out_of_range("Composite Shape is empty");
  }
  if ((index < 0) || (index > size_ - 1))
  {
    throw std::invalid_argument("Invalid index");
  }
  std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > 
      newList (new std::shared_ptr < satyukov::Shape >[size_ - 1]);
  for (int i = 0; i < index; ++i)
  {
    newList[i] = list_[i];
  }
  for (int i = index; i < size_ - 1; ++i)
  {
    newList[i] = list_[i + 1];
  }
  list_.swap(newList);
  --size_;
}

void satyukov::CompositeShape::clear() noexcept
{
  list_.reset();
  list_ = nullptr;
  size_ = 0;
  angle_ = 0.0;
}

int satyukov::CompositeShape::getSize() const noexcept
{
  return size_;
}
