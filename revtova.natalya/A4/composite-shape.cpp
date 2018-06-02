#include <memory>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include "composite-shape.hpp"

using namespace revtova;

revtova::CompositeShape::CompositeShape(const ptr_type rhs):
  figures_(nullptr),
  count_(0),
  angle_(0.0)
{
  if (rhs == nullptr)
  {
    throw std::invalid_argument("Invalid Pointer");
  }
  addShape(rhs);
}
revtova::CompositeShape::CompositeShape(const revtova::CompositeShape &rhs):
  figures_(new ptr_type[rhs.count_]),
  count_(rhs.getCount())
{
  for (size_t i = 0; i < count_; i++)
  {
    figures_[i] = rhs.figures_[i];
  }
}
revtova::CompositeShape::~CompositeShape()
{
  figures_.reset();
  figures_ = nullptr;
  count_ = 0;
}
double revtova::CompositeShape::getArea() const noexcept
{
  double area = figures_[0]->getArea();
  for (size_t i = 1; i < count_; i++)
  {
    area += figures_[i]->getArea();
  }
  return area;
}
rectangle_t revtova::CompositeShape::getFrameRect() const
{
  if (count_ <= 0)
  {
    return {0, 0, {0, 0}};
  }
  else
  {
    double left = figures_[0]->getFrameRect().pos.x - figures_[0]->getFrameRect().width / 2;
    double right = figures_[0]->getFrameRect().pos.x + figures_[0]->getFrameRect().width / 2;
    double top = figures_[0]->getFrameRect().pos.y + figures_[0]->getFrameRect().height / 2;
    double bottom = figures_[0]->getFrameRect().pos.y - figures_[0]->getFrameRect().height / 2;

    for (size_t i = 1; i < count_; i++)
    {
      double iLeft = figures_[i]->getFrameRect().pos.x - figures_[i]->getFrameRect().width / 2;
      double iRight = figures_[i]->getFrameRect().pos.x + figures_[i]->getFrameRect().width / 2;
      double iTop = figures_[i]->getFrameRect().pos.y + figures_[i]->getFrameRect().height / 2;
      double iBottom = figures_[i]->getFrameRect().pos.y - figures_[i]->getFrameRect().height / 2;
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
void revtova::CompositeShape::move(const point_t & pos)
{
  point_t center = getFrameRect().pos;
  for (size_t i = 0; i<count_; i++)
  {
    figures_[i]->move(pos.x-center.x,pos.y-center.y);
  }
}
void revtova::CompositeShape::move(const double dx, const double dy)
{
  for (size_t i = 0; i<count_; i++)
  {
    figures_[i]->move(dx, dy);
  }
}
void revtova::CompositeShape::scale(const double kscale)
{
  if (kscale <= 0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  const point_t newPos = getFrameRect().pos;
  for (size_t i = 0; i < count_; i++)
  {
    figures_[i]->scale(kscale);
    const point_t curPos = figures_[i]->getFrameRect().pos;
    figures_[i]->move({newPos.x + kscale*(curPos.x - newPos.x),newPos.y + kscale*(curPos.y - newPos.y)});
    figures_[i]->scale(kscale);
  }
}
size_t revtova::CompositeShape::getCount() const
{
  return count_;
}
point_t revtova::CompositeShape::getPos() const
{
  return getFrameRect().pos;
}
void revtova::CompositeShape::addShape(std::shared_ptr<Shape> rhs)
{
  if (rhs == nullptr)
  {
    throw std::invalid_argument("Invalid_figures");
  }
  layer_type tmp (new ptr_type[count_+1]);
  for (size_t i = 0; i<count_; i++)
  {
    tmp[i] = figures_[i];
  }
  tmp[count_] = rhs;
  count_++;
  figures_.swap(tmp);
}
void revtova::CompositeShape::remove(size_t index)
{
  if (count_ <= 0)
  {
    throw std::out_of_range("List is Empty");
  }
  layer_type newElements(new ptr_type[count_ - 1]);
  for (size_t i = 0; i < index; ++i)
  {
    newElements[i] = figures_[i];
  }
  for (size_t i = index; i < count_ - 1; ++i)
  {
    newElements[i] = figures_[i + 1];
  }
  figures_.swap(newElements);
  count_--;
}
void CompositeShape::rotate(const double angle)
{
  angle_ += angle;
  if (angle_ >= 360.0)
  {
    angle_ = fmod(angle_, 360.0);
  }
  const double sint = sin(angle * M_PI / 180);
  const double cost = cos(angle * M_PI / 180);
  const point_t currPos = getFrameRect().pos;
  for (size_t i = 0; i < count_; ++i)
  {
    const point_t shapePos = figures_[i]->getFrameRect().pos;
    figures_[i]->move({(shapePos.x - currPos.x) * cost - (shapePos.y - currPos.y) * sint + currPos.x,
      (shapePos.y - currPos.y) * cost + (shapePos.x - currPos.x) * sint + currPos.y});
    figures_[i]->rotate(angle);
  }
}
CompositeShape & revtova::CompositeShape::operator=(const CompositeShape & rhs)
{
  if (this != &rhs)
  {
    count_ = rhs.count_;
    layer_type newElements(new std::shared_ptr<Shape>[count_]);
    for (size_t i = 0; i < rhs.count_; ++i)
    {
      newElements[i] = rhs.figures_[i];
    }
    figures_.swap(newElements);
  }
  return *this;
}
revtova::CompositeShape::layer_type revtova::CompositeShape::operator[](size_t index) const
{
  if (index >= count_)
  {
    throw std::out_of_range("Index out of range");
  }
  layer_type layer (new ptr_type[count_]);
  for (size_t i = 0; i < count_; ++i)
  {
    layer[i] = figures_[index * count_ + i];
  }
  return layer;
}
