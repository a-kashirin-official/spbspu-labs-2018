
#include "composite-shape.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include "rectangle.hpp"
#include "circle.hpp"

zhukova::CompositeShape::CompositeShape(std::shared_ptr <Shape> element):
count_(0),
shapeList_()
{
  if ( element == nullptr ) {
    throw std::invalid_argument("CompositeShape: invalid pointer for new element in constructor");
  }

  shapeList_ = boost::shared_array< std::shared_ptr <Shape> >{ new std::shared_ptr <Shape>[1] };
  shapeList_[0] = element;

  count_ = 1;
}

zhukova::CompositeShape::CompositeShape(const zhukova::CompositeShape & compShape)
{
  if (this != & compShape) {
    shapeList_ = boost::shared_array< std::shared_ptr <Shape> >{ new std::shared_ptr <Shape>[compShape.count_] };
    count_ = compShape.count_;

    for (int i = 0; i < count_; i++) {
      shapeList_[i] = compShape.shapeList_[i];
    }
  } else {
    throw std::invalid_argument("CompositeShape: initialization by itself");
  }
}

zhukova::CompositeShape & zhukova::CompositeShape::operator = (const zhukova::CompositeShape & rhs)
{
  if (this != & rhs) {
    this->shapeList_ = boost::shared_array< std::shared_ptr <Shape> >{ new std::shared_ptr <Shape>[rhs.count_] };
    this->count_ = rhs.count_;

    for (int i = 0; i < count_; i++) {
      shapeList_[i] = rhs.shapeList_[i];
    }
  } else {
    throw std::invalid_argument("CompositeShape: assignment by itself");
  }
  return *this;
}

std::shared_ptr<zhukova::Shape> zhukova::CompositeShape::operator [] (int i) const
{
  if ((i >= count_) || (i < 0)) {
    throw std::invalid_argument("CompositeShape: index out of range");
  }
  return shapeList_[i];
}

double zhukova::CompositeShape::getArea() const
{
  double curArea = 0;
  for (int i = 0; i < count_; i++) {
    curArea += shapeList_[i]->getArea();
  }
  return curArea;
}

zhukova::rectangle_t zhukova::CompositeShape::getFrameRect() const
{
  point_t max = { 0,0 };
  rectangle_t rec = { 0, 0,{ 0, 0 } };
  point_t curCenter = calcCenter();

  for (int i = 0; i < count_; i++) {
    rec = shapeList_[i]->getFrameRect();

    if (abs(curCenter.y - rec.pos.y) + rec.height / 2 > max.y) {
      max.y = abs(curCenter.y - rec.pos.y) + rec.height / 2;
    }
    if (abs(curCenter.x - rec.pos.x) + rec.width / 2 > max.x) {
      max.x = abs(curCenter.x - rec.pos.x) + rec.width / 2;
    }
  }

  return { max.x * 2,  max.y * 2 ,   curCenter };
}

void zhukova::CompositeShape::move(double dx, double dy)
{
  for (int i = 0; i < count_; i++) {
    shapeList_[i]->move(dx, dy);
  }
}

void zhukova::CompositeShape::move(const point_t & point)
{
  point_t curCenter = calcCenter();
  double dx = point.x - curCenter.x;
  double dy = point.y - curCenter.y;

  for (int i = 0; i < count_; i++) {
    shapeList_[i]->move(dx, dy);
  }
}

void zhukova::CompositeShape::scale(double coefficient)
{
  if (coefficient < 0) {
    throw std::invalid_argument("CompositeShape: Invalid scaling factor");
  }

  rectangle_t rec = { 0, 0, {0, 0} };
  double dx = 0;
  double dy = 0;
  point_t curCenter = calcCenter();

  for (int i = 0; i < count_; i++) {
    rec = shapeList_[i]->getFrameRect();

    shapeList_[i]->scale(coefficient);
    dy = curCenter.y - rec.pos.y;
    dx = curCenter.x - rec.pos.x;
    shapeList_[i]->move( {curCenter.x + coefficient * dx, curCenter.y + coefficient * dy} );
  }
}

void zhukova::CompositeShape::rotate(double deg)
{
  double rad = (M_PI / 180) * deg;
  point_t curCenter = calcCenter();

  double x = 0;
  double y = 0;
  rectangle_t rec = { 0, 0,{ 0, 0 } };

  for (int i = 0; i < count_; i++) {
    rec = shapeList_[i]->getFrameRect();
    x = curCenter.x + (rec.pos.x - curCenter.x) * cos(rad) - (rec.pos.y - curCenter.y) * sin(rad);
    y = curCenter.y + (rec.pos.y - curCenter.y) * cos(rad) + (rec.pos.x - curCenter.x) * sin(rad);

    shapeList_[i]->move( {x, y} );
    shapeList_[i]->rotate(deg);
  }

  //X = x0 + (x - x0) * cos(a) - (y - y0) * sin(a); 
  //Y = y0 + (y - y0) * cos(a) + (x - x0) * sin(a);
  //where (x0, y0) — point around which we rotate
}

void zhukova::CompositeShape::addElement(std::shared_ptr <Shape> element)
{
  if (element == nullptr) {
    throw std::invalid_argument("CompositeShape: invalid pointer for adding new element");
  }

  boost::shared_array< std::shared_ptr <Shape> > tmpList{ new std::shared_ptr <Shape>[count_ + 1] };

  for (int i = 0; i < count_; i++) {
    tmpList[i] = shapeList_[i];
  }

  tmpList[count_] = element;

  shapeList_ = tmpList;

  count_++;
}

int zhukova::CompositeShape::getCount() const
{
  return count_;
}

zhukova::point_t zhukova::CompositeShape::calcCenter() const
{
  rectangle_t rec = { 0, 0,{ 0, 0 } };
  double xSum = 0;
  double ySum = 0;

  for (int i = 0; i < count_; i++) {
    rec = shapeList_[i]->getFrameRect();

    ySum += rec.pos.y;
    xSum += rec.pos.x;
  }

  return { xSum / count_, ySum / count_ };
}
