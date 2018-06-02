#include <iostream>
#include "composite-shape.hpp"

using namespace almukhametov;

CompositeShape::CompositeShape(Shape *shape):
  composition(new Shape *[1]),
  size_(1)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Error with pointer");
  }
  composition[0] = shape;
}

CompositeShape::CompositeShape():
  composition(new Shape *[0]),
  size_(0)
{

}

CompositeShape::~CompositeShape()
{

}

double CompositeShape::getArea() const
{
  double Area=0;
  for (int i=0;i<size_;i++)
  {
    Area+=composition[i]->getArea();
  }
  return Area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  rectangle_t rec = composition[0]->getFrameRect();
  double xMax = rec.pos.x + rec.width/2;
  double xMin = rec.pos.x - rec.width/2;
  double yMax = rec.pos.y + rec.height/2;
  double yMin = rec.pos.y - rec.height/2;

  for (int i = 1; i < size_; i++)
  {
    rec = composition[i]->getFrameRect();

    if ((rec.pos.x + rec.width/2) > xMax)
    {
      xMax = rec.pos.x + rec.width/2;
    }
    if ((rec.pos.x - rec.width/2) > xMin)
    {
      xMin = rec.pos.x - rec.width/2;
    }
    if ((rec.pos.y + rec.height/2) > yMax)
    {
      yMax = rec.pos.y + rec.height/2;
    }
    if ((rec.pos.y - rec.height/2) > yMin)
    {
      yMin = rec.pos.y - rec.height/2;
    }
  }

  point_t center = {xMax - (xMax-xMin)/2,yMax - (yMax-yMin)/2};
  return {xMax-xMin,yMax-yMin,center};
}

void CompositeShape::move(point_t c)
{
  for (int i=0;i<size_;i++)
  {
    composition[i]->move(c);
  }
}

void CompositeShape::move(double dx, double dy)
{
  for (int i=0;i<size_;i++)
  {
    composition[i]->move(dx,dy);
  }
}

void CompositeShape::scale(double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Factor must be >= 0");
  }
  for (int i=0;i<size_;i++)
  {
    composition[i]->scale(factor);
  }
}

void CompositeShape::newShape(Shape *shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Error with pointer");
  }
  std::unique_ptr<Shape *[]> newComp (new Shape *[size_+1]);
  for (int i=0;i<size_;i++)
  {
    newComp[i]=composition[i];
  }
  newComp[size_]=shape;
  composition.swap(newComp);
  size_++;
}

void CompositeShape::delShape(int index)
{
  if (index > size_-1)
  {
    throw std::invalid_argument("There is no element with that index");
  }

  std::unique_ptr<Shape *[]> newComp(new Shape *[size_-1]);
  for (int i=0;i<size_;i++)
  {
    if (i!=index)
    {
      if (i > index)
      {
        newComp[i - 1] = composition[i];
      }
      else
      {
        newComp[i] = composition[i];
      }
    }
  }
  composition.swap(newComp);
  size_--;
}
