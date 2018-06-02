#ifndef STARIKOV_ANDREY_LABS_SHAPE_HPP
#define STARIKOV_ANDREY_LABS_SHAPE_HPP

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t &centre) = 0;
  virtual void move(const double offsetAxisX, const double offsetAxisY) = 0;
};

#endif //STARIKOV_ANDREY_LABS_SHAPE_HPP
