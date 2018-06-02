#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace styagov
{
  class Triangle :
    public Shape
  {
  public:
    Triangle(const styagov::point_t & a, const styagov::point_t & b, const styagov::point_t & c) noexcept;
    void setVertexAtIndex(const int index, const styagov::point_t & vertex);
    styagov::point_t getVertexAtIndex(const int index) const;
    styagov::point_t getPos() const noexcept override;
    double getArea() const noexcept override;
    styagov::rectangle_t getFrameRect() const noexcept override;
    void move(const styagov::point_t & pos) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double ratio) override;
    void rotate(const double alpha /*in degrees*/) noexcept override;

  private:
    styagov::point_t vertices_[3];
  };
}

#endif
