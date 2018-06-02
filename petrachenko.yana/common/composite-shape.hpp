#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace petrachenko
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape(Shape *shp);
    CompositeShape(CompositeShape &&shp);
    CompositeShape(const CompositeShape &shp);
    ~CompositeShape();

    Shape *operator[](size_t num) const;
    CompositeShape &operator = (CompositeShape &shp);
    CompositeShape &operator = (CompositeShape &&shp);

    void addShape(Shape *shp);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &p) override;
    void move(const double dx, const double dy) override;
    void scale(double coefficient) override;
    void rotate(double alpha) override;
    size_t getCount() const;
    point_t rotatePoint(const point_t &center, const point_t &p, double alpha);
    void print() const;
  private:
    std::unique_ptr<Shape *[]> figures_;
    size_t count_;
  };
}

#endif

