#ifndef RECTANGLE_HEADER
#define RECTANGLE_HEADER
#include "shape.hpp"
namespace zasyadko
{
class Rectangle :
  public Shape
{
public:
  
  Rectangle(const point_t & center, const double & height, const double & width);
  
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  
  void move(const point_t & Center) override;
  void move(const double add_x, const double add_y) override;
  
  void print() const override;
  void scale(const double factor) override;
  
private :
  
  point_t cntr_;
  
  double height_;
  
  double width_;
};
}

#endif
