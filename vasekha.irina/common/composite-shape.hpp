#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <iostream>
#include <memory>
#include "base-types.hpp"
#include "shape.hpp"

namespace vasekha
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape() noexcept;
    CompositeShape(const CompositeShape & compSh);
    CompositeShape(CompositeShape && compSh) noexcept;
    CompositeShape & operator= (const CompositeShape & compSh);
    CompositeShape & operator= (CompositeShape && compSh) noexcept;
    Shape::ptr_shape operator[] (size_t index) const;
    void add(const std::shared_ptr<Shape> & shape);
    void remove(size_t index);
    size_t getSize() const noexcept;
    virtual double getArea() const noexcept override;
    virtual rectangle_t getFrameRect() const noexcept override;
    virtual void move(const point_t & point) noexcept override;
    virtual void move(const double dx, const double dy) noexcept override;
    virtual void scale(const double factor) override;
    virtual void rotate(const double angle) noexcept override;
  private:
    point_t pos_;
    size_t size_;
    std::unique_ptr<ptr_shape[]> shapes_;
    virtual void print(std::ostream & out) const noexcept override;
  };
}

#endif
