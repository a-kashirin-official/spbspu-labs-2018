#ifndef A1_SHAPE_HPP_ZHD
#define A1_SHAPE_HPP_ZHD

#include "base-types.hpp"

namespace zhigalin
{
  class Shape
  {
    public:
      virtual ~Shape() = default;
      virtual double getArea() const = 0;
      virtual rectangle_t getFrameRect() const = 0;
      virtual void move(const point_t & pos)  = 0;
      virtual void move(const double dx, const double dy) = 0;
      virtual void scale(const double coeff) = 0;

    protected:
      point_t pos_;
      Shape(const point_t & pos)
      {
        pos_ = pos;
      }
  };
} //zhigalin

#endif //A1_SHAPE_HPP_ZHD
