#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace vlasov
{
  class Circle: public Shape
  {
  public:
    Circle(const double r,const point_t &pos);
    double getArea() const;
    rectangle_t getFrameRect() const;
    void move(const point_t &poss);
    void move(const double xOffset, const double yOffset);
    void scale(double coef_);
  private:
    double radius_;
    point_t center_;
  };
}

#endif //VLASOV_DMITRY_LABS_CIRCLE_HPP
