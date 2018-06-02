#include "triangle.hpp"
#include <iostream>

Triangle::Triangle(const point_t &a, const point_t &b, const point_t &c):a_(a), b_(b), c_(c)
{
}

double Triangle::getArea() const
{
    return (0.5 * ((a_.x - c_.x)*(b_.y - c_.y) - (b_.x - c_.x)*(a_.y - c_.y)));
}

void Triangle::move(const double dx, const double dy)
{
    a_.x += dx;
    a_.y += dy;
    b_.x += dx;
    b_.y += dy;
    c_.x += dx;
    c_.y += dy;
}

void Triangle::move(const point_t &newPoint)
{
    //calculate old center and move to new one
    move(newPoint.x - ((a_.x + b_.x + c_.x)/3.0), newPoint.y - ((a_.y + b_.y + c_.y)/3.0));
}

rectangle_t Triangle::getFrameRect() const
{
    point_t lowerLeftPoint = a_;
    if (lowerLeftPoint.x > b_.x)
    {
        lowerLeftPoint.x = b_.x;
    }
    if (lowerLeftPoint.x > c_.x)
    {
        lowerLeftPoint.x = c_.x;
    }
    if (lowerLeftPoint.y > b_.y)
    {
        lowerLeftPoint.y = b_.y;
    }
    if (lowerLeftPoint.y > c_.y)
    {
        lowerLeftPoint.y = c_.y;
    }

    point_t upperRightPoint = a_;
    if (upperRightPoint.x < b_.x)
    {
        upperRightPoint.x = b_.x;
    }
    if (upperRightPoint.x < c_.x)
    {
        upperRightPoint.x = c_.x;
    }
    if (upperRightPoint.y < b_.y)
    {
        upperRightPoint.y = b_.y;
    }
    if (upperRightPoint.y < c_.y)
    {
        upperRightPoint.y = c_.y;
    }

    return {upperRightPoint.x - lowerLeftPoint.x, upperRightPoint.y - lowerLeftPoint.y,
            {(upperRightPoint.x + lowerLeftPoint.x) / 2.0, (upperRightPoint.y + lowerLeftPoint.y) / 2.0}};
}





