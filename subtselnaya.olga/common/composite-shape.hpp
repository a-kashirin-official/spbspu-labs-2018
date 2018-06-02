#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include <memory>
#include "shape.hpp"

namespace subtselnaya
{
  class CompositeShape : public Shape {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape & rhs);
    CompositeShape(CompositeShape && rhs);

    using ptr_type = std::shared_ptr < Shape >;

    CompositeShape & operator =(const CompositeShape & rhs);
    CompositeShape & operator =(CompositeShape && rhs);

    size_t size() const;
    ptr_type operator [](size_t index) const;
    void addShape(const ptr_type & shape);
    void removeShape(const size_t index);

    double getArea() const noexcept;
    rectangle_t getFrameRect() const noexcept;
    void move(const point_t & resPoint) noexcept;
    void move(const double dx, const double dy) noexcept;
    void scale(const double value);

  private:
    size_t size_;
    std::unique_ptr < ptr_type[] > shapes_;
  };
}

#endif
