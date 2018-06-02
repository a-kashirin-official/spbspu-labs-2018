#include "circle.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(const point_t & center, const double radius):pos(center), r(radius)
{
    if (radius < 0.0)
    {
        std::cerr << "Error: radius can't be less than zero" << std::endl;
    }
}

double Circle::getArea() const
{
    return M_PI*r*r;
}

rectangle_t Circle::getFrameRect() const
{
    return {2.0 * r, 2.0 * r, pos};
}

void Circle :: move(const point_t & newPos)
{
    pos = newPos;
}

void Circle :: move(const double dx, const double dy)
{
    pos.x += dx;
    pos.y += dy;
}
