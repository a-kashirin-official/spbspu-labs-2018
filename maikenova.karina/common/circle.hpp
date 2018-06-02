#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace maikenova
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t & center, const double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & newPos) override;
    void move(const double dx, const double dy) override;
    void scale(const double ratio) override;
    point_t getPos() const override;
    void rotate(double phi) override;
  private:
    point_t center_;
    double r_;
  };
}
#endif //CIRCLE_HPP
