#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace lobanova {
  class CompositeShape : public Shape {
  public:
    CompositeShape(const CompositeShape &shapes);

    explicit CompositeShape();

    ~CompositeShape() override;

    CompositeShape &operator=(CompositeShape b);

    Shape *operator[](int index) const;

    Shape *&operator[](int index);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &newPos) override;

    void move(double dx, double dy) override;

    void scale(double p) override;

    void rotate(double p) override;

    void rotatePoint(const point_t &a, double p) override;

    point_t getCentre() const;

    int getSize() const;

    void add(Shape *shape);

    void remove(int index);

    void clear();

  protected:
    int size_;
    int capacity_;

    Shape **elements_;


  };
}


#endif
