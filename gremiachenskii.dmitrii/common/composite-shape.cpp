#include "composite-shape.hpp"

#include <stdexcept>
#include <iostream>
#include <cmath>

using namespace gremiachenskii;

CompositeShape::CompositeShape(const std::shared_ptr<Shape> & object):
  size_(0),
  elements_(nullptr)
{
  if (object == nullptr)
  {
    elements_.reset();
    throw std::invalid_argument("ERROR: Invalid pointer");
  }
  addElement(object);
}

CompositeShape::CompositeShape(const CompositeShape & object):
  size_(0),
  elements_(new std::shared_ptr<Shape>[object.size_])
{
  for (size_t i = 0; i < object.size_; i++)
  {
    elements_[i] = object.elements_[i];
  }
  size_ = object.size_;
}

CompositeShape::CompositeShape(CompositeShape && object):
  size_(0)
{
  elements_ = std::move(object.elements_),
  size_ = object.size_;
  object.size_ = 0;
  object.elements_.reset();
}

std::shared_ptr<Shape> CompositeShape::operator [] (size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("ERROR: Index is out of range");
  }
  return elements_[index];
}

void CompositeShape::addElement(const std::shared_ptr<Shape> & object)
{
  if (object == nullptr)
  {
    throw std::invalid_argument("ERROR: Invalid pointer");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> newArray(new std::shared_ptr<Shape> [size_ + 1]); 
  for (size_t i = 0; i < size_; i++)
  {
    newArray[i] = elements_[i];
  }
  newArray[size_] = object;
  size_++;
  elements_.swap(newArray);
}

void CompositeShape::removeElement(size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("ERROR: Index is out of range");
  }
  if ((size_ == 1) && (index == 0))
  {
    elements_.reset();
    size_ = 0;
    return;
  }
  std::unique_ptr<std::shared_ptr <Shape >[]> newArray(new std::shared_ptr<Shape> [size_ - 1]);
  for (size_t i = 0; i < index; i++)
  {
    newArray[i] = elements_[i];
  }
  for (size_t i = index; i < size_ - 1; ++i)
  {
    newArray[i] = elements_[i + 1];
  }
  elements_.swap(newArray);
  size_--;
}

CompositeShape & CompositeShape::operator= (const CompositeShape & object)
{
  if (this == & object)
  {
    return *this;
  }
  std::unique_ptr <std::shared_ptr<Shape>[]> newArray(new std::shared_ptr<Shape>[size_]);
  size_ = object.size_;
  for (size_t i = 0; i < size_; i++)
  {
    newArray[i] = object.elements_[i];
  }
  elements_.swap(newArray);
  return *this;
}

CompositeShape & CompositeShape::operator= (CompositeShape && object)
{
  size_ = object.size_;
  elements_ = std::move(object.elements_);
  object.size_ = 0;
  return *this;
}

double CompositeShape::getArea() const noexcept
{
  double commonArea = 0;
  for (size_t i = 0; i < size_; i++)
  {
    commonArea += elements_[i] -> getArea();
  }
  return commonArea;
}

rectangle_t CompositeShape::getFrameRect() const noexcept
{
  if (size_ <= 0)
  {
    return { {0.0 , 0.0}, 0.0 , 0.0 };
  }

  rectangle_t frameRect = elements_[0] -> getFrameRect();
  double minX = frameRect.pos.x - frameRect.width / 2;
  double maxX = frameRect.pos.x + frameRect.width / 2;
  double maxY = frameRect.pos.y + frameRect.height / 2;
  double minY = frameRect.pos.y - frameRect.height / 2;

  for (size_t i = 1; i < size_; i++)
  {
    frameRect = elements_[i]->getFrameRect();
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
  return { {(minX + maxX) / 2, (minY + maxY) / 2}, (maxY - minY), (maxX - minX) };
}

void CompositeShape::move(const point_t & pos) noexcept
{
  move(pos.x - getFrameRect().pos.x, pos.y - getFrameRect().pos.y);
}

void CompositeShape::move(double dx, double dy) noexcept
{
  for (size_t i = 0; i < size_; i++)
  {
    elements_[i] -> move(dx, dy);
  }
}

void CompositeShape::scale(double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("ERROR: Negative scale ratio");
  }
  point_t currentPos = getFrameRect().pos;

  for (size_t i = 0; i < size_; i++)
  {
    point_t elementPos = elements_[i]->getFrameRect().pos;

    elements_[i]->move((ratio - 1) * (elementPos.x - currentPos.x), (ratio - 1) * (elementPos.y - currentPos.y));

    elements_[i]->scale(ratio);
  }
}

size_t CompositeShape::getSize() const noexcept
{
  return size_;
}
