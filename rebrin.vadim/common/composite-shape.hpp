#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace rebrin
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape(const std::shared_ptr< rebrin::Shape > newShape);
    CompositeShape(const rebrin::CompositeShape & composite_shape);
    CompositeShape & operator= (const rebrin::CompositeShape & composite_shape);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t & newPos) override;
    void scale(const double factor) override;

    void addShape(const std::shared_ptr< rebrin::Shape > newShape);
    void removeShape(const int index);
    void clear();
    
  private:
    std::unique_ptr < std::shared_ptr < rebrin::Shape >[] > list_;
    int count_;
  };
}

#endif //COMPOSITE_SHAPE_HPP
