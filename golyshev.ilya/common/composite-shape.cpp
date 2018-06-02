#include <iostream>
#include <iomanip>
#include <memory>
#include <cmath>
#include "shape.hpp"
#include "composite-shape.hpp"

using namespace golyshev;

CompositeShape::CompositeShape(const std::shared_ptr<Shape> shape) :
  list_(nullptr),
  size_(0)
{
  add(shape);
}

CompositeShape::CompositeShape(const golyshev::CompositeShape &ShapeArray) :
  size_(ShapeArray.size_)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> list(new std::shared_ptr<Shape>[size_]);
  for (size_t i = 0; i < size_; ++i) {
    list[i] = ShapeArray.list_[i];
  }
  list_ = std::move(list);

}

CompositeShape::CompositeShape(CompositeShape &&ShapeArray) noexcept:
  list_(std::move(ShapeArray.list_)),
  size_(ShapeArray.size_)
{
  ShapeArray.size_ = 0;
}


CompositeShape &CompositeShape::operator=(const CompositeShape &shape)
{
  if (this != &shape) {
    list_ = std::unique_ptr<std::shared_ptr<Shape>[]>(new std::shared_ptr<Shape>[shape.size_]);
    size_ = shape.size_;
    for (size_t i = 0; i < size_; ++i) {
      list_[i] = shape.list_[i];
    }
  }
  return *this;

}

CompositeShape &CompositeShape::operator=(CompositeShape &&ShapeArray) noexcept
{
  if (this != &ShapeArray) {
    size_ = ShapeArray.size_;
    list_ = std::move(ShapeArray.list_);
    ShapeArray.size_ = 0;
  }
  return *this;

}

std::shared_ptr<golyshev::Shape> &CompositeShape::operator[](size_t index) const
{
  if (index >= size_) {
    throw std::out_of_range("Index goes beyond the boundaries of the array!");
  }
  return list_[index];

}

void CompositeShape::add(const std::shared_ptr<golyshev::Shape> shape)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> list(new std::shared_ptr<Shape>[size_ + 1]);
  for (size_t i = 0; i < size_; i++) {
    list[i] = list_[i];
  }
  list[size_++] = shape;
  list_ = std::move(list);
}

void CompositeShape::remove(size_t i)
{
  if (size_ == 0) {
    throw std::invalid_argument("Composite shape is empty");
  }
  if (i >= size_) {
    throw std::out_of_range("Index goes beyond the boundaries of the array!");
  }

  --size_;
  for (size_t j = i; j < size_; ++j) {
    list_[j] = list_[j + 1];
  }
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

void CompositeShape::move(const golyshev::point_t &center)
{
  for (size_t i = 0; i < size_; ++i) {
    list_[i]->move(center.x - getFrameRect().pos.x, center.y - getFrameRect().pos.y);
  }
}

void CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < size_; ++i) {
    list_[i]->move(dx, dy);
  }
}

void CompositeShape::scale(double coeff)
{
  if (coeff < 0) {
    throw std::invalid_argument("Scale multiplier for CompositeShape can't be < 0");
  }
  const point_t pos = getFrameRect().pos;
  for (size_t i = 0; i < size_; ++i) {
    list_[i]->scale(coeff);
    const point_t ShapePos = list_[i]->getFrameRect().pos;
    list_[i]->move({pos.x + (ShapePos.x - pos.x) * coeff, pos.y + (ShapePos.y - pos.y) * coeff});
  }
}

void CompositeShape::rotate(const double angle)
{
  rectangle_t frame = getFrameRect();
  point_t centre_cs = frame.pos;
  for (size_t i = 0; i < size_; i++) {
    point_t point_p = list_[i]->getFrameRect().pos;
    point_t new_point = {centre_cs.x + (point_p.x - centre_cs.x) * cos((angle * M_PI) / 180) -
                         (point_p.y - centre_cs.y) * sin((angle * M_PI) / 180),
                         centre_cs.y + (point_p.y - centre_cs.y) * cos((angle * M_PI) / 180) +
                         (point_p.x - centre_cs.x) * sin((angle * M_PI) / 180)};
    list_[i]->move(new_point);
    list_[i]->rotate(angle);
  }
}

void CompositeShape::OutInf() const
{
  std::cout << "_________________________________________________________" << std::endl;
  std::cout << "Size:   " << std::setprecision(3) << std::fixed << size() << std::endl;
  std::cout << "Area:   " << getArea() << std::endl;
  std::cout << "Width:  " << getFrameRect().width << std::endl;
  std::cout << "Height: " << getFrameRect().height << std::endl;
  std::cout << "Pos(x): " << getFrameRect().pos.x << std::endl;
  std::cout << "Pos(y): " << getFrameRect().pos.y << std::endl;
  std::cout << "_________________________________________________________" << std::endl;
}
