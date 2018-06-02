#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace dumaev
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape(const std::shared_ptr < Shape > shape);
    CompositeShape(const CompositeShape &compositeShape);
    CompositeShape &operator = (const CompositeShape &compositeShape);
    void addShape(const std::shared_ptr < Shape > shape);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t &point) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double angle) noexcept override;
    point_t getPos() const noexcept override;

  private:
    std::unique_ptr < std::shared_ptr < Shape > [] > shapes_;
    int size_;
    double angle_;
  };
}

#endif
