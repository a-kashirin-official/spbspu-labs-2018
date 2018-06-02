#include "shape.hpp"

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

namespace aleksovski
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(double width, double height, const point_t & point);
    double getWidth() const;
    double getHeight() const;
    point_t getCentre() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t & p) override;
    void scale(double k) override;

  private:
    double m_width;
    double m_height;
    point_t m_centre;
    rectangle_t rect_;
  };
}

#endif 
