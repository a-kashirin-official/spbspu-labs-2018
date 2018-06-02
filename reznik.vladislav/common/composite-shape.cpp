#include <algorithm>
#include "composite-shape.hpp"

reznik::CompositeShape::CompositeShape():
  arr_(new std::shared_ptr<reznik::Shape>[0]),
  count_(0)
{

}

reznik::CompositeShape::CompositeShape(const CompositeShape & copy) :
  count_(copy.count_)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> Copyarr_(new std::shared_ptr<Shape>[count_]);
  for (size_t i = 0; i < count_; i++)
  {
    Copyarr_[i] = copy.arr_[i];
  }
  arr_.swap(Copyarr_);
}

reznik::CompositeShape::CompositeShape(CompositeShape && other) :
  arr_(nullptr),
  count_(0)
{
  arr_.swap(other.arr_);
  count_ = other.count_;
  other.arr_.release();
  other.count_ = 0;
}

reznik::CompositeShape & reznik::CompositeShape::operator=(CompositeShape && other)
{
  if (this == &other)
  {
    return *this;
  }

  count_ = other.count_;
  std::swap(arr_,other.arr_);
  other.arr_ = nullptr;
  other.count_ = 0;

  return *this;
}

reznik::CompositeShape & reznik::CompositeShape::operator=(const CompositeShape & copy)
{
  if (this == &copy)
  {
    return *this;
  }

  arr_.reset(new std::shared_ptr< Shape >[copy.count_]);
  for (size_t i = 0; i < count_; i++)
  {
    arr_[i] = copy.arr_[i];
  }
  count_ = copy.count_;
  return *this;
}

double reznik::CompositeShape::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < count_; i++)
  {
    area += arr_[i]->getArea();
  }
  return area;
}

reznik::rectangle_t reznik::CompositeShape::getFrameRect() const
{
  rectangle_t rect = arr_[0]->getFrameRect();
  double minX = rect.pos.x - rect.width / 2;
  double maxX = rect.pos.x + rect.width / 2;
  double minY = rect.pos.y - rect.height / 2;
  double maxY = rect.pos.y + rect.height / 2;
  for (size_t i = 1; i < count_; i++)
  {
    rect = arr_[i]->getFrameRect();
    minX = std::min(minX, rect.pos.x - rect.width / 2);
    maxX = std::max(maxX, rect.pos.x + rect.width / 2);
    minY = std::min(minY, rect.pos.y - rect.height / 2);
    maxY = std::max(maxY, rect.pos.y + rect.height / 2);
  }
  return { maxX - minX, maxY - minY,{ maxX - (maxX - minX) / 2, maxY - (maxY - minY) / 2 } };
}

void reznik::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < count_; i++)
  {
    arr_[i]->move(dx, dy);
  }
}

void reznik::CompositeShape::move(const point_t & center)
{
  point_t pos = getFrameRect().pos;
  for (size_t i = 0; i < count_; i++)
  {
    arr_[i]->move(center.x - pos.x, center.y - pos.y);
  }
}

void reznik::CompositeShape::scale(double k)
{
  if (k < 0)
  {
    throw std::invalid_argument("Error: negative argument scale!");
  }
  point_t tmp_centre = getFrameRect().pos;
  for (size_t i = 0; i < count_; i++)
  {
    arr_[i]->move({ tmp_centre.x + (arr_[i]->getFrameRect().pos.x - tmp_centre.x) * k,
                   tmp_centre.y + (arr_[i]->getFrameRect().pos.y - tmp_centre.y) * k });
    arr_[i]->scale(k);
  }
}

void reznik::CompositeShape::addShape(const std::shared_ptr<Shape> shape)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> newEllement(new std::shared_ptr<Shape>[count_ + 1]);
  for (size_t i = 0; i < count_; i++)
  {
    newEllement[i] = arr_[i];
  }
  newEllement[count_++] = shape;
  arr_.swap(newEllement);
}
