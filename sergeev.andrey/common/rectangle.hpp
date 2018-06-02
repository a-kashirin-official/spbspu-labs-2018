#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace sergeev
{
  class Rectangle : public Shape
  {
    public:
      Rectangle(const rectangle_t & rect_init, double angle = 0);
      virtual double getArea() const override;
      virtual rectangle_t getFrameRect() const override;
      virtual void move(const point_t & point) override;
      virtual void move(double dx, double dy) override;
      virtual void scale(double factor) override;
      virtual void rotate(double angle) override;
    private:
      rectangle_t m_rect;
      double angle_;
  };
}

#endif // RECTANGLE_HPP
