#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include <memory>
#include "shape.hpp"

namespace shumkovskaya

{
  class CompositeShape :public Shape
  {
  public:
    CompositeShape(std::shared_ptr<Shape> shape);
    CompositeShape(const CompositeShape & rhs);
    CompositeShape & operator = (const CompositeShape & rsh);
    std::shared_ptr<Shape > operator[](int index) const;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & p) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double angle) noexcept override;
    void addShape(const std::shared_ptr<Shape> newShape);
    void removeShape(const int index);
    void removeAll();
    int getAmount() const;
  private:
    int amount_;
    std::unique_ptr<std::shared_ptr<Shape>[]> array_;
    double angle_;
  };
}

#endif
