#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace spodeneyko
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape(const std::shared_ptr<Shape> & shapeElement);
    CompositeShape(const CompositeShape & object);
    CompositeShape(CompositeShape && object);
    CompositeShape & operator =(const CompositeShape & object);
    CompositeShape &  operator =(CompositeShape && object);
    std::shared_ptr<Shape> operator [](const unsigned int index) const;
    void addShape (const std::shared_ptr<Shape> & shapeElement);
    void removeShape(const unsigned int index);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    std::string getName() const noexcept override;
    void scale(const double factor) override;
    void move(const point_t & point) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void rotate (const double angle) noexcept override;

  private:
    using array_type = std::unique_ptr<std::shared_ptr<Shape>[]>;
    array_type shapeList_;
    size_t shapeAmount_;
  };
}

#endif
