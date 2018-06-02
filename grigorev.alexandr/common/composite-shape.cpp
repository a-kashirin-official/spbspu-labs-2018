#include "composite-shape.hpp"
#include <memory>
#include <iostream>
#include <math.h>

grigorev::CompositeShape::CompositeShape():
  list_(nullptr),
  size_(0),
  angle_(0.0)
{
}

grigorev::CompositeShape::CompositeShape(const std::shared_ptr< grigorev::Shape > shape):
  list_(nullptr),
  size_(0),
  angle_(0.0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  addShape(shape);
}

grigorev::CompositeShape::CompositeShape(const grigorev::CompositeShape & comp):
  list_(new std::shared_ptr< grigorev::Shape > [comp.size_]),
  size_(comp.size_),
  angle_(comp.angle_)
{
  for (int i = 0; i < size_; ++i)
  {
    list_[i] = comp.list_[i];
  }
}

grigorev::CompositeShape::CompositeShape(grigorev::CompositeShape && comp):
  list_(nullptr),
  size_(comp.size_),
  angle_(comp.angle_)
{
  list_.swap(comp.list_);
  comp.list_ = nullptr;
}


grigorev::CompositeShape & grigorev::CompositeShape::operator = (const grigorev::CompositeShape & comp)
{
  if (this != & comp)
  {
    size_ = comp.size_;
    std::unique_ptr< std::shared_ptr< grigorev::Shape >[] > tempArray(new std::shared_ptr< grigorev::Shape >[size_]);
    for (int i = 0; i < size_; ++i)
    {
      tempArray[i] = comp.list_[i];
    }
    list_.swap(tempArray);
  }
  return *this;
}

grigorev::CompositeShape & grigorev::CompositeShape::operator = (grigorev::CompositeShape && comp)
{
  if (this != & comp)
  {
    size_ = comp.size_;
    list_.swap(comp.list_);
    comp.list_ = nullptr;
    comp.size_ = 0;
  }
  return *this;
}

std::shared_ptr< grigorev::Shape > grigorev::CompositeShape::operator[] (const int index) const
{
  if ((index >= size_) || (index < 0 ))
  {
    throw std::invalid_argument("Invalid index");
  }
  return list_[index];
}

double grigorev::CompositeShape::getArea() const
{
  double area = 0.0;
  for (int i = 0; i < size_; i++)
  {
    area += list_[i]->getArea();
  }
  return area;
}

grigorev::rectangle_t grigorev::CompositeShape::getFrameRect() const
{
  grigorev::rectangle_t baseRect = list_[0]->getFrameRect();
  double minX = baseRect.pos.x - baseRect.width / 2.0;
  double maxX = baseRect.pos.x + baseRect.width / 2.0;
  double minY = baseRect.pos.y - baseRect.height / 2.0;
  double maxY = baseRect.pos.y + baseRect.height / 2.0;
  for (int i = 1; i < size_; ++i)
  {
    baseRect = list_[i]->getFrameRect();
    double newMinX = baseRect.pos.x - baseRect.width / 2.0;
    double newMaxX = baseRect.pos.x + baseRect.width / 2.0;
    double newMinY = baseRect.pos.y - baseRect.height / 2.0;
    double newMaxY = baseRect.pos.y + baseRect.height / 2.0;

    minX = std::min(minX, newMinX);
    maxX = std::max(maxX, newMaxX);
    minY = std::min(minY, newMinY);
    maxY = std::max(maxY, newMaxY);
  }
  return grigorev::rectangle_t {{(minX+maxX)/2, (minY+maxY)/2}, maxX - minX, maxY - minY};
}

void grigorev::CompositeShape::move(const grigorev::point_t & newCenter)
{
  grigorev::point_t point = getFrameRect().pos;
  for (int i = 0; i < size_; i++)
  {
    list_[i]->move(newCenter.x - point.x, newCenter.y - point.y);
  }
}

void grigorev::CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < size_; i++)
  {
    list_[i]->move(dx,dy);
  }
}

void grigorev::CompositeShape::scale(const double coef)
{
  if (coef < 0.0)
  {
    throw std::invalid_argument("Error: Invalid scale coef");
  }

  const grigorev::point_t currPos = getFrameRect().pos;
  for (int i = 0; i < size_; ++i)
  {
    const grigorev::point_t shapePos = list_[i]->getFrameRect().pos;
    list_[i]->move((coef -1) * (shapePos.x - currPos.x), (coef - 1) * (shapePos.y - currPos.y));
    list_[i]->scale(coef);
  }
}

void grigorev::CompositeShape::rotate(const double angle)
{
  angle_ += angle;
  if (abs(angle_) >= 360.0)
  {
    angle_ = fmod(angle, 360.0);
  }
  const double sine = sin(angle_ * M_PI / 180);
  const double cosine = cos(angle_ * M_PI / 180);
  const grigorev::point_t curPos = getFrameRect().pos;
  for (int i = 0; i < size_; ++i)
  {
    const grigorev::point_t shapePos = list_[i]-> getFrameRect().pos;
    list_[i]->move({(shapePos.x - curPos.x) * cosine - (shapePos.y - curPos.y) * sine + curPos.x,
      (shapePos.y - curPos.y) * cosine + (shapePos.x - curPos.x) * sine + curPos.y});
    list_[i]->rotate(angle);
  }
}

void grigorev::CompositeShape::addShape(std::shared_ptr< grigorev::Shape > shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Error: Invalid pointeer");
  }

  std::unique_ptr<std::shared_ptr< grigorev::Shape >[]> tempArray (new std::shared_ptr< grigorev::Shape >[size_ + 1]);
  for (int i = 0; i < size_; ++i)
  {
    tempArray[i] = list_[i];
  }
  tempArray[size_++] = shape;
  list_.swap(tempArray);
}

void grigorev::CompositeShape::removeShape(const int index)
{
  if (size_ == 0)
  {
    throw std::invalid_argument("Composite Shape is empty");
  }
  else
  {
    if (index > size_)
    {
      throw std::invalid_argument("Invalid index");
    }
  }
  if (size_ == 1)
  {
    deleteShapes();
  }
  else
  {
    std::unique_ptr< std::shared_ptr< grigorev::Shape >[] > tempArray(new std::shared_ptr< grigorev::Shape >[size_ - 1]);
    for (int i = 0; i < (index - 1); ++i)
    {
      tempArray[i] = list_[i];
    }
    for (int i = index; i < size_; ++i)
    {
      tempArray[i-1] = list_[i];
    }
    list_.swap(tempArray);
    --size_;
  }
}

void grigorev::CompositeShape::deleteShapes()
{
  list_.reset();
  list_ = nullptr;
  size_ = 0;
}

int grigorev::CompositeShape::getSize() const
{
  return size_;
}

