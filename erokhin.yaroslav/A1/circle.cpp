//
// Created by Yaroslav on 31.03.2018.
//

#include "circle.hpp"
#include <cmath>
#include <cassert>

Circle::Circle(const point_t &pos, double rads):
        radius_(rads),
        posit_(pos)
{
    assert(radius_ >= 0);
};

double Circle::getArea() const
{
    return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
    return {2 * radius_, 2 * radius_, posit_};
}

void Circle::move(const double dx, const double dy)
{
    posit_.x = posit_.x + dx;
    posit_.y = posit_.y + dy;
}

void Circle::move(const point_t &p)
{
    posit_ = p;
}
