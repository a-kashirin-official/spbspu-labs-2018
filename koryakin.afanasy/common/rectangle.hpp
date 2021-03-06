#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"
#include "base-types.hpp"

namespace koryakin
{
  class Rectangle : public Shape
  {
    public:
      Rectangle(const point_t &center, const double width, const double height);
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(const double dx, const double dy) override;
      void move(const point_t &p) override;
      void scale(const double factor) override;
    private:
      rectangle_t rectangle_;
  };
}  //koryakin 13534/6

#endif
