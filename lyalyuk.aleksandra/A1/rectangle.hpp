#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.hpp"

class Rectangle : public Shape
{
public:
    Rectangle(const rectangle_t & rec);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t &p) override;
    void print() const override;
    
private:
    rectangle_t rec_;
};
#endif

