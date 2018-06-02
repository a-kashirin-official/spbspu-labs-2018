#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t & center, const double width, const double height):rect_{width, height, center}
{
    if  (width < 0.0 || height < 0.0)
    {
        std::cerr << "Error: width or height can't be less than zero" << std::endl;
    }
}

double Rectangle::getArea() const
{
    return rect_.height * rect_.width;
}

rectangle_t Rectangle::getFrameRect() const
{
    return rect_;
}

void Rectangle::move(const point_t &newPoint)
{
    rect_.pos = newPoint;
}

void Rectangle::move(const double dx, const double dy)
{
    rect_.pos.x += dx;
    rect_.pos.y += dy;
}
