#include "composite-shape.hpp"
#include <iostream>
#include <cmath>

using namespace lashchenov;

CompositeShape::CompositeShape() :
  list_(nullptr),
  size_(0)
{
}

CompositeShape::CompositeShape(const Shape & shape) :
  list_(new std::shared_ptr<Shape>[1]),
  size_(1)
{
  list_[0] = shape.getCopy();
}

CompositeShape::CompositeShape(const CompositeShape & ShapeArray) :
  size_(ShapeArray.size_)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> tmp(new std::shared_ptr<Shape>[size_]);
  for (size_t i = 0; i < size_; ++i) {
    tmp[i] = ShapeArray.list_[i]->getCopy();
  }
  list_ = std::move(tmp);
}

CompositeShape::CompositeShape(CompositeShape && ShapeArray) noexcept :
  list_(std::move(ShapeArray.list_)),
  size_(ShapeArray.size_)
{

  ShapeArray.list_.reset();
  ShapeArray.size_ = 0;
}

CompositeShape & CompositeShape::operator=(const CompositeShape & ShapeArray)
{
  if (this != &ShapeArray) {
    size_ = ShapeArray.size_;
    std::unique_ptr<std::shared_ptr<Shape>[]> tmp(new std::shared_ptr<Shape>[size_]);
    for (size_t i = 0; i < size_; ++i) {
      tmp[i] = ShapeArray.list_[i]->getCopy();
    }
    list_ = std::move(tmp);
  }
  return *this;
}

CompositeShape & CompositeShape::operator=(CompositeShape && ShapeArray) noexcept
{
  if (this != &ShapeArray) {
    size_ = ShapeArray.size_;
    list_ = std::move(ShapeArray.list_);
    ShapeArray.list_.reset();
    ShapeArray.size_ = 0;
  }
  return *this;
}

Shape & CompositeShape::operator[](const size_t i) const
{
  if (i >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return *list_[i];
}

void CompositeShape::add(const Shape & shape)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> tmp(new std::shared_ptr<Shape>[size_ + 1]);
  for (size_t i = 0; i < size_; ++i) {
    tmp[i] = list_[i];
  }
  tmp[size_++] = shape.getCopy();
  list_ = std::move(tmp);
}

void CompositeShape::remove(const size_t i)
{
  if (size_ == 0) {
    throw std::invalid_argument("Composite shape is empty");
  }
  if (i >= size_) {
    throw std::out_of_range("Index out of range");
  }

  --size_;
  for (size_t j = i; j < size_; ++j) {
    list_[j] = list_[j + 1];
  }
}

void CompositeShape::clear()
{
  for (size_t i = 0; i < size_; ++i) {
    list_[i].reset();
  }
  this->list_.reset();
  size_ = 0;
}

size_t CompositeShape::size() const
{
  return size_;
}

double CompositeShape::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < size_; ++i) {
    area += list_[i]->getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  if (size_ == 0) {
    return {0, 0, {0, 0}};
  }

  double MaxX = list_[0]->getFrameRect().pos.x + list_[0]->getFrameRect().width / 2;
  double MaxY = list_[0]->getFrameRect().pos.y + list_[0]->getFrameRect().height / 2;
  double MinX = list_[0]->getFrameRect().pos.x - list_[0]->getFrameRect().width / 2;
  double MinY = list_[0]->getFrameRect().pos.y - list_[0]->getFrameRect().height / 2;
  double width = 0, height = 0, x = 0, y = 0;

  for (size_t i = 1; i < size_; ++i) {
    width = list_[i]->getFrameRect().width;
    height = list_[i]->getFrameRect().height;
    x = list_[i]->getFrameRect().pos.x;
    y = list_[i]->getFrameRect().pos.y;
    MaxX = (x + width / 2 > MaxX) ? (x + width / 2) : MaxX;
    MaxY = (y + height / 2 > MaxY) ? (y + height / 2) : MaxY;
    MinX = (x - width / 2 < MinX) ? (x - width / 2) : MinX;
    MinY = (y - height / 2 < MinY) ? (y - height / 2) : MinY;
  }
  return {MaxX - MinX, MaxY - MinY, {MinX + (MaxX - MinX) / 2, MinY + (MaxY - MinY) / 2}};
}

void CompositeShape::move(const point_t & NewCenter)
{
  for (size_t i = 0; i < size_; ++i) {
    list_[i]->move(NewCenter.x - getFrameRect().pos.x, NewCenter.y - getFrameRect().pos.y);
  }
}

void CompositeShape::move(const double dx, const double dy)
{
  for (size_t i = 0; i < size_; ++i) {
    list_[i]->move(dx, dy);
  }
}

void CompositeShape::scale(const double multiplier)
{
  if (multiplier < 0) {
    throw std::invalid_argument("Scale multiplier for CompositeShape can't be < 0");
  }
  const point_t pos = getFrameRect().pos;
  for (size_t i = 0; i < size_; ++i) {
    list_[i]->scale(multiplier);
    const point_t ShapePos = list_[i]->getFrameRect().pos;
    list_[i]->move({pos.x + (ShapePos.x - pos.x) * multiplier, pos.y + (ShapePos.y - pos.y) * multiplier});
  }
}

void CompositeShape::rotate(const double degrees)
{
  const point_t center = getFrameRect().pos;
  for (size_t i = 0; i < size_; ++i) {
    list_[i]->rotate(degrees);
    list_[i]->move(rotatePoint(center, list_[i]->getFrameRect().pos, degrees));
  }
}

std::unique_ptr<Shape> CompositeShape::getCopy() const
{
  return std::unique_ptr<Shape>(new CompositeShape(*this));
}

void CompositeShape::printInfo() const
{
  std::cout << "CompositeShape:";
  std::cout << "  Size - " << size_ << ";  Area - " << getArea() << ";";
  std::cout << "  FrameRectangle:";
  const rectangle_t rectangle = getFrameRect();
  std::cout << " Width - " << rectangle.width << ", ";
  std::cout << "Height - " << rectangle.height << ", ";
  std::cout << "x = " << rectangle.pos.x << ", ";
  std::cout << "y = " << rectangle.pos.y << std::endl;
}

point_t CompositeShape::rotatePoint(const point_t & center, const point_t & point, const double degrees)
{
  const double radians = degrees * M_PI / 180;
  const double NewX = center.x + (point.x - center.x) * cos(radians) - (point.y - center.y) * sin(radians);
  const double NewY = center.y + (point.x - center.x) * sin(radians) + (point.y - center.y) * cos(radians);
  return {NewX, NewY};
}
