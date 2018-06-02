//
// Created by 811432 on 06.05.2018.
//
#include "composite-shape.hpp"
#include <iostream>
#include <memory>
#include <cmath>

double turkin::CompositeShape::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < size_; i++) {
    area += array_[i]->getArea();
  }
  return area;
}

turkin::rectangle_t turkin::CompositeShape::getFrameRect() const
{
  if (size_ == 0) {
    return {0, 0, {0, 0}};
  }

  double MaxX = array_[0]->getFrameRect().pos.x + array_[0]->getFrameRect().width / 2;
  double MaxY = array_[0]->getFrameRect().pos.y + array_[0]->getFrameRect().height / 2;
  double MinX = array_[0]->getFrameRect().pos.x - array_[0]->getFrameRect().width / 2;
  double MinY = array_[0]->getFrameRect().pos.y - array_[0]->getFrameRect().height / 2;
  double width = 0, height = 0, x = 0, y = 0;

  for (size_t i = 1; i < size_; ++i) {
    width = array_[i]->getFrameRect().width;
    height = array_[i]->getFrameRect().height;
    x = array_[i]->getFrameRect().pos.x;
    y = array_[i]->getFrameRect().pos.y;
    MaxX = (x + width / 2 > MaxX) ? (x + width / 2) : MaxX;
    MaxY = (y + height / 2 > MaxY) ? (y + height / 2) : MaxY;
    MinX = (x - width / 2 < MinX) ? (x - width / 2) : MinX;
    MinY = (y - height / 2 < MinY) ? (y - height / 2) : MinY;
  }
  return {MaxX - MinX, MaxY - MinY, {MinX + (MaxX - MinX) / 2, MinY + (MaxY - MinY) / 2}};

}

void turkin::CompositeShape::move(const turkin::point_t &center)
{
  for (size_t i = 0; i < size_; ++i) {
    array_[i]->move(center.x - array_[i]->getFrameRect().pos.x, center.y - array_[i]->getFrameRect().pos.y);
  }

}

void turkin::CompositeShape::move(double Ox, double Oy)
{
  for (size_t i = 0; i < size_; ++i) {
    array_[i]->move(Ox, Oy);
  }
}

void turkin::CompositeShape::scale(double k)
{
  if (k < 0) {
    throw std::invalid_argument("Scale k for CompositeShape can't be < 0");
  }
  const point_t pos = getFrameRect().pos;
  for (size_t i = 0; i < size_; ++i) {
    array_[i]->scale(k);
    const point_t ShapePos = array_[i]->getFrameRect().pos;
    array_[i]->move({pos.x + (ShapePos.x - pos.x) * k, pos.y + (ShapePos.y - pos.y) * k});
  }

}

std::shared_ptr<turkin::Shape> turkin::CompositeShape::operator[](unsigned int i) const
{
  if (i >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return array_[i];
}

void turkin::CompositeShape::del(size_t i)
{
  if (size_ == 0) {
    throw std::invalid_argument("Composite shape is empty");
  }
  if (i >= size_) {
    throw std::out_of_range("Index out of range");
  }
  --size_;
  for (size_t j = i; j < size_; ++j) {
    array_[j] = array_[j + 1];
  }
}

void turkin::CompositeShape::add(const std::shared_ptr<turkin::Shape> NewSh)
{
  std::unique_ptr<std::shared_ptr<turkin::Shape>[]> list(new std::shared_ptr<turkin::Shape>[size_ + 1]);
  for (size_t i = 0; i < size_; ++i) {
    list[i] = array_[i];
  }
  list[size_++] = NewSh;
  array_.swap(list);
}

turkin::CompositeShape::CompositeShape(const std::shared_ptr<turkin::Shape> NewSh) :
  array_(nullptr),
  size_(0)
{
  if (NewSh == nullptr) {
    throw std::invalid_argument("Null pointer");
  }
  add(NewSh);
}

void turkin::CompositeShape::printInfo()
{
  std::cout << "Array: " << std::endl;
}

size_t turkin::CompositeShape::getSize()const
{
  return size_;
}

turkin::CompositeShape::CompositeShape(const turkin::CompositeShape &ShapeArray) :
  size_(ShapeArray.size_)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> list(new std::shared_ptr<Shape>[size_]);
  for (size_t i = 0; i < size_; ++i) {
    list[i] = ShapeArray.array_[i];
  }
  array_ = std::move(list);

}

turkin::CompositeShape::CompositeShape(turkin::CompositeShape &&ShapeArray) noexcept:
  array_(std::move(ShapeArray.array_)),
  size_(ShapeArray.size_)
{
  ShapeArray.size_ = 0;
}


turkin::CompositeShape &turkin::CompositeShape::operator=(const turkin::CompositeShape &ShapeArray)
{
  if (this != &ShapeArray) {
    array_ = std::unique_ptr<std::shared_ptr<Shape>[]>(new std::shared_ptr<Shape>[ShapeArray.size_]);
    size_ = ShapeArray.size_;
    for (size_t i = 0; i < size_; ++i) {
      array_[i] = ShapeArray.array_[i];
    }
  }
  return *this;
}

turkin::CompositeShape &turkin::CompositeShape::operator=(turkin::CompositeShape &&ShapeArray) noexcept
{
  if (this != &ShapeArray) {
    size_ = ShapeArray.size_;
    array_ = std::move(ShapeArray.array_);
    ShapeArray.size_ = 0;
  }
  return *this;
}

void turkin::CompositeShape::rotate(double angle)
{
  const point_t center = getFrameRect().pos;
  double radians = angle * M_PI / 180;
  for (size_t i = 0; i < size_; ++i) {
    array_[i]->rotate(angle);
    array_[i]->move({center.x + (array_[i]->getCenter().x - center.x) * cos(radians) -
                     (array_[i]->getCenter().y - center.y) * sin(radians),
                     center.y + (array_[i]->getCenter().x - center.x) * sin(radians) +
                     (array_[i]->getCenter().y - center.y) * cos(radians)});
  }

}

turkin::point_t turkin::CompositeShape::getCenter() const
{
  return {getFrameRect().pos.x, getFrameRect().pos.y};
}


