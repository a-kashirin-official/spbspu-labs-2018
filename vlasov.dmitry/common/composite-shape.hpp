#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <iostream>
#include <memory>
#include "shape.hpp"

namespace vlasov
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape(std::shared_ptr<Shape> newShape);
    CompositeShape();
    void move(const point_t &poss);
    void move(const double xOffset, const double yOffset);
    double getArea() const;
    rectangle_t getFrameRect() const;
    void scale(const double coef_);
    void addShape(const std::shared_ptr<Shape> newShape);
    void removeShape(const int index);

  private:
    int size_;
    rectangle_t compositeRect_;
    std::unique_ptr<std::shared_ptr<Shape>[]> shapeArr_;
  };
}

#endif //VLASOV_DMITRY_LABS_COMPOSITE_SHAPE_HPP
