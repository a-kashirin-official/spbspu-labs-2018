#include "composite-shape.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace khodyreva;

CompositeShape::CompositeShape(const std::shared_ptr <Shape> & newShape):
  data_(new std::shared_ptr<Shape>[1]),
  size_(1)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Empty shape");
  }
  data_[0] = newShape;
}


CompositeShape::CompositeShape(const CompositeShape & object):
  size_(object.size_)
{
  std::unique_ptr <std::shared_ptr<Shape>[]> shpCopy(new std::shared_ptr<Shape>[size_]);
  for(size_t i=0; i < size_; i++)
  {
    shpCopy[i]=object.data_[i];
  }
  data_.swap(shpCopy);
}

CompositeShape::CompositeShape(CompositeShape && object):
  size_(object.size_)
{
  data_=std::move(object.data_);
  object.data_=(nullptr);
  object.size_=0;
}

CompositeShape & CompositeShape::operator=(const CompositeShape & object)
{
  if (this != &object)
  {
    size_=object.size_;
    std::unique_ptr <std::shared_ptr<Shape>[]> shpCopy(new std::shared_ptr<Shape>[size_]);
    for(size_t i=0; i<size_; i++)
    {
      shpCopy[i]=object.data_[i];
    }
    data_.swap(shpCopy);
  }
  return *this;
}

CompositeShape & CompositeShape::operator= (CompositeShape && object)
{
  if (this != &object)
  {
    size_=object.size_;
    data_=std::move(object.data_);
    object.data_=(nullptr);
    object.size_=0;
  }
  return *this;
}

std::shared_ptr<Shape> & CompositeShape::operator[] (size_t index) const
{
  if(index >= size_)
  {
    throw std::out_of_range("Index is out of range");
  }
  return data_[index];
}

void CompositeShape::addShape(const std::shared_ptr<Shape> & newShape)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Empty shape");
  }
  std::unique_ptr <std::shared_ptr<Shape>[]> temp (new std::shared_ptr<Shape>[size_ + 1]);
  for (size_t i = 0; i < size_; i++)
  {
    temp[i] = data_[i];
  }
  temp[size_] = newShape;
  size_++;
  data_.swap(temp);
}

void CompositeShape::deleteShape(size_t index)
{
  {
    if (size_ == 0)
    {
      throw std::invalid_argument("Composite shape is empty");
    }
    if (index >= size_)
    {
      throw std::invalid_argument("Wrong index");
    }
    for (size_t i = index; i < size_ - 1; i++)
    {
      data_[i] = data_[i + 1];
    }
    data_[size_ - 1] = nullptr;
    size_--;
  }
}

size_t CompositeShape::getSize() const
{
  return size_;
}

void CompositeShape::move(const point_t & centre)
{
  double dx = centre.x - getFrameRect().pos.x;
  double dy = centre.y - getFrameRect().pos.y;
  move(dx, dy);
}


void CompositeShape::move(const double dx, const double dy)
{
  for (size_t i = 0; i < size_; i++)
  {
    data_[i]->move(dx, dy);
  }
}


void CompositeShape::scale(const double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Invalid ratio");
  }
  point_t compCenter = getFrameRect().pos;
  for (size_t i = 0; i < size_; i++)
  {
    double dx = data_[i]->getFrameRect().pos.x - compCenter.x;
    double dy = data_[i]->getFrameRect().pos.y - compCenter.y;
    point_t newPos;
    newPos.x = compCenter.x + ratio*dx;
    newPos.y = compCenter.y + ratio*dy;
    data_[i]->move(newPos);
    data_[i]->scale(ratio);
  }
}

double CompositeShape::getArea() const
{
  double wholearea = 0.0;
  for (size_t i = 0; i < size_; i++)
  {
    wholearea += data_[i]->getArea();
  }
  return wholearea;
}

rectangle_t CompositeShape::getFrameRect() const
{
  {
  if (size_ == 0)
    {
      return {{0, 0}, 0, 0};
    }
    double MaxX = data_[0]->getFrameRect().pos.x + data_[0]->getFrameRect().width / 2;
    double MaxY = data_[0]->getFrameRect().pos.y + data_[0]->getFrameRect().height / 2;
    double MinX = data_[0]->getFrameRect().pos.x - data_[0]->getFrameRect().width / 2;
    double MinY = data_[0]->getFrameRect().pos.y - data_[0]->getFrameRect().height / 2;
    double width = 0, height = 0, x = 0, y = 0;
    for (size_t i = 1; i < size_; ++i)
    {
      width = data_[i]->getFrameRect().width;
      height = data_[i]->getFrameRect().height;
      x = data_[i]->getFrameRect().pos.x;
      y = data_[i]->getFrameRect().pos.y;
      MaxX = (x + width / 2 > MaxX) ? (x + width / 2) : MaxX;
      MaxY = (y + height / 2 > MaxY) ? (y + height / 2) : MaxY;
      MinX = (x - width / 2 < MinX) ? (x - width / 2) : MinX;
      MinY = (y - height / 2 < MinY) ? (y - height / 2) : MinY;
    }
  return {{MinX + (MaxX - MinX) / 2, MinY + (MaxY - MinY) / 2}, MaxX - MinX, MaxY - MinY};
  }
}

void CompositeShape::rotate(double angle)
{
  double cosA = cos(angle * M_PI / 180);
  double sinA = sin(angle * M_PI / 180);

  point_t center = getFrameRect().pos;

  for (size_t i = 0; i < size_; i++)
  {
    point_t shape_center = data_[i]->getFrameRect().pos;

    data_[i]->move({center.x + cosA * (shape_center.x - center.x)
                    - sinA * (shape_center.y - center.y),
                      center.y + cosA * (shape_center.y - center.y)
                        + sinA * (shape_center.x - center.x)});
    data_[i]->rotate(angle);
  }
}

std::string CompositeShape::getName() const
{
  return "CompositeShape";
}
