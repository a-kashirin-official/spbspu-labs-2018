#ifndef A1_TRIANGLE_HPP
#define A1_TRIANGLE_HPP

#include "shape.hpp"

namespace zhigalin
{
  class Triangle:
    public Shape
  {
    public:
      Triangle(const point_t & point_a, const point_t & point_b, const point_t & point_c);
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(const point_t & pos) override;
      void move(const double dx, const double dy) override;
      void scale(const double coeff) override;

    private:
      point_t point_a_, point_b_, point_c_;
  };
} //zhigalin

#endif //A1_TRIANGLE_HPP
