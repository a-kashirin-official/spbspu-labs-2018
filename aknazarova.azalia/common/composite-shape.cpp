#include "composite-shape.hpp"
#include <memory>
#include <stdexcept>

using namespace aknazarova;

CompositeShape::CompositeShape(const std::shared_ptr <Shape> shape):
  shapes_(nullptr),
  size_(0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Null pointer!!");
  }
  addShape(shape);
}

CompositeShape::CompositeShape(const CompositeShape &compositeShape):
  shapes_ (std::unique_ptr<std::shared_ptr<Shape>[]>(new std::shared_ptr <Shape> [compositeShape.size_])),
  size_ (compositeShape.size_)
{ 
  for (int i=0; i<size_; ++i)
  {
    shapes_[i] = compositeShape.shapes_[i];
  }
}

CompositeShape::CompositeShape(CompositeShape &&compositeShape):
  shapes_(std::move(compositeShape.shapes_)),
  size_(compositeShape.size_)
{
  compositeShape.size_ = 0;
  compositeShape.shapes_.reset();
}

CompositeShape &CompositeShape::operator = (const CompositeShape &compositeShape)
{
  if (this !=  &compositeShape)
  {
    shapes_.reset(new std::shared_ptr <Shape> [compositeShape.size_]);
    size_ = compositeShape.size_;
    for (int i=0; i<size_; ++i)
    {
      shapes_[i]=compositeShape.shapes_[i];
    }
  }
  return *this;
}

CompositeShape &CompositeShape::operator= (CompositeShape &&compositeShape)
{
  shapes_ = std::move(compositeShape.shapes_);
  size_ = compositeShape.size_;
  compositeShape.size_ = 0;

  return *this;
}

std::shared_ptr <Shape> &CompositeShape::operator[] (int i) const
{
  if (i >= size_) 
  {
    throw std::out_of_range("Incorrect index");
  }
  return shapes_[i];
}

void CompositeShape::removeShape(const int num)
{
  if (size_ ==0)
  {
    throw std::out_of_range("CompositeShape is empty");
  }
  else
  {
    if ((num<=0)||(num>=size_))
    {
      throw std::out_of_range("Incorrect number");
    }
  }
  if (size_==1)
  {
    deleteShapes();
  }
  else
  {
    std::unique_ptr<std::shared_ptr<Shape>[]>newShapes(new std::shared_ptr<Shape>[size_-1]);
    for (int i=0; i<(num-1); ++i)
    {
      newShapes[i]=shapes_[i];
    }
    for (int i=num; i<size_;++i)
    {
      newShapes[i-1]=shapes_[i];
    }
    shapes_.swap(newShapes);
    --size_;
  }
}

void CompositeShape::addShape(const std::shared_ptr <Shape> shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid shape");
  }
  std::unique_ptr <std::shared_ptr <Shape> []> newShapes (new std::shared_ptr <Shape> [size_ + 1]);
  for (int i = 0; i<size_; ++i)
  {
    newShapes[i]=shapes_[i];
  }
  newShapes[size_++]=shape;
  shapes_.swap(newShapes);
}

void CompositeShape::deleteShapes()
{
  shapes_.reset();
  shapes_=nullptr;
  size_=0;
}

int CompositeShape::getSize() const
{
  return size_;
}

double CompositeShape::getArea() const
{
  double area=0.0;
  for (int i=0;i<size_;++i)
  {
    area=area+shapes_[i]->getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  if (size_ ==0)
  {
    return {{0.0,0.0},0.0,0.0};
  }
  else
  {
    rectangle_t frameRect = shapes_[0]->getFrameRect();
    double xmin = frameRect.pos.x - frameRect.width/2;
    double xmax = frameRect.pos.x + frameRect.width/2;
    double ymin = frameRect.pos.y - frameRect.height/2;
    double ymax = frameRect.pos.y + frameRect.height/2;
    
    for (int i=1; i<size_; ++i)
    {
      frameRect = shapes_[i]->getFrameRect();
      if (xmin>frameRect.pos.x - frameRect.width/2)
      {
        xmin = frameRect.pos.x - frameRect.width/2;
      }
      if (ymin>frameRect.pos.y - frameRect.height/2)
      {
        ymin = frameRect.pos.y - frameRect.height/2;
      }
      if (xmax<frameRect.pos.x + frameRect.width/2)
      {
        xmax = frameRect.pos.x + frameRect.width/2;
      }
      if (ymax<frameRect.pos.y + frameRect.height/2)
      {
        ymax = frameRect.pos.y + frameRect.height/2;
      }
    }
    return rectangle_t {{(xmax+xmin)/2,(ymax+ymin)/2},xmax-xmin,ymax-ymin};
  }
}


void CompositeShape::scale(const double kof)
{
  if (kof<0.0)
  {
    throw std::invalid_argument("Invalid koefficent");
  }
  point_t cent=getFrameRect().pos;
  for (int i=0; i<size_; ++i)
  {
    const point_t Shapecent = shapes_[i]->getFrameRect().pos;
    shapes_[i]->scale(kof);
    shapes_[i]->move({(Shapecent.x-cent.x)*kof,(Shapecent.y-cent.y)*kof});
  }
}

void CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i<size_; i++)
  {
    shapes_[i]->move(dx,dy);
  }
}

void CompositeShape::move(const point_t &pos)
{
  point_t cent = getFrameRect().pos;
  for (int i=0; i<size_; i++)
  {
    shapes_[i]->move(pos.x-cent.x,pos.y-cent.y);
  }
}
