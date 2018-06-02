#ifndef HPP_CIRCLE
#define HPP_CIRCLE

#include "shape.hpp"

class Circle : public Shape
{
  public:
    Circle(const point_t &centre, double radius);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void scale(double factor) override;
    void move(const point_t & newcentre) override;
    void move(double dx, double dy) override;
  
  private:
    double radius_;
};

#endif

