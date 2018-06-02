#include "composite-shape.hpp"
#include <iostream>

vasekha::CompositeShape::CompositeShape() noexcept:
  pos_({0.0,0.0}),
  size_(0),
  shapes_(nullptr)
{}

vasekha::CompositeShape::CompositeShape(const CompositeShape & compSh):
  pos_(compSh.pos_),
  size_(compSh.size_),
  shapes_((compSh.size_)?std::make_unique<ptr_shape[]>(compSh.size_):nullptr)
{
  for(size_t i = 0; i<size_; ++i)
  {
    shapes_[i]=compSh.shapes_[i];
  }
}

vasekha::CompositeShape::CompositeShape(CompositeShape && compSh) noexcept:
  pos_(compSh.pos_),
  size_(compSh.size_),
  shapes_(std::move(compSh.shapes_))
{
  compSh.size_=0;
  compSh.pos_={0.0,0.0};
}

vasekha::CompositeShape & vasekha::CompositeShape::operator= (const CompositeShape & compSh)
{
  if(this==&compSh)
  {
    return *this;
  }
  shapes_=(compSh.size_)?std::make_unique<ptr_shape[]>(compSh.size_):nullptr;
  for(size_t i = 0; i<compSh.size_; ++i)
  {
    shapes_[i]=compSh.shapes_[i];
  }
  pos_ = compSh.pos_;
  size_ = compSh.size_;
  return *this;
}

vasekha::CompositeShape & vasekha::CompositeShape::operator= (CompositeShape && compSh) noexcept
{
  if(this==&compSh)
  {
    return *this;
  }
  pos_ = compSh.pos_;
  size_ = compSh.size_;
  shapes_ = std::move(compSh.shapes_);
  compSh.pos_={0.0,0.0};
  compSh.size_=0;
  return *this;
}

void vasekha::CompositeShape::add(const vasekha::Shape::ptr_shape & shape)
{
if(shape==nullptr)
  {
    throw std::invalid_argument("Invalid Shape");
  }
  std::unique_ptr<ptr_shape[]> shapes(std::make_unique<ptr_shape[]>(size_+1));
  for(size_t i=0; i<size_; ++i)
  {
    shapes[i]=shapes_[i];
  }
  shapes[size_++]=shape;
  shapes_=std::move(shapes);
  pos_=getFrameRect().pos;
}

void vasekha::CompositeShape::remove(const size_t index)
{
  if(index>=size_)
  {
    throw std::out_of_range("Index out of range");
  }
  if(size_==0)
  {
    throw std::invalid_argument("Array is empty");
  }
  std::unique_ptr<ptr_shape[]> shapes(std::make_unique<ptr_shape[]>(--size_));
  for(size_t i=0; i<index; ++i)
  {
    shapes[i]=shapes_[i];
  }
  for(size_t i=index;i<size_; ++i)
  {
    shapes[i]=shapes_[i+1];
  }
  shapes_=std::move(shapes);
  pos_=getFrameRect().pos;
}

size_t vasekha::CompositeShape::getSize() const noexcept
{
  return size_;
}

vasekha::Shape::ptr_shape vasekha::CompositeShape::operator[] (size_t index) const
{
  if(index>=size_)
  {
    throw std::out_of_range("Index out of range");
  }
  return shapes_[index];
}

double vasekha::CompositeShape::getArea() const noexcept
{
  double area = 0.0;
  for(size_t i=0; i<size_; ++i)
  {
    area+=shapes_[i]->getArea();
  }
  return area;
}

vasekha::rectangle_t vasekha::CompositeShape::getFrameRect() const noexcept
{
  if(!size_)
  {
    return {{0.0,0.0},0.0,0.0};
  }
  rectangle_t frame = shapes_[0]->getFrameRect();
  double left = frame.pos.x-frame.width/2.0;
  double right = frame.pos.x+frame.width/2.0;
  double top = frame.pos.y+frame.height/2.0;
  double bottom = frame.pos.y-frame.height/2.0;
  for(size_t i=1;i<size_;++i)
  {
    frame = shapes_[i]->getFrameRect();
    left = std::min(left,frame.pos.x-frame.width/2.0);
    right = std::max(right,frame.pos.x+frame.width/2.0);
    top = std::max(top, frame.pos.y+frame.height/2.0);
    bottom = std::min(bottom, frame.pos.y-frame.height/2.0);
  }
  return {{(left+right)/2, (top+bottom)/2},right-left,top-bottom};
}

void vasekha::CompositeShape::move(const point_t & point) noexcept
{
  move(pos_.x-point.x, pos_.y-point.y);
}

void vasekha::CompositeShape::move(const double dx,const double dy) noexcept
{
  pos_.x=dx;
  pos_.y=dy;
  for(size_t i=0;i<size_;++i)
  {
    shapes_[i]->move(dx,dy);
  }
}

void vasekha::CompositeShape::scale(const double factor)
{
  for(size_t i=0;i<size_;++i)
  {
    point_t shapePos = shapes_[i]->getFrameRect().pos;
    shapes_[i]->move(factor*(pos_.x-shapePos.x)-shapePos.x,factor*(pos_.y-shapePos.y)-shapePos.y);
    shapes_[i]->scale(factor);
  }
}

void vasekha::CompositeShape::rotate(const double angle) noexcept
{
  for(size_t i=0;i<size_;++i)
  {
    shapes_[i]->rotate(angle);
  }
}

void vasekha::CompositeShape::print(std::ostream & out) const noexcept
{
  out << "Composite Shape:" << std::endl;
  for(size_t i=0;i<size_;++i)
  {
    out << *shapes_[i];
  }
}
