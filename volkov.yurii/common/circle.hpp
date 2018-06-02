#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include <iostream>

namespace volkov
{
  class Circle: public Shape
  {
  public:
    Circle(const point_t & pos, double radius);
    friend std::ostream & volkov::operator <<(std::ostream & out, const Circle & circle);
    double getRadius() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t & pos) override;
    void scale(const double f) override;

  private:
    point_t pos_;
    double radius_;
  };

  std::ostream & operator << (std::ostream & out, const Circle & circle);
}

#endif //CIRCLE_HPP

