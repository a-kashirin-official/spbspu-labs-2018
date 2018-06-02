#ifndef STARIKOV_ANDREY_LABS_CIRCLE_HPP
#define STARIKOV_ANDREY_LABS_CIRCLE_HPP

#include "shape.hpp"

namespace starikov
{
  class Circle:public Shape
  {
  public:
    Circle(const double &radius, const point_t centre);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t &centre) noexcept override;
    void move(const double offsetAxisX, const double offsetAxisY) override;
    void scale(const double ratio) override;
    void rotate(const double angleDeg) override;
  private:
    double radius_, angleDeg_;
    point_t centre_;
    point_t constCentre_;
  };
}

#endif //STARIKOV_ANDREY_LABS_CIRCLE_HPP
