#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <cstddef>
#include "shape.hpp"

namespace sibikin
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(Shape * newShape);
    CompositeShape(const CompositeShape &comp);
    CompositeShape(CompositeShape &&comp);
    ~CompositeShape();

    CompositeShape& operator=(const CompositeShape &comp);
    CompositeShape& operator=(CompositeShape &&comp);
    Shape& operator[](const size_t index) const;

    void addShape(Shape * newShape);
    void deleteShape(const size_t index);
    size_t getSize() const;
    point_t getPos() const;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & newCenter) override;
    void move(const double dx, const double dy) override;
    void scale(const double coef) override;
    void rotate(const double phi) override;
  private:
    size_t count_;
    Shape ** arr_;
    point_t pos_;
  };
}

#endif
