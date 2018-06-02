#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace gusev
{
  class Rectangle : public Shape
  {
    public:
      Rectangle(const double width, const double height, const point_t &pos);
      rectangle_t getFrameRect() const override;
      double getArea() const override;
      point_t getCenter() const override;
      void move(const point_t &point) override;
      void move(const double dx, const double dy) override;
      void scale(const double coef) override;

    private:
      double width_;
      double height_;
      point_t center_;
  };
}
#endif
