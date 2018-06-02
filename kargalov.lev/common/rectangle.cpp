#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>

using namespace kargalov;

Rectangle::Rectangle(const rectangle_t& parametrs)
: parametrs_(parametrs)
{
    if (parametrs_.height < 0.0 || parametrs_.width < 0.0) {
        throw std::invalid_argument("WARNIG: invalid parametr of Rectangle\n");
    }
}

void Rectangle::move(const point_t& point)
{
    parametrs_.pos = point;
}

void Rectangle::move(const double dx, const double dy)
{
    parametrs_.pos.x += dx;
    parametrs_.pos.y += dy;
}
void Rectangle::scale(const double increment)
{
    parametrs_.width *= increment;
    parametrs_.height *= increment;
    
    if (increment < 0.0){
        throw std::invalid_argument("WARNING: invalid coefficient of scaling\n");
    }
}
double Rectangle::getArea() const
{
    return parametrs_.height * parametrs_.width;
}

rectangle_t Rectangle::getFrameRect() const
{
    return parametrs_;
}



