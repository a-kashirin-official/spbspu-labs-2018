#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include <memory>
#include "shape.hpp"

namespace stakhiev
{
  class CompositeShape : public Shape
  {
  public:
    //Default constructor
    CompositeShape();
    //Constructor with pointer on shape to add
    CompositeShape(const std::shared_ptr <Shape> newShape);
    double getArea() const override;
    stakhiev::rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const stakhiev::point_t & newCenter) override;
    void scale(const double increaseCoefficient) override;

    void add(const std::shared_ptr <Shape> newShape);
    void remove(const size_t index);
  private:
    size_t size_;
    //Array of pointers on shapes
    std::unique_ptr<std::shared_ptr <Shape> []> list_;
  };
}

#endif
