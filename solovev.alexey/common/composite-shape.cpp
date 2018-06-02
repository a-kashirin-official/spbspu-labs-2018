#include "composite-shape.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>

using namespace solovev;

CompositeShape::CompositeShape():
  countShapes_(0),
  shapes_(nullptr)
{
}

CompositeShape::CompositeShape(const std::shared_ptr<Shape> &shape):
  countShapes_(0),
  shapes_(nullptr)
{
  if (!shape)
  {
    throw std::invalid_argument("Error. Invalid pointer shape");
  }
  addShape(shape);
}

CompositeShape::CompositeShape(const CompositeShape& object):
  countShapes_(object.getCount())
{
  std::unique_ptr<std::shared_ptr <Shape>[]> copyObject (new std::shared_ptr<Shape>[object.getCount()]);
  for (size_t i = 0; i < object.getCount(); i++)
  {
    copyObject[i] = object.shapes_[i];
  }
  shapes_.swap(copyObject);
}

CompositeShape::CompositeShape(CompositeShape&& object):
  countShapes_(object.getCount())
{
  shapes_.swap(object.shapes_);
}

CompositeShape& CompositeShape::operator=(const CompositeShape& otherObj)
{
  if (this != &otherObj)
  {
    countShapes_ = otherObj.getCount();
    std::unique_ptr<std::shared_ptr<Shape>[]> copyObject (new std::shared_ptr<Shape>[otherObj.getCount()]);
    for (size_t i=0; i < otherObj.getCount(); i++)
    {
      copyObject[i] = otherObj.shapes_[i];
    }
    shapes_.swap(copyObject);
  }
  return *this;
}

std::shared_ptr<Shape> CompositeShape::operator[](const unsigned int index) const
{
  if (index >= countShapes_ || index <= 0)
  {
    throw std::out_of_range("Index is out of range");
  }
  return shapes_[index];
}

void CompositeShape::addShape(const std::shared_ptr<Shape>& shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Incorrect pointer");
  }

  if (shape.get() == this)
  {
    throw std::invalid_argument("This is the same shape (Addresses are the same)");
  }

  std::unique_ptr <std::shared_ptr<Shape>[]> tempArray (new std::shared_ptr<Shape>[countShapes_ + 1]);

  for (size_t i=0; i < countShapes_; i++)
  {
    tempArray[i] = shapes_[i];
  }

  tempArray[countShapes_] = shape;
  shapes_.swap(tempArray);
  countShapes_++;
}

void CompositeShape::rmShape(const unsigned int index)
{
  if (index >= countShapes_)
  {
    throw std::out_of_range("Index is out of range");
  }
  if (countShapes_ <= 0)
  {
    throw std::invalid_argument("Composite figure consist of 0 figures");
  }
  if (countShapes_ == 1)
  {
    clear();
    return;
  }
  else
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> temp (new std::shared_ptr<Shape>[countShapes_-1]);
    for (size_t i = 0; i < index; i++)
    {
      temp[i] = shapes_[i];
    }
    for (size_t i = index; i<countShapes_ - 1; i++)
    {
      temp[i] = shapes_[i + 1];
    }
    shapes_.swap(temp);
    countShapes_ --;
  }
}

size_t CompositeShape::getCount() const
{
  return countShapes_;
}

void CompositeShape::move(const point_t newxy)
{
  const point_t pos = getFrameRect().pos;
  move(newxy.x - pos.x, newxy.y - pos.y);
}

void CompositeShape::move(const double dx, const double dy)
{
  for (size_t i = 0; i < countShapes_; i++)
  {
    shapes_[i]->move(dx, dy);
  }
}

void CompositeShape::scale(double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  const point_t pos = getFrameRect().pos;
  for (size_t i = 0; i < countShapes_; i++)
  {
    shapes_[i]->move({pos.x + (shapes_[i]->getFrameRect().pos.x - pos.x) * factor,
    pos.y + (shapes_[i]->getFrameRect().pos.y - pos.y) * factor});
    shapes_[i]->scale(factor);
  }
}

double CompositeShape::getArea() const
{
  double area = 0.0;
  for (size_t i = 0; i < countShapes_; i++)
  {
    area += shapes_[i]->getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  if (countShapes_ <= 0)
  {
    return {NAN, NAN, {NAN, NAN}};
  }
  else
  {
    rectangle_t rectangle = shapes_[0]->getFrameRect();
    double maxX = rectangle.pos.x + rectangle.width / 2;
    double maxY = rectangle.pos.y + rectangle.height / 2;
    double minX = rectangle.pos.x - rectangle.width / 2;
    double minY = rectangle.pos.y - rectangle.height / 2;

    for (size_t i = 1; i < countShapes_; i++)
    {
      rectangle = shapes_[i]->getFrameRect();
      point_t pos = shapes_[i]->getFrameRect().pos;
      double nowMaxX = pos.x + rectangle.width / 2;
      double nowMinX = pos.x - rectangle.width / 2;
      double nowMaxY = pos.y + rectangle.height / 2;
      double nowMinY = pos.y - rectangle.height / 2;
      if (nowMinX < minX)
      {
        minX = nowMinX;
      }
      if (nowMaxX > maxX)
      {
        maxX = nowMaxX;
      }
      if (nowMinY < minY)
      {
        minY = nowMinY;
      }
      if (nowMaxY > maxY)
      {
        maxY = nowMaxY;
      }
    }
    return {(maxX - minX), (maxY - minY), {((maxX + minX) / 2), ((maxY + minY) / 2)}};
  }
}

void CompositeShape::clear()
{
  shapes_.reset();
  shapes_ = nullptr;
  countShapes_ = 0;
}
