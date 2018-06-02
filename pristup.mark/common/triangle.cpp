#include <cmath>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <assert.h>

#include "triangle.hpp"

pristup::Triangle::Triangle(const point_t & firstPt, const point_t & secondPt, const point_t & thirdPt) :
  firstPt_(firstPt),
  secondPt_(secondPt),
  thirdPt_(thirdPt)
{
    if (getArea() <= 0)
    {
        throw std::invalid_argument("it is not right triangle parameters");
    }
}

double pristup::Triangle::getArea() const noexcept
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

pristup::rectangle_t pristup::Triangle::getFrameRect() const noexcept
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

void pristup::Triangle::move(const point_t &p) noexcept
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

void pristup::Triangle::move(double dx, double dy) noexcept
{
    firstPt_ = { firstPt_.x + dx,
        firstPt_.y+ dy };
    secondPt_ = { secondPt_.x + dx,
        secondPt_.y + dy };
    thirdPt_ = { thirdPt_.x + dx,
        thirdPt_.y + dy };
}

void pristup::Triangle::scale(double k)
{
    if (k <= 0)
    {
        throw std::invalid_argument("Invalid scaling coefficient");
    }
    point_t pos = getFrameRect().pos;
    firstPt_ = { (firstPt_.x - pos.x) * k + pos.x,
        (firstPt_.y - pos.y) * k + pos.y };
    secondPt_ = { (secondPt_.x - pos.x) * k + pos.x,
        (secondPt_.y - pos.y) * k + pos.y };
    thirdPt_ = { (thirdPt_.x - pos.x) * k + pos.x,
        (thirdPt_.y - pos.y) * k + pos.y };
}

