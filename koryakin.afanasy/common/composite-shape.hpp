#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"

namespace koryakin
{
  class CompositeShape:
    public Shape
  {
  public:
    CompositeShape(Shape * newShape);
    ~CompositeShape();
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t & newPos) noexcept override;
    void move(const double dx, const double dy) noexcept override;
   // point_t getPos() const noexcept override;
    void scale(const double factor) override;

    int getCount() const noexcept;
    void addShape(Shape * shape);
    void removeShape(const int index);
    void clear();

    CompositeShape &operator=(const CompositeShape & rhs) noexcept;
    Shape * operator[](const int index) const;
  private:
    Shape ** list_;
    int count_;
  };
}

#endif
