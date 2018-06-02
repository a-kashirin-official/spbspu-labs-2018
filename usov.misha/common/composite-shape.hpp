#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace usov {
  class CompositeShape :
    public Shape {
  public:
    CompositeShape(const std::shared_ptr<Shape> shape);
    CompositeShape(const CompositeShape& copy);
    CompositeShape(CompositeShape && other);

    CompositeShape & operator=(const CompositeShape& copy);
    CompositeShape & operator=(CompositeShape && other);
    std::shared_ptr<Shape> getInfoShape(const int counter);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t& center) override;
    void scale(double dscale) override;
    void print() const override;

    void addShape(const std::shared_ptr<Shape> shape);
  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> arr_;
    int count_;
  };
}

#endif // COMPOSITESHAPE_HPP
