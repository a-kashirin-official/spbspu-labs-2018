#ifndef CIRCLE_HPP_INCLUDED
#define CIRCLE_HPP_INCLUDED
#include "shape.hpp"

namespace solovev {
  class Circle:
    public Shape
  {
    public:
      Circle(double rad, point_t pos);
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move (double dx, double dy) override;
      void move (point_t pos) override;
      void scale (double factor) override;
    private:
      double rad_;
      point_t center_;
  };
}

#endif


