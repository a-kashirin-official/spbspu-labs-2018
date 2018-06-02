//
// Created by Yaroslav on 30.03.2018.
//

#ifndef LABA1_CIRCLE_HPP
#define LABA1_CIRCLE_HPP

#include "shape.hpp"

class Circle: public Shape
{
public:
    Circle(const point_t &pos, const double rads);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const double dx,const double dy) override;
    void move(const point_t &p) override;
private:
    double radius_;
    point_t posit_;
};
#endif //LABA1_CIRCLE_HPP
