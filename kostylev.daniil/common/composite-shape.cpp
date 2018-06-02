#include "composite-shape.hpp"

#include <stdexcept>
#include <iostream>


kostylev::CompositeShape::CompositeShape(const std::shared_ptr<Shape> & obj) :
  shapes_(new std::shared_ptr<Shape>[1]),
  length_(0)
{
  if (obj == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  shapes_[length_++] = obj;
}

kostylev::CompositeShape::CompositeShape(const CompositeShape & obj) :
  shapes_(new std::shared_ptr<Shape>[obj.length_]),
  length_(obj.length_)
{
  for (size_t i = 0; i < obj.length_; i++)
  {
    shapes_[i] = obj.shapes_[i];
  }
}

kostylev::CompositeShape::CompositeShape(CompositeShape && obj):
  shapes_(std::move(obj.shapes_)),
  length_(obj.length_)
{
  obj.length_ = 0;
  obj.shapes_.reset();
}

std::shared_ptr<kostylev::Shape> kostylev::CompositeShape::operator [] (const size_t index) const
{
  if ((index >= length_) )
  {
    throw std::out_of_range("Index is out of range");
  }
  return shapes_[index];
}

kostylev::CompositeShape & kostylev::CompositeShape::operator= (const kostylev::CompositeShape & obj)
{
  if (this == & obj)
  {
    return *this;
  }
  
  shapes_ = std::make_unique <std::shared_ptr<kostylev::Shape> []>(obj.length_);
  length_ = obj.length_;
    
  for (size_t i = 0; i < length_; i++)
  {
    shapes_[i] = obj.shapes_[1];
  }
  
  return *this;
}

kostylev::CompositeShape & kostylev::CompositeShape::operator= (kostylev::CompositeShape && obj)
{
  length_ = obj.length_;
  shapes_ = std::move(obj.shapes_);
  obj.length_ = 0;
  return *this;
}

void kostylev::CompositeShape::addShape(const std::shared_ptr<Shape> & obj)
{
  if (obj == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> tmpArray(new std::shared_ptr<Shape> [length_ + 1]);
  for (size_t i = 0; i < length_; i++)
  {
    tmpArray[i] = shapes_[i];
  }
  tmpArray[length_] = obj;
  length_++;
  shapes_.swap(tmpArray);
}

void kostylev::CompositeShape::removeShape (const size_t index)
{
  if (index >= length_)
  {
    throw std::out_of_range("Index is out of array size");
  }
  if ((length_ == 1) && (index == 0))
  {
    shapes_.reset();
    length_ = 0;
    return;
  }
  std::unique_ptr<std::shared_ptr <Shape >[]> tmpArray(new std::shared_ptr<Shape> [length_ - 1]);
  for (size_t i = 0; i < index; i++)
  {
    tmpArray[i] = shapes_[i];
  }
  for (size_t i = index; i < length_ - 1; ++i)
  {
    tmpArray[i] = shapes_[i + 1];
  }
  shapes_.swap(tmpArray);
  length_--;
}

double kostylev::CompositeShape::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < length_; i++)
  {
    area += shapes_[i] -> getArea();
  }
  return area;
}

kostylev::rectangle_t kostylev::CompositeShape::getFrameRect() const
{
  if (length_ <= 0)
  {
    return { {0.0 , 0.0}, 0.0 , 0.0};
  }

  kostylev::rectangle_t frameRect = shapes_[0] -> getFrameRect();
  double minX = frameRect.pos.x - frameRect.width / 2;
  double maxX = frameRect.pos.x + frameRect.width / 2;
  double maxY = frameRect.pos.y + frameRect.height / 2;
  double minY = frameRect.pos.y - frameRect.height / 2;

  for (size_t i = 1; i < length_; i++)
  {
    frameRect = shapes_[i]->getFrameRect();
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
  return {{(minX + (maxX - minX) / 2), (minY + (maxY - minY) / 2)}, (maxX - minX), (maxY - minY) };
}

void kostylev::CompositeShape::move(const point_t & posTo)
{
  move(posTo.x - getFrameRect().pos.x, posTo.y - getFrameRect().pos.y);
}

void kostylev::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < length_; i++)
  {
    shapes_[i] -> move(dx, dy);
  }
}

void kostylev::CompositeShape::scale(double coef)
{
  if (coef < 0.0)
  {
    throw std::invalid_argument("Invalid coefficient");
  }
  kostylev::point_t initialPos = getFrameRect().pos;
  for (size_t i = 0; i < length_; i++)
  {
    kostylev::point_t nowPos = shapes_[i] -> getFrameRect().pos;
    shapes_[i] -> move((coef - 1) * (nowPos.x - initialPos.x),
      (coef - 1)* (nowPos.y - initialPos.y));
    shapes_[i] -> scale(coef);
  }
}

size_t kostylev::CompositeShape::getLength() const
{
  return length_;
}
