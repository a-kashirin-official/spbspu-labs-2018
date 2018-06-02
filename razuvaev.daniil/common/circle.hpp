#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace razuvaev {
  class Circle : public Shape {
  public:   
    Circle(double r, double x, double y);

    double getArea() const override;
    rectangle_t getFrameRect() const override;   
    void move(point_t c) override;
    void move(double dx, double dy) override;
    
    void scale(double ratio) override;

    void writeInfoOfObject() const override;  

    double getRadius();
    double getHeight();
    double getWidth();
    
  private:
    double  radius_;
    point_t center_;
  };
}
#endif
