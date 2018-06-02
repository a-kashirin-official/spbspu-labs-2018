#ifndef COMPOSITE_SHAPE_HPP_INCLUDED
#define COMPOSITE_SHAPE_HPP_INCLUDED

#include "shape.hpp"
#include <memory>

namespace kostylev
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape(const std::shared_ptr<Shape> & obj);
    CompositeShape(const CompositeShape & obj);
    CompositeShape(CompositeShape && obj);

    std::shared_ptr<Shape> operator [] (const size_t index) const;
    CompositeShape & operator= (const CompositeShape & object);
    CompositeShape & operator= (CompositeShape && object);
    void addShape(const std::shared_ptr<Shape> & obj);
    void removeShape(const size_t index);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t & point) override;
    void scale(double coef) override;
    size_t getLength() const;

  private:
   std::unique_ptr< std::shared_ptr<Shape>[]> shapes_;
    size_t length_;
  };
}

#endif // COMPOSITE_SHAPE_HPP_INCLUDED

