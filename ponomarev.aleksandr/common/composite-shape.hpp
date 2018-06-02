#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"
#include "matrix-shape.hpp"

namespace ponomarev
{
  class CompositeShape : public Shape
  {
  public:

    CompositeShape();

    CompositeShape(const CompositeShape &obj);

    CompositeShape(CompositeShape &&obj) noexcept;

    ~CompositeShape();

    CompositeShape &operator=(const CompositeShape &rhs);

    CompositeShape &operator=(CompositeShape &&rhs) noexcept;

    std::shared_ptr<Shape> operator[](const unsigned int index) const;

    void addShape(const std::shared_ptr<Shape> &shape);

    void removeShape(const unsigned int index);

    size_t getQuantity() const;

    void move(const point_t &center)override;
    void move(const double dx, const double dy) override;

    void scale(const double coefficient) override;
    void rotate(const double angle) override;

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void printShape() const override;

    MatrixShape split() const;

  private:

    size_t figuresInArray_;
    std::unique_ptr <std::shared_ptr <Shape>[]> figures_;

  };
}

#endif

