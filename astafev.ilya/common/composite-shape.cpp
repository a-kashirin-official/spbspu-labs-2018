
#include"composite-shape.hpp"

#include <stdexcept>
#include <iostream>
#include <new>
#include <cmath>
#include <algorithm>

astafev::CompositeShape::CompositeShape():
  size_(0),
  array_(nullptr),
  angle_(0.0)
{
}

astafev::CompositeShape::CompositeShape(const std::shared_ptr<astafev::Shape> &shape):
  size_(0),
  array_(nullptr),
  angle_(0.0)
{
  if (shape == nullptr) 
  {
    throw std::invalid_argument("Empty shape");
  }
  addElement(shape);
}


astafev::CompositeShape::CompositeShape(const astafev::CompositeShape & other):
  size_(0),
  array_(nullptr),
  angle_(0.0)
{
  std::unique_ptr<std::shared_ptr<astafev::Shape>[]> buff(new std::shared_ptr<astafev::Shape>[other.size_]);
  for(size_t i=0;i<other.size_;++i)
  {
    buff[i]=other.array_[i];  
  }
  size_=other.size_;
  angle_=other.angle_;
  array_=std::move(buff);
}

astafev::CompositeShape::CompositeShape(astafev::CompositeShape && other):
  size_(other.size_),
  array_(std::move(other.array_)),
  angle_(other.angle_)
{
  other.array_=(nullptr);
  other.size_=0;
  other.angle_=0.0;
}

astafev::CompositeShape::~CompositeShape()
{
  clear();
}

astafev::CompositeShape & astafev::CompositeShape::operator= (const astafev::CompositeShape & other)
{
  if (this == &other)
  {
    return *this;
  }
  array_.reset(new std::shared_ptr<astafev::Shape> [other.size_] );
  size_=other.size_;
  angle_=other.angle_;
  for(size_t i=0;i<size_;++i)
  {
    array_[i]=other.array_[i];
  }
  return *this;
}

astafev::CompositeShape & astafev::CompositeShape::operator= (astafev::CompositeShape && other)
{
  if (this == &other)
  {
    return *this;
  }
  array_.reset(new std::shared_ptr<astafev::Shape>[other.size_]);
  size_=other.size_;
  angle_=other.angle_;
  array_=std::move(other.array_);
  other.array_=(nullptr);
  other.size_=0;
  other.angle_=0.0;
  return *this;
}

std::shared_ptr<astafev::Shape> & astafev::CompositeShape::operator [](size_t index)
{
  if(size_==0)
  {
    throw std::out_of_range("error, CompositeShape is empty ");
  }
  if(index>=size_)
  {
    throw std::out_of_range("error, index can't be > Size ");
  }
  return array_[index];
}

double astafev::CompositeShape::getArea() const noexcept
{
  double totalArea =0.0;
  for(size_t i=0;i<size_;i++)
  {
    totalArea+=array_[i]->getArea();
  }
  return totalArea;
}

astafev::rectangle_t astafev::CompositeShape::getFrameRect() const noexcept
{
    if (size_ == 0)
  {
    return astafev::rectangle_t{{0, 0}, 0, 0 };
  }
  double left = array_[0]->getFrameRect().pos.x - array_[0]->getFrameRect().width / 2;
  double right = array_[0]->getFrameRect().pos.x + array_[0]->getFrameRect().width / 2;
  double top = array_[0]->getFrameRect().pos.y + array_[0]->getFrameRect().height / 2;
  double bottom = array_[0]->getFrameRect().pos.y - array_[0]->getFrameRect().height / 2;
  for (size_t i = 1; i < size_; i++)
  {
    left = std::min(left, (array_[i]->getFrameRect().pos.x - array_[i]->getFrameRect().width / 2));
    right = std::max(right, (array_[i]->getFrameRect().pos.x + array_[i]->getFrameRect().width / 2));
    top = std::max(top, (array_[i]->getFrameRect().pos.y + array_[i]->getFrameRect().height / 2));
    bottom = std::min(bottom, (array_[i]->getFrameRect().pos.y - array_[i]->getFrameRect().height / 2));
  }
  const double sine = sin(angle_ * M_PI / 180);
  const double cosine = cos(angle_ * M_PI / 180);
  const double width = (top - bottom) * fabs(sine) + (right - left) * fabs(cosine);
  const double height = (top - bottom) * fabs(cosine) + (right - left) * fabs(sine);
  return {{ ((left + right) / 2.0), ((top + bottom) / 2.0) }, width, height};
}

void astafev::CompositeShape::move(const point_t & newcentre) noexcept
{
  const astafev::point_t centre=getFrameRect().pos;
  double dx=newcentre.x-centre.x;
  double dy=newcentre.y-centre.y;
  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->move(dx,dy);
  }
}

void astafev::CompositeShape::move(double dx, double dy) noexcept
{
  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->move(dx, dy);
  }
}

void astafev::CompositeShape::scale(double koeficent)
{
  if (koeficent <= 0.0) 
  {
    throw std::invalid_argument("error, koeficent can't be <=0 ");
  }
  astafev::point_t comp_centre = getFrameRect().pos;
  for (size_t i = 0; i < size_; i++)
  {
    astafev::point_t shape_centre = array_[i]->getFrameRect().pos;
    double dx=shape_centre.x-comp_centre.x;
    double dy=shape_centre.y-comp_centre.y;
    astafev::point_t new_centre = {comp_centre.x + koeficent * dx, comp_centre.y + koeficent * dy};
    array_[i]->move(new_centre);
    array_[i]->scale(koeficent);
  }
}

void astafev::CompositeShape::rotate(const double degrees) noexcept
{
  angle_+=degrees;
  const double sine = sin(degrees * M_PI / 180);
  const double cosine = cos(degrees * M_PI / 180);
  const astafev::point_t comp_centre = getFrameRect().pos;
  for(size_t i=0;i<size_;++i)
  {
    const astafev::point_t shape_centre = array_[i]->getFrameRect().pos;
    const double dx=(shape_centre.x-comp_centre.x) * cosine - (shape_centre.y-comp_centre.y) * sine;
    const double dy=(shape_centre.y-comp_centre.y) * cosine - (shape_centre.x-comp_centre.x) * sine;
    array_[i]->move(dx,dy);
    array_[i]->rotate(degrees);
  }
}

void astafev::CompositeShape::printInfo() const noexcept
{
  std::cout<<"------CompositeShape----------"<<std::endl;
  for(size_t i=0; i<size_;++i)
  {
    array_[i]->printInfo();
  }
  std::cout<<"-----------------------------"<<std::endl;
}

void astafev::CompositeShape::addElement(const std::shared_ptr<astafev::Shape> & shape)
{
  if (shape == nullptr) 
  {
    throw std::invalid_argument("Empty shape!");
  }
  std::unique_ptr< std::shared_ptr< astafev::Shape >[] > buf;
  buf = std::move(array_);
  array_.reset(new std::shared_ptr< astafev::Shape >[size_ + 1]);
  array_[size_] = shape;
  size_++;
  for (size_t i = 0; i < size_ - 1; i++)
  {
    array_[i] = buf[i];
  }
}

void astafev::CompositeShape::deleteElement(size_t index)
{
  if (size_ == 0)
  {
    throw std::out_of_range("error, CompositeShape is empty ");
  }
  if (index >= size_)
  {
    throw std::out_of_range("error, index can't be > Size ");
  }
  for (size_t i = index; i < size_ - 1; i++)
  {
    array_[i] = array_[i + 1];
  }
  array_[size_ - 1] = nullptr;
  size_--;
}

size_t astafev::CompositeShape::getSize() const noexcept
{
  return size_;
}

void astafev::CompositeShape::clear() noexcept
{
  size_ = 0;
  array_ = nullptr;
  angle_ = 0.0;
}

