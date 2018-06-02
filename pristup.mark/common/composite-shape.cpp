#include <iostream>
#include <stdexcept>

#include "composite-shape.hpp"

pristup::CompositeShape::CompositeShape(Shape * shapeElement):
  shapes_(new Shape *[1]),
  shapeAmount_(0)
{
  if (shapeElement == nullptr)
  {
    shapes_.reset();
    throw std::invalid_argument("object doesn't exist");
  }
  shapes_[0] = shapeElement;
  shapeAmount_++;
}

void pristup::CompositeShape::addShape(Shape * shapeElement)
{
  if (shapeElement == nullptr)
  {
    throw std::invalid_argument("object doesn't exist");
  }
  std::unique_ptr<Shape *[]> new_arr(new Shape *[shapeAmount_ + 1]);
  for (size_t i = 0; i < shapeAmount_; i++)
  {
    new_arr[i] = shapes_[i];
  }
  new_arr[shapeAmount_] = shapeElement;
  shapeAmount_++;
  shapes_.swap(new_arr);
}

void pristup::CompositeShape::delShape(const size_t index)
{
  if (shapeAmount_ <= 0)
  {
    throw std::out_of_range("list of shapes is empty");
  }
  if (index >= shapeAmount_)
  {
    throw std::out_of_range("index is out of range");
  }
  if ((shapeAmount_ == 1) && (index == 0))
  {
    shapes_.reset();
    shapeAmount_ = 0;
    return;
  }
  std::unique_ptr<Shape *[]> new_arr(new Shape *[shapeAmount_ - 1]);
  for (size_t i = 0; i < index; i++)
  {
    new_arr[i] = shapes_[i];
  }
  for (size_t i = index; i < shapeAmount_ - 1; ++i)
  {
    new_arr[i] = shapes_[i + 1];
  }
  shapes_.swap(new_arr);
  shapeAmount_--;
}


double pristup::CompositeShape::getArea() const noexcept
{
  double totalArea = 0.0;
  for (size_t i = 0; i < shapeAmount_; i++)
  {
    totalArea += shapes_[i] -> getArea();
  }
  return totalArea;
}

pristup::rectangle_t pristup::CompositeShape::getFrameRect() const noexcept
{
  rectangle_t frameRect = shapes_[0] -> getFrameRect();
    
  double maxX = frameRect.pos.x + frameRect.width / 2;
  double minX = frameRect.pos.x - frameRect.width / 2;
  double maxY = frameRect.pos.y + frameRect.height / 2;
  double minY = frameRect.pos.y - frameRect.height / 2;
    
  for (size_t i = 1; i < shapeAmount_; i++)
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

void pristup::CompositeShape::move(const point_t & p) noexcept
{
  move(p.x - getFrameRect().pos.x, p.y - getFrameRect().pos.y);
}

void pristup::CompositeShape::move(double dx, double dy) noexcept
{
  for (size_t i = 0; i < shapeAmount_; i++)
  {
    shapes_[i] -> move(dx, dy);
  }
}

void pristup::CompositeShape::scale(double k)
{
    if (k < 0.0)
    {
        throw std::invalid_argument("invalid scaling coefficient");
    }
    
    point_t comp_shapePos = getFrameRect().pos;
    for (size_t i = 0; i < shapeAmount_; i++)
    {
        point_t shapePos = shapes_[i] -> getFrameRect().pos;
        shapes_[i] -> move((k - 1) * (shapePos.x - comp_shapePos.x), (k - 1) * (shapePos.y - comp_shapePos.y));
        shapes_[i] -> scale(k);
    }
}


