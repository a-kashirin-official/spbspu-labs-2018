#include "composite-shape.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <cmath>

kudryavtseva::CompositeShape::CompositeShape():
  objects_(nullptr),
  size_(0)
{
}

kudryavtseva::CompositeShape::CompositeShape(kudryavtseva::Shape *newShape):
  objects_(new kudryavtseva::Shape *[1]),
  size_(1)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Address doesn't exist");
  }
  objects_[0] = newShape;
}

kudryavtseva::CompositeShape::CompositeShape(const kudryavtseva::CompositeShape &cmp):
  objects_(new kudryavtseva::Shape *[cmp.size_]),
  size_(cmp.size_)
{
  for (int i = 0; i < size_; i++)
  {
    objects_[i] = cmp.objects_[i];
  }
}

kudryavtseva::CompositeShape::CompositeShape(kudryavtseva::CompositeShape &&cmp):
  objects_(nullptr),
  size_(0)
{
  *this = std::move(cmp);
}

kudryavtseva::Shape* kudryavtseva::CompositeShape::operator[](int index) const
{
  if (index>size_)
  {
    throw std::invalid_argument("Out of array range");
  }
  return objects_[index];
}

kudryavtseva::CompositeShape &kudryavtseva::CompositeShape::operator=(kudryavtseva::CompositeShape &cmp)
{
  if (this !=&cmp)
  {
    size_ = cmp.size_;
    objects_.swap(cmp.objects_);
  }
  return *this;
}

kudryavtseva::CompositeShape& kudryavtseva::CompositeShape::operator=(kudryavtseva::CompositeShape &&cmp)
{
  if (this !=&cmp)
  {
    size_ = cmp.size_;
    objects_.swap(cmp.objects_);
    cmp.objects_ = nullptr;
    cmp.size_ = 0;
  }
  return *this;
}

void kudryavtseva::CompositeShape::removeShape(const int index)
{
  if (index < size_)
  {
    size_--;
    std::unique_ptr<kudryavtseva::Shape*[]> tempArray(new kudryavtseva::Shape*[size_]);
    for (int i = 0; i < index; i++)
    {
      tempArray[i] = objects_[i];
    }
    for (int i = index; i < size_; i++)
    {
      tempArray[i] = objects_[i+1];
    }
    objects_.swap(tempArray);
  }
  else
  {
    throw std::out_of_range("CompositeShape removeFromArray : out of size range");
  }
}

void kudryavtseva::CompositeShape::add(Shape *object)
{
  if (object == nullptr)
  {
    throw std::invalid_argument("Address doesn't exist");
  }
  std::unique_ptr<kudryavtseva::Shape *[]> tempArray(new kudryavtseva::Shape *[size_+1]);
  for(int i = 0; i < size_; i++)
  {
    tempArray[i] = objects_[i];
  }
  tempArray[size_] = object;
  size_++;
  objects_.swap(tempArray);
}

double kudryavtseva::CompositeShape::getArea() const
{
  double s = 0.0;
  for (int i = 0; i < size_; i++)
  {
    s = s+objects_[i]->getArea();
  }
  return s;
}

kudryavtseva::rectangle_t kudryavtseva::CompositeShape::getFrameRect() const
{
  kudryavtseva::point_t maxRightP {objects_[0]->getFrameRect().pos.x + objects_[0]->getFrameRect().width/2.0,
                      objects_[0]->getFrameRect().pos.y + objects_[0]->getFrameRect().height/2.0};
  kudryavtseva::point_t minLeftP {objects_[0]->getFrameRect().pos.x - objects_[0]->getFrameRect().width/2.0,
                      objects_[0]->getFrameRect().pos.y - objects_[0]->getFrameRect().height/2.0};
  for(int i = 1; i < size_; i++)
  {
    if ((objects_[i]->getFrameRect().pos.x + objects_[i]->getFrameRect().width/2.0)>maxRightP.x)
    {
      maxRightP.x = (objects_[i]->getFrameRect().pos.x + objects_[i]->getFrameRect().width/2.0);
    }
    if ((objects_[i]->getFrameRect().pos.y + objects_[i]->getFrameRect().height/2.0)>maxRightP.y)
    {
      maxRightP.y = (objects_[i]->getFrameRect().pos.y + objects_[i]->getFrameRect().height/2.0);
    }
      if ((objects_[i]->getFrameRect().pos.x - objects_[i]->getFrameRect().width/2.0)<minLeftP.x)
    {
      minLeftP.x = (objects_[i]->getFrameRect().pos.x - objects_[i]->getFrameRect().width/2.0);
    }
    if ((objects_[i]->getFrameRect().pos.y - objects_[i]->getFrameRect().height/2.0)<minLeftP.y)
    {
      minLeftP.y = (objects_[i]->getFrameRect().pos.y - objects_[i]->getFrameRect().height/2.0);
    }
  }
  return {maxRightP.x - minLeftP.x, maxRightP.y - minLeftP.y, {(maxRightP.x + minLeftP.x)/2.0,(maxRightP.y + minLeftP.y)/2.0}};
}

void kudryavtseva::CompositeShape::move(double dx, double dy)
{
  for (int i = 0; i < size_; i++)
  {
    objects_[i]->move(dx, dy);
  }
}

void kudryavtseva::CompositeShape::move(const kudryavtseva::point_t &center)
{
  kudryavtseva::point_t point = getFrameRect().pos;
  for (int i = 0; i < size_; i++)
  {
    objects_[i]->move(center.x-point.x, center.y-point.y);
  }
}

void kudryavtseva::CompositeShape::scale(double coeff)
{
  if (coeff<0.0)
  {
    throw std::invalid_argument("Invalid coefficient");
  }
  for (int i = 0; i < size_; i++)
  {
    objects_[i]->scale(coeff);
  }
}

int kudryavtseva::CompositeShape::getSize() const
{
  return size_;
}

void kudryavtseva::CompositeShape::printf() const
{
 for (int i = 0; i < size_; i++)
  {
    std::cout << "Figure number" << i+1 << ":" << std::endl;
    objects_[i]->printf();
  }
}

kudryavtseva::point_t kudryavtseva::CompositeShape::getPos() const
{
  return getFrameRect().pos;
}

void kudryavtseva::CompositeShape::rotate(double angle)
{
  angle = angle*M_PI/180.0;
  kudryavtseva::point_t center = getFrameRect().pos;
  for (int i = 0; i < size_; i++)
  {
    objects_[i]->move({objects_[i]->getPos().x * std::cos(angle) - objects_[i]->getPos().y * std::sin(angle),
                       objects_[i]->getPos().x * std::sin(angle) + objects_[i]->getPos().y * std::cos(angle)});
    objects_[i]->rotate(angle);
  }
  move(center);
}
