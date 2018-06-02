//
// Created by matvey on 30.04.18.
//
#include "composite-shape.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

russkov::CompositeShape::CompositeShape(const std::shared_ptr<russkov::Shape> shape_ptr):
  shapes_(nullptr),
  size_(0),
  alpha_(0.0)

{
  if (shape_ptr == nullptr)
  {
    throw std::invalid_argument("Error. Null pointer.");
  }

  addShape(shape_ptr);
}

russkov::CompositeShape::CompositeShape(const russkov::CompositeShape & obj):
  size_(obj.size_),
  alpha_(obj.alpha_)
{
  shapes_ = std::unique_ptr<std::shared_ptr<russkov::Shape>[]>(new std::shared_ptr<russkov::Shape>[size_]);
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i] = obj.shapes_[i];
  }
}

russkov::CompositeShape::CompositeShape(russkov::CompositeShape && obj):
  shapes_(std::move(obj.shapes_)),
  size_(obj.size_),
  alpha_(obj.alpha_)
{
  obj.size_ = 0;
  obj.shapes_ = nullptr;
}

russkov::CompositeShape &russkov::CompositeShape::operator =(const russkov::CompositeShape & obj)
{
  if (this != &obj)
  {
    size_ = obj.size_;
    shapes_.reset(new std::shared_ptr<russkov::Shape>[size_]);
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i] = obj.shapes_[i];
    }
  }
  return *this;
}

russkov::CompositeShape &russkov::CompositeShape::operator =(russkov::CompositeShape && obj)
{
 if (this == &obj)
 {
   return *this;
 }

 size_ = (obj.size_);
 shapes_ = std::move(obj.shapes_);
 alpha_ = (obj.alpha_);

 obj.size_ = 0;
 obj.shapes_ = nullptr;
 obj.alpha_ = 0.0;

 return *this;
}

std::shared_ptr<russkov::Shape> russkov::CompositeShape::operator [](size_t index)
{
  if(index >= size_)
  {
    throw std::out_of_range("CompositeShape index out of range");
  }

  return shapes_[index];
}

void russkov::CompositeShape::addShape(std::shared_ptr <russkov::Shape> shape_ptr)
{
  if (shape_ptr == nullptr)
  {
    throw std::invalid_argument("Error. Null pointer.");
  }

  std::unique_ptr<std::shared_ptr <russkov::Shape>[]> local_array(new std::shared_ptr<russkov::Shape>[size_+1]);
  for (size_t i = 0; i < size_; i++)
  {
    local_array[i] = shapes_[i];
  }
  local_array[size_++] = shape_ptr;
  shapes_.swap(local_array);
}

void russkov::CompositeShape::deleteShape(const size_t index)
{
  if (index >= size_)
  {
    throw std::invalid_argument("Error. Index is out of range.");
  }

  if (size_ == 0)
  {
    throw std::invalid_argument("Error. Container of shape is empty.");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> local_array(new std::shared_ptr<russkov::Shape>[size_ - 1]);
  for (size_t i = 0; i < index; i++)
  {
    local_array[i] = shapes_[i];
  }
  for (size_t i = index; i < size_ - 1; i++)
  {
    local_array[i] = shapes_[i + 1];
  }

  shapes_.swap(local_array);
  --size_;
}

double russkov::CompositeShape::getArea() const
{
  double area = 0.0;
  for (size_t i = 0; i < size_; i++)
  {
    area += shapes_[i] -> getArea();
  }
  return area;
}

russkov::rectangle_t russkov::CompositeShape::getFrameRect() const
{
  rectangle_t frameRect = shapes_[0] -> getFrameRect();
  double maxX = frameRect.pos.x + frameRect.width / 2;
  double minX = frameRect.pos.x - frameRect.width / 2;
  double maxY = frameRect.pos.y + frameRect.height / 2;
  double minY = frameRect.pos.y - frameRect.height / 2;
  for (size_t i = 1; i < size_; i++)
  {
    frameRect = shapes_[i] -> getFrameRect();
    if (maxX < frameRect.pos.x + frameRect.width / 2)
    {
      maxX = frameRect.pos.x + frameRect.width / 2;
    }
    if (minX > frameRect.pos.x - frameRect.width / 2)
    {
      minX = frameRect.pos.x - frameRect.width / 2;
    }
    if (maxY < frameRect.pos.y + frameRect.height / 2)
    {
      maxY = frameRect.pos.y + frameRect.height / 2;
    }
    if (minY > frameRect.pos.y - frameRect.height / 2)
    {
      minY = frameRect.pos.y - frameRect.height / 2;
    }
  }
  return {maxX - minX, maxY - minY, {(maxX + minX) / 2, (maxY + minY) / 2}};
}

void russkov::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i] -> move(dx, dy);
  }
}

void russkov::CompositeShape::move(const russkov::point_t &point)
{
  point_t center = getFrameRect().pos;
  double dx = point.x - center.x;
  double dy = point.y - center.y;
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i] -> move(dx, dy);
  }
}

void russkov::CompositeShape::scale(const double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("coefficient should be not negative");
  }
  point_t comp_shape_pos = getFrameRect().pos;
  for (size_t i =0; i < size_; i++)
  {
    point_t shape_pos = shapes_[i] -> getFrameRect().pos;
    shapes_[i] -> move(ratio * (shape_pos.x - comp_shape_pos.x), ratio * (shape_pos.y - comp_shape_pos.y));
    shapes_[i] -> scale(ratio);
  }
}

void russkov::CompositeShape::rotate(const double alpha)
{
  alpha_ += alpha;
  if (alpha_ > 360.0)
  {
    alpha_ = fmod(alpha_, 360.0);
  }
  point_t center = getFrameRect().pos;
  const double sinA = sin(alpha_ * M_PI / 180);
  const double cosA = cos(alpha_ * M_PI / 180);
  for (size_t i = 0; i < size_; i++)
  {
    russkov::point_t shapePos = shapes_[i] -> getFrameRect().pos;
    double newX = center.x + (shapePos.x - center.x) * cosA - (shapePos.y - center.y) * sinA;
    double newY = center.y + (shapePos.x - center.x) * sinA + (shapePos.y - center.y) * cosA;
    shapes_[i] -> move({newX, newY});
    shapes_[i] -> rotate(alpha);
  }
}
