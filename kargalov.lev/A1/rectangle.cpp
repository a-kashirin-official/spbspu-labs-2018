#include "rectangle.hpp"
#include <iostream>


Rectangle::Rectangle(const rectangle_t& parametrs)
: parametrs_(parametrs)
{
    if (parametrs_.height < 0 || parametrs_.width < 0) {
        std::cerr << "WARNIG: invalid parametr of Rectangle\n";
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

double Rectangle::getArea() const
{
    return parametrs_.height * parametrs_.width;
}

rectangle_t Rectangle::getFrameRect() const
{
    return parametrs_;
}

