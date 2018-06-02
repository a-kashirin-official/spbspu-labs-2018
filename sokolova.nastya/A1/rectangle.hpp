#ifndef HPP_RECTANGLE
#define HPP_RECTANGLE

#include "shape.hpp"

class Rectangle : public Shape
{
  public:
    Rectangle(const point_t &centre, double width, double height);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void scale(double factor) override;
    void move(const point_t & newcentre) override;
    void move(double dx, double dy) override;

  private:
    double width_;
    double height_;
};
#endif
  
