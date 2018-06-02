#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace pichugina
{
  class CompositeShape:
    public pichugina::Shape
  {
  public:
    CompositeShape(const std::shared_ptr <pichugina::Shape> shape_n);
    CompositeShape(const pichugina::CompositeShape & copy);
    CompositeShape(pichugina::CompositeShape && move) = default;
    CompositeShape & operator=(const pichugina::CompositeShape & copy);
    CompositeShape & operator=(pichugina::CompositeShape && move);
    double getArea() const override;
    void scale(const double factor) override;
    pichugina::rectangle_t getFrameRect() const override;
    void move(const pichugina::point_t & new_centre) override;
    void move(const double dx, const double dy) override;
    void addShape(std::shared_ptr <pichugina::Shape> shape_n);
    std::shared_ptr < pichugina::Shape > getShape(int const shapeNumber) const;
    void removeShape(const int shapeNumber);
    void deleteShapes();
    int getSize() const;
  private:
    std::unique_ptr <std::shared_ptr <pichugina::Shape>[] > parts_;
    int size_;
  };
}

#endif
