#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <bits/unique_ptr.h>
#include "shape.hpp"

namespace almukhametov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape(Shape *shape);

    CompositeShape();

    ~CompositeShape();

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(point_t c) override;

    void move(double dx, double dy) override;

    void scale(double factor) override;

    void newShape(Shape *shape);

    void delShape(int index);

  private:
    std::unique_ptr<Shape *[]> composition;

    int size_;
  };
}

#endif
