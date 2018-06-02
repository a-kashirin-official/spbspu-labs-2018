#ifndef COMPOSITE_SHAPE_HPP_INCLUDED
#define COMPOSITE_SHAPE_HPP_INCLUDED
#include <memory>
#include "shape.hpp"

namespace revtova
{
  class CompositeShape: public Shape
  {
  public:
    using ptr_type = std::shared_ptr<Shape>;
    using layer_type = std::unique_ptr<ptr_type[]>;

    CompositeShape(const ptr_type rhs);
    CompositeShape(const CompositeShape &rhs);
    ~CompositeShape();

    double getArea() const noexcept override;
    rectangle_t getFrameRect() const override;
    void scale(const double kscale) override;
    void move(const point_t & pos) override;
    void move(const double dx, const double dy) override;

    size_t getCount() const;
    point_t getPos() const;
    void addShape (ptr_type rhs);
    void remove(size_t index);
    void rotate(const double angle) override;

    layer_type operator[](size_t index) const;
    CompositeShape &operator = (const CompositeShape &rhs);

  private:
    layer_type figures_;
    size_t count_;
    double angle_;
  };
}
#endif // COMPOSITE_SHAPE_HPP_INCLUDED
