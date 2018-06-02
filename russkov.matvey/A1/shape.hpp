//
// Created by russk on 13.03.2018.
//

#ifndef A1_SHAPE_HPP
#define A1_SHAPE_HPP

#include "base-types.hpp"

class Shape
{
public:
  virtual ~ Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t &point) = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void scale(const double ratio) = 0;
};

#endif //A1_SHAPE_HPP
