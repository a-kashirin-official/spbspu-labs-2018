#ifndef STARIKOV_ANDREY_LABS_RECTANGLE_HPP
#define STARIKOV_ANDREY_LABS_RECTANGLE_HPP

#include "shape.hpp"

namespace starikov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const rectangle_t modelRect);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t &centre) noexcept override;
    void move(const double offsetAxisX, const double offsetAxisY) override;
    void scale(const double ratio) override;
    void rotate(const double angle) override;
  private:
    rectangle_t modelRect_, constModelRect_;
    double angleDeg_;
  };
}

#endif //STARIKOV_ANDREY_LABS_RECTANGLE_HPP
