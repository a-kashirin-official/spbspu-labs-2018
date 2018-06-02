//
// Created by Yaroslav on 30.03.2018.
//

#include "rectangle.hpp"
#include <cassert>

Rectangle::Rectangle(const point_t &pos, const double width, const double height) :
        width_(width),
        height_(height),
        posit_(pos)
{
    assert((width_ >= 0) && (height_ >= 0));
}

double Rectangle::getArea() const
{
    return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
    return {width_, height_, posit_};
}

void Rectangle::move(const double dx, const double dy)
{
    posit_.x = posit_.x + dx;
    posit_.y = posit_.y + dy;
}

void Rectangle::move(const point_t &p)
{
    posit_ = p;
}
