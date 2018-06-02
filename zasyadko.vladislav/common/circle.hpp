#ifndef CIRCLE_HEADER
#define CIRCLE_HEADER
#include "shape.hpp"
namespace zasyadko
{
class Circle :
  public Shape
{
public:
  
  Circle(const point_t & center, const double radius);
  
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  double getRadius() const;
  
  void move(const point_t & Center) override;
  void move(const double add_x, const double add_y) override;
  
  void print() const override;
  void scale(const double factor) override;
  
private:
  
  point_t cntr_;
  
  double r_;
  
};
}
  
#endif
    
