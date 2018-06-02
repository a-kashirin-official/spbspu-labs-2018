#include <cmath>
#include <stdexcept>
#include <iostream>
#include "composite-shape.hpp"

using namespace revtova;

CompositeShape::CompositeShape(Shape *rhs):
  list_(new Shape *[1]),
  count_(1)
{
  if (rhs == nullptr)
  {
    throw std::invalid_argument("Null pointer");
  }
  list_[0] = rhs;
}
CompositeShape::CompositeShape(CompositeShape &&rhs) :
  list_(nullptr),
  count_(0)
{
  *this = std::move(rhs);
}
CompositeShape::CompositeShape(const CompositeShape &rhs) :
  list_(new Shape *[rhs.count_]),
  count_(rhs.count_)
{
  for (size_t i = 0; i < count_; i++)
  {
    list_[i] = rhs.list_[i];
  }
}
CompositeShape &CompositeShape::operator=(const CompositeShape & rhs)
{
  if (this != &rhs)
  {
    std::unique_ptr<Shape *[]> tmp(new Shape *[count_ - 1]);
    for (size_t i = 0; i < rhs.getCount(); ++i)
    {
      tmp[i] = rhs.list_[i];
    }
    count_ = rhs.count_;
  }
  return *this;
}
CompositeShape &CompositeShape::operator = (CompositeShape &&rhs)
{
  if (this != &rhs)
  {
    count_ = rhs.count_;
    list_.swap(rhs.list_);
    rhs.list_ = nullptr;
    rhs.count_ = 0;
  }
  return *this;
}
Shape *CompositeShape::operator[](size_t index) const
{
  if (index >= count_)
  {
    throw std::out_of_range("Index out of range");
  }
  return list_[index];
}
double CompositeShape::getArea() const
{
  double area = list_[0]->getArea();
  for (size_t i = 1; i < count_; ++i)
  {
    area += list_[i]->getArea();
  }
  return area;
}
rectangle_t CompositeShape::getFrameRect() const
{
  if (count_ <= 0)
  {
    return {0, 0, {0, 0}};
  }
  else
  {
    double left = list_[0]->getFrameRect().pos.x - list_[0]->getFrameRect().width / 2;
    double right = list_[0]->getFrameRect().pos.x + list_[0]->getFrameRect().width / 2;
    double top = list_[0]->getFrameRect().pos.y + list_[0]->getFrameRect().height / 2;
    double bottom = list_[0]->getFrameRect().pos.y - list_[0]->getFrameRect().height / 2;

    for (size_t i = 1; i < count_; i++)
    {
      double iLeft = list_[i]->getFrameRect().pos.x - list_[i]->getFrameRect().width / 2;
      double iRight = list_[i]->getFrameRect().pos.x + list_[i]->getFrameRect().width / 2;
      double iTop = list_[i]->getFrameRect().pos.y + list_[i]->getFrameRect().height / 2;
      double iBottom = list_[i]->getFrameRect().pos.y - list_[i]->getFrameRect().height / 2;
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
void CompositeShape::move(const point_t & pos)
{
  const point_t newPos = getFrameRect().pos;
  move(pos.x - newPos.x, pos.y - newPos.y);
}
void CompositeShape::move(const double dx, const double dy)
{
  for (size_t i = 0; i < count_; i++)
  {
    list_[i]->move(dx, dy);
  }
}
void CompositeShape::scale(const double kscale)
{
  if (kscale <= 0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  const point_t newPos = getFrameRect().pos;
  for (size_t i = 0; i < count_; i++)
  {
    const point_t curPos = list_[i]->getFrameRect().pos;
    list_[i]->move({newPos.x+kscale*(curPos.x-newPos.x),newPos.y-kscale*(curPos.y - newPos.y)});
    list_[i]->scale(kscale);
  }
}
size_t CompositeShape::getCount() const
{
  return count_;
}
void CompositeShape::addShape(Shape *rhs)
{
  if (!rhs)
  {
    throw std::invalid_argument("Invalid Pointer");
  }
  std::unique_ptr<Shape *[]> temp (new Shape*[count_ + 1]);
  for (size_t i = 0; i < count_; ++i)
  {
    temp[i] = list_[i];
  }
  temp[count_] = rhs;
  count_++;
  list_.swap(temp);
}
void CompositeShape::remove(size_t index)
{
  if (count_ <= 0)
  {
    throw std::out_of_range("List is Empty");
  }
  if ((count_ == 1) && (index == 0))
  {
    clear();
    return;
  }
  std::unique_ptr<Shape *[]> temp(new Shape *[count_ - 1]);
  for (size_t i = 0; i < index; ++i)
  {
    temp[i] = list_[i];
  }
  for (size_t i = index; i < count_ - 1; ++i)
  {
    temp[i] = list_[i + 1];
  }
  list_.swap(temp);
  count_--;
}
void CompositeShape::clear()
{
  list_.reset();
  list_ = nullptr;
  count_ = 0;
}
