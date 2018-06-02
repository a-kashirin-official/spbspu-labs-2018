#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include "rectangle.hpp"
#include <memory>

namespace golyshev
{
  class CompositeShape : public Shape
  {
  public:
    explicit CompositeShape(std::shared_ptr<golyshev::Shape> shape);
    CompositeShape(const CompositeShape &ShapeArray);
    CompositeShape(CompositeShape &&ShapeArray) noexcept;
    ~CompositeShape() override = default;
    CompositeShape &operator=(const CompositeShape &shape);
    CompositeShape &operator=(CompositeShape &&ShapeArray) noexcept;
    std::shared_ptr<golyshev::Shape> &operator[](size_t index) const;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &center) override;
    void move(double dx, double dy) override;
    void scale(double coeff) override;
    void rotate(const double angle) override;
    void OutInf() const override;
    void add(std::shared_ptr<golyshev::Shape> shape);
    void remove(size_t i);
    size_t size() const;


  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> list_;
    size_t size_;
  };
}
#endif
