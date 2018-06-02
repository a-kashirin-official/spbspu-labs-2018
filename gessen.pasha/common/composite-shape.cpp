#include "composite-shape.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace gessen;

gessen::CompositeShape::CompositeShape():
  shapeList_(new Shape*[0]),
  shapeCounter_(0)
{

}

gessen::CompositeShape::CompositeShape(Shape * shapeElement):
  shapeList_(new Shape *[1]),
  shapeCounter_(0)
{
  if (shapeElement == nullptr)
  {
    throw std::invalid_argument("Error. No object.");
  }
  shapeList_[0] = shapeElement;
  shapeCounter_++;
}

CompositeShape::CompositeShape(CompositeShape &&shp):
  shapeList_(nullptr),
  shapeCounter_(0)
{
  *this = std::move(shp);
}

CompositeShape::CompositeShape(const CompositeShape &shp):
  shapeList_(new Shape *[shp.shapeCounter_]),
  shapeCounter_(shp.shapeCounter_)
{
  for (int i = 0; i < shapeCounter_; i++)
  {
    shapeList_[i] = shp.shapeList_[i];
  }
}

CompositeShape::~CompositeShape()
{
  for (int i = 0; i<shapeCounter_; i++)
  {
    delete shapeList_[i];
  }
}

Shape *CompositeShape::operator[](int num) const
{
  if (num>shapeCounter_)
  {
    throw std::invalid_argument("Invalid_value");
  }
  return shapeList_[num];
}

CompositeShape &CompositeShape::operator = (CompositeShape &shp)
{
  if(this!=&shp)
  {
    shapeCounter_ = shp.shapeCounter_;
    shapeList_.swap(shp.shapeList_);
  }
  return *this;
}

CompositeShape &CompositeShape::operator = (CompositeShape &&shp)
{
  if (this!=&shp)
  {
    shapeCounter_ = shp.shapeCounter_;
    shapeList_.swap(shp.shapeList_);
    shp.shapeList_ = nullptr;
    shp.shapeCounter_ = 0;
  }
  return *this;
}


double gessen::CompositeShape::getArea() const
{
  double area = 0.0;
  for (int i = 0; i < shapeCounter_; i++)
  {
    area += shapeList_[i] -> getArea();
  }
  return area;
}

rectangle_t gessen::CompositeShape::getFrameRect() const
{
  if (shapeCounter_ <= 0)
  {
    return {{0.0, 0.0}, 0.0, 0.0};
  }
  else
  {
    rectangle_t frameRect = shapeList_[0] -> getFrameRect();
    double rightLine = frameRect.pos.x + frameRect.width / 2;
    double leftLine = frameRect.pos.x - frameRect.width / 2;
    double highLine = frameRect.pos.y + frameRect.height / 2;
    double downLine = frameRect.pos.y - frameRect.height / 2;
    for (int i = 1; i < shapeCounter_; i++)
    {
      frameRect = shapeList_[i] -> getFrameRect();
      if (rightLine < frameRect.pos.x + frameRect.width / 2)
      {
        rightLine = frameRect.pos.x + frameRect.width / 2;
      }
      if (leftLine > frameRect.pos.x - frameRect.width / 2)
      {
        leftLine = frameRect.pos.x - frameRect.width / 2;
      }
      if (highLine < frameRect.pos.y + frameRect.height / 2)
      {
        highLine = frameRect.pos.y + frameRect.height / 2;
      }
      if (downLine > frameRect.pos.y - frameRect.height / 2)
      {
        downLine = frameRect.pos.y - frameRect.height / 2;
      }
    }
    return {{(rightLine + leftLine) / 2, (highLine + downLine) / 2}, rightLine - leftLine, highLine - downLine};
  }
}

void gessen::CompositeShape::move(const point_t & point)
{
  move(point.x - getFrameRect().pos.x, point.y - getFrameRect().pos.y);
}

void gessen::CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < shapeCounter_; i++)
  {
    shapeList_[i] -> move(dx, dy);
  }
}

void gessen::CompositeShape::scale (const double scaleCoefficient)
{
  if (scaleCoefficient < 0.0)
  {
    throw std::invalid_argument("Error. Scale coefficient must be more than zero or equal to it.");
  }
  point_t compositeShapePos = getFrameRect().pos;
  for (int i = 0; i < shapeCounter_; i++)
  {
    point_t shapePos = shapeList_[i] -> getFrameRect().pos;
    shapeList_[i] -> move((scaleCoefficient - 1) * (shapePos.x - compositeShapePos.x), (scaleCoefficient - 1) * (shapePos.y - compositeShapePos.y));
    shapeList_[i] -> scale(scaleCoefficient);
  }
}

void gessen::CompositeShape::addShape (Shape * shapeElement)
{
  if (shapeElement == nullptr)
  {
    throw std::invalid_argument("Error. No object.");
  }
  std::unique_ptr<Shape *[]> new_arr(new Shape *[shapeCounter_ + 1]);
  for (int i = 0; i < shapeCounter_; i++)
  {
    new_arr[i] = shapeList_[i];
  }
  new_arr[shapeCounter_] = shapeElement;
  shapeCounter_++;
  shapeList_.swap(new_arr);
}

void gessen::CompositeShape::removeShape(const int index)
{
  if (shapeCounter_ <= 0)
  {
    throw std::out_of_range("Error. There are no object.");
  }
  if (index >= shapeCounter_)
  {
    throw std::out_of_range("Error. Index is out of range.");
  }
  if ((shapeCounter_ == 1) && (index == 0))
  {
    shapeList_.reset();
    shapeCounter_ = 0;
    return;
  }
  std::unique_ptr<Shape *[]> new_arr(new Shape *[shapeCounter_ - 1]);
  for (int i = 0; i < index; i++)
  {
    new_arr[i] = shapeList_[i];
  }
  for (int i = index; i < shapeCounter_ - 1; ++i)
  {
    new_arr[i] = shapeList_[i + 1];
  }
  shapeList_.swap(new_arr);
  shapeCounter_--;
}

void CompositeShape::printShapeName() const
{
  for (int i = 0; i<shapeCounter_; ++i)
  {
    shapeList_[i]->printShapeName();
    std::cout << std::endl;
  }
}

void CompositeShape::rotate(double angleRotate)
{
  const point_t center = getFrameRect().pos;
  for (int i = 0; i < shapeCounter_; ++i) 
  {
    shapeList_[i]->rotate(angleRotate);
    shapeList_[i]->move(rotatePoint(center, shapeList_[i]->getFrameRect().pos, angleRotate));
  }
}

point_t CompositeShape::rotatePoint(const point_t &center, const point_t &p, double angleRotate)
{
  const double rad = angleRotate * M_PI / 180;
  const double newX = center.x + (p.x - center.x) * cos(rad) - (p.y - center.y) * sin(rad);
  const double newY = center.y + (p.x - center.x) * sin(rad) + (p.y - center.y) * cos(rad);
  return {newX, newY};
}

