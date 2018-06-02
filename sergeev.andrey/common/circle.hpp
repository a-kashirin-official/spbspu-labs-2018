#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace sergeev
{
  class Circle : public Shape
  {
    public:
      Circle(const point_t & center, double r);
      virtual double getArea() const override;
      virtual rectangle_t getFrameRect() const override;
      virtual void move(const point_t & point) override;
      virtual void move(double dx, double dy) override;
      virtual void scale(double factor) override;
      virtual void rotate(double angle) override;
    private:
      point_t m_center;
      double m_radius;
  };
}

#endif // CIRCLE_HPP
