#define _USE_MATH_DEFINES

#include "composite-shape.hpp"
#include <cmath>
#include <iostream>

mihajlov::CompositeShape::CompositeShape():
  arrSize_(0),
  shapeArr_(nullptr),
  angle_(0.0)
{
}

mihajlov::CompositeShape::CompositeShape(const std::shared_ptr<mihajlov::Shape>& shape):
  arrSize_(1),
  shapeArr_(new std::shared_ptr<Shape>[1])
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Error! Shape expected, not a nullptr!");
  }
  shapeArr_[0] = shape;
}

const mihajlov::Shape& mihajlov::CompositeShape::operator[](int index) const
{
  if (index >= arrSize_ || index < 0)
  {
    throw std::out_of_range("Error! Out of range!");
  }
  return *shapeArr_[index];
}

void mihajlov::CompositeShape::addShape(const std::shared_ptr<mihajlov::Shape>& shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Error! Shape expected, not a nullptr!");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> tempArr(new std::shared_ptr<Shape>[arrSize_ + 1]);
  for (int i = 0; i < arrSize_; i++)
  {
    tempArr[i] = shapeArr_[i];
  }

  tempArr[arrSize_] = shape;
  shapeArr_ = std::move(tempArr);
  arrSize_++;
}

double mihajlov::CompositeShape::getArea() const
{
  if (arrSize_ != 0)
  {
    double area = 0.0;
    for (int i = 0; i < arrSize_; i++)
    {
      area += shapeArr_[i]->getArea();
    }
    return area;
  }
  else
  {
    throw std::logic_error("Empy composite-shape!");
  }
}

mihajlov::rectangle_t mihajlov::CompositeShape::getFrameRect() const
{
  if (arrSize_ != 0)
  {
    rectangle_t frameRect = shapeArr_[0]->getFrameRect();
    double minX = frameRect.pos.x - frameRect.width / 2;
    double minY = frameRect.pos.y - frameRect.height / 2;
    double maxX = frameRect.pos.x + frameRect.width / 2;
    double maxY = frameRect.pos.y + frameRect.height / 2;
    point_t minXY = {minX, minY};
    point_t maxXY = {maxX, maxY};

    for (int i = 1; i < arrSize_; i++)
    {
      frameRect = shapeArr_[i]->getFrameRect();
      minX = frameRect.pos.x - frameRect.width / 2;
      minY = frameRect.pos.y - frameRect.height / 2;
      maxX = frameRect.pos.x + frameRect.width / 2;
      maxY = frameRect.pos.y + frameRect.height / 2;

      if (minX < minXY.x)
      {
        minXY.x = minX;
      }

      if (minY < minXY.y)
      {
        minXY.y = minY;
      }

      if (maxX > maxXY.x)
      {
        maxXY.x = maxX;
      }

      if (maxY > maxXY.y)
      {
        maxXY.y = maxY;
      }
    }
    point_t center = {minXY.x + (maxXY.x - minXY.x) / 2, minXY.y + (maxXY.y - minXY.y) / 2};
    return {center, maxXY.y - minXY.y, maxXY.x - minXY.x};
  }
  else
  {
    throw std::logic_error("Can't get frame from nothing!");
  }
}

void mihajlov::CompositeShape::move(const mihajlov::point_t& centerPos)
{
  point_t center = getFrameRect().pos;
  move(centerPos.x - center.x, centerPos.y - center.y);
}

void mihajlov::CompositeShape::move(const double shiftX, const double shiftY)
{
  for (int i = 0; i < arrSize_; i++)
  {
    shapeArr_[i]->move(shiftX, shiftY);
  }
}

void mihajlov::CompositeShape::scale(double multiplier)
{
  if (multiplier < 0.0)
  {
    throw std::invalid_argument("Negative multiplier!");
  }
  if (arrSize_ == 0)
  {
    throw std::logic_error("Can't scale that not exist!");
  }

  point_t center = getFrameRect().pos;


  for (int i = 0; i < arrSize_; i++)
  {
    point_t centerShape = shapeArr_[i]->getFrameRect().pos;

    shapeArr_[i]->move({
                               center.x + multiplier * (centerShape.x - center.x),
                               center.y + multiplier * (centerShape.y - center.y)
                       });
    shapeArr_[i]->scale(multiplier);
  }
}

void mihajlov::CompositeShape::getInfo() const
{
  const rectangle_t frame = getFrameRect();
  std::cout << "Composite shape: " << std::endl;
  std::cout << "Frame properties: Height = " << frame.height << "; Width = " << frame.width << ";" << std::endl;
  std::cout << "CenterPos: X = {" << frame.pos.x << ", " << frame.pos.y << "}; " << std::endl;
  std::cout << "Area of composite-shape: " << getArea() << "." << std::endl;
}

void mihajlov::CompositeShape::printName() const
{
  std::cout << "CompositeShape ";
}

void mihajlov::CompositeShape::rotate(const double angle)
{
  angle_ += angle;

  double currentAngle = angle * M_PI / 180;
  double selfAngle = 0;
  point_t center = getFrameRect().pos;

  for (int i = 0; i < arrSize_; i++)
  {
    point_t centerShape = shapeArr_[i]->getFrameRect().pos;
    double radius = sqrt(pow(center.x - centerShape.x, 2) + pow(center.y - centerShape.y, 2));

    if (centerShape.y > center.y)
    {
      selfAngle = acos((centerShape.x - center.x) / radius);
    }
    else
    {
      selfAngle = 2 * M_PI - acos((centerShape.x - center.x) / radius);
    }
    shapeArr_[i]->move((cos(selfAngle + currentAngle) - cos(selfAngle)) * radius,
                       (sin(selfAngle + currentAngle) - sin(selfAngle)) * radius);
    shapeArr_[i]->rotate(angle);
  }
}

void mihajlov::CompositeShape::remove(const int index)
{
  if (index >= arrSize_ || index < 0)
  {
    throw std::out_of_range("Error! Out of range!");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> tempArr(new std::shared_ptr<Shape>[arrSize_ - 1]);
  for (int i = 0; i < index; i++)
  {
    tempArr[i] = shapeArr_[i];
  }

  for (int i = index; i < arrSize_ - 1; i++)
  {
    tempArr[i] = shapeArr_[i + 1];
  }
  shapeArr_.swap(tempArr);
  arrSize_--;
}
