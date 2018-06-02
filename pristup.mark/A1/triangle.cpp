#include <cmath>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <assert.h>

#include "triangle.hpp"

Triangle::Triangle(const point_t & firstPt, const point_t & secondPt, const point_t & thirdPt) :
firstPt_(firstPt),
secondPt_(secondPt),
thirdPt_(thirdPt)
{
    assert (getArea() >= 0);
}

double Triangle::getArea() const
{
    double firstSide = sqrt(pow(secondPt_.x - firstPt_.x, 2)
                            + pow(secondPt_.y - firstPt_.y, 2));
    double secondSide = sqrt(pow(thirdPt_.x - firstPt_.x, 2)
                             + pow(thirdPt_.y - firstPt_.y, 2));
    double thirdSide = sqrt(pow(thirdPt_.x - secondPt_.x, 2)
                            + pow(thirdPt_.y - secondPt_.y, 2));
    double halfPer = (firstSide + secondSide + thirdSide) / 2;
    return sqrt(halfPer * (halfPer - firstSide) * (halfPer - secondSide) * (halfPer - thirdSide));
}

rectangle_t Triangle::getFrameRect() const
{
    double maxY = std::max(std::max(firstPt_.y, secondPt_.y),
                           thirdPt_.y);
    double maxX = std::max(std::max(firstPt_.x, secondPt_.x),
                           thirdPt_.x);
    double minY = std::min(std::min(firstPt_.y, secondPt_.y),
                           thirdPt_.y);
    double minX = std::min(std::min(firstPt_.x, secondPt_.x),
                           thirdPt_.x);
    return { sqrt(pow(maxX - minX, 2)), sqrt(pow(maxY - minY, 2)),
        { (minX + maxX) / 2, (minY + maxY) / 2 } };
}


void Triangle::move(double dx, double dy)
{
    firstPt_ = { firstPt_.x + dx,
        firstPt_.y+ dy };
    secondPt_ = { secondPt_.x + dx,
        secondPt_.y + dy };
    thirdPt_ = { thirdPt_.x + dx,
        thirdPt_.y + dy };
}

void Triangle::move(const point_t &p)
{
    point_t pos = { (firstPt_.x + secondPt_.x + thirdPt_.x) / 3,
        (firstPt_.y + secondPt_.y + thirdPt_.y) / 3 };
    firstPt_.x += p.x - pos.x;
    firstPt_.y += p.y - pos.y;
    secondPt_.x += p.x - pos.x;
    secondPt_.y += p.y - pos.y;
    thirdPt_.x += p.x - pos.x;
    thirdPt_.y += p.y - pos.y;
}

