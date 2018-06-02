#include "rectangle.hpp"
#include <iostream>

namespace kudryakov
{
  Rectangle::Rectangle(const point_t &center, const double width, const double height) :
    center_(center),
    width_(width),
    height_(height)
  {
    if (width < 0.0)
    {
      throw std::invalid_argument("Width can't be negative");
    }
    if (height < 0.0)
    {
      throw std::invalid_argument("Height can't be negative");
    }
  }
  
  double Rectangle::getArea() const
  {
    return width_ * height_;
  }
  
  rectangle_t Rectangle::getFrameRect() const
  {
    return {center_, width_, height_};
  }
  
  void Rectangle::move(const point_t &newCenterPoint)
  {
    center_ = newCenterPoint;
  }
  
  void Rectangle::move(const double dx, const double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }
  
  void Rectangle::scale(const double factor)
  {
    if (factor < 0.0)
    {
      throw std::invalid_argument("Factor can't be negative");
    }
    width_ *= factor;
    height_ *= factor;
  }
}
