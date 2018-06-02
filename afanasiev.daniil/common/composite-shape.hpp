#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace afanasiev
{
  class CompositeShape:
    public Shape
  {
  public:
    CompositeShape(const std::shared_ptr<Shape> shape);
    CompositeShape(const CompositeShape & compositeShape);
    ~CompositeShape();
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t & newPos) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    point_t getPos() const noexcept override;
    void scale(const double factor) override;

    int getCount() const noexcept;
    void addShape(std::shared_ptr<Shape> shape);
    void removeShape(const int index);
    void clear();
    void rotate(const double angle) noexcept override;

    CompositeShape &operator=(const CompositeShape & rhs) noexcept;
    std::shared_ptr<Shape> operator[](const int index) const;
  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> list_;
    int count_;
    double angle_;
  };
}

#endif
