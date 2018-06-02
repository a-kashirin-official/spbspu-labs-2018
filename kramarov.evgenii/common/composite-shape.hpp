#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"

namespace kramarov
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape (Shape * shape);
    ~CompositeShape();
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move (const point_t & newLocation) override;
    void move (const double dx, const double dy) override;
    void scale (const double scaleRate) override;

    void addShape (Shape * newShape);
    void deleteShape (const int numb);

    void clear();

    int getQtt() const;
    point_t getXY() const;

    CompositeShape &operator= (const CompositeShape & rValue);
    Shape * operator[] (const int i) const;
  private:
    Shape ** arr_;
    int qtt_;
  };
}

#endif
