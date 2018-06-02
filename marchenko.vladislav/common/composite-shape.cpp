#include "composite-shape.hpp"

#include <stdexcept>
#include <iostream>


marchenko::CompositeShape::CompositeShape() :
  parts_(nullptr),
  size_(0)
{
}

marchenko::CompositeShape::CompositeShape(const std::shared_ptr<Shape> & obj) :
  parts_(new std::shared_ptr<Shape>[1]),
  size_(0)
{
  if (obj == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  parts_[size_++] = obj;
}

marchenko::CompositeShape::CompositeShape(const CompositeShape & obj) :
  parts_(new std::shared_ptr<Shape>[obj.size_]),
  size_(obj.size_)
{
  for (size_t i = 0; i < obj.size_; i++)
  {
    parts_[i] = obj.parts_[i];
  }
}

marchenko::CompositeShape::CompositeShape(CompositeShape && obj):
  size_(obj.size_)
{
  parts_ = std::move(obj.parts_);
  obj.size_ = 0;
  obj.parts_.reset();
}

marchenko::CompositeShape & marchenko::CompositeShape::operator= (const CompositeShape & elem) noexcept
{
  if (this != &elem)
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> buf(new std::shared_ptr<Shape>[elem.size_]);
    for (size_t i = 0; i < elem.size_; i++)
    {
      buf[i] = elem.parts_[i];
    }
    parts_.swap(buf);
    size_ = elem.size_;
  }
  return *this;
}

marchenko::CompositeShape & marchenko::CompositeShape::operator= (CompositeShape && elem)
{
  parts_ = std::move(elem.parts_);
  size_ = elem.size_;
  elem.size_ = 0;
  return *this;
}

std::shared_ptr<marchenko::Shape> marchenko::CompositeShape::operator [] (const size_t ind) const
{
  if ((ind >= size_) )
  {
    throw std::out_of_range("ind is out of range");
  }
  return parts_[ind];
}

void marchenko::CompositeShape::addShape(const std::shared_ptr<Shape> & obj)
{
  if (obj == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> newArray(new std::shared_ptr<Shape> [size_ + 1]);
  for (size_t i = 0; i < size_; i++)
  {
    newArray[i] = parts_[i];
  }
  newArray[size_] = obj;
  size_++;
  parts_.swap(newArray);
}

void marchenko::CompositeShape::deleteShape (const size_t ind)
{
  if (ind >= size_)
  {
    throw std::out_of_range("Invalid index");
  }
  if ((size_ == 1) && (ind == 0))
  {
    parts_.reset();
    size_ = 0;
    return;
  }
  std::unique_ptr<std::shared_ptr <Shape >[]> newArray(new std::shared_ptr<Shape> [size_ - 1]);
  for (size_t i = 0; i < ind; i++)
  {
    newArray[i] = parts_[i];
  }
  for (size_t i = ind; i < size_ - 1; ++i)
  {
    newArray[i] = parts_[i + 1];
  }
  parts_.swap(newArray);
  size_--;
}

double marchenko::CompositeShape::getArea() const
{
  double commonArea = 0;
  for (size_t i = 0; i < size_; i++)
  {
    commonArea += parts_[i] -> getArea();
  }
  return commonArea;
}

marchenko::rectangle_t marchenko::CompositeShape::getFrameRect() const
{
  if (size_ <= 0)
  {
    return { 0.0 , 0.0, {0.0 , 0.0}};
  }
  marchenko::rectangle_t frameRect = parts_[0] -> getFrameRect();
  double minX = frameRect.pos.x - frameRect.width / 2;
  double maxX = frameRect.pos.x + frameRect.width / 2;
  double maxY = frameRect.pos.y + frameRect.height / 2;
  double minY = frameRect.pos.y - frameRect.height / 2;
  for (size_t i = 1; i < size_; i++)
  {
    frameRect = parts_[i]->getFrameRect();
    if ((frameRect.pos.x - frameRect.width / 2) < minX)
    {
      minX = frameRect.pos.x - frameRect.width / 2;
    }
    if ((frameRect.pos.x + frameRect.width / 2) > maxX)
    {
      maxX = frameRect.pos.x + frameRect.width / 2;
    }
    if ((frameRect.pos.y + frameRect.height / 2) > maxY)
    {
      maxY = frameRect.pos.y + frameRect.height / 2;
    }
    if ((frameRect.pos.y - frameRect.height / 2) < minY)
    {
      minY = frameRect.pos.y - frameRect.height / 2;
    }
  }
  return {(maxX - minX), (maxY - minY), {(minX + (maxX - minX) / 2), (minY + (maxY - minY) / 2)}};
}

void marchenko::CompositeShape::move(const point_t & newPos)
{
  move(newPos.x - getFrameRect().pos.x, newPos.y - getFrameRect().pos.y);
}

void marchenko::CompositeShape::move(const double dx, const double dy)
{
  for (size_t i = 0; i < size_; i++)
  {
    parts_[i] -> move(dx, dy);
  }
}

void marchenko::CompositeShape::scale(const double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Invalid coefficient");
  }
  marchenko::point_t startedShapePos = getFrameRect().pos;
  for (size_t i = 0; i < size_; i++)
  {
    marchenko::point_t shapePos = parts_[i] -> getFrameRect().pos;
    parts_[i] -> move((coefficient - 1.0) * (shapePos.x - startedShapePos.x),
      (coefficient - 1.0)* (shapePos.y - startedShapePos.y));
    parts_[i] -> scale(coefficient);
  }
}

size_t marchenko::CompositeShape::getSize() const
{
  return size_;
}
