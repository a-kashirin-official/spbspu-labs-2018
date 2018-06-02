#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace hvetsckovich
{
  class Triangle :
    public Shape
  {
  public:
    Triangle(const point_t & vertexA, const point_t & vertexB, const point_t & vertexC);
    point_t getVertex(const int index) const;
    point_t getPos() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & pos) override;
    void move(const double dx, const double dy) override;
    void scale(const double factor) override;
    void rotate(const double degrees) override;

  private:
    point_t vertexA_;
    point_t vertexB_;
    point_t vertexC_;
    double angle_;
  };
}

#endif
