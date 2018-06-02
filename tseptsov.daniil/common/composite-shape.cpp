#include "composite-shape.hpp"
#include "shape.hpp"
#include <iostream>
#include <cmath>
#include <memory>

using namespace tseptsov;

tseptsov::CompositeShape::CompositeShape(const std::shared_ptr < tseptsov::Shape > NewSh) :
  list_(nullptr),
  size_(0)
{
  if (NewSh == nullptr) {
    throw std::invalid_argument("Null pointer");
  }
  add(NewSh);
}

tseptsov::CompositeShape::CompositeShape(const tseptsov::CompositeShape &ShapeArray) :
  size_(ShapeArray.size_)
{
  std::unique_ptr < std::shared_ptr < Shape >[] > list(new std::shared_ptr < Shape >[size_]);
  for (size_t i = 0; i < size_; ++i) {
    list[i] = ShapeArray.list_[i];
  }
  list_ = std::move(list);
}

tseptsov::CompositeShape::CompositeShape(tseptsov::CompositeShape &&ShapeArray) noexcept:
  list_(std::move(ShapeArray.list_)),
  size_(ShapeArray.size_)
{
  ShapeArray.size_ = 0;
}

tseptsov::CompositeShape &tseptsov::CompositeShape::operator=(const tseptsov::CompositeShape &ShapeArray)
{
  if (this != &ShapeArray) {
    list_ = std::unique_ptr < std::shared_ptr < Shape >[] >(new std::shared_ptr < Shape >[ShapeArray.size_]);
    size_ = ShapeArray.size_;
    for (size_t i = 0; i < size_; ++i) {
      list_[i] = ShapeArray.list_[i];
    }
  }
  return *this;
}

tseptsov::CompositeShape &tseptsov::CompositeShape::operator=(tseptsov::CompositeShape &&ShapeArray) noexcept
{
  if (this != &ShapeArray) {
    size_ = ShapeArray.size_;
    list_ = std::move(ShapeArray.list_);
    ShapeArray.size_ = 0;
  }
  return *this;
}

std::shared_ptr < tseptsov::Shape > tseptsov::CompositeShape::operator[](unsigned int i) const
{
  if (i >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return list_[i];
}

void tseptsov::CompositeShape::add(const std::shared_ptr < tseptsov::Shape > NewSh)
{
  std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > list(new std::shared_ptr < tseptsov::Shape >[size_ + 1]);
  for (size_t i = 0; i < size_; ++i) {
    list[i] = list_[i];
  }
  list[size_++] = NewSh;
  list_.swap(list);
}

void tseptsov::CompositeShape::remove(size_t i)
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

double tseptsov::CompositeShape::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < size_; i++) {
    area += list_[i]->getArea();
  }
  return area;
}

tseptsov::rectangle_t tseptsov::CompositeShape::getFrameRect() const
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

void tseptsov::CompositeShape::move(const tseptsov::point_t &center)
{
  for (size_t i = 0; i < size_; ++i) {
    list_[i]->move(center.x - list_[i]->getFrameRect().pos.x, center.y - list_[i]->getFrameRect().pos.y);
  }
}

void tseptsov::CompositeShape::move(double Ox, double Oy)
{
  for (size_t i = 0; i < size_; ++i) {
    list_[i]->move(Ox, Oy);
  }
}

void tseptsov::CompositeShape::scale(double coef)
{
  if (coef < 0) {
    throw std::invalid_argument("Scale coef for CompositeShape can't be < 0");
  }
  const point_t pos = getFrameRect().pos;
  for (size_t i = 0; i < size_; ++i) {
    list_[i]->scale(coef);
    const point_t ShapePos = list_[i]->getFrameRect().pos;
    list_[i]->move({pos.x + (ShapePos.x - pos.x) * coef, pos.y + (ShapePos.y - pos.y) * coef});
  }
}

void tseptsov::CompositeShape::OutData() const
{
  std::cout << "Width = " << getFrameRect().width << std::endl;
  std::cout << "Height = " << getFrameRect().height << std::endl;
  std::cout << "Spot of middle on Ox = " << getFrameRect().pos.x << std::endl;
  std::cout << "Spot of middle on Oy = " << getFrameRect().pos.y << std::endl;
  std::cout << "Area of Frame = " << getArea() << std::endl << std::endl;
}

size_t tseptsov::CompositeShape::getSize()
{
  return size_;
}

void tseptsov::CompositeShape::rotate(const double deg)
{
  const point_t center = getFrameRect().pos;
  for (size_t i = 0; i < size_; ++i) {
    list_[i]->rotate(deg);
    list_[i]->move(rotatePoint(center, list_[i]->getCenter(), deg));
  }
}

tseptsov::point_t tseptsov::CompositeShape::rotatePoint(const point_t &center, const point_t &point, const double deg)
{
  const double deg_ = deg * M_PI / 180;
  const double NewX = center.x + (point.x - center.x) * cos(deg_) - (point.y - center.y) * sin(deg_);
  const double NewY = center.y + (point.x - center.x) * sin(deg_) + (point.y - center.y) * cos(deg_);
  return {NewX, NewY};
}

point_t CompositeShape::getCenter() const
{
  return {getFrameRect().pos.x, getFrameRect().pos.y};
}

