#include "composite-shape.hpp"

#include <stdexcept>
#include <math.h>

using namespace afanasiev;

afanasiev::CompositeShape::CompositeShape(std::shared_ptr<Shape> newShape):
  list_(nullptr),
  count_(0),
  angle_(0.0)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Invalid Pointer");
  }
  addShape(newShape);
}

afanasiev::CompositeShape::CompositeShape(const CompositeShape & compositeShape):
  list_(new std::shared_ptr<Shape>[compositeShape.count_]),
  count_(compositeShape.count_),
  angle_(compositeShape.angle_)
{
  for (int i = 0; i < count_; ++i)
  {
    list_[i] = compositeShape.list_[i];
  }
}


afanasiev::CompositeShape::~CompositeShape()
{
  clear();
}

double afanasiev::CompositeShape::getArea() const noexcept
{
  double area = 0;
  for (int i = 0; i < count_; ++i)
  {
    area += list_[i]->getArea();
  }
  return area;
}

rectangle_t afanasiev::CompositeShape::getFrameRect() const noexcept
{
  if (count_ <= 0) 
  {
    return {0, 0, {0, 0}};
  } 
  else
  {
    rectangle_t shapeFrameRect = list_[0]->getFrameRect();
    double left = shapeFrameRect.pos.x - shapeFrameRect.width / 2;
    double right = shapeFrameRect.pos.x + shapeFrameRect.width / 2;
    double top = shapeFrameRect.pos.y + shapeFrameRect.height / 2;
    double bottom = shapeFrameRect.pos.y - shapeFrameRect.height / 2;

    for (int i = 1; i < count_; i++) 
    {
      shapeFrameRect = list_[i]->getFrameRect();
      double iLeft = shapeFrameRect.pos.x - shapeFrameRect.width / 2;
      double iRight = shapeFrameRect.pos.x + shapeFrameRect.width / 2;
      double iTop = shapeFrameRect.pos.y + shapeFrameRect.height / 2;
      double iBottom = shapeFrameRect.pos.y - shapeFrameRect.height / 2;
      if (iLeft < left) 
      {
        left = iLeft;
      }
      if (iRight > right)
      {
        right = iRight;
      }
      if (iTop > top)
      {
        top = iTop;
      }
      if (iBottom < bottom)
      {
        bottom = iBottom;
      }
    }
    return {(right - left), (top - bottom), {(left + (right - left) / 2), (bottom + (top - bottom) / 2)}};
  }
}

void afanasiev::CompositeShape::move(const point_t & newPos) noexcept
{
  const point_t curPos = getPos();
  move(newPos.x - curPos.x, newPos.y - curPos.y);
}

void afanasiev::CompositeShape::move(const double dx, const double dy) noexcept
{
  for (int i = 0; i < count_; ++i)
  {
    list_[i]->move(dx, dy);
  }
}

point_t afanasiev::CompositeShape::getPos() const noexcept
{
  return getFrameRect().pos;
}

void afanasiev::CompositeShape::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }

  const point_t curPos = getPos();
  for (int i = 0; i < count_; ++i)
  {
    const point_t shapePos = list_[i]->getPos();
    list_[i]->move({curPos.x + factor * (shapePos.x - curPos.x),
                      curPos.y + factor * (shapePos.y - curPos.y)});
    list_[i]->scale(factor);
  }
}

void afanasiev::CompositeShape::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (angle_ >= 360.0)
  {
    angle_ = fmod(angle_, 360.0);
  }
  const double sine = sin(angle * M_PI / 180);
  const double cosine = cos(angle * M_PI / 180);
  const point_t currPos = getFrameRect().pos;
  for (int i = 0; i < count_; ++i)
  {
    const point_t shapePos = list_[i]->getPos();
    list_[i]->move({(shapePos.x - currPos.x) * cosine - (shapePos.y - currPos.y) * sine + currPos.x,
      (shapePos.y - currPos.y) * cosine + (shapePos.x - currPos.x) * sine + currPos.y});
    list_[i]->rotate(angle);
  }
}

int afanasiev::CompositeShape::getCount() const noexcept
{
  return count_;
}

void afanasiev::CompositeShape::addShape(const std::shared_ptr<Shape> shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid Pointer");
  }
  for (int i = 0; i < count_; ++i)
  {
    if (list_[i] == shape)
    {
      throw std::invalid_argument("Can not add this Shape");
    }
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> newElements(new std::shared_ptr<Shape>[count_ + 1]);
  for (int i = 0; i < count_; ++i)
  {
    newElements[i] = list_[i];
  }
  newElements[count_++] = shape;
  list_.swap(newElements);
}

void afanasiev::CompositeShape::removeShape(const int index)
{
  if (count_ <= 0)
  {
    throw std::out_of_range("List is Empty");
  }
  if ((index >= count_) || (index < 0))
  {
    throw std::out_of_range("Index out of range");
  }
  if ((count_ == 1) && (index == 0))
  {
    clear();
    return;
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> newElements(new std::shared_ptr<Shape>[count_ - 1]);

  for (int i = 0; i < index; ++i)
  {
    newElements[i] = list_[i];
  }
  for (int i = index; i < count_ - 1; ++i)
  {
    newElements[i] = list_[i + 1];
  }
  list_.swap(newElements);
  count_--;
}

void afanasiev::CompositeShape::clear()
{
  list_.reset();
  list_ = nullptr;
  count_ = 0;
}

CompositeShape & afanasiev::CompositeShape::operator=(const CompositeShape & rhs) noexcept
{
  if (this != &rhs)
  {
    count_ = rhs.count_;
    angle_ = rhs.angle_;
    std::unique_ptr<std::shared_ptr<Shape>[]> newElements(new std::shared_ptr<Shape>[count_]);
    for (int i = 0; i < rhs.count_; ++i)
    {
      newElements[i] = rhs.list_[i];
    }
    list_.swap(newElements);
  }
  return *this;
}

std::shared_ptr<Shape> afanasiev::CompositeShape::operator[](const int index) const
{
  if (index >= count_)
  {
    throw std::out_of_range("Index out of range");
  }
  return list_[index];
}
