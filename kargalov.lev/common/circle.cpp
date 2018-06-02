#include "circle.hpp"
#include <iostream>
#include <math.h>
#include <stdexcept>


using namespace kargalov;

Circle::Circle(const point_t& center, const double radius)
: center_(center),
radius_(radius)
{
    if (radius_ < 0.0 ) {
        throw std::invalid_argument ("WARNIG: invalid parametr of Circle\n");
    }
}

void Circle::move(const point_t& point)
{
    center_ = point;
}

void Circle::move(const double dx, const double dy)
{
    center_.x += dx;
    center_.y += dy;
}

void Circle::scale(const double increment)
{
    radius_ *= increment;
    
    if (increment < 0.0){
        throw std::invalid_argument("WARNING: invalid coefficient of scaling\n");
    }
}

double Circle::getArea() const
{
    return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{  
    return {radius_ * 2, radius_ * 2, center_};
}


