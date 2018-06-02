#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
namespace gessen
{
  class Rectangle: public Shape
  {
    public:
      Rectangle(const point_t & angle, const double width, const double height);
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(const double dx, const double dy) override;
      void move(const point_t & newPoint) override;
      void scale(const double dk) override;
      void rotate (const double angleRotate) override;
      void printShapeName() const override;
    private:
      point_t shapeAnglePos_[4];
      double width_;
      double height_;
  };
}
#endif

