#include <cmath>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <assert.h>

#include "triangle.hpp"

Triangle::Triangle(const point_t &fPt, const point_t &sPt, const point_t &tPt) :
fPt_(fPt),
sPt_(sPt),
tPt_(tPt)
{
    assert (getArea() >= 0);
}

double Triangle::getArea() const
{
    double fSide = sqrt(pow(sPt_.x - fPt_.x, 2)
                            + pow(sPt_.y - fPt_.y, 2));
    double sSide = sqrt(pow(tPt_.x - fPt_.x, 2)
                             + pow(tPt_.y - fPt_.y, 2));
    double tSide = sqrt(pow(tPt_.x - sPt_.x, 2)
                            + pow(tPt_.y - sPt_.y, 2));
    double halfPer = (fSide + sSide + tSide) / 2;
    return sqrt(halfPer * (halfPer - fSide) * (halfPer - sSide) * (halfPer - tSide));
}

rectangle_t Triangle::getFrameRect() const
{
    double maxY = std::max(std::max(fPt_.y, sPt_.y),
                           tPt_.y);
    double maxX = std::max(std::max(fPt_.x, sPt_.x),
                           tPt_.x);
    double minY = std::min(std::min(fPt_.y, sPt_.y),
                           tPt_.y);
    double minX = std::min(std::min(fPt_.x, sPt_.x),
                           tPt_.x);
    return { sqrt(pow(maxX - minX, 2)), sqrt(pow(maxY - minY, 2)),
        { (minX + maxX) / 2, (minY + maxY) / 2 } };
}


void Triangle::move(double dx, double dy)
{
    fPt_ = { fPt_.x + dx,
        fPt_.y+ dy };
    sPt_ = { sPt_.x + dx,
        sPt_.y + dy };
    tPt_ = { tPt_.x + dx,
        tPt_.y + dy };
}

void Triangle::move(const point_t &p)
{
    point_t pos = { (fPt_.x + sPt_.x + tPt_.x) / 3,
        (fPt_.y + sPt_.y + tPt_.y) / 3 };
    fPt_.x += p.x - pos.x;
    fPt_.y += p.y - pos.y;
    sPt_.x += p.x - pos.x;
    sPt_.y += p.y - pos.y;
    tPt_.x += p.x - pos.x;
    tPt_.y += p.y - pos.y;
}

void Triangle::print() const
{
    std::cout << "area: " << getArea() << std::endl;
    std::cout << "width of frame: " << getFrameRect().width << std::endl;
    std::cout << "height of frame: " << getFrameRect().height << std::endl;
    std::cout << "center point: (" << getFrameRect().pos.x
    << ";" << getFrameRect().pos.y << ")" << std::endl;
}
