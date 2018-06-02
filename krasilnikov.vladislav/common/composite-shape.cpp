#include "composite-shape.hpp"

#include <memory>
#include <stdexcept>
#include <math.h>

using namespace krasilnikov;

krasilnikov::CompositeShape::CompositeShape(std::shared_ptr< Shape > newShape):
  list_(nullptr),
  count_(0),
  angle_(0.0)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Null pointer");
  }
  addShape(newShape);
}

krasilnikov::CompositeShape::CompositeShape(const CompositeShape & rhs):
  list_(new std::shared_ptr< Shape >[rhs.count_]),
  count_(rhs.count_),
  angle_(rhs.angle_)
{
  for (int i = 0; i < count_; i++)
  {
    list_[i] = rhs.list_[i];
  }
}

krasilnikov::CompositeShape::~CompositeShape()
{
  this->clear();
}

double krasilnikov::CompositeShape::getArea() const
{
  double area = 0;
  for (int i = 0; i < count_; i++)
  {
    area += list_[i]->getArea();
  }
  return area;
}

rectangle_t krasilnikov::CompositeShape::getFrameRect() const
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
    return {(right - left), (top - bottom), {(left + (right-left) / 2), (bottom + (top - bottom) / 2)}};
  }
}

void krasilnikov::CompositeShape::move(const point_t & newPosition)
{
  const point_t curPosition = getPosition();
  move(newPosition.x - curPosition.x, newPosition.y - curPosition.y);
}

void krasilnikov::CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < count_; i++)
  {
    list_[i]->move(dx, dy);
  }
}

point_t krasilnikov::CompositeShape::getPosition() const
{
  return getFrameRect().pos;
}

void krasilnikov::CompositeShape::scale(const double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Invalid factor");
  }

  const point_t curPosition = getPosition();
  for (int i = 0; i < count_; i++)
  {
    const point_t shapePosition = list_[i]->getPosition();
    list_[i]->move({curPosition.x + factor * (shapePosition.x - curPosition.x),
                      curPosition.y + factor * (shapePosition.y - curPosition.y)});
    list_[i]->scale(factor);
  }
}

void krasilnikov::CompositeShape::rotate(const double angle)
{
  angle_ += angle;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }
  const double sine = sin(angle * M_PI / 180);
  const double cosine = cos(angle * M_PI / 180);
  const point_t curPosition = getFrameRect().pos;
  for (int i = 0; i < count_; i++)
  {
    const point_t shapePosition = list_[i]->getFrameRect().pos;
    list_[i]->move({(shapePosition.x - curPosition.x) * cosine - (shapePosition.y - curPosition.y) * sine +curPosition.x,
      (shapePosition.y - curPosition.y) * cosine + (shapePosition.x - curPosition.x) * sine + curPosition.y});
    list_[i]->rotate(angle);
  }
}

int krasilnikov::CompositeShape::getCount() const
{
  return count_;
}

void krasilnikov::CompositeShape::addShape(const std::shared_ptr< Shape > shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Null pointer");
  }
  for (int i = 0; i < count_; i++)
  {
    if (shape == list_[i])
    {
      throw std::invalid_argument("Can not add this shape, it is added already.");
    }
  }
  std::unique_ptr< std::shared_ptr< Shape >[] > temp(new std::shared_ptr< Shape >[count_ + 1]);
  for (int i = 0; i < count_; i++)
  {
    temp[i] = list_[i];
  }
  temp[count_++] = shape;
  list_.swap(temp);
}

void krasilnikov::CompositeShape::removeShape(const int index)
{
  if (count_ <= 0)
  {
    throw std::out_of_range("List is empty");
  }
  if (index >= count_)
  {
    throw std::out_of_range("Index out of range");
  }
  if ((count_ == 1) && (index == 0))
  {
    clear();
    return;
  }
  std::unique_ptr< std::shared_ptr< Shape >[] > temp (new std::shared_ptr< Shape >[count_ - 1]);
  for (int i = 0; i < index; i++)
  {
    temp[i] = list_[i];
  }
  for (int i = index; i < count_ - 1; i++)
  {
    temp[i] = list_[i + 1];
  }
  list_.swap(temp);
  count_--;
}

void krasilnikov::CompositeShape::clear()
{
  list_.reset();
  list_ = nullptr;
  count_ = 0;
}

CompositeShape & krasilnikov::CompositeShape::operator=(const CompositeShape & rhs)
{
  if (this != &rhs)
  {
    count_ = rhs.count_;
    angle_ = rhs.angle_;
    std::unique_ptr< std::shared_ptr< Shape >  [] > temp(new std::shared_ptr< Shape >[count_]);
    for (int i = 0; i < rhs.getCount(); i++)
    {
      temp[i] = rhs.list_[i];
    }
    list_.swap(temp);
  }
  return *this;
}

std::shared_ptr< krasilnikov::Shape > krasilnikov::CompositeShape::operator[](const int index) const
{
  if ((index >= count_) || (index < 0))
  {
    throw std::out_of_range("Index out of range");
  }
  return list_[index];
}
