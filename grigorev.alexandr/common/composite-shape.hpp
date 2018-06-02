#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace grigorev
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const std::shared_ptr< Shape > shape);
    CompositeShape(const CompositeShape & comp);
    CompositeShape(CompositeShape && comp);
    CompositeShape & operator = (const CompositeShape & comp);
    CompositeShape & operator = (CompositeShape && comp);
    std::shared_ptr< Shape > operator [] (const int index) const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & newCenter) override;
    void move(const double dx, const double dy) override;
    void scale(const double coef) override;
    void rotate(const double angle) override;
    void addShape(std::shared_ptr< Shape > shape);
    void removeShape(const int index);
    void deleteShapes();
    int getSize() const;
  private:
    std::unique_ptr< std::shared_ptr< Shape >[] > list_;
    int size_;
    double angle_;
  };
}

#endif
