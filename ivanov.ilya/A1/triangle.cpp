#include "triangle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

Triangle::Triangle(const point_t & value_A, const point_t & value_B, const point_t & value_C) :
pos_({ (value_A.x + value_B.x + value_C.x) / 3 , (value_A.y + value_B.y + value_C.y) / 3 }),
A_vershina_(value_A),
B_vershina_(value_B),
C_vershina_(value_C)
{
    if (getArea() == 0)
    {
        throw std::invalid_argument("vershina_ are the same, enter different ones");
    }
}

void Triangle::show() const
{
    std::cout << "Object of triangle:\n";
    std::cout << "Centre: {" << pos_.x << "," << pos_.y << "}\n";
    std::cout << "vershina_ A: {" << A_vershina_.x << "," << A_vershina_.y << "}\n";
    std::cout << "vershina_ B: {" << B_vershina_.x << "," << B_vershina_.y << "}\n";
    std::cout << "vershina_ C: {" << C_vershina_.x << "," << C_vershina_.y << "}\n";
}

void Triangle::setPoints(const point_t & value_A, const point_t & value_B, const point_t & value_C)
{
    A_vershina_ = value_A;
    B_vershina_ = value_B;
    C_vershina_ = value_C;
}
double Triangle::getMin(const double & value_A, const double & value_B, const double & value_C)
{
    double min = value_A;
    if (value_B < min)
    {
        min = value_B;
    }
    if (value_C < min)
    {
        min = value_C;
    }
    return min;
}
double Triangle::getMax(const double & value_A, const double & value_B, const double & value_C)
{
    double max = value_A;
    if (value_B > max)
    {
        max = value_B;
    }
    if (value_C > max)
    {
        max = value_C;
    }
    return max;
}
double Triangle::getArea() const
{
    return ((std::abs(((A_vershina_.x - C_vershina_.x) * (B_vershina_.y - C_vershina_.y)) - ((A_vershina_.y - C_vershina_.y) * (B_vershina_.x - C_vershina_.x))) / 2));
}
rectangle_t Triangle::getFrameRect() const
{
    double max_x = getMax(A_vershina_.x, B_vershina_.x, C_vershina_.x);
    double min_x = getMin(A_vershina_.x, B_vershina_.x, C_vershina_.x);
    double max_y = getMax(A_vershina_.y, B_vershina_.y, C_vershina_.y);
    double min_y = getMin(A_vershina_.y, B_vershina_.y, C_vershina_.y);
    return {pos_, max_x - min_x, max_y - min_y };
}
void Triangle::move(const point_t &point)
{
    A_vershina_.x += point.x - pos_.x;
    B_vershina_.x += point.x - pos_.x;
    C_vershina_.x += point.x - pos_.x;
    A_vershina_.y += point.y - pos_.y;
    B_vershina_.y += point.y - pos_.y;
    C_vershina_.y += point.y - pos_.y;
    pos_ = point;
}
void Triangle::move(double dx, double dy)
{
    pos_.x += dx;
    A_vershina_.x += dx;
    B_vershina_.x += dx;
    C_vershina_.x += dx;
    pos_.y += dy;
    A_vershina_.y += dy;
    B_vershina_.y += dy;
    C_vershina_.y += dy;
}
