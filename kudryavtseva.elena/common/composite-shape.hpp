#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include <memory>
#include <stdexcept>
#include "shape.hpp"

namespace kudryavtseva
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape();
    CompositeShape(Shape *newShape);
    CompositeShape(const CompositeShape &cmp);
    CompositeShape(CompositeShape &&cmp);
    Shape* operator[](int index) const;
    CompositeShape &operator=(CompositeShape &cmp);
    CompositeShape &operator=(CompositeShape &&cmp);
    void removeShape(const int index);
    void add(Shape *object);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t &center) override;
    void scale (double coeff) override;
    int getSize() const;
    void printf() const override;
    point_t getPos() const override;
    void rotate(double angle) override;
  private:
    std::unique_ptr<Shape *[]> objects_;
    int size_;
  };
}

#endif
