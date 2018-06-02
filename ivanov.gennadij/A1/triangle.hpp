#ifndef A1_TRIANGLE_H
#define A1_TRIANGLE_H

#include "shape.hpp"

class Triangle : public Shape
{
public:
    Triangle(const point_t & a, const point_t & b, const point_t & c);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move (const point_t & newPoint) override;
    void move (const double dx, const double dy) override;
private:
    point_t a_, b_, c_;
};

#endif //A1_TRIANGLE_H
