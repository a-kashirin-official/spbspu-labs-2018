#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.hpp"

class Triangle : public Shape
{
public:
    Triangle(const point_t &firstPt, const point_t &secondPt, const point_t &thirdPt);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t &p) override;

private:
    point_t firstPt_;
    point_t secondPt_;
    point_t thirdPt_;
};
#endif

