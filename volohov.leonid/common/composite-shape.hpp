#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace volohov
{
  class CompositeShape:public Shape
  {
  public:
    CompositeShape(std::shared_ptr<Shape> shape);
    CompositeShape(const CompositeShape & compositeshape);
    CompositeShape & operator = (const CompositeShape & compositeshape);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & newCenter) override;
    void move(const double dx, const double dy) override;
    void scale(const double coefficient) override;
    void addShape(const std::shared_ptr<Shape> newShape);
    void removeShape(const int index);
    void removeAll();
    int getCount() const;
  private:
    int counter_;
    std::unique_ptr<std::shared_ptr<Shape>[]> array_;
  };
}

#endif //COMPOSITE_SHAPE_HPP
