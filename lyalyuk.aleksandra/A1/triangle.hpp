#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.hpp"

class Triangle : public Shape
{
public:
    Triangle(const point_t &fPt, const point_t &sPt, const point_t &tPt);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t &p) override;
    void print() const override;
    
private:
    point_t fPt_;
    point_t sPt_;
    point_t tPt_;
};
#endif

