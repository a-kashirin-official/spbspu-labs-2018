#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace ivanov
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t & center, const double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & transferPoint) override;
    void move(const double dx, const double dy) override;
    void scale(const double scaleFactor) override;
    void printCurrentInfo() const override;
  private:
    point_t center_;
    double radius_;
  };
};

#endif
