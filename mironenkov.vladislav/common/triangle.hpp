#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace mironenkov
{
  class Triangle:public Shape
  {
    private:
      point_t a_, b_, c_;
    
    public:
      Triangle(const point_t & a, const point_t & b, const point_t & c);
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(const point_t & pos) override;
      void move(const double dx, const double dy) override;
      void scale(const double coeff) override;
  };
}

#endif //TRIANGLE_HPP
