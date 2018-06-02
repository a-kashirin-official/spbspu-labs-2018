//
// Created by Yaroslav on 31.03.2018.
//

#include "circle.hpp"
#include <cmath>
#include <iostream>

erokhin::Circle::Circle(const point_t &pos, double rads):
        radius_(rads),
        posit_(pos),
        angle_(0.0)
{
    if (rads < 0.0)
    {
        throw std::invalid_argument("radius");
    }
};

double erokhin::Circle::getArea() const
{
    return M_PI * radius_ * radius_;
}

erokhin::rectangle_t erokhin::Circle::getFrameRect() const
{
    return {2 * radius_, 2 * radius_, posit_};
}

void erokhin::Circle::move(const double dx, const double dy)
{
    posit_.x = posit_.x + dx;
    posit_.y = posit_.y + dy;
}

void erokhin::Circle::move(const point_t &p)
{
    posit_ = p;
}

void erokhin::Circle::scale(const double x)
{
    if (x < 0.0)
    {
        throw std::invalid_argument("scale");
    }
    radius_ = radius_ * x;
}

void erokhin::Circle::rotate(const double degrees)
{
    angle_ += degrees;
}

void erokhin::Circle::viewName() const
{
    std::cout << "Circle ";
}
