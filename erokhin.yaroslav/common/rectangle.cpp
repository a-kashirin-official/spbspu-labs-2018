//
// Created by Yaroslav on 30.03.2018.
//

#include "rectangle.hpp"
#include <iostream>
#include <cmath>

erokhin::Rectangle::Rectangle(const point_t &pos, const double width, const double height) :
        width_(width),
        height_(height),
        posit_(pos),
        angle_(0.0),
        rectw_(width),
        recth_(height)
{
    if (width < 0.0 && height < 0.0)
    {
        throw std::invalid_argument("width and height");
    }
    else
    {
        if (width < 0.0)
        {
            throw std::invalid_argument("width");
        }
        if (height < 0.0)
        {
            throw std::invalid_argument("height");
        }
    }
}

double erokhin::Rectangle::getArea() const
{
    return width_ * height_;
}

erokhin::rectangle_t erokhin::Rectangle::getFrameRect() const
{
    return {rectw_, recth_, posit_};
}

void erokhin::Rectangle::move(const double dx, const double dy)
{
    posit_.x = posit_.x + dx;
    posit_.y = posit_.y + dy;
}

void erokhin::Rectangle::move(const point_t &p)
{
    posit_ = p;
}

void erokhin::Rectangle::scale(const double x)
{
    if (x < 0.0)
    {
        throw std::invalid_argument("scale");
    }
    width_ = width_ * x;
    height_ = height_ * x;
    rotate(0);
}

void erokhin::Rectangle::rotate(const double degrees)
{
    angle_ += degrees;
    point_t rtup = {width_ / 2, height_ / 2};
    point_t rtdn = {width_ / 2, - height_ / 2};
    double radns = angle_ * M_PI / 180;
    point_t edge[2] = {{0, 0}, {0, 0}};
    edge[0].x = fabs(rtup.x * cos(radns) - rtup.y * sin(radns));
    edge[0].y = fabs(rtup.y * cos(radns) + rtup.x * sin(radns));
    edge[1].x = fabs(rtdn.x * cos(radns) - rtdn.y * sin(radns));
    edge[1].y = fabs(rtdn.y * cos(radns) + rtdn.x * sin(radns));
    if (edge[0].x < edge[1].x)
    {
        rectw_ = edge[1].x * 2;
    }
    else
    {
        rectw_ = edge[0].x * 2;
    }
    if (edge[0].y < edge[1].y)
    {
        recth_ = edge[1].y * 2;
    }
    else
    {
        recth_ = edge[0].y * 2;
    }
}

void erokhin::Rectangle::viewName() const
{
    std::cout << "Rectangle ";
}
