#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace petrov
{
  class CompositeShape:
    public petrov::Shape
  {
  public:
    CompositeShape(const std::shared_ptr< petrov::Shape > shape);
    CompositeShape(const CompositeShape & compositeShape);
    ~CompositeShape();
    CompositeShape & operator=(const CompositeShape & compositeShape);
    double getArea() const noexcept override;
    petrov::rectangle_t getFrameRect() const noexcept override;
    void move(const petrov::point_t & pos) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double factor) override;
    void rotate(const double angle) noexcept override;
    void addShape(std::shared_ptr< petrov::Shape > shape);
    void removeShape(const int shapeNumber);
    void deleteShapes() noexcept;
    int getSize() const noexcept;
  private:
    std::unique_ptr< std::shared_ptr< petrov::Shape >[] > elements_;
    int size_;
    double angle_;
  };
}

#endif
