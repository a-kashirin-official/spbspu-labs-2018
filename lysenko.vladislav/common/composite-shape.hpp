#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace lysenko
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape(const std::shared_ptr <Shape> newShape);
    CompositeShape(const CompositeShape & copyShape);
    CompositeShape(CompositeShape && moveShape);
    CompositeShape & operator= (const CompositeShape & copyShape);
    CompositeShape & operator= (CompositeShape && moveShape);
    std::shared_ptr<Shape> & operator[] (const int numb);
    int getSize();
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &center) override;
    void move(const double dx, const double dy) override;
    void scale(const double dk) override;
    void addShape(const std::shared_ptr<Shape> new_shape);
  private:
    std::unique_ptr<std::shared_ptr<Shape> []> array_;
    int size_;
  };
}
#endif
