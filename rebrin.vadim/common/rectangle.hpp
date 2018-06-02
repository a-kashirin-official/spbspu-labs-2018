#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace rebrin
{
  class Rectangle : public Shape
  {
  public:

    Rectangle(const rectangle_t& parameters);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t& pos) override;

    void move(const double dx, const double dy) override;

    void scale(const double factor) override;

  private:
    rectangle_t parameters_;
  };
}

#endif
