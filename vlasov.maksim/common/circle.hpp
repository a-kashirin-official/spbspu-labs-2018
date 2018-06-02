#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace vlasov {
  class Circle : public Shape {
    public:
    Circle(double _radius, point_t _pos);

    virtual double getArea() const override;

    virtual rectangle_t getFrameRect() const override;

    virtual void scale(double _multiplier) override;

    private:
    double radius;
  };
}
#endif 
