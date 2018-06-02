#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"

namespace zhigalin
{
  class Circle:
    public Shape
  {
    public:
      Circle(const point_t & pos, const double radius);
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(const point_t & pos) override;
      void move(const double dx, const double dy) override;
      void scale(const double coeff) override; 

    private:
      double radius_;
  };
} //zhigalin

#endif //A1_CIRCLE_HPP
