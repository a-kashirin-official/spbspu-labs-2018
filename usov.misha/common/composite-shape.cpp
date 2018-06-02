#include "composite-shape.hpp"
#include <algorithm>

usov::CompositeShape::CompositeShape(const std::shared_ptr<Shape> shape):
  arr_(nullptr),
  count_(0)
{
  if(shape == nullptr)
  {
    throw std::invalid_argument("Error: try to adding nullptr");
  }
  addShape(shape);
}

usov::CompositeShape::CompositeShape(const CompositeShape & copy) :
  count_(copy.count_)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> CopyArr(new std::shared_ptr<Shape>[count_]);
  for (int i = 0; i < count_; i++)
  {
    CopyArr[i] = copy.arr_[i];
  }
  arr_.swap(CopyArr);
}

usov::CompositeShape::CompositeShape(CompositeShape && other) :
  arr_(nullptr),
  count_(other.count_)
{
  arr_.swap(other.arr_);
  other.arr_.reset();
  other.count_ = 0;
}

usov::CompositeShape & usov::CompositeShape::operator=(CompositeShape && other)
{
 if (this != &other)
 {
   arr_.swap(other.arr_);
   count_ = other.count_;
   other.count_ = 0;
   other.arr_.reset();
 }
 else
 {
   throw std::invalid_argument("Error: same object");
 }
 return *this;
}

std::shared_ptr<usov::Shape> usov::CompositeShape::getInfoShape(const int counter)
{
  return arr_[counter];
}

usov::CompositeShape & usov::CompositeShape::operator=(const CompositeShape & copy)
{
  if (this != &copy)
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> newMass(new std::shared_ptr<Shape>[copy.count_]);
    for (int i = 0; i < copy.count_; i++)
    {
      newMass[i] = copy.arr_[i];
    }
    arr_.swap(newMass);
    count_ = copy.count_;
  }
  else
  {
    throw std::invalid_argument("Error: same object");
  }
  return *this;
}

double usov::CompositeShape::getArea() const
{
  double area = 0;
  for (int i = 0; i < count_; i++)
  {
    area += arr_[i]->getArea();
  }
  return area;
}

usov::rectangle_t usov::CompositeShape::getFrameRect() const
{
  rectangle_t rect = arr_[0]->getFrameRect();
  double minX = rect.pos.x - rect.width / 2;
  double maxX = rect.pos.x + rect.width / 2;
  double minY = rect.pos.y - rect.height / 2;
  double maxY = rect.pos.y + rect.height / 2;
  for (int i = 1; i < count_; i++)
  {
    rect = arr_[i]->getFrameRect();
    minX = std::min(minX, rect.pos.x - rect.width / 2);
    maxX = std::max(maxX, rect.pos.x + rect.width / 2);
    minY = std::min(minY, rect.pos.y - rect.height / 2);
    maxY = std::max(maxY, rect.pos.y + rect.height / 2);
  }
  return { maxX - minX, maxY - minY,{ maxX - (maxX - minX) / 2, maxY - (maxY - minY) / 2 } };
}

void usov::CompositeShape::move(double dx, double dy)
{
  for (int i = 0; i < count_; i++)
  {
    arr_[i]->move(dx, dy);
  }
}

void usov::CompositeShape::move(const point_t & center)
{
  point_t pos = getFrameRect().pos;
  for (int i = 0; i < count_; i++)
  {
    arr_[i]->move(center.x - pos.x, center.y - pos.y);
  }
}

void usov::CompositeShape::scale(double dscale)
{
  if (dscale < 0)
  {
    throw std::invalid_argument("Error: negative argument scale!");
  }
  point_t tmp_centre = getFrameRect().pos;
  for (int i = 0; i < count_; i++)
  {
    arr_[i]->move({ tmp_centre.x + (arr_[i]->getFrameRect().pos.x - tmp_centre.x) * dscale,
    tmp_centre.y + (arr_[i]->getFrameRect().pos.y - tmp_centre.y) * dscale });
    arr_[i]->scale(dscale);
  }
}

void usov::CompositeShape::print() const
{
  std::cout << "Size of composite: " << count_ << std::endl;
}

void usov::CompositeShape::addShape(const std::shared_ptr<Shape> shape)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> newEllement(new std::shared_ptr<Shape>[count_ + 1]);
  for (int i = 0; i < count_; i++)
  {
    newEllement[i] = arr_[i];
  }
  newEllement[count_++] = shape;
  arr_.swap(newEllement);
}
