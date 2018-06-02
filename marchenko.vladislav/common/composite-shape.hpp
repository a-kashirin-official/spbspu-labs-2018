#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace marchenko
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const std::shared_ptr<Shape> & obj);
    CompositeShape(const CompositeShape & obj);
    CompositeShape(CompositeShape && obj);
    CompositeShape & operator= (const CompositeShape & elem) noexcept;
    CompositeShape & operator= (CompositeShape && elem);
    std::shared_ptr<Shape> operator [] (const size_t ind) const;
    void addShape(const std::shared_ptr<Shape> & obj);
    void deleteShape(const size_t ind);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t & newPos) override;
    void scale(const double coefficient) override;
    size_t getSize() const;
  private:
    std::unique_ptr< std::shared_ptr<Shape>[]> parts_;
    size_t size_;
  };
}

#endif 
