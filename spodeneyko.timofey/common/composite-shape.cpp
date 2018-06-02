#include "composite-shape.hpp"
#include <stdexcept>
#include <cmath>

spodeneyko::CompositeShape::CompositeShape(const std::shared_ptr<Shape> & shapeElement):
  shapeList_(new std::shared_ptr<Shape>[1]),
  shapeAmount_(0)
{
  if (!shapeElement)
  {
    throw std::invalid_argument("Error. Object does not exist.");
  }
  shapeList_[0] = shapeElement;
  ++shapeAmount_;
}

spodeneyko::CompositeShape::CompositeShape(const CompositeShape & object):
  shapeList_(new std::shared_ptr<Shape>[object.shapeAmount_]),
  shapeAmount_(object.shapeAmount_)
{
  for (size_t i = 0; i < shapeAmount_; ++i)
  {
    shapeList_[i] = object.shapeList_[i];
  }
}

spodeneyko::CompositeShape::CompositeShape(CompositeShape && object):
  shapeList_(std::move(object.shapeList_)),
  shapeAmount_(std::move(object.shapeAmount_))
{
  object.shapeList_.reset();
  object.shapeAmount_ = 0;
}

spodeneyko::CompositeShape & spodeneyko::CompositeShape::operator =(const CompositeShape & object)
{
  if (this != &object)
  {
    shapeAmount_ = object.shapeAmount_;
    array_type new_arr(new std::shared_ptr<Shape>[shapeAmount_]);
    for (size_t i = 0; i < shapeAmount_; ++i)
    {
      new_arr[i] = object.shapeList_[i];
    }
    shapeList_.swap(new_arr);
  }
  return *this;
}

spodeneyko::CompositeShape & spodeneyko::CompositeShape::operator =(CompositeShape && object)
{
  if (this != &object)
  {
    shapeAmount_ = std::move(object.shapeAmount_);
    shapeList_ = std::move(object.shapeList_);
    object.shapeList_.reset();
    object.shapeAmount_ = 0;
  }
  return *this;
}

std::shared_ptr<spodeneyko::Shape> spodeneyko::CompositeShape::operator [](const unsigned int index) const
{
  if (index >= shapeAmount_) 
  {
    throw std::out_of_range("Error. Index is out of range.");
  }
  return shapeList_[index];
}

void spodeneyko::CompositeShape::addShape(const std::shared_ptr<Shape> & shapeElement)
{
  if (!shapeElement)
  {
    throw std::invalid_argument("Error. Object does not exist.");
  }
  array_type new_arr(new std::shared_ptr<Shape>[shapeAmount_ + 1]);
  for (size_t i = 0; i < shapeAmount_; ++i)
  {
    new_arr[i] = shapeList_[i];
  }
  new_arr[shapeAmount_++] = shapeElement;
  shapeList_.swap(new_arr);
}

void spodeneyko::CompositeShape::removeShape(const unsigned int index)
{
  if (shapeAmount_ <= 0)
  {
    throw std::out_of_range("Error. List of shapes is empty.");
  }
  if (index >= shapeAmount_)
  {
    throw std::out_of_range("Error. Index is out of range.");
  }
  if ((index < shapeAmount_) && (shapeAmount_ > 0)) 
  {
    shapeList_[index].reset();
    for (unsigned int tmp_index = index; tmp_index < shapeAmount_ - 1; ++tmp_index) 
    {
      shapeList_[tmp_index] = shapeList_[tmp_index + 1];
    }
    shapeList_[--shapeAmount_].reset();
  }
}

double spodeneyko::CompositeShape::getArea() const noexcept
{
  double totalArea = 0.0;
  for (size_t i = 0; i < shapeAmount_; ++i)
  {
    totalArea += shapeList_[i] -> getArea();
  }
  return totalArea;
}

spodeneyko::rectangle_t spodeneyko::CompositeShape::getFrameRect() const noexcept
{
  rectangle_t frameRect = shapeList_[0] -> getFrameRect();
  double maxX = frameRect.pos.x + frameRect.width / 2;
  double minX = frameRect.pos.x - frameRect.width / 2;
  double maxY = frameRect.pos.y + frameRect.height / 2;
  double minY = frameRect.pos.y - frameRect.height / 2;
  for (size_t i = 1; i < shapeAmount_; ++i)
  {
    frameRect = shapeList_[i] -> getFrameRect();
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

std::string spodeneyko::CompositeShape::getName() const noexcept
{
  return "Composite Shape";
}

void spodeneyko::CompositeShape::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Error. Invalid parameter of scaling.");
  }
  const point_t comp_shapePos = getFrameRect().pos;
  for (size_t i = 0; i < shapeAmount_; ++i)
  {
    const point_t shapePos = shapeList_[i] -> getFrameRect().pos;
    shapeList_[i] -> move((factor - 1) * (shapePos.x - comp_shapePos.x), (factor - 1) * (shapePos.y - comp_shapePos.y));
    shapeList_[i] -> scale(factor);
  }
}

void spodeneyko::CompositeShape::move(const point_t & point) noexcept
{
  move(point.x - getFrameRect().pos.x, point.y - getFrameRect().pos.y);
}

void spodeneyko::CompositeShape::move(const double dx, const double dy) noexcept
{
  for (size_t i = 0; i < shapeAmount_; ++i)
  {
    shapeList_[i] -> move(dx, dy);
  }
}

void spodeneyko::CompositeShape::rotate(const double angle) noexcept
{
  const point_t comp_shapePos = getFrameRect().pos;
  const double cosA = cos(angle * M_PI / 180);
  const double sinA = sin(angle * M_PI / 180);
  for (size_t i = 0; i < shapeAmount_; ++i)
  {
    const point_t shapePos = shapeList_[i] -> getFrameRect().pos;
    shapeList_[i] -> move({comp_shapePos.x + (shapePos.x - comp_shapePos.x) * cosA - (shapePos.y - comp_shapePos.y) * sinA,
                         comp_shapePos.y + (shapePos.x - comp_shapePos.x) * sinA + (shapePos.y - comp_shapePos.y) * cosA});
    shapeList_[i] -> rotate(angle);
  }
}
