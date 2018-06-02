#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace styagov
{
  class Rectangle:
    public Shape
  {
  public:
    Rectangle(const styagov::point_t & pos, const double width, const double height);
    double getWidth() const noexcept;
    double getHeight() const noexcept;
    void setWidth(const double width);
    void setHeight(const double height);
    double getArea() const noexcept override;
    styagov::point_t getPos() const noexcept override;
    styagov::rectangle_t getFrameRect() const noexcept override;
    void move(const styagov::point_t & pos) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double ratio) override;
    void rotate(const double alpha /*in degrees*/) noexcept override;

  private:
    styagov::point_t pos_;
    double width_;
    double height_;
    double angle_;
  };
}

#endif //RECTANGLE_HPP
