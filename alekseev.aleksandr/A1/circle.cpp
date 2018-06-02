#include "circle.hpp"

#include <stdexcept>
#include <math.h>

Circle::Circle(const point_t & centre, const double radius):
centre_(centre),
radius_(radius)
{
    if (radius < 0)
    {
        throw std::invalid_argument("Invalid circle");
    }
}

double Circle::getArea() const
{
    return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
    return {centre_, 2 * radius_, 2 * radius_};
}

void Circle::move(const point_t & pos)
{
    centre_ = pos;
}

void Circle::move(const double dx, const double dy)
{
    centre_.x += dx;
    centre_.y += dy;
}
