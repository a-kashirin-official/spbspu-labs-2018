#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace styagov
{
  class Circle:
    public Shape
  {
  public:
    Circle(const styagov::point_t & pos, double radius);
    double getRadius() const noexcept;
    styagov::point_t getPos() const noexcept override;
    double getArea() const noexcept override;
    styagov::rectangle_t getFrameRect() const noexcept override;
    void move(const styagov::point_t & pos) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double ratio) override;
    void rotate(const double alpha /*in degrees*/) noexcept override;

  private:
    styagov::point_t pos_;
    double radius_;
    double angle_;
  };
}

#endif //CIRCLE_HPP
