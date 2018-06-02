#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include <memory>
#include "base-types.hpp"
#include "shape.hpp"

namespace reznik
{
  class CompositeShape :
    public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape& copy);
    CompositeShape(CompositeShape && other);

    CompositeShape & operator=(const CompositeShape& copy);
    CompositeShape & operator=(CompositeShape && other);

    double getArea() const;
    rectangle_t getFrameRect() const;
    void move(double dx, double dy);
    void move(const point_t& center);
    void scale(double k);

    void addShape(const std::shared_ptr<Shape> shape);

  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> arr_;
    size_t count_;
  };
}

#endif
