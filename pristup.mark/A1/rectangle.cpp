#include <iostream>
#include <stdexcept>
#include <assert.h>

#include "rectangle.hpp"

Rectangle::Rectangle(const rectangle_t & rec) :
rec_(rec)
{
    assert ((rec_.width >= 0) && (rec_.height >= 0));
}

double Rectangle::getArea() const
{
    return (rec_.width * rec_.height);
}

rectangle_t Rectangle::getFrameRect() const
{
    return { rec_.width, rec_.height, rec_.pos };
}

void Rectangle::move(double dx, double dy)
{
    rec_.pos.x += dx;
    rec_.pos.y += dy;
}

void Rectangle::move(const point_t &p)
{
    rec_.pos = p;
}

