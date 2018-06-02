#include "composite-shape.hpp"
#include <cmath>

shapovalova::CompositeShape::CompositeShape(const std::shared_ptr<Shape> & element):
  shapeList_(new std::shared_ptr<Shape>[1]),
  shapeAmount_(0)
{
  if (element == nullptr)
  {
    shapeList_.reset();
    throw std::invalid_argument ("Error! Detected nullptr");
  }
  shapeList_[0] = element;
  shapeAmount_++;
}

shapovalova::CompositeShape::CompositeShape(const CompositeShape & elem):
  shapeList_(new std::shared_ptr<Shape>[elem.shapeAmount_]),
  shapeAmount_(elem.shapeAmount_)
{
  for (int i = 0; i < shapeAmount_; i++)
  {
    shapeList_[i] = elem.shapeList_[i];
  }
}

shapovalova::CompositeShape::CompositeShape(CompositeShape && elem):
  shapeList_(std::move(elem.shapeList_)),
  shapeAmount_(elem.shapeAmount_)
{
  elem.shapeList_.reset();
  elem.shapeAmount_ = 0;
}

shapovalova::CompositeShape & shapovalova::CompositeShape::operator= (const CompositeShape & elem)
{
  if (this == &elem)
  {
    return *this;
  }
  shapeList_.reset(new std::shared_ptr<Shape>[shapeAmount_]);
  shapeAmount_ = elem.shapeAmount_;
  for (int i = 0; i < shapeAmount_; i++)
  {
    shapeList_[i] = elem.shapeList_[i];
  }
  return *this;
}

shapovalova::CompositeShape & shapovalova::CompositeShape::operator= (CompositeShape && elem)
{
  shapeList_ = std::move(elem.shapeList_);
  shapeAmount_ = elem.shapeAmount_;
  elem.shapeAmount_ = 0;
  return *this;
}

std::shared_ptr<shapovalova::Shape> shapovalova::CompositeShape::operator [](const int index) const
{
  if (index >= shapeAmount_)
  {
    throw std::out_of_range ("Index is out of range");
  }
  return shapeList_[index];
}

void shapovalova::CompositeShape::add(std::shared_ptr<Shape> & element)
{
  if (element == nullptr)
  {
    throw std::invalid_argument ("Error! Detected nullptr");
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> newArr (new std::shared_ptr<Shape>[shapeAmount_ + 1]);
  for (int i = 0; i < shapeAmount_; i++)
  {
    newArr[i] = shapeList_[i];
  }
  newArr[shapeAmount_] = element;
  shapeAmount_++;
  newArr.swap(shapeList_);
}

void shapovalova::CompositeShape::remove(const int index)
{
  if (shapeAmount_ <= 0)
  {
    std::out_of_range ("The list is empty");
  }
  if (index >= shapeAmount_)
  {
    std::out_of_range ("Trying to remote unexisting object");
  }
  if ((index == 0) && (shapeAmount_ == 1))
  {
    shapeList_.reset();
    shapeAmount_ = 0;
    return;
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> newArr (new std::shared_ptr<Shape>[shapeAmount_ - 1]);
  for (int i = 0; i < index; i++)
  {
    newArr[i] = shapeList_[i];
  }
  for (int i = index; i < shapeAmount_ - 1; i++)
  {
    newArr[i] = shapeList_[i + 1];
  }
  newArr.swap(shapeList_);
  shapeAmount_--;
}

double shapovalova::CompositeShape::getArea() const noexcept
{
  double generalArea = 0.0;
  for (int i = 0; i < shapeAmount_; i++)
  {
    generalArea += shapeList_[i] -> getArea();
  }
  return generalArea;
}

shapovalova::rectangle_t shapovalova::CompositeShape::getFrameRect() const noexcept
{
  shapovalova::rectangle_t frameRect = shapeList_[0] -> getFrameRect();
  double maxX = frameRect.pos.x + frameRect.width/2;
  double minX = frameRect.pos.x - frameRect.width/2;
  double maxY = frameRect.pos.y + frameRect.height/2;
  double minY = frameRect.pos.y - frameRect.height/2;
  for (int i = 0; i < shapeAmount_; i++)
  {
    frameRect = shapeList_[i] -> getFrameRect();
    if ((frameRect.pos.x + frameRect.width/2) > maxX)
    {
      maxX = frameRect.pos.x + frameRect.width/2;
    }
    if ((frameRect.pos.x - frameRect.width/2) < minX)
    {
      minX = frameRect.pos.x - frameRect.width/2;
    }
    if ((frameRect.pos.y + frameRect.height/2) > maxY)
    {
      maxY = frameRect.pos.y + frameRect.height/2;
    }
    if ((frameRect.pos.y - frameRect.height/2) < minY)
    {
      minY = frameRect.pos.y - frameRect.height/2;
    }
  }
  return {{((maxX + minX)/2), ((maxY + minY)/2)}, maxX - minX, maxY - minY};
}

void shapovalova::CompositeShape::move (const point_t & posTo) noexcept
{
  move(posTo.x - getFrameRect().pos.x, posTo.y - getFrameRect().pos.y);
}

void shapovalova::CompositeShape::move (const double dx, const double dy) noexcept
{
  for (int i = 0; i < shapeAmount_; i++)
  {
    shapeList_[i] -> move(dx, dy);
  }
}

void shapovalova::CompositeShape::scale (const double coefficient)
{
  if (coefficient <= 0.0)
  {
    throw std::invalid_argument ("Invalid parameter of scaling!");
  }
  shapovalova::point_t compositeCenter = getFrameRect().pos;
  for (int i = 0; i < shapeAmount_; i++)
  {
    double dx = shapeList_[i] -> getFrameRect().pos.x - compositeCenter.x;
    double dy = shapeList_[i] -> getFrameRect().pos.y - compositeCenter.y;

    shapovalova::point_t shapePos;
    shapePos.x = compositeCenter.x + coefficient*dx;
    shapePos.y = compositeCenter.y + coefficient*dy;
    shapeList_[i] -> move(shapePos);
    shapeList_[i] -> scale(coefficient);
  }
}

void shapovalova::CompositeShape::rotate(const double degrees) noexcept
{
  shapovalova::point_t centerPos = getFrameRect().pos;
  double sinValue = sin(degrees * M_PI / 180);
  double cosValue = cos(degrees * M_PI / 180);
  for (int i = 0; i < shapeAmount_; i++)
  {
    shapovalova::point_t shapePos = shapeList_[i] -> getFrameRect().pos;
    double newX = centerPos.x + (shapePos.x - centerPos.x) * cosValue - (shapePos.y - centerPos.y) * sinValue;
    double newY = centerPos.y + (shapePos.x - centerPos.x) * sinValue + (shapePos.y - centerPos.y) * cosValue;
    shapeList_[i] -> move({newX, newY});
    shapeList_[i] -> rotate(degrees);
  }
}

