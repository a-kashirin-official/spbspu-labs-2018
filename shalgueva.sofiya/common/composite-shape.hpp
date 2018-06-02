#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace shalgueva
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape(const std::shared_ptr<Shape> & object);
    CompositeShape(const CompositeShape & object);
    CompositeShape(CompositeShape && object);

    std::shared_ptr<Shape> operator [] (const size_t index) const;
    CompositeShape & operator= (const CompositeShape & object);
    CompositeShape & operator= (CompositeShape && object);
    void addShape(const std::shared_ptr<Shape> & object);
    void removeShape(const size_t index);

    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(const point_t & posTo) noexcept override;
    void scale(double coefficient) override;
    void rotate(double alpha) noexcept override;
    size_t getLength() const noexcept;

  private:
   std::unique_ptr< std::shared_ptr<Shape>[]> figures_;
   size_t length_;
  };
}// shalgueva

#endif // COMPOSITE_SHAPE_HPP_INCLUDED
