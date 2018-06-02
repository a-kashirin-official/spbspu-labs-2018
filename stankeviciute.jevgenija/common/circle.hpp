#ifndef CIRCLE_HPP_INCLUDED
#define CIRCLE_HPP_INCLUDED
#include "shape.hpp"

namespace stankeviciute
{
  class Circle:
    public Shape
  {
  public:
    Circle(const point_t &pos, double radius);
    friend bool stankeviciute::operator==(const Circle &, const Circle &);
    double getRadius() const;
    std::string getName() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void printFeatures() const override;
    void move(double dx, double dy) override;
    void move(const point_t &pos) override;
    void scale(double k) override;
    void rotate(double /*angle*/) override {};

  private:
    point_t pos_;
    double radius_;
  };

  bool operator==(const Circle &, const Circle &);
}

#endif
