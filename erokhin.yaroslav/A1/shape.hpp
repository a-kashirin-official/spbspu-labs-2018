//
// Created by Yaroslav on 24.03.2018.
//

#ifndef LABA1_SHAPE_HPP
#define LABA1_SHAPE_HPP
#include "base-types.hpp"

class Shape
{
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const double dx,const double dy) = 0;
    virtual void move(const point_t &p) = 0;
};
#endif //LABA1_SHAPE_HPP
