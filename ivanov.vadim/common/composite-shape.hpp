#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace ivanov
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape(const std::shared_ptr<Shape> &shapeElement);
    CompositeShape(const CompositeShape &);
    CompositeShape & operator=(const CompositeShape &);
    void addShape (const std::shared_ptr<Shape> &shapeElement);
    void removeShape(const size_t index);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void scale(const double factor) override;
    void move(const point_t & pos) noexcept override;
    void move(const double dx, const double dy) noexcept override;

  private:
    std::unique_ptr <std::shared_ptr<Shape>[]> shapeList_;
    size_t shapeAmount_;
  };
  std::ostream & operator <<(std::ostream & out, const CompositeShape & s);
}
#endif
