#include <iostream>
#include "composite-shape.hpp"
#include <cmath>

using std::cout;
using std::endl;
using namespace averin;

CompositeShape::CompositeShape(Shape *obj) :
  arr_(new Shape *[1]),
  size_(1),
  angle_(0)
{
  if (obj == nullptr)
  {
    throw std::invalid_argument("Wrong pointer");
  }
  obj->setAngle(angle_);
  arr_[0] = obj;
}

CompositeShape::CompositeShape() :
  arr_(new Shape *[0]),
  size_(0),
  angle_(0)
{
  
}

double CompositeShape::getArea() const
{
  double sumArea = 0;
  for (int i = 0; i < size_; i++)
  {
    sumArea += arr_[i]->getArea();
  }
  return sumArea;
}

rectangle_t CompositeShape::getFrameRect() const
{
  rectangle_t rect = arr_[0]->getFrameRect();
  double maxX = rect.pos.x + rect.width/2;
  double minX = rect.pos.x - rect.width/2;
  double maxY = rect.pos.y + rect.height/2;
  double minY = rect.pos.y - rect.height/2;
  
  for (int i = 0; i < size_; i++)
  {
    rect = arr_[i]->getFrameRect();
    if ((rect.pos.x + rect.width/2) > maxX)
    {
      maxX = rect.pos.x + rect.width/2;
    }
    if ((rect.pos.x - rect.width/2) > minX)
    {
      minX = rect.pos.x - rect.width/2;
    } 
    if ((rect.pos.y + rect.height/2) > maxY)
    {
      maxY = rect.pos.y + rect.height/2;
    }
    if ((rect.pos.y - rect.height/2) > minY)
    {
      minY = rect.pos.y - rect.height/2;
    }     
  }
  point_t center;
  center.x = maxX - (maxX-minX)/2;
  center.y = maxY - (maxY-minY)/2;
  return {maxX-minX,maxY-minY,center}; 
}

void CompositeShape::move(point_t c)
{
  for (int i = 0; i < size_; i++)
  {
    arr_[i]->move(c);
  }
}

void CompositeShape::move(double dx, double dy)
{
  for (int i = 0; i < size_; i++)
  {
    arr_[i]->move(dx,dy);
  }
}

void CompositeShape::printInfo() const
{
  cout << endl << "--COMPOSITE SHAPE--"<< endl;
  cout << "Number of elements: " << size_ << endl;
  cout << "Area " << getArea() << endl;
  rectangle_t frec;
  frec = getFrameRect();
  cout << endl << "FRAME RECTANGLE" << endl << "Height: " << frec.height << endl;
  cout << "Width: " << frec.width << endl << "x, y cords: " << frec.pos.x << " " << frec.pos.y << endl;
  cout << "Angles of shapes: " << endl;
  printAngle();
}

void CompositeShape::scale(double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Ratio must be >= 0");
  }
  for (int i = 0; i < size_; i++)
  {
    arr_[i]->scale(ratio);
  }
}

void CompositeShape::addShape(Shape* obj)
{
  if (obj == nullptr)
  {
    throw std::invalid_argument("Wrong pointer");
  }
  obj->setAngle(angle_);
  std::unique_ptr<Shape *[]> tempArr (new Shape*[size_+1]);
  for (int i = 0; i < size_; i++)
  {
    tempArr[i] = arr_[i];
  }
  tempArr[size_] = obj;
  arr_.swap(tempArr);
  size_++;
}

void CompositeShape::deleteShape(int index)
{
  if (index > size_ - 1)
  {
    throw std::invalid_argument("Wrong index");
  }
  std::unique_ptr<Shape *[]> tempArr (new Shape*[size_-1]);
  for (int i = 0; i < size_; i++)
  {
    if (i != index)
    {
      if (i > index)
      {
        tempArr[i-1] = arr_[i]; 
      }
      else
      {
        tempArr[i] = arr_[i];
      }
    }
  }
  arr_.swap(tempArr);
  size_--;
}

void CompositeShape::rotate(double deg)
{
  angle_ = deg;
  for (int i = 0; i < size_; i++)
  {
    arr_[i]->rotate(deg);
    rectangle_t recComp = getFrameRect();
    rectangle_t recShp = arr_[i]->getFrameRect();
    double x = recComp.pos.x;
    double y = recComp.pos.y;
    double x0 = recShp.pos.x;
    double y0 = recShp.pos.y;
    double degRad = deg * (M_PI/180);
    double rx = x0 - x;
    double ry = y0 - y;
    double c = cos(degRad);
    double s = sin(degRad);
    double x1 = x + rx * c - ry * s;
    double y1 = y + rx * s + ry * c;
    arr_[i]->move({x1,y1});
  } 
}

void CompositeShape::printAngle() const
{
  for (int i = 0; i < size_; i++)
  {
    arr_[i]->printAngle();
  }
}

void CompositeShape::setAngle(double deg) 
{
  angle_ = deg;
}

void CompositeShape::printName() const
{
  cout << "CompositeShape";
}
