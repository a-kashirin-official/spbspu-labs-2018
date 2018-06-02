#include <stdexcept>
#include "composite-shape.hpp"

using namespace iliintsev;

CompositeShape::CompositeShape():
  size_(0),
  shapes_(nullptr)
{
}

CompositeShape::CompositeShape(std::shared_ptr<Shape> &shape):
  size_(0),
  shapes_(nullptr)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("error, we can't add empty shape");
  }
  add(shape);
}

CompositeShape::CompositeShape(const CompositeShape & comp_shape):
  size_(comp_shape.size_),
  shapes_(new std::shared_ptr<Shape>[comp_shape.size_])
{
  for(int i = 0; i < size_; ++i)
  {
    shapes_[i] = comp_shape.shapes_[i];  
  }
}

CompositeShape::CompositeShape(CompositeShape && comp_shape):
  size_(comp_shape.size_)
{
  shapes_ = std::move(comp_shape.shapes_);
  comp_shape.shapes_ = (nullptr);
  comp_shape.size_ = 0;
}

CompositeShape::~CompositeShape()
{
}

CompositeShape & CompositeShape::operator = (const CompositeShape & comp_shape)
{
  if (this == & comp_shape)
  {
    return * this;
  }
  size_ = comp_shape.size_;
  shapes_.reset(new std::shared_ptr<Shape>[size_] );
  for (int i = 0; i < size_; ++i)
  {
    shapes_[i] = comp_shape.shapes_[i];
  }
  return * this;
}

CompositeShape & CompositeShape::operator = (CompositeShape && comp_shape)
{
  if (this == & comp_shape)
  {
    return * this;
  }
  size_ = comp_shape.size_;
  shapes_.reset(new std::shared_ptr<Shape>[size_]);
  shapes_ = std::move(comp_shape.shapes_);
  comp_shape.shapes_ = (nullptr);
  comp_shape.size_ = 0;
  return * this;
}

std::shared_ptr<Shape> & CompositeShape::operator [](int index)
{
  if(index < 0)
  {
    throw std::invalid_argument("error, index can't be < 0 ");
  }
  if(index >= size_)
  {
    throw std::invalid_argument("error, index can't be > Size ");
  }
  return shapes_[index];
}



double CompositeShape::getArea() const noexcept
{
  double totalArea = 0.0;
  for(int i = 0 ; i<size_; i++)
  {
    totalArea += shapes_[i]->getArea();
  }
  return totalArea;
}

rectangle_t CompositeShape::getFrameRect() const noexcept
{
    if (size_ == 0)
  {
    return rectangle_t{{0, 0}, 0, 0 };
  }
  rectangle_t buf_rect = shapes_[0]->getFrameRect();
  double left = buf_rect.pos.x - buf_rect.width / 2;
  double right = buf_rect.pos.x + buf_rect.width / 2;
  double top = buf_rect.pos.y + buf_rect.height / 2;
  double bottom = buf_rect.pos.y - buf_rect.height / 2;
  for (int i = 1; i < size_; i++)
  {
    buf_rect = shapes_[i]->getFrameRect();
    double buf_left = buf_rect.pos.x - buf_rect.width / 2;
    double buf_right = buf_rect.pos.x + buf_rect.width / 2;
    double buf_top = buf_rect.pos.y + buf_rect.height / 2;
    double buf_bottom = buf_rect.pos.y - buf_rect.height / 2;

    if (buf_left < left)
    {
      left = buf_left;
    }
    if (buf_right > right)
    {
      right = buf_right;
    }
    if (buf_top > top)
    {
      top = buf_top;
    }
    if (buf_bottom < bottom)
    {
      bottom = buf_bottom;
    }
  }
  return rectangle_t{ { ((left + right) / 2.0), ((top + bottom) / 2.0) }, (right - left), (top - bottom) };
}

void CompositeShape::move(const point_t & new_center) noexcept
{
  const point_t center = getCenter();
  double dx = new_center.x-center.x;
  double dy = new_center.y-center.y;
  for (int i = 0; i < size_; i++)
  {
    shapes_[i]->move(dx,dy);
  }
}

void CompositeShape::move(double dx, double dy) noexcept
{
  for (int i = 0; i < size_; i++)
  {
    shapes_[i]->move(dx, dy);
  }
}

void CompositeShape::scale(const double koef) 
{
  point_t comp_center = getCenter();
  for (int i = 0; i < size_; i++)
  {
    point_t shape_center = shapes_[i]->getCenter();
    double dx = shape_center.x-comp_center.x;
    double dy = shape_center.y-comp_center.y;
    point_t new_center = {comp_center.x + koef * dx, comp_center.y + koef * dy};
    shapes_[i]->move(new_center);
    shapes_[i]->scale(koef);
  }
}

point_t CompositeShape::getCenter() const noexcept
{
  return getFrameRect().pos;
}

void CompositeShape::add(const std::shared_ptr<Shape> & shape)
{
  std::unique_ptr<std::shared_ptr<Shape> [] >buf;
  buf = std::move(shapes_);
  shapes_.reset(new std::shared_ptr< Shape >[size_ + 1]);
  shapes_[size_] = shape;
  size_++;
  for (int i = 0; i < size_ - 1; i++)
  {
    shapes_[i] = buf[i];
  }
}

void CompositeShape::remove(int index) 
{
  if (index < 0)
  {
    throw std::invalid_argument("error, index can't be < 0 ");
  }
  if (index >= size_)
  {
    throw std::invalid_argument("error, index can't be > Size ");
  }
  for (int i = index; i <= size_ - 2; i++)
  {
    shapes_[i] = shapes_[i + 1];
  }
  shapes_[size_ - 1] = nullptr;
  size_--;
}

int CompositeShape::getSize() const noexcept
{
  return size_;
}

void CompositeShape::clear() noexcept
{
  size_ = 0;
  shapes_ = nullptr;
}
