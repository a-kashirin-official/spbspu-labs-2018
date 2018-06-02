#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace ponomarev
{
  class Rectangle : public Shape
  {
  public:

    Rectangle(const point_t &center, const double width, const double height);

    double getArea() const override;
 
    rectangle_t getFrameRect () const override;

    void move(const point_t &center) override;
    void move(const double dx, const double dy) override;

    void scale(const double coefficient) override;
    void rotate(const double angle) override;

    void printShape() const override;

  private:

    point_t corners_[4];
    double width_;
    double height_;

  };
}
#endif
