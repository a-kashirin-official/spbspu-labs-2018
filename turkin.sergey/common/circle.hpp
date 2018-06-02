#ifndef A3_CIRCLE_HPP
#define A3_CIRCLE_HPP

#include "shape.hpp"
namespace turkin
{
  class Circle : public turkin::Shape
  {
  public:
    Circle(double r, const point_t &pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &pos) override;
    void move(double Ox, double Oy) override;
    void printInfo() override;
    void scale(double k) override;
    void rotate(double angle) override;
    point_t getCenter() const override ;

  private:
    double radius_;
    point_t center_;

  };
}

#endif
