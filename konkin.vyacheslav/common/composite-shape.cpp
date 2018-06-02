#include "composite-shape.hpp"

#include <stdexcept>
#include <iostream>
#include <cmath>

using namespace konkin;

CompositeShape::CompositeShape():
  size_(0u),
  shapes_(nullptr)
{}


CompositeShape::CompositeShape(const CompositeShape & rhs):
  size_(rhs.size_),
  shapes_((rhs.size_ != 0u) ? new ptr_type[rhs.size_] : nullptr)
{
  for (size_t i = 0; i < size_; ++i)
  {
    shapes_[i] = rhs.shapes_[i];
  }
}

CompositeShape::CompositeShape(CompositeShape && rhs):
  size_(rhs.size_),
  shapes_(std::move(rhs.shapes_))
{
  rhs.size_ = 0u;
  rhs.shapes_ = nullptr;
}

CompositeShape & CompositeShape::operator =(const CompositeShape & rhs)
{
  if (this == &rhs)
  {
    return *this;
  }

  std::unique_ptr<ptr_type[]> new_data( (rhs.size_ != 0) ? new ptr_type[rhs.size_] : nullptr);

  for (size_t i = 0u; i < rhs.size_; ++i)
  {
    new_data[i] = rhs.shapes_[i];
  }
  size_ = rhs.size_;
  shapes_.swap(new_data);

  return *this;
}


CompositeShape & CompositeShape::operator =(CompositeShape && rhs)
{
  if (this == &rhs)
  {
    return *this;
  }

  size_ = rhs.size_;
  shapes_ = std::move(rhs.shapes_);

  rhs.size_ = 0u;
  rhs.shapes_ = nullptr;

  return *this;
}


size_t CompositeShape::size() const
{
  return size_;
}


CompositeShape::ptr_type CompositeShape::operator [](size_t index) const
{
  if(index >= size_)
  {
    throw std::out_of_range("CompositeShape index out of range");
  }

  return shapes_[index];
}

void CompositeShape::addShape(const ptr_type & shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid pointer!");
  }
  std::unique_ptr< ptr_type[]> shapes_new(new ptr_type[size_ + 1]);

  for (size_t i = 0; i < size_; ++i)
  {
    shapes_new[i]=std::move(shapes_[i]);
  }
  shapes_new[size_++] = shape;
  shapes_.swap(shapes_new);
}



void CompositeShape::removeShape(size_t index)
{
  if(index >= size_)
  {
      throw std::out_of_range("CompositeShape index out of range");
  }
  for(size_t i = index + 1; i < size_; i++)
  {
      shapes_[i - 1] = std::move(shapes_[i]);
  }
  shapes_[--size_] = nullptr;
}


double CompositeShape::getArea() const noexcept
{
  double shapesArea = 0.0;

  for (size_t i = 0; i < size_; ++i)
  {
    shapesArea += shapes_[i] -> getArea();
  }

  return shapesArea;
}


rectangle_t CompositeShape::getFrameRect() const noexcept
{
  if (size_ == 0)
  {
    return {0.0, 0.0,{0.0, 0.0}};
  }
  rectangle_t rect = shapes_[0] -> getFrameRect();

  double xMax = rect.pos.x + rect.width/2,
  yMax = rect.pos.y + rect.height/2,
  xMin = rect.pos.x - rect.width/2,
  yMin = rect.pos.y - rect.height/2;

  for (size_t i = 1; i < size_; ++i)
  {
    rect = shapes_[i] -> getFrameRect();
    xMax = std::max(xMax, rect.pos.x + rect.width/2);
    yMax = std::max(yMax, rect.pos.y + rect.height/2);
    xMin = std::min(xMin, rect.pos.x - rect.width/2);
    yMin = std::min(yMin, rect.pos.y - rect.height/2);
}
  return {xMax - xMin, yMax - yMin,{(xMax + xMin)/2, (yMax + yMin)/2}};
}


void CompositeShape::move(const point_t & resPoint) noexcept
{
  std::cout << "movetopoint";
  point_t center = getFrameRect().pos;

  for (size_t i = 0; i < size_; ++i)
  {
    shapes_[i] -> move( resPoint.x - center.x, resPoint.y - center.y);
  }
}


void CompositeShape::move(const double dx, const double dy) noexcept
{
  for (size_t i = 0; i < size_; ++i)
  {
    shapes_[i] -> move(dx, dy);
  }
}


void CompositeShape::scale(const double value)
{
  if (value < 0)
  {
    throw std::invalid_argument("Invalid scaling value!");
  }

  point_t center = getFrameRect().pos;

  for (size_t i = 0; i < size_; ++i)
  {
    point_t shape_center = shapes_[i] -> getFrameRect().pos;
    shapes_[i] -> scale(value);
    shapes_[i] -> move((shape_center.x - center.x) * (value - 1), (shape_center.y - center.y) * (value - 1));
  }
}

