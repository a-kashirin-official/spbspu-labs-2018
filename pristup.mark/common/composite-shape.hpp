#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"


namespace pristup
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape(Shape * shapeElement);
    void addShape (Shape * shapeElement);
    void delShape(const size_t index);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(const point_t & p) noexcept override;
    void scale(double k) override;
      
  private:
    std::unique_ptr <Shape *[]> shapes_;
    size_t shapeAmount_;
  };
}

#endif

