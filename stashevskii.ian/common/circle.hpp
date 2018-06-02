#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace stashevskii
{
  class Circle : public Shape
  {
  public:
    Circle(const double radius, const point_t& point);
    rectangle_t getFrameRect() const override;
    double getArea() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t &point) override;
    void scale(const double k) override;
    void printf() const;    
    point_t getPosition() const  override;
    void rotate(const double angle);
    
  private:
    double angle_;
    double radius_;
    point_t pos;    
  };
}
#endif
