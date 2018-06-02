//
// Created by matvey on 30.04.18.
//
#ifndef A3_COMPOSITESHAPE_HPP
#define A3_COMPOSITESHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace russkov
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape(const std::shared_ptr<russkov::Shape> shape_ptr);
    CompositeShape(const russkov::CompositeShape & obj);
    CompositeShape(russkov::CompositeShape && obj);

    CompositeShape &operator =(const russkov::CompositeShape & obj);
    CompositeShape &operator =(russkov::CompositeShape && obj);
    std::shared_ptr<Shape> operator [](const size_t index);

    void addShape(const std::shared_ptr <russkov::Shape> shape_ptr);
    void deleteShape(const size_t index);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & point) override;
    void move(double dx, double dy) override;
    void scale(const double ratio) override;
    void rotate(const double alpha) override;

  private:
    std::unique_ptr <std::shared_ptr <russkov::Shape>[]> shapes_;
    size_t size_;
    double alpha_;
  };
}
#endif
