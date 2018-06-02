#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include <memory>
#include <iostream>

namespace khodyreva
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape(const std::shared_ptr <Shape> & newShape);
    CompositeShape(const CompositeShape & object);
    CompositeShape(CompositeShape && object);
    CompositeShape & operator=(const CompositeShape & object);
    CompositeShape & operator=(CompositeShape && object);
    std::shared_ptr<Shape> & operator[] (size_t index) const;
    void addShape(const std::shared_ptr<Shape> & newShape);
    void deleteShape(size_t index);
    size_t getSize() const;
    void move(const point_t & centre) override;
    void move(const double dx, const double dy);
    void scale(const double ratio) override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void rotate(double angle) override;
    std::string getName() const override;
  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> data_;
    size_t size_;
  };
}


#endif // COMPOSITE_SHAPE_HPP
