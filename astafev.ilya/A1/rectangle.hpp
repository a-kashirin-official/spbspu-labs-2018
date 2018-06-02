#ifndef HPP_RECTANGLE
#define HPP_RECTANGLE

#include "shape.hpp"

class Rectangle: 
  public Shape
{
public:
  Rectangle(const point_t &centre, double width, double height);

  double getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;  
  void move(const double dx, const double dy) noexcept override;
  void move(const point_t &newcentre) noexcept override;

private:
  point_t centre_;
  double width_;
  double height_;
};

#endif

