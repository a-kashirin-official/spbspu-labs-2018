#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace vlasov {
  class Shape {
    public:

    virtual double getArea() const = 0;

    virtual rectangle_t getFrameRect() const = 0;

    virtual void move(const point_t & arrival);

    virtual void move(double difX, double difY);

    virtual void showPosition() const;

    virtual void scale(double _multiplier)= 0;

    virtual ~Shape() = default;

    point_t pos;
  };
}
#endif
