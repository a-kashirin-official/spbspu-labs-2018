#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace shapovalova
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape(const std::shared_ptr<Shape> & element);
    CompositeShape(const CompositeShape & elem);
    CompositeShape(CompositeShape && elem);
    CompositeShape & operator=(const CompositeShape & elem);
    CompositeShape & operator=(CompositeShape && elem);
    std::shared_ptr<Shape> operator [](const int index) const;

    void add(std::shared_ptr<Shape> & element);
    void remove(const int index);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t & posTo) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double degrees) noexcept override;

  private:
    std::unique_ptr<std::shared_ptr<Shape> []> shapeList_;
    int shapeAmount_;
  };
}

#endif // COMPOSITE_SHAPE_HPP

