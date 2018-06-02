#include "composite-shape.hpp"

#include <stdexcept>
#include <iostream>
#include <cmath>

shalgueva::CompositeShape::CompositeShape(const std::shared_ptr<Shape> & object) : 
  figures_(new std::shared_ptr<Shape>[1]),
  length_(0)
{
  if (object == nullptr)
  {
    figures_.reset();
    throw std::invalid_argument("Invalid pointer");
  }
  figures_[0] = object;
  length_++;
}

shalgueva::CompositeShape::CompositeShape(const CompositeShape & object) :
  figures_(new std::shared_ptr<Shape>[object.length_]),
  length_(object.length_)
{
  for (size_t i = 0; i < object.length_; i++)
  {
    figures_[i] = object.figures_[i];
  }
}

shalgueva::CompositeShape::CompositeShape(CompositeShape && object):
  figures_(std::move(object.figures_)),
  length_(object.length_)
{
  object.length_ = 0;
  object.figures_.reset();
}

std::shared_ptr<shalgueva::Shape> shalgueva::CompositeShape::operator [] (const size_t index) const
{
  if ((index >= length_) )
  {
    throw std::out_of_range("Index is out of range");
  }
  return figures_[index];
}

void shalgueva::CompositeShape::addShape(const std::shared_ptr<Shape> & object)
{
  if (object == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> newArray(new std::shared_ptr<Shape> [length_ + 1]);
  for (size_t i = 0; i < length_; i++)
  {
    newArray[i] = figures_[i];
  }
  newArray[length_] = object;
  length_++;
  figures_.swap(newArray);
}

void shalgueva::CompositeShape::removeShape (const size_t index)
{
  if (index >= length_)
  {
    throw std::out_of_range("Index is out of array size");
  }
  if ((length_ == 1) && (index == 0))
  {
    figures_.reset();
    length_ = 0;
    return;
  }
  std::unique_ptr<std::shared_ptr <Shape >[]> newArray(new std::shared_ptr<Shape> [length_ - 1]);
  for (size_t i = 0; i < index; i++)
  {
    newArray[i] = figures_[i];
  }
  for (size_t i = index; i < length_ - 1; ++i)
  {
    newArray[i] = figures_[i + 1];
  }
  figures_.swap(newArray);
  length_--;
}

shalgueva::CompositeShape & shalgueva::CompositeShape::operator= (const shalgueva::CompositeShape & object)
{
  if (this == & object)
  {
    return *this;
  }
  length_ = object.length_;
  std::unique_ptr <std::shared_ptr<shalgueva::Shape>[]>
      newArray(new std::shared_ptr<shalgueva::Shape>[length_]);
  for (size_t i = 0; i < length_; i++)
  {
    newArray[i] = object.figures_[i];
  }
  figures_.swap(newArray);
  return *this;
}

shalgueva::CompositeShape & shalgueva::CompositeShape::operator= (shalgueva::CompositeShape && object)
{
  length_ = object.length_;
  figures_ = std::move(object.figures_);
  object.length_ = 0;
  return *this;
}



double shalgueva::CompositeShape::getArea() const noexcept
{
  double commonArea = 0;
  for (size_t i = 0; i < length_; i++)
  {
    commonArea += figures_[i] -> getArea();
  }
  return commonArea;
}

shalgueva::rectangle_t shalgueva::CompositeShape::getFrameRect() const noexcept
{
  if (length_ <= 0)
  {
    return { 0.0 , 0.0, {0.0 , 0.0}};
  }

  shalgueva::rectangle_t frameRect = figures_[0] -> getFrameRect();
  double minX = frameRect.pos.x - frameRect.width / 2;
  double maxX = frameRect.pos.x + frameRect.width / 2;
  double maxY = frameRect.pos.y + frameRect.height / 2;
  double minY = frameRect.pos.y - frameRect.height / 2;

  for (size_t i = 1; i < length_; i++)
  {
    frameRect = figures_[i]->getFrameRect();
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

void shalgueva::CompositeShape::move(const point_t & posTo) noexcept
{
  move(posTo.x - getFrameRect().pos.x, posTo.y - getFrameRect().pos.y);
}

void shalgueva::CompositeShape::move(double dx, double dy) noexcept
{
  for (size_t i = 0; i < length_; i++)
  {
    figures_[i] -> move(dx, dy);
  }
}

void shalgueva::CompositeShape::scale(double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Invalid coefficient");
  }
  shalgueva::point_t initialShapePos = getFrameRect().pos;
  for (size_t i = 0; i < length_; i++)
  {
    shalgueva::point_t shapePos = figures_[i] -> getFrameRect().pos;
    figures_[i] -> move((coefficient - 1) * (shapePos.x - initialShapePos.x),
      (coefficient - 1)* (shapePos.y - initialShapePos.y));
    figures_[i] -> scale(coefficient);
  }
}

size_t shalgueva::CompositeShape::getLength() const noexcept
{
  return length_;
}

void shalgueva::CompositeShape::rotate(double alpha) noexcept
{
  double sinAlpha = sin(alpha * 3.14 / 180);
  double cosAlpha = cos(alpha * 3.14 / 180);

  shalgueva::point_t center = getFrameRect().pos;

  for(size_t i = 0; i < length_; i++)
  {
    shalgueva::point_t shapePos = figures_[i] -> getFrameRect().pos;
    double newX = center.x + (shapePos.x - center.x) * cosAlpha - (shapePos.y - center.y) * sinAlpha;
    double newY = center.y + (shapePos.y - center.y) * cosAlpha + (shapePos.x - center.x) * sinAlpha;
    figures_[i] -> move({newX, newY});
    figures_[i] -> rotate(alpha);
  }
}
