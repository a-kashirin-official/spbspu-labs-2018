#ifndef COMPOSITE_SHAPE_HPP_INCLUDED
#define COMPOSITE_SHAPE_HPP_INCLUDED
#include <memory>
#include "shape.hpp"

namespace revtova
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape(Shape *rhs);
    CompositeShape(CompositeShape &&rhs);
    CompositeShape(const CompositeShape &rhs);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void scale(const double kscale) override;
    void move(const point_t & pos) override;
    void move(const double dx, const double dy) override;

    size_t getCount() const;
    void addShape (Shape *rhs);
    void remove(size_t index);
    void clear();

    Shape *operator[](size_t index) const;
    CompositeShape &operator = (const CompositeShape &rhs);
    CompositeShape &operator = (CompositeShape &&rhs);

  private:
    std::unique_ptr<Shape*[]> list_;
    size_t count_;
  };
}
#endif // COMPOSITE_SHAPE_HPP_INCLUDED
