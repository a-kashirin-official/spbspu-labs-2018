#include "composite-shape.hpp"
#include <iostream>
#include <memory>

namespace kudryakov
{
  CompositeShape::CompositeShape() :
    arr_(new Shape *[0]),
    size_(0)
  {
    
  }
  
  CompositeShape::CompositeShape(Shape* newShape) :
    arr_(new Shape*[1]),
    size_(1)
  {
    arr_[0] = newShape;
  }
  
  CompositeShape::CompositeShape(const CompositeShape& other)
  {
    std::unique_ptr<Shape *[]> tempArr (new Shape*[other.size_]);
    for (int i = 0; i < other.size_; i++)
    {
      tempArr[i] = other.arr_[i];
    }
    size_ = other.size_;
    arr_.swap(tempArr);
  }
  
  CompositeShape::CompositeShape(CompositeShape&& other)
  {
    arr_.swap(other.arr_);
    size_=other.size_;
    other.size_ = 0;
  }
  
  void CompositeShape::operator= (const CompositeShape& other)
  {
    std::unique_ptr<Shape *[]> tempArr (new Shape*[other.size_]);
    for (int i = 0; i < other.size_; i++)
    {
      tempArr[i] = other.arr_[i];
    }
    this->arr_.swap(tempArr);
    size_=other.size_;
  }
  
  
  void CompositeShape::operator= (CompositeShape&& other)
  {
    this->arr_.swap(other.arr_);
    this->size_=other.size_;
    other.size_ = 0;
  }
  
  Shape* CompositeShape::operator[] (int index) const
  {
    if ((index >= size_) || (index < 0))
    {
      throw std::out_of_range("Out of range");
    }
    return arr_[index];
  }
  
  void CompositeShape::addShape(Shape* obj)
  {
    if (obj == nullptr)
    {
      throw std::invalid_argument("Wrong pointer");
    }
    std::unique_ptr<Shape *[]> tempArr (new Shape*[size_+1]);
    for (int i = 0; i < size_; i++)
    {
      tempArr[i] = arr_[i];
    }
    tempArr[size_] = obj;
    arr_.swap(tempArr);
    size_++;
  }
  
  double CompositeShape::getArea() const
  {
    double totalArea = 0.0;
    for (int i = 0; i < size_; ++i)
    {
      totalArea += arr_[i]->getArea();
    }
    return totalArea;
  }
  
  rectangle_t CompositeShape::getFrameRect() const
  {
    if (size_ == 0)
    {
      return {{0,0}, 0, 0};
    }
    
    rectangle_t initFrame = arr_[0]->getFrameRect();
    
    double minX = initFrame.pos.x - initFrame.width / 2;
    double maxX = initFrame.pos.x + initFrame.width / 2;
    for (int i = 0; i < size_; ++i)
    {
      if ((arr_[i]->getFrameRect().pos.x - arr_[i]->getFrameRect().width / 2) < minX)
      {
        minX = arr_[i]->getFrameRect().pos.x - arr_[i]->getFrameRect().width / 2;
      }
    
      if ((arr_[i]->getFrameRect().pos.x + arr_[i]->getFrameRect().width / 2) > maxX)
      {
        maxX = arr_[i]->getFrameRect().pos.x + arr_[i]->getFrameRect().width / 2;
      }
    }
  
    double maxY = initFrame.pos.y + initFrame.height / 2;
    double minY = initFrame.pos.y - initFrame.height / 2;
    for (int i = 0; i < size_; ++i)
    {
      if ((arr_[i]->getFrameRect().pos.y - arr_[i]->getFrameRect().height / 2) < minY)
      {
        minY = arr_[i]->getFrameRect().pos.y - arr_[i]->getFrameRect().height / 2;
      }
    
      if ((arr_[i]->getFrameRect().pos.y + arr_[i]->getFrameRect().height / 2) > maxY)
      {
        maxY = arr_[i]->getFrameRect().pos.y + arr_[i]->getFrameRect().height / 2;
      }
    }
    return {{(maxX + minX) / 2, (maxY + minY) / 2}, (maxX - minX), (maxY - minY)};
    
  }
  
  void CompositeShape::move(const point_t& newCenterPoint)
  {
    double dx = newCenterPoint.x - getFrameRect().pos.x;
    double dy = newCenterPoint.y - getFrameRect().pos.y;
    for (int i = 0; i < size_; ++i)
    {
      arr_[i]->move(dx, dy);
    }
  }
  
  void CompositeShape::move(const double dx, const double dy)
  {
    for (int i = 0; i < size_; ++i)
    {
      arr_[i]->move(dx, dy);
    }
  }
  
  void CompositeShape::scale(const double factor)
  {
    if (factor < 0.0)
    {
      throw std::invalid_argument("Factor can't be negative");
    }
    
    const double xo = getFrameRect().pos.x;
    const double yo = getFrameRect().pos.y;
    
    for (int i = 0; i < size_; ++i)
    {
      arr_[i]->scale(factor);
      double dx = arr_[i]->getFrameRect().pos.x - xo;
      double dy = arr_[i]->getFrameRect().pos.y - yo;
      arr_[i]->move(dx*(factor-1), dy*(factor-1));
    }
  }
}
