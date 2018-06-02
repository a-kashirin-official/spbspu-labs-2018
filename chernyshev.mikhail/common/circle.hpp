#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include"shape.hpp"
namespace chernyshev
{
  class Circle : public Shape
  {   
  public:
    Circle(double r,point_t c);
    double getArea()const override;
    rectangle_t getFrameRect() const override; 
    void Move(double delta_x,double delta_y) override;
    void Move(point_t newPoint) override;
    void scale(double size) override;
    void printScale()const override;
  private:
    double rad_;
     point_t center_;
  };
}
#endif
