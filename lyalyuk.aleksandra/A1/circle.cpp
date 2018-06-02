#include <iostream>
#include <stdexcept>
#include <cmath>
#include <assert.h>

#include "circle.hpp"

Circle::Circle(double radius, const point_t &position) :
r_(radius),
p_(position)
{
    assert (r_ >= 0);
}

double Circle::getArea() const
{
    return M_PI * r_ * r_;
}

rectangle_t Circle::getFrameRect() const
{
    return { 2 * r_, 2 * r_, p_ };
}

void Circle::move(double dx, double dy)
{
    p_.x += dx;
    p_.y += dy;
}

void Circle::move(const point_t &p)
{
    p_ = p;
}

void Circle::print() const
{
    std::cout << "area: " << getArea() << std::endl;
    std::cout << "width of frame: " << getFrameRect().width << std::endl;
    std::cout << "height of frame: " << getFrameRect().height << std::endl;
    std::cout << "center point: (" << getFrameRect().pos.x
    << ";" << getFrameRect().pos.y << ")" << std::endl;
}

