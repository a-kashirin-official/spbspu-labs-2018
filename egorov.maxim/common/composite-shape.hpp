#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace egorov
{
  class CompositeShape : Shape
  {
  public:
    CompositeShape();

    CompositeShape(const CompositeShape &object);

    CompositeShape(CompositeShape &&object) noexcept;

    CompositeShape &operator=(const CompositeShape &rhs);

    CompositeShape &operator=(CompositeShape &&rhs) noexcept;

    std::shared_ptr<Shape> operator[](const unsigned int index) const;

    void addShape(const std::shared_ptr<Shape> &shape);

    void removeShape(const unsigned int index);

    size_t getQuantity() const noexcept;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t &point) noexcept override;

    void move(const double deltax, const double deltay) noexcept override;

    void scale(const double coefficent) override;

    void rotate(double angle) noexcept override;

    void clear() noexcept;

    std::string getName() const noexcept override;

  private:
    size_t cout_;
    std::unique_ptr <std::shared_ptr <Shape>[]> figures_;
  };
}

#endif
